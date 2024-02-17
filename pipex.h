/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:16:27 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/17 11:53:13 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
# include <fcntl.h>
#include <sys/wait.h>

typedef struct s_pipex
{
	int		fd[2];
	int		fd_in;
	int		fd_out;
	char	*commands;
}		t_pipex;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	open_fd(t_pipex *data, int argc, char **argv);
char	*mine_path(char **envp);
void fun_second_child(int argc, int fd[2], t_pipex *data, char *argv[],char **envp);
void fun_first_child(int fd[2], t_pipex *data, char *argv[],char **envp);
