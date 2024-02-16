#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
int main (int argc, char *argv[])
{
	int fd[2];

	if (pipe(fd) == -1)
	{
		printf("error");
		return (1);

	}
	int pid1 = fork();
	if (pid1 < 0){
		return (1);
	}
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		char *cat_argv[] = {"cat", argv[1], NULL};
		char *envp[] = {NULL};
		execve("/bin/cat", cat_argv, envp);
		perror("execve1");
		return (1);
	}
	int pid2 = fork();
	if(pid2< 0)
	{
		return(1);
	}
	if(pid2 == 0)
	{
		int file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644 );
		if(file == -1)
			return(1);
		dup2(fd[0], STDIN_FILENO);
        dup2(file, STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
		char *child_argv[] = {"wc","-l", NULL};
		char *envp[] = {NULL};
		execve("/usr/bin/wc",child_argv, envp);
		perror("execve2");
		return (1);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
