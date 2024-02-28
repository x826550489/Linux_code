#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>


#include "pool.h"
//程序退出标志
// terminate = 1 进程要退出啦
// terminate = 0 进程不退出  
int terminate = 0;
typedef struct 
{
    char file1[512];
    char file2[512];
}cp_data_t;



pool_t *pool = NULL;

//程序退出标志
// terminate = 1 进程要退出啦
// terminate = 0 进程不退出  
int terminate = 0;

void usage(void)
{
    printf("这个程序实现两个目录的拷贝。\n");
    printf("需要带两个参数: 第一个参数为  源目录  第二个参数为  目标目录\n");
    printf("如:");
    printf("cp /home/china   /mnt\n");
}



//信号处理函数
void sig_handler(int sig)
{
    switch (sig)
    {
    case SIGINT:   //用户在终端按下 Ctrl+C 时发送的
    case SIGTERM:   //通过发送 kill 命令或其他方式来终止程序时发送
        terminate = 1;
        pool->terminate = 1;
        break;
    
    default:
        break;
    }
}




void* cp_file(void* data)
{
    cp_data_t * file = (void*) (data);

    // pthread_detach( pthread_self() );

    printf("正在拷贝普通文件  %s --> %s\n", file->file1, file->file2);

    int fd1 = open(file->file1, O_RDONLY);
    int fd2 = open(file->file2, O_WRONLY | O_TRUNC | O_CREAT, 0666);
    if (fd1 == -1 || fd2 == -1)
    {
        //free(file);
        return NULL;
    }

    while (1)
    {
        char buf[1024];
        int r = read(fd1, buf, 1024);
        if (r == 0)
        {
            break;
        }
        else if (r > 0)
        {
            write(fd2, buf,r);
        }
    }

    close(fd1);
    close(fd2);
    //free(file);
    return NULL;
}



//拷贝整个目录
void cp_dir(const char* dir1, const char* dir2)
{
    int ret;
    DIR* dir = opendir(dir1);
    if (dir == NULL)
    {
        perror("opendir error");
        return ;
    }

    printf("正在拷贝目录:  %s  ---> %s\n", dir1, dir2);


    struct  dirent *dirp;

    while (dirp = readdir(dir))
    {
        char filename[512];
        sprintf(filename, "%s/%s", dir1, dirp->d_name);

        if (strcmp(dirp->d_name, ".") == 0 || 
            strcmp(dirp->d_name,"..") == 0)
        {
            continue;
        }

        struct stat st;

        ret = stat(filename, &st); //获取文件的状态
        if (ret == -1)
        {
            perror("stat error");
            continue;
        }


        char new_file[512];
        sprintf(new_file, "%s/%s", dir2, dirp->d_name);
        
        
        if (S_ISDIR(st.st_mode) ) //这是一子目录
        {
          
            mkdir(new_file, 0776);

            cp_dir(filename, new_file); //递归拷贝子目录.
        }
        else if (S_ISREG(st.st_mode)) //这是一个普通文件
        {
            cp_data_t* p = (cp_data_t*) malloc(sizeof(cp_data_t));
            sprintf(p->file1, "%s", filename);
            sprintf(p->file2, "%s", new_file);

            // pthread_t tid;
            // int ret = pthread_create(&tid, NULL, cp_file, (void*)p);
            // if (ret == -1)
            // {
            //     perror("failed to pthread_create");

            // }

            if (add_task(pool, cp_file, p) == 0)
            {
                printf("failed to add_task\n");
                //...
            }
        }
    }   
}


// cp  dir1  dir2
int main(int argc, char *argv[])
{
    // if (argc != 3)
    // {
    //     usage();
    //     exit(0);
    // }

    signal(SIGINT, sig_handler);     //屏蔽从键盘上收到的中断信号，按下ctrl+c就会产生信号
    /*程序结束(terminate)信号，
    与SIGKILL不同的是该信号可以被阻塞和处理。通常用来要求程序自己正常退出*/
    signal(SIGTERM, sig_handler);  


    pool_t *p = init_pool(1000); //创建一个有20个线程的线程池
    if (p == NULL)
    {
        printf("failed to init_pool");
        return -1;
    }
    pool = p;   



   // cp_dir(argv[1], argv[2]);
   cp_dir("/mnt/linuxshare/Marelli", "/home/sky/Documents/Code/temp");
   p->finished = 1;
   
    wait_pool_over(p);
    printf("\n拷贝完成\n");
    return 0;
}