
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
        void *t_val;
        if (pthread_create(&tid, NULL, thread_func, &t_arg))
                perror("Fail to create thread");
// set delay as the end of the pthread
        pthread_join(tid, &t_val);       //has Q how to get a return of thread.
// stop the pthread before the return of main
        pthread_cancel(tid);            
        printf("Main thread!\n");

        return 0;
}