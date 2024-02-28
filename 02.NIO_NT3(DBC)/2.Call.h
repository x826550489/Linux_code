#ifndef CALL_H
#define CALL_H

#include <string.h>
#include "globel_var.h"


extern void str_replace(char *source, const char *oldStr, const char *newStr);
extern void printf_list(struct Node *h);
extern void addNode(char* original, char* replacement,char *group);


#endif