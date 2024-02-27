/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:16:27 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/26 17:17:17 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>

typedef struct s_pipex
{
	int		fd[2];
	int		fd_in;
	int		fd_out;
	char	**com_fir_child;
	char	**com_sec_child;
	char	**commands_path;
}	t_pipex;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		open_fd_in(t_pipex *data, char **argv);
void	open_fd_out(t_pipex *data, char **argv, int argc);
char	*mine_path(char **envp);
void	fun_first_child(char **argv, t_pipex *data, char **envp);
void	fun_second_child(char **argv, t_pipex *data, char **envp);
char	**ft_split(char const *s, char c);
void	free_w(size_t i, char **ptr);
char	*ft_wd(const char *str, char c);
int		ft_words(const char *str, char c);
char	*path_for_commands(t_pipex *data, char **child_command, char **path);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str );
void	creating_children(char **argv, t_pipex *data, int argc, char **envp );
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	free_fun(t_pipex *data);
void	free_array(char **array);
void	ft_error(void);
void	close_and_wait(t_pipex *data, int first_child, int second_child);
void	check_permissions(char *argv[]);

#endif