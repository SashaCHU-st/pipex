/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:28:39 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/22 12:52:43 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*mine_path(char **first_child_com, char **sec_child_com, char **envp)
{
	if (envp == NULL || *envp == NULL)
		return (0);

	while (ft_strncmp("PATH=", *envp, 5) != 0)
	{
		envp++;
		if (*envp == NULL)
		{
			ft_putstr_fd(*first_child_com, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			ft_putstr_fd(*sec_child_com, 2);
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
	data.commands_fir_child = ft_split(argv[2], ' ');
	data.commands_sec_child = ft_split(argv[3], ' ');
	path = mine_path(data.commands_fir_child, data.commands_sec_child, envp);
	data.commands_path = ft_split(path, ':');
	creating_children(fd, &data, envp);
	return (0);
}
