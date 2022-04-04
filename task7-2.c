#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a = 0;

void *mythread(void *dummy) {
    pthread_t mythid = pthread_self();

    a = a + 1;
    printf("Thread %u, Calculation result = %d\n", mythid, a);
    return NULL;
}

int main() {
    pthread_t second, first, third;
    int result = pthread_create(&second, (pthread_attr_t *) NULL, mythread, NULL) +
             pthread_create(&third, (pthread_attr_t *) NULL, mythread, NULL);

    if (result != 0) {
        printf("Error on thread create, return value = %d\n", result);
        exit(-1);
    }

    printf("Thread created, second = %u\n", second);
    printf("Thread created, third = %u\n", third);

    first = pthread_self();

    a = a + 1;

    printf("Thread %u, Calculation result = %d\n", first, a);

    pthread_join(second, (void **) NULL);
    pthread_join(third, (void **) NULL);
    return 0;
}
