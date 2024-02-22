/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:30:26 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/22 12:28:58 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	creating_children(int fd[2], t_pipex *data, char **envp)
{
	int		first_child;
	int		second_child;

	first_child = fork();
	if (first_child < 0)
	{
		perror("Error first_child fork()");
		exit(1);
	}
	if (first_child == 0)
		fun_first_child(fd, data, envp);
	second_child = fork();
	if (second_child < 0)
	{
		perror("Error second_child fork()");
		exit(1);
	}
	if (second_child == 0)
		fun_second_child(fd, data, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(first_child, NULL, 0);
	waitpid(second_child, NULL, 0);
}

void	fun_first_child(int fd[2], t_pipex *data, char **envp)
{
	char	*final;

	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	dup2(data->fd_in, STDIN_FILENO);
	final = path_for_commands(data->commands_fir_child, data->commands_path);
	execve(final, data->commands_fir_child, envp);
}

void	fun_second_child( int fd[2], t_pipex *data, char **envp)
{
	char	*final;

	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	dup2(data->fd_out, STDOUT_FILENO);
	final = path_for_commands(data->commands_sec_child, data->commands_path);
	execve(final, data->commands_sec_child, envp);
}

char	*path_for_commands(char **child_command, char **path)
{
	char	*command;
	char	*command_temp;

	while (*path)
	{
		command_temp = ft_strjoin(*path, "/");
		command = ft_strjoin (command_temp, *child_command);
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
