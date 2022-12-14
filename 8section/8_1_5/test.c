
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#ifdef TEST

#else

void bye(void)
{
        printf("That was all, folks\n");
}

void bye1(void)
{
        printf("This should called first!\n");
}

int main()
{
        int i;

        // function will be uesd after this process end
        i = atexit(bye); 
        if (i != 0) {
                // int fprintf( FILE *stream, const char *format, ... );
                // this function will change the infor of document
                fprintf(stderr, "cannot set exit function bye\n");  
                return EXIT_FAILURE;
        }

        i = atexit(bye1);
        if (i != 0) {
                fprintf(stderr, "cannot set exit function bye1\n");
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;

}

#endif
