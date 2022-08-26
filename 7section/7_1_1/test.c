#define PROJ_3

// test.c
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int g_var_a = 0;        //全局已初始化
char g_var_b;           //bbs(未初始化全局)

int main()
{
        int* var_a;                             //栈
        int* var_b;
        int* p_str2; 
        char var_str[] = "string1";             //已初始化区？
        char *p_str1;                //堆栈
        char *p_str3 = "string2";


#ifdef PROJ_1

        p_str1 = (char*)malloc(sizeof(char));
        memset(p_str1, 0, sizeof(char));
        p_str2 = (int*)malloc(sizeof(int));   //产生一个ptr返回值
        memset(p_str2, 0, sizeof(int));

#endif

#ifdef PROJ_3

        p_str1 = (char*)calloc(1, sizeof(char));
        p_str2 = (int*)calloc(1, sizeof(int));

        p_str1 = (char*)realloc(p_str1, sizeof(int));
#endif

        var_a = (int*)p_str1;
        printf("%p\n", &var_a);
        var_b = (int*)p_str2;
        printf("%p\n", &var_b);
        free(p_str1);
        free(p_str2); 

        return 0;
}

//test2
