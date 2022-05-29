//
// Created by bananus on 29.05.22.
//

#include <signal.h>
#include <stdio.h>

void my_handler(int nsig) {
    if (nsig == 2)
        printf("Received nsig: %d\nYou pressed CTRL+C\n", nsig);
    if (nsig == 3)
        printf("Received nsig: %d\nYou pressed CTRL+4\n", nsig);
}

int main(void) {
    (void) signal(SIGINT, my_handler);
    (void) signal(SIGQUIT, my_handler);

    while (1);
}
