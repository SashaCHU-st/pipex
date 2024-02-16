#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *const argv[] = {"/bin/ls", "-l", NULL};
    char *const envp[] = {NULL};

    // Execute the "ls -l" command
    if (execve("/bin/ls", argv, envp) == -1) {
        perror("execve");
        exit(EXIT_FAILURE);
    }

    // This code will not be reached if execve is successful
    printf("This line will not be executed\n");

    return 0;
}
