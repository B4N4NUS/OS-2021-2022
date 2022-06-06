//
// Created by bananus on 06.06.22.
//
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int current = 0;
int pid;
int number = 0b11111111111111111111111111111111;

void handleOnes() {
    number = number ^ (1 << current);
    if (++current < 32) {
        printf("[R] Got %d bit: %d\n", current, 0);
        kill(pid, SIGUSR1);
    } else {
        printf("[R] Received number: %d", number);
        printf("\n[R] Exiting...\n");
        exit(0);
    }
}

void handleZeros() {
    if (++current == 32) {
        printf("[R] Got %d bit: %d\n", current, 1);
        kill(pid, SIGUSR1);
    } else {
        printf("[R] Received number: %d", number);
        printf("\n[R] Exiting...\n");
        exit(0);
    }
}

int main(void) {
    (void) signal(SIGUSR1, handleOnes);
    (void) signal(SIGUSR2, handleZeros);

    printf("[R] my PID: %d\n", getpid());

    printf("[R] enter sender\'s PID: ");
    scanf("%d", &pid);

    while(1) {}

    return 0;
}
