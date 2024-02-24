/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:30:26 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/24 15:55:24 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	creating_children(char **argv, int fd[2], t_pipex *data, char **envp)
{
	int	first_child;
	int	second_child;

	first_child = fork();
	if (first_child < 0)
	{
		perror("Error first_child fork()");
		exit(1);
	}
	if (first_child == 0)
		fun_first_child(argv, fd, data, envp);
	second_child = fork();
	if (second_child < 0)
	{
		perror("Error second_child fork()");
		exit(1);
	}
	if (second_child == 0)
		fun_second_child(argv, fd, data, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(first_child, NULL, 0);
	waitpid(second_child, NULL, 0);
}

void	fun_first_child(char **argv, int fd[2], t_pipex *data, char **envp)
{
	char	*final;

	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	dup2(data->fd_in, STDIN_FILENO);
	data->com_fir_child = ft_split(argv[2], ' ');
	if (data->com_fir_child == 0)
		free_fun(data);
	final = path_for_commands(data, data->com_fir_child, data->commands_path);
	if (!final)
	{
		free(data->com_sec_child);
		free(final);
		exit(1);
	}
	execve(final, data->com_fir_child, envp);
}

void	fun_second_child(char **argv, int fd[2], t_pipex *data, char **envp)
{
	char	*final;

	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	dup2(data->fd_out, STDOUT_FILENO);
	data->com_sec_child = ft_split(argv[3], ' ');
	if (data->com_sec_child == 0)
		free_fun(data);
	final = path_for_commands(data, data->com_sec_child, data->commands_path);
	if (!final)
	{
		free(data->com_sec_child);
		free(final);
		exit(1);
	}
	execve(final, data->com_sec_child, envp);
}

char	*path_for_commands(t_pipex *data, char **child_command, char **path)
{
	char	*command;
	char	*command_temp;

	while (*path)
	{
		command_temp = ft_strjoin(*path, "/");
		if (command_temp == 0)
			free_fun(data);
		command = ft_strjoin (command_temp, *child_command);
		if (command == 0)
			free_fun(data);
		free(command_temp);
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		free(command);
		path++;
	}
	if (!*path)
	{
		ft_putstr_fd(*child_command, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	return (0);
}
