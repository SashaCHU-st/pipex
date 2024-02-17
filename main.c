/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:28:39 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/17 11:54:47 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
int main (int argc, char *argv[], char **envp)
{
	t_pipex	*data;
	int		fd[2];
	char	*path;
	int		first_child;
	int		second_child;
	
	
	if (argc != 3)
		perror("Less the 5 argc");
	//open_fd(&data, argc, argv);
	if (pipe(fd) == -1)
		perror("Error in pipe()");
	//path = mine_path(envp);///???????
	first_child = fork();
	if (first_child < 0)
		perror("Error first_child fork()");
	if(first_child == 0)
		fun_first_child(fd, data, argv, envp);
	second_child = fork();
	if (second_child < 0)
		perror("Error second_child fork()");
	if(second_child == 0)
		fun_second_child(argc, fd, data, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(first_child, NULL, 0);
	waitpid(second_child, NULL, 0);
	return (0);
	
}
// t_pipex *pipex_data(int argc, char *argv[], char *envp[])
// {
// 	t_pipex *data;
	
// 	data = malloc(sizeof(struct s_pipex));
	
// 	return(data);
// }
void open_fd(t_pipex *data, int argc, char **argv)
{
	
	data->fd_in = open(argv[1], O_RDONLY);
	if(data->fd_in == -1)
		perror("Error in infile");
	data->fd_out = open(argv[argc - 1], O_CREAT, O_WRONLY, O_TRUNC, 0644);
	if(data->fd_out == -1)
		perror("Error in outfile");
	return ;
}
// char *mine_path(char **envp)
// {
// 	while (ft_strncmp ("PATH", *envp, 4))
// 		envp++;
// 	return(*envp + 5);
// }
void fun_first_child(int fd[2], t_pipex *data, char *argv[],char **envp)
{
	//data = malloc(sizeof(struct s_pipex));
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	char *cat_argv[] = {"cat", argv[1], NULL};
	execve("/bin/cat", cat_argv, envp);
}
void fun_second_child(int argc, int fd[2], t_pipex *data, char *argv[],char **envp)
{
	int file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644 );
	if(file == -1)
		perror("Error open file");
	dup2(fd[0], STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	char *child_argv[] = {"wc","-l", NULL};
	execve("/usr/bin/wc",child_argv, envp);
}