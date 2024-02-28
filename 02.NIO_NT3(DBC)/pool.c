
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include "pool.h"


//线程池中的“消费者线程”对应的线程函数
static void* consumer(void* data)
{
    pool_t *p = (pool_t*)data;

    while (1)
    {

        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); //设置该线程可以取消

        pthread_mutex_lock(&p->m); //P操作 

        //没有任务  且 进程不结束 且 还有任务要添加 ,需要等待“任务的到来”
        while (p->task_len == 0 && p->terminate == 0 && p->finished == 0)
        {   
            /*cond: 等待的那个条件变量
            mutex: 线程互斥锁。为了保护所代表的事件或资源的。
            并且在调用 pthread_cond_wait时，mutex一定要
            是一个 “Lock”状态的。*/
            //pthread_cond_wait(&p->ev, &p->m);

            /*首先使用pthread_cond_wait函数等待条件变量的信号。如果超过2秒钟还没有接收到信号，
            就使用pthread_cond_timedwait函数等待2秒钟。这样可以避免线程无限等待的情况，
            保证线程池的销毁过程不会被阻塞太长时间。*/
            struct timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            ts.tv_sec += 2;

            pthread_cond_timedwait(&p->ev, &p->m, &ts);
        }

        // 上面的那个while结束的条件是:
        // 1. 进程要结束啦 p->terminate == 1  or
        // 2. 有任务要去执行啦   p->task_len > 0
        // 3. 没有任务执行，且不会添加新任务。
        if (p->terminate == 1 ||p->finished == 1 && p->task_len == 0)
        {
            pthread_mutex_unlock(&p->m);
            pthread_exit(NULL);    //退出调用线程
        }

        //从“任务链表”中取一个任务下来
        task_t *t = p->head;
        p->head = t->next;
        t->next = NULL;
        p->task_len --;
        if (p->task_len == 0)
        {
            p->last = NULL;
        }
    
    

        pthread_mutex_unlock(&p->m); //V操作

        //执行任务结点的函数 
        //在执行任务时，我们不希望线程被 取消
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
        t->func(t->arg); //执行任务函数
        free(t->arg);
        free(t);


    }


}

/*
    init_pool: 创建并初始化线程池
    @threads: 线程池中线程的数量
    返回值:
        成功 返回线程池结构体的指针
        失败 返回NULL
*/
pool_t* init_pool(int threads)
{
    int ret, i;
    pool_t* pool = (pool_t*) malloc(sizeof(pool_t));   //创建一个名字为pool，类型的pool_t*,的线程池头节点，并分配空间

    pool->head = NULL;
    pool->last = NULL;
    pool->task_len = 0;
    pool->terminate = 0;       


    pthread_mutex_init(&pool->m, NULL);//初始化“线程互斥锁”
    pthread_cond_init(&pool->ev, NULL);//初始化“线程条件变量”

    //pool->thread_num = threads;
    pool->tids = (pthread_t*) malloc(sizeof(pthread_t) * threads);  

    for (i = 0; i < threads; i++)
    {
        /* thread: 指向的空间，用来保存新创建的线程的id的  
                attr: 指定线程的线程属性结构体。 一般为NULL，表示采用默认的属性。 
                start_routine:  指向线程对应的线程函数。线程的任务就是去执行    
                                这个start_routine指向的函数
                arg: void*, 指向的数据，将作为线程函数的参数。
            返回值:
                成功返回0
                失败返回-1,同时errno被设置。*/
        ret = pthread_create( &pool->tids[i], NULL, consumer, (void*)pool);
        if (ret == -1)
        {
            perror("pthread_creat error");
            break;
        }
    }
    pool->thread_num = i; //保存实际创建成功的线程数量
    if (pool->thread_num == 0)
    {
        free(pool->tids);
        free(pool);

        printf("I'm sorry, 线程池创建失败!\n");
        return NULL;
    }
    return pool;
}


/*
    add_task: 往“线程池”链表中添加一个“任务”
    @pool:线程池，指针。
    @func: 该“任务”对应的函数
    @arg: 函数的参数
    返回值:
        成功返回1
        失败返回0
*/
int add_task(pool_t* pool, void*(*func)(void*), void*arg)
{
    if (pool == NULL || func == NULL)
    {
        return 0;
    }

    //1. 构建一个“任务结点”
    task_t *p = (task_t*) malloc(sizeof(task_t));
    if (p == NULL)
    {
        perror("malloc task_t error:");
        return 0;
    }
    p->func = func;
    p->arg = arg;
    p->next = NULL;

    //2. 把“任务结点”加入到  线程池的任务链表中去
    pthread_mutex_lock(&pool->m);
    if (pool->head == NULL)
    {
        pool->head = p;
        pool->last = p;
    }
    else 
    {
        pool->last->next = p;
        pool->last = p;
    }
    pool->task_len++;

    pthread_mutex_unlock(&pool->m);   //互斥锁v操作

    pthread_cond_signal(&pool->ev); //唤醒等待的线程

    return 1;

}
//销毁线程池
void destroy_pool(pool_t* p)
{   
    if (p == NULL)
    {
        return ;
    }

    pthread_mutex_lock(&p->m);

    p->terminate = 1;

    pthread_cond_broadcast(&p->ev);

    pthread_mutex_unlock(&p->m);


    for (int i = 0; i < p->thread_num; i++)
    {
        pthread_join(p->tids[i], NULL);
    }

    free(p->tids);

    task_t *t;
    while (t = p->head)
    {
        p->head = t->next;
        t->next = NULL;

        free(t);
    }

    free(p);
}

//等待“线程池”中的线程全部结束
void wait_pool_over(pool_t* p)
{
    if (p == NULL || p->thread_num == 0)
    {
        return ;
    }

    
    for (int i = 0; i < p->thread_num; i++)
    {
        pthread_join(p->tids[i], NULL);
    }
}