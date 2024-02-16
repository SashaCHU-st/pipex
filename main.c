/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:28:39 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/16 12:41:46 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
int main (int argc, char *argv[], char *envp)
{
	t_pipex	*p;
	if (argc != 5)
		return(0);
	p = pipex_data (argc, argv, envp);
	
	
}
t_pipex *pipex_data(int argc, char *argv[], char *envp[])
{
	t_pipex *data;
	
	data = malloc(sizeof(struct s_pipex));
	
	return(data);
}
void open_fd(t_pipex *data, int argc, char **argv)
{
	
	data->fd_in = open(argv[1], O_RDONLY);
	data->fd_out = open(argv[argc - 1], O_CREAT, O_WRONLY, O_TRUNC, 0644);
	return ;
}