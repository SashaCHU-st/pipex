/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:45:42 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/27 12:28:34 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_permissions(char *argv[])
{
	if (argv[2][0] == '\0' || argv[3][0] == '\0')
	{
		write(2, "zsh: permission denied:\n", 24);
	}
	else if (argv[2][0] == '\0' && argv[3][0] == '\0')
	{
		write(2, "zsh: permission denied:\n", 24);
		exit(1);
	}
}

void	close_and_wait(t_pipex *data, int first_child, int second_child)
{
	close(data->fd[0]);
	close(data->fd[1]);
	waitpid(first_child, NULL, 0);
	waitpid(second_child, NULL, 0);
}
