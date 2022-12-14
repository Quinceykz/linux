
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* thread_func(void *arg)
{
        int *val = arg;
        printf("Hi, I'm a thread!\n");
        if (NULL!=arg) {
                while(1)
                        printf("argument set: %d\n", *val);
        }

}
               
int main()
{
        pthread_t tid;
        int t_arg = 100;

        if (pthread_create(&tid, NULL, thread_func, &t_arg))
                perror("Fail to create thread");

        sleep(1);
        pthread_cancel(tid);            //stop the pthread after the end of thread
        printf("thread has been canceled!\n");
        sleep(1);
        printf("Main thread!\n");

        return 0;
}