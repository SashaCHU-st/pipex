/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:28:39 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/20 16:42:03 by aheinane         ###   ########.fr       */
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

	if (argc != 5)
		perror("Less the 5 argc");
	open_fd(&data, argv, argc);
	if (pipe(fd) == -1)
		perror("Error in pipe()");
	path = mine_path(envp);
	data.commands_path = ft_split(path, ':');
	data.commands_fir_child = ft_split(argv[2], ' ');
	data.commands_sec_child = ft_split(argv[3], ' ');
	first_child = fork();
	if (first_child < 0)
		perror("Error first_child fork()");
	if (first_child == 0)
		fun_first_child(fd, &data, envp);
	second_child = fork();
	if (second_child < 0)
		perror("Error second_child fork()");
	if (second_child == 0)
		fun_second_child(fd, &data, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(first_child, NULL, 0);
	waitpid(second_child, NULL, 0);
	return (0);
}

