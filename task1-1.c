#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("User: %d\n",getuid());
    printf("User Group: %d", getgid());

    return 0;
}