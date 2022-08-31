
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* thread_func(void *arg)
{
        int *val = arg;
        printf("Hi, I'm a thread!\n");
        if (NULL!=arg)
                printf("argument set: %d\n", *val);
}
               
int main()
{
        pthread_t tid;
        int t_arg = 100;

        if (pthread_create(&tid, NULL, (void*)thread_func, &t_arg))
                perror("Fail to create thread");

        pthread_join(tid, NULL);        //set delay as the end of the pthread
        pthread_cancel(tid);            //stop the pthread before the return of main
        printf("Main thread!\n");

        return 0;
}