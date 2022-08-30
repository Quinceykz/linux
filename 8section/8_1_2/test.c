// filename getenv.c
#include <stdlib.h>
#include <stdio.h>

#ifdef TEST

#else

int main()
{
        char *env_path = "PATH";
        char *env_vaule = NULL;

        env_vaule = getenv(env_path);
        if (NULL==env_vaule)
                printf("Not found!\n");
        printf("Get Env PATH:\n%s \n", env_vaule);

        return 0;

}

#endif
