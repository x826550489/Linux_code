
#include "2.Call.h"
#include "replace.h"
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

FILE *input_file, *output_file;
char input_line[MAX_LINE_LENGTH];
void clean_buf(void);
Node* head = NULL;
static int ok = 0;

int main(int argc, char *argv[]) 
{

    // 检查命令行参数
    if (argc != 2) 
    {
        printf("用法: %s 输入文件名\n", argv[0]);
        return 1;
    }

    // 打开输入和输出文件
    input_file = fopen(argv[1], "r");
    if (input_file == NULL) 
    {
        printf("错误: 无法打开输入文件 %s\n", argv[1]);
        return 1;
    }
    output_file = fopen("source_output.txt", "w");
    if (output_file == NULL) 
    {
        printf("错误: 无法打开输出文件\n");
        fclose(input_file);
        return 1;
    }

    int lineNumber = 0;   //行数
    // 逐行读取输入文件
    while (fgets(input_line, MAX_LINE_LENGTH, input_file) != NULL) 
    {
        lineNumber++;
        printf("\n**************lineNumber:%d*************\n",lineNumber);
        //清除每行末尾“\n”换行符
        size_t len = strlen(input_line); // 获取行的长度
        if (input_line[len - 1] == '\n') 
        {   // 如果行末有换行符
            input_line[len -1] = '\0'; // 将换行符替换为字符串结束符
            //fseek(input_file, -len, SEEK_CUR); // 将文件指针移动到当前行开头
            fputs(input_line, input_file); // 将修改后的行写回文件
        }

        char* token = strtok((char*)input_line, "/");
        while (token != NULL)
        {
            printf("input_line: %s\n",token);
            extractMacroIdentifier(token); // 对每个分割后的宏定义调用提取标识符函数
            token = strtok(NULL, "/");    
        }    
    }
        printf_list(head);
        fclose(input_file);
        fclose(output_file);
        printf("\n****str decode done!****\n");

    return 0;
}

void clean_buf(void)
{

}

// 定义一个函数，用于提取宏定义中的标识符
void extractMacroIdentifier(const char* macro) 
{
    char macroX[100];
    char identifier[100];
    static char identifier_Group[100];
    char cleanedStrX[100];
    char cleanedStr[2][100];
    int i = 0;
    int j = 0;
    

    strcpy(macroX, macro);

    if(macroX[0] == '?')
    {
        strcpy(identifier_Group,macroX+1);
        printf("*****Macro identifier_Group:%s\n", identifier_Group);
    }
    else
    {
        strcpy(identifier, macroX + 8);

        while (isspace(identifier[i])) 
        {
            i++;
        }
        while((identifier[i] != ' ') && (identifier[i] != '\0'))
        {
            cleanedStrX[j] = identifier[i];
            j++;
            i++;
        }
        cleanedStrX[j] = '\0';

        // cleanedStr[ok] = cleanedStrX;
        // 将字符串复制到新的内存空间
        strcpy(cleanedStr[ok] ,cleanedStrX); 
        ok++;
        printf("*****Macro Identifier:%s\n", cleanedStrX);
    }
    if(ok == 1)
    {
        addNode(cleanedStr[0],cleanedStr[1],identifier_Group);
        ok = 0;
    }
}

void printf_list(struct Node *h)
{
	while(h)
	{
		printf("\noriginal:%s ",h->original_content);
        printf("\nreplacement:%s ",h->replacement_content);
        printf("\n group:%s ",h->group);
		h=h->next;
	}
	putchar('\n');
}


void addNode(char *original, char* replacement,char *group)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->original_content,original);
    strcpy(newNode->replacement_content,replacement);
    strcpy(newNode->group,group);
    newNode->next = head;
    head = newNode;
}


