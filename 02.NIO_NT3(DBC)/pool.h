
#ifndef __POOL_H__
#define __POOL_H__

#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
//"任务结点"
typedef struct task_node
{
    void* (*func)(void*);  //函数指针，指向要执行的那个函数

    void* arg; //函数的参数
    // int arg_len; //参数的长度

    struct task_node *next ; //下一个“任务”

} task_t;


//“线程池”
//“头结点”
typedef struct 
{
    task_t *head; //指向“任务链表”的第一个任务结点
    task_t *last; //指向“任务链表”的最后一个任务结点
    int task_len; //任务个数。
    /*// 进程结束的标志
    // terminate = 1 结束
    // terminate = 0 不结束*/
    int terminate; 

    // "线程池"这个数据结构，是多个线程都要访问
    // 而且要互斥访问，所以这个数据结构是需要被保护的
    // "临界区"： 所以对这个数据结构(“带头结点的链表”)进行操作的代码
    //          区域就都是“临界区”
    pthread_mutex_t m; //用来保护整个“带头结点的链表”

    pthread_cond_t ev; // "有任务到来 的事件"


    int thread_num; //线程池中线程的数量
    pthread_t *tids;  //"动态数组" 保存每一个线程的线程id的!!!
                //tids = () malloc( sizeof(pthread_t) * thread_num)

    int finished; //标记  是否所有任务都已经添加完毕!!!
                // finished = 1  所有任务都添加完毕了
                // finished = 0  后面还有任务添加
}pool_t;


/*
    init_pool: 创建并初始化线程池
    @threads: 线程池中线程的数量
    返回值:
        成功 返回线程池结构体的指针
        失败 返回NULL
*/
pool_t*
init_pool(int threads);


/*
    add_task: 往“线程池”链表中添加一个“任务”
    @pool:线程池，指针。
    @func: 该“任务”对应的函数
    @arg: 函数的参数
    返回值:
        成功返回1
        失败返回0
*/
int add_task(pool_t* pool, void*(*func)(void*), void*arg);

//销毁线程池
void destroy_pool(pool_t* p);


//等待“线程池”中的线程全部结束
void wait_pool_over(pool_t* p);
#endif 




