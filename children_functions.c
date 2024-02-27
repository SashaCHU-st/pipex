/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:30:26 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/27 12:38:59 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	creating_children(char **argv, t_pipex *data, int argc, char **envp)
{
	int		first_child;
	int		second_child;

	first_child = 0;
	second_child = 0;
	check_permissions(argv);
	if (open_fd_in(data, argv) == 1)
		ft_putstr_fd(": No such file or directory\n", 2);
	else
	{
		first_child = fork();
		if (first_child < 0)
			ft_error();
		if (first_child == 0)
			fun_first_child(argv, data, envp);
	}
	open_fd_out(data, argv, argc);
	second_child = fork();
	if (second_child < 0)
		ft_error();
	if (second_child == 0)
		fun_second_child(argv, data, envp);
	close_and_wait(data, first_child, second_child);
}

void	fun_first_child(char **argv, t_pipex *data, char **envp)
{
	char	*final;

	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[0]);
	close(data->fd[1]);
	dup2(data->fd_in, STDIN_FILENO);
	data->com_fir_child = ft_split(argv[2], ' ');
	if (data->com_fir_child == 0)
	{
		close(data->fd[0]);
		close(data->fd[1]);
		free_fun(data);
	}
	final = path_for_commands(data, data->com_fir_child, data->commands_path);
	if (!final)
	{
		free(data->com_sec_child);
		free(final);
		exit(1);
	}
	if (execve(final, data->com_fir_child, envp) == -1)
		free_fun(data);
}

void	fun_second_child(char **argv, t_pipex *data, char **envp)
{
	char	*final;

	dup2(data->fd[0], STDIN_FILENO);
	close(data->fd[0]);
	close(data->fd[1]);
	dup2(data->fd_out, STDOUT_FILENO);
	data->com_sec_child = ft_split(argv[3], ' ');
	if (data->com_sec_child == 0)
	{
		close(data->fd[0]);
		close(data->fd[1]);
		free_fun(data);
	}
	final = path_for_commands(data, data->com_sec_child, data->commands_path);
	if (!final)
	{
		free(data->com_sec_child);
		free(final);
		exit(1);
	}
	if (execve(final, data->com_sec_child, envp) == -1)
		free_fun(data);
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
		free(command_temp);
		if (command == 0)
			free_fun(data);
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
