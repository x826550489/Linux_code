#ifndef REPLACE_H
#define REPLACE_H

extern void replace_task(void);
extern void extractMacroIdentifier(const char* macro); 
extern void sig_handler(int sig);
extern void* replace_key(void* data);
extern void RecursiveDirectoryIterator(const char* dir1);
extern void str_replace(char *source, const char *oldStr, const char *newStr);
#endif