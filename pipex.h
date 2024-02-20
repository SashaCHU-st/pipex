/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:16:27 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/20 16:35:02 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>

typedef struct s_pipex
{
	int		fd[2];
	char	*path;
	int		fd_in;
	int		fd_out;
	char	**commands_fir_child;
	char	**commands_sec_child;
	char	**commands_path;
}		t_pipex;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	open_fd(t_pipex *data, char **argv, int argc );
char	*mine_path(char **envp);
void	fun_first_child(int fd[2], t_pipex *data, char **envp);
void	fun_second_child( int fd[2], t_pipex *data, char **envp);
char	**ft_split(char const *s, char c);
void	free_w(size_t i, char **ptr);
char	*ft_wd(const char *str, char c);
int		ft_words(const char *str, char c);
char	*path_for_commands(char **child_command, char **path);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str );

#endif