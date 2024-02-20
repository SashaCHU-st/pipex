/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:35:47 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/19 14:00:56 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	fun_first_child(int fd[2], t_pipex *data, char *argv[],char **envp)
// {
// 	//data = malloc(sizeof(struct s_pipex));
// 	dup2(fd[1], STDOUT_FILENO);
// 	close(fd[0]);
// 	dup2(data->fd_in, STDIN_FILENO);
// 	close(fd[1]);
// 	char *cat_argv[] = {"cat", NULL};
// 	execve("/bin/cat", cat_argv, envp);
// }

// void	fun_second_child( int fd[2], t_pipex *data, char *argv[],char **envp)
// {
// 	dup2(fd[0], STDIN_FILENO);
// 	close(fd[1]);
// 	dup2(data->fd_out, STDOUT_FILENO);
// 	close(fd[0]);
// 	char *child_argv[] = {"wc","-l", NULL};
// 	execve("/usr/bin/wc",child_argv, envp);
// }