/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:28:39 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/24 16:22:34 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*mine_path(char **argv, char **envp)
{
	if (envp == NULL || *envp == NULL)
		return (0);
	while (ft_strncmp("PATH=", *envp, 5) != 0)
	{
		envp++;
		if (*envp == NULL)
		{
			ft_putstr_fd(argv[2], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			ft_putstr_fd(argv[3], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(0);
		}
	}
	return (*envp + 5);
}

void	open_fd(t_pipex *data, char **argv, int argc )
{
	if (access(argv[1], F_OK | R_OK) == -1)
	{
		perror("No access for input");
		exit(0);
	}
	data->fd_in = open(argv[1], O_RDONLY);
	if (data->fd_in == -1)
	{
		perror("Error in infile");
		exit(1);
	}
	data->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_out == -1)
	{
		perror("Error in outfile");
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		fd[2];
	char	*path;

	if (argc != 5)
	{
		perror("Less the 5 argc");
		exit(1);
	}
	open_fd(&data, argv, argc);
	if (pipe(fd) == -1)
	{
		perror("Error in pipe()");
		exit(1);
	}
	path = mine_path(argv, envp);
	data.commands_path = ft_split(path, ':');
	if (data.commands_path == 0)
		free_fun(&data);
	creating_children(argv, fd, &data, envp);
	close(data.fd_in);
	close(data.fd_out);
	return (0);
}
