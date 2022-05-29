//
// Created by bananus on 29.05.22.
//

#include <signal.h>

int main(void) {
    (void)signal(SIGINT, SIG_IGN);
    (void)signal(SIGQUIT, SIG_IGN);

    while(1);
}
