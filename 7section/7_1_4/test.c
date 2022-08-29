// #define TEST
// c_memory_test.c
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#ifdef TEST

/*      cannt know the size of pointer point to.        */
// int main()
// {
//         char *p_str1, *p_str2;
//         p_str1 = (char*)malloc(64);
        
//         p_str2 = (char*)calloc(32, sizeof(char));
//         printf("%ld",sizeof(p_str1));
//         free(p_str1);
//         free(p_str2);
//         return 0;
// }

/*      What happens when the function returns -1        */
// int main()
// {
//         return -1;
// }

#else
int main()
{
        char *p_str1, *p_str2;

        p_str1 = (char*)malloc(32);           //Create a memory area  size 32                //
        if (NULL==p_str1) {
                printf("Alloc p_str1 memory ERROR!\n");    //avoid overflow
                return -1;
        }
        memset(p_str1, 0, sizeof(char));        //presonal add: clear the data of p_str1

        p_str2 = (char*)calloc(32, sizeof(char));       //an other way to create a memory size 32*(sizeof(char))
        if (NULL==p_str2) {
                printf("Alloc p_str2 memory ERROR!\n");
                free(p_str1);
                return -1;
        }

        strcpy(p_str1, "This is a simple sentence.jjjj");   // parameter 1: a pointer 2: a string
// extern char *strcpy (char *__restrict __dest, const char *__restrict __src)
// __THROW __nonnull ((1, 2));
        strcpy(p_str2, p_str1);

        printf("p_str1 by malloc():\n");
        printf("p_str1 address: 0x%p\n", &p_str1);
        printf("p_str1: %s(%ld chars)\n", p_str1, strlen(p_str1));

        printf("p_str2 by malloc():\n");
        printf("p_str2 address: 0x%p\n", &p_str2);
        printf("p_str2: %s(%ld chars)\n", p_str2, strlen(p_str2));

        p_str1 = (char*)realloc(p_str1, 16);  
        if(NULL==p_str1) {
                printf("Realloc p_str1 memory ERROR1\n");
                free(p_str1);                   //If the data fails to be realloced, the original data will not be moved or deleted.
                free(p_str2);
                return -1;
        }
        p_str1[15] = '\0';

        p_str2 = (char*)realloc(p_str2, 128);
        if(NULL==p_str2) {
                printf("Realloc p_str2 memory ERROR1\n");
                free(p_str1);
                free(p_str2);
                return -1;
        }
        strcat(p_str2, "The second sentence in extra memory after realloced!");

        printf("p_str1 after realloced\n");
        printf("p_str1 address: 0x%p\n", &p_str1);
        printf("p_str1: %s(%ld chars)\n", p_str1, strlen(p_str1));

        printf("p_str2 after realloced\n");
        printf("p_str2 address: 0x%p\n", &p_str2);
        printf("p_str2: %s(%ld chars)\n", p_str2, strlen(p_str2));

        free(p_str1);
        free(p_str2);
        
        return 0;
}

#endif

//test2
