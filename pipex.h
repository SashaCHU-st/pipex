/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:16:27 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/16 17:47:54 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
# include <fcntl.h>
#include <sys/wait.h>

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	char	**file1;
	char	**cmd1;
	char	**cmd2;
	char	**file2;
}		t_pipex;
