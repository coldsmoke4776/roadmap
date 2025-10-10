#ifndef STRINGLIB_H
#define STRINGLIB_H
#include <stddef.h> // For size_t

size_t matt_strlen(const char *str);
int matt_strcmp(const char *s1, const char *s2);
char matt_strcpy(char *dest, const char *src);
char matt_strcat(char *dest, const char *src);








#endif