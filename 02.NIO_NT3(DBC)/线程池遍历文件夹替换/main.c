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
#include "StrDecode.h"
static int num =0;
void sig_handler(int sig);
void* replace_key(void* data);
void RecursiveDirectoryIterator(const char* dir1);
//void str_replace(char *source, const char *oldStr, const char *newStr);

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
#define MAX_LINE_LENGTH 1024
char input_line_replace[MAX_LINE_LENGTH];
char input_lines[5][MAX_LINE_LENGTH];


int main(int argc, char *argv[])
{
    
    //str_decode_task(argc,argv);  //解码字符串，获取数据链表
    //Pool_task();                 //线程池遍历上下文匹配查找替换  

    // FILE *testfile = fopen("/mnt/linuxshare/Marelli/Code/02.NIO_NT3(DBC)/线程池遍历文件夹替换/input.txt","r+");
    // char ptr[1024] = {0};
    // if(-1 == fread(ptr,sizeof(char),800,testfile))
    // {
	// 	perror("fread failed");
	// 	return -1;     
    // }
    // printf("souce  :\n %s\n",ptr);
    // str_replace("ComConf_ComSignal_Day_oZONE_3B2_obodyrr1_9fa7df59_Rx","89890809",ptr,sizeof(ptr));  //50c9eb2a
    // printf("replace:\n %s\n",ptr);
    // fflush(NULL);
    //     // 将文件指针重新定位到文件开头
    // fseek(testfile, 0, SEEK_SET);
    // if(-1 == fwrite(ptr,sizeof(char),800,testfile))
    // {
	// 	perror("fwrite failed");
	// 	return -1; 
    // }
    // fclose(testfile);
    // // char temp[100] = "niudsaijdjsalkd112321";
    // // printf("souce  : %s\n",temp);
    // // str_replace("kd1","666",temp,sizeof(temp)); 
    // // printf("replace: %s\n",temp);

    FILE *testfile = fopen("/mnt/linuxshare/Marelli/Code/02.NIO_NT3(DBC)/线程池遍历文件夹替换/input.txt", "r+");
    if (testfile == NULL) 
    {
        perror("fopen failed");
        return -1;
    }
    
    // 获取文件大小
    fseek(testfile, 0, SEEK_END);
    long fileSize = ftell(testfile);
    rewind(testfile);

    char ptr[fileSize];
    if (fread(ptr, sizeof(char), fileSize, testfile) != fileSize) 
    {
        perror("fread failed");
        return -1;
    }
    ptr[fileSize] = EOF;//'\0'; // 添加字符串结束符
    printf("source:\n%s\n",ptr);
    str_replace("ComConf_ComSignal_Day_oZONE_3B2_obodyrr1_9fa7df59_Rx", "89890809", ptr, sizeof(ptr));
    printf("result:\n%s\n",ptr);
    // 将文件指针重新定位到文件开头并截断文件大小为0
    fseek(testfile, 0, SEEK_SET);
    ftruncate(fileno(testfile), 0);

    if (fwrite(ptr, sizeof(char), fileSize, testfile) != fileSize) 
    {
        perror("fwrite failed");
        return -1;
    }
    fclose(testfile);
}

void Pool_task(void)
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
    
    RecursiveDirectoryIterator("/mnt/linuxshare/Marelli/test");  //M4_Application
    p->finished = 1;
    wait_pool_over(p);
    printf("\n替换完成\n");
    printf("*.c,*.h文件总数:%d\n",num); 
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
        //str_replace(input_lines[lineNumber],head->original_content,head->replacement_content);
        // if(lineNumber == 2)
        // {
        //     //str_replace(input_lines[lineNumber],head->original_content,head->replacement_content);
        //     lineNumber = 0;
        // }
        printf("line:%d",lineNumber);

    }

    fclose(fd);
    return NULL;
}



// void str_replace(char *source, const char *oldStr, const char *newStr) 
// {
//     int len_old = strlen(oldStr); // 获取要被替换的子字符串长度
//     int len_new = strlen(newStr); // 获取要被替换的子字符串长度
    
//     while (strstr(source, oldStr)) { // 判断原始字符串中是否存在需要替换的子字符串
//         char *p;
        
//         p = strstr(source, oldStr); // 查找第一次出现的位置
        
//         memmove(p + len_old, p, sizeof(char)*(strlen(source)-(p-source)+1)); // 将后面部分向前移动
        
//         memcpy(p, newStr, sizeof(char)*len_old); // 复制新字符串到指定位置
//     }
// }

void RecursiveDirectoryIterator(const char* dir1)
{
    int ret;
    DIR* dir = opendir(dir1);
    if (dir == NULL)
    {
        perror("opendir error");
        return ;
    }

    printf("正在打开文件夹:  %s  \n", dir1);

    struct  dirent *dirp;

    while (dirp = readdir(dir))
    {
        char filename[512];
        sprintf(filename, "%s/%s", dir1, dirp->d_name);

        if (strcmp(dirp->d_name, ".") == 0 || 
            strcmp(dirp->d_name,"..") == 0
            )
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
            
            
            if (S_ISDIR(st.st_mode) ) //这是一子目录
            {
                RecursiveDirectoryIterator(filename); //递归进入子目录.
            }
            else if (S_ISREG(st.st_mode)) //这是一个普通文件
            {
                if(strstr(dirp->d_name, ".c") != NULL ||strstr(dirp->d_name, ".h") != NULL)
                {
                    cp_data_t* p = (cp_data_t*) malloc(sizeof(cp_data_t));
                    sprintf(p->file2, "%s", filename);
                    printf("%s",p->file2);
                    fflush(stdout);

                    num++;

                    if (add_task(pool,replace_key,p) == 0)
                    {
                        printf("failed to add_task\n");
                    }
                }
            }
     }  
     
}

