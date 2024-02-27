/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:28:39 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/27 12:42:33 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*mine_path(char **envp)
{
	if (envp == NULL || *envp == NULL)
		return (0);
	while (ft_strncmp("PATH=", *envp, 5) != 0)
	{
		envp++;
		if (*envp == NULL)
			return (0);
	}
	return (*envp + 5);
}

int	open_fd_in(t_pipex *data, char **argv)
{
	if (access(argv[1], F_OK | R_OK) == -1)
	{
		perror("No access for input");
		return (1);
	}
	data->fd_in = open(argv[1], O_RDONLY);
	if (data->fd_in == -1)
	{
		perror("Error in infile");
		return (1);
	}
	return (0);
}

void	open_fd_out(t_pipex *data, char **argv, int argc)
{
	data->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_out == -1)
	{
		perror("Error in outfile");
		close(data->fd_in);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	char	*path;

	if (argc != 5)
	{
		perror("Less the 5 argc");
		exit(1);
	}
	path = mine_path(envp);
	if (pipe(data.fd) == -1)
	{
		perror("Error in pipe()");
		exit(1);
	}
	data.commands_path = ft_split(path, ':');
	if (data.commands_path == 0)
	{
		close(data.fd[0]);
		close(data.fd[1]);
		free_fun(&data);
	}
	creating_children(argv, &data, argc, envp);
	close(data.fd_in);
	close(data.fd_out);
	return (0);
}
