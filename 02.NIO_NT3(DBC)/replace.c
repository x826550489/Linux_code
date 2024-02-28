#include "replace.h"
#include "globel_var.h"
#include "pool.h"

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
#include <stdio.h>



#define MAX_LINE_LENGTH 1024
char input_line_replace[MAX_LINE_LENGTH];
char input_lines[5][MAX_LINE_LENGTH];
pool_t *pool = NULL;
//FILE *input_file, *output_file;

//pool_t *pool = NULL;
int terminate = 0;

typedef struct 
{
    char file1[512];
    char file2[512];
}cp_data_t;

void replace_task(void)
{
    
    signal(SIGINT, sig_handler);     //屏蔽从键盘上收到的中断信号，按下ctrl+c就会产生信号
    /*程序结束(terminate)信号，
    与SIGKILL不同的是该信号可以被阻塞和处理。通常用来要求程序自己正常退出*/
    signal(SIGTERM, sig_handler); 

    pool_t *p = init_pool(10); //创建一个有20个线程的线程池
    if (p == NULL)
    {
        printf("failed to init_pool");
        return ;
    }
    pool = p;   



    RecursiveDirectoryIterator("/mnt/linuxshare/Marelli");
    p->finished = 1;
   
     //wait_pool_over(p);
    printf("\n替换完成\n");
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




void* replace_key(void* data)
{
    cp_data_t * file = (void*) (data);

    FILE *fd = fopen(file->file2, "r+");
    if (fd == NULL) 
    {
        printf("错误: 无法打开输出文件\n");
        fclose(fd);
        return NULL;
    }
    int lineNumber = 0;   //行数
    while (fgets(input_line_replace, MAX_LINE_LENGTH, fd) != NULL) 
    {
        strcpy(input_lines[lineNumber],input_line_replace);
        //input_lines[lineNumber][100] = input_line_replace;
        lineNumber++;
        if(lineNumber == 2)
        {
            str_replace(input_lines[lineNumber],head->original_content,head->replacement_content);
            
            lineNumber = 0;
        }

    }

    fclose(fd);
    return NULL;
}

void RecursiveDirectoryIterator(const char* dir1)
{
    int ret;
    DIR* dir = opendir("/mnt/linuxshare/Marelli");
    if (dir == NULL)
    {
        perror("opendir error");
        return ;
    }

    //printf("正在拷贝目录:  %s  ---> %s\n", dir1, dir2);


    struct  dirent *dirp;

    // while (dirp = readdir(dir))
    // {
    //     char filename[512];
    //     sprintf(filename, "%s/%s", dir1, dirp->d_name);

    //     if (strcmp(dirp->d_name, ".") == 0 || 
    //         strcmp(dirp->d_name,"..") == 0)
    //     {
    //         continue;
    //     }

    //     if (strstr(dirp->d_name, ".c") != NULL || strstr(dirp->d_name, ".h") != NULL)
    //     {
    //         struct stat st;

    //         ret = stat(filename, &st); //获取文件的状态
    //         if (ret == -1)
    //         {
    //             perror("stat error");
    //             continue;
    //         }
            
            
    //         if (S_ISDIR(st.st_mode) ) //这是一子目录
    //         {
    //             RecursiveDirectoryIterator(filename); //递归进入子目录.
    //         }
    //         else if (S_ISREG(st.st_mode)) //这是一个普通文件
    //         {
    //             cp_data_t* p = (cp_data_t*) malloc(sizeof(cp_data_t));
    //             sprintf(p->file2, "%s", filename);

    //             if (add_task(pool,replace_key,p) == 0)
    //             {
    //                 printf("failed to add_task\n");
    //             }
    //         }
    //     }
    //     else
    //     {
    //         /*do nothing*/
    //     }
     //}   
}

// void str_replace(char *source, const char *oldStr, const char *newStr) 
// {
//     int len = strlen(oldStr);
    
//     while (1) {
//         source = strstr(source, oldStr); // 查找第一次出现的位置
        
//         if (!source) break; // 如果没有找到则退出循环
        
//         memmove(source + len, source, strlen(source)); // 将后面的内容向前移动
//         memcpy(source, newStr, len); // 复制新的字符串到指定位置
//     }
// }