
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* mid_thread(void *arg);
void* term_thread(void *arg);
               
int main()
{
        pthread_t mid_tid, term_tid;

        if (pthread_create(&mid_tid, NULL, mid_thread, NULL)) {

                perror("Create mid thread error!");
                return 0;
        }

        if (pthread_create(&term_tid, NULL, term_thread, &mid_tid)) {

                perror("Create mid thread fail!");
                return 0; 
        }

        if (pthread_join(mid_tid, NULL)) {

                perror("Wait mid thread error!");
                return 0; 
        }

        if (pthread_join(term_tid, NULL)) {

                perror("Wait term thread error!");
                return 0; 
        }

        return 0;
}

void* mid_thread(void *arg)
{
        int times = 0;
        printf("mid thread created!\n");
        while(2) {
                printf("waitting term thread %d times!\n",times);
                sleep(1);
                times++;
        }
}

void* term_thread(void *arg)
{
        pthread_t *tid;
        printf("term thread created!\n");
        sleep(2);
        if (NULL!=arg) {
                tid = arg;
                pthread_cancel(*tid);
        }
}
