#include <stddef.h> // For size_t
#include <stdio.h> // for printf, stderr
#include "stringlib.h"



size_t matt_strlen(const char *str){
     // Defensive programming check for NULL
     if(str == NULL){
        fprintf(stderr,"matt_strlen: NULL string pointer\n");
        return 0; // Length of nothing is 0
    }
    const char *p = str;
    while (*p != '\0'){
        p++; //iterate through string
    }
    return (size_t)(p - str); // gives difference between the final pointer and the start pointer. I.e - the length of the string
}


int matt_strcmp(const char *s1, const char *s2){
     // Defensive programming check for NULL
    if (s1 == NULL || s2 == NULL){
        if (s1 == NULL && s2 == NULL) return 0;
        return (s1 == NULL) ? -1 : 1;
    }
    const char *p1 = s1;
    const char *p2 = s2;
    while (*p1 && (*p1 == *p2)){
        p1++;
        p2++;
    }
    return (int)((unsigned char)*p1 - (unsigned char)*p2);
}


char *matt_strcpy(char *dest, const char *src){
    // Defensive programming check
    if (dest == NULL || src == NULL){
        fprintf(stderr,"matt_strcpy error: NULL source or destination\n");
        return NULL;
    }

    // We need to create temp variahles to allow for the information to be copied from one string to the other
    char *d = dest;
    const char *s = src;

    // We need to iterate through each character in src and make sure it ends up in dest to "copy the string"
    while (*s != '\0'){
        *d = *s;
        d++;
        s++;
    }
    *d = '\0'; // NULL terminate the destination string once, after loop.
    // return destination pointer as finished copied string
    return dest;
}

char *matt_strcat(char *dest, const char *src){
    // Defensive programming check
    if (dest == NULL || src == NULL){
        fprintf(stderr,"matt_strcpy error: NULL source or destination\n");
        return NULL;
    }
    // We need to create temp variables to allow for the information to be copied from one string to the other
    char *d = dest;
    const char *s = src;
    // We need to iterate find the end of the destination string
    while (*d != '\0'){
        d++;
    }
    // copy source to end of destination string
    while (*s != '\0'){
        *d = *s;
        d++;
        s++;
    }
    //Null terminate final string
    *d = '\0';
    // return destination pointer as finished cocncatenated string
    return dest;
}
