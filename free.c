/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:26:32 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/26 14:59:06 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_fun(t_pipex *data)
{
	if (data->commands_path != NULL)
		free_array(data->commands_path);
	if (data->com_fir_child != NULL)
		free_array(data->com_fir_child);
	if (data->com_sec_child != NULL)
		free_array(data->com_sec_child);
	exit(1);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		if (array[i] != NULL)
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
	}
}

void	ft_error(void)
{
	perror("Error fork()");
	exit(1);
}
