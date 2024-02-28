#ifndef STRDECODE_H
#define STRDECODE_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
 // 定义链表节点结构
typedef struct Node {
    char original_content[100];
    char replacement_content[100];
    char group[10];
    struct Node* next;
} Node;

extern Node* head;
//extern void str_replace(char *source, const char *oldStr, const char *newStr);
char *str_replace(const char *search, const char *replace, char *subject, int bufsize);
extern void printf_list(struct Node *h);
extern void addNode(char* original, char* replacement,char *group);
extern void str_decode_task(int argc, char *argv[]);
extern void extractMacroIdentifier(const char* macro);

#endif