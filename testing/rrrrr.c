/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:37:53 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/12 14:55:06 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
void forki()
{
	pid_t p;

	p = fork();
	if(p < 0)
	{
		printf("fork fails");
		exit(1);
	}
	if(p > 0)
		printf("hello from parent %d\n", p);
	else if (p == 0)
		printf("hellos this is child  %d\n", 0);
}
int main()
{
	forki();
	return(0);	
}