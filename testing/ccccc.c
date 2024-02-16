#include <stdio.h>
#include <unistd.h> 
int main (int argc, char **argv)
{
	int fd[2];
	//fd[0] read
	//fd[1] write
	if (pipe(fd) == -1)
	{
		printf("error");
		return (1);
		}
	int id = fork();
	if (id ==0)
	{
		close(fd[0]);
		int x;
		printf("Input");
		scanf("%d", &x);
		write(fd[1], &x, sizeof(int) );
		close(fd[1]);
	}
	else 
	{
		close(fd[1]);
		int y;
		read(fd[0], &y, sizeof(int));
		close(fd[0]);
		printf("got from child %d", y);
	}
	return (0);
}