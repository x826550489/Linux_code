#ifndef GLOBEL_VAR_H
#define GLOBEL_VAR_H

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
#endif