/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:28:39 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/20 16:23:42 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*mine_path(char **envp)
{
	while (ft_strncmp ("PATH=", *envp, 5))
		envp++;
	return (*envp + 5);
}

void	open_fd(t_pipex *data, char **argv, int argc )
{
	if (access(argv[1], F_OK) == -1)
		perror("No access for input");
	data->fd_in = open(argv[1], O_RDONLY);
	if (data->fd_in == -1)
		perror("Error in infile");
	if (access(argv[argc - 1], W_OK) == -1)
		perror("No access for output");
	data->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_out == -1)
		perror("Error in outfile");
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		fd[2];
	char	*path;
	int		first_child;
	 int		second_child;
	//char	**path_commands;

	if (argc != 5)
		perror("Less the 5 argc");
	open_fd(&data, argv, argc);
	if (pipe(fd) == -1)
		perror("Error in pipe()");
	path = mine_path(envp);
	//printf("%s", path);
	data.commands_path = ft_split(path, ':');
	// int i = 0;
	// while(data.commands_path[i])
	// {
	// 	printf("123%s\n", data.commands_path[i]);
	// 	i++;
	// }
	data.commands_first_child = ft_split(argv[2], ' ');
	//printf("FIRST CHILD COMMAND %s\n", *data.commands_first_child);
	data.commands_second_child = ft_split(argv[3], ' ');
	//printf("SEC CHILD COMMAND %s\n", *data.commands_second_child);
	first_child = fork();
	if (first_child < 0)
		perror("Error first_child fork()");
	if (first_child == 0)
	{
		///printf("hellon");
		fun_first_child(fd, &data, envp);
	}
	//printf("333333333\n");
	second_child = fork();
	if (second_child < 0)
		perror("Error second_child fork()");
	if (second_child == 0)
	{
		//printf("hellon2");
		fun_second_child(fd, &data, envp);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(first_child, NULL, 0);
	waitpid(second_child, NULL, 0);
	return (0);
}

void	fun_first_child(int fd[2], t_pipex *data, char **envp)
{
	//printf("here\n");
	char *the_final_path;
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	dup2(data->fd_in, STDIN_FILENO);
	the_final_path = path_for_commands(data->commands_first_child, data->commands_path);
	//printf("THE FINAL PATH = %s\n", the_final_path);
	//char *cat_argv[] = {"cat", NULL};
	execve(the_final_path, data->commands_first_child, envp);
}

void	fun_second_child( int fd[2], t_pipex *data, char **envp)
{
	//printf("here\n");
	char *the_final_path;
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	dup2(data->fd_out, STDOUT_FILENO);
	the_final_path = path_for_commands(data->commands_second_child, data->commands_path);
	// printf("THE FINAL PATH = %s\n", the_final_path);
	//char *child_argv[] = {"wc","-l", NULL};
	execve(the_final_path,data->commands_second_child, envp);
} 

char	*path_for_commands(char **child_command, char **path)
{
	char	*command;
	char	*command_temp;
	// printf("CHILD COMMAND =%s\n", *child_command);
	while (*path)
	{
		command_temp = ft_strjoin(*path, "/");
		command = ft_strjoin (command_temp, *child_command);
		// printf("PATH%s\n", *path);
		// printf("COMMAND%s\n", command);
		if (access(command, F_OK | X_OK) == 0)
			return(command);
		path++;
	}
	return (0);
}
