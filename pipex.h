/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:16:27 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/24 15:57:47 by aheinane         ###   ########.fr       */
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
	char	**com_fir_child;
	char	**com_sec_child;
	char	**commands_path;
}	t_pipex;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	open_fd(t_pipex *data, char **argv, int argc );
char	*mine_path(char **argv, char **envp);
void	fun_first_child(char **argv, int fd[2], t_pipex *data, char **envp);
void	fun_second_child(char **argv, int fd[2], t_pipex *data, char **envp);
char	**ft_split(char const *s, char c);
void	free_w(size_t i, char **ptr);
char	*ft_wd(const char *str, char c);
int		ft_words(const char *str, char c);
char	*path_for_commands(t_pipex *data, char **child_command, char **path);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str );
void	creating_children(char **argv, int fd[2], t_pipex *data, char **envp);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	free_fun(t_pipex *data);
void	free_array(char **array);
#endif