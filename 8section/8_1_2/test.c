// filename getenv.c
#include <stdlib.h>
#include <stdio.h>

int main()
{
// "PATH": Search path for executable files.
        char *env_path = "PATH";
        char *env_vaule = NULL;

// char *getenv(const char *name);
        env_vaule = getenv(env_path);
        if (NULL==env_vaule)
                printf("Not found!\n");
        printf("Get Env PATH:\n%s \n", env_vaule);

        return 0;

}
