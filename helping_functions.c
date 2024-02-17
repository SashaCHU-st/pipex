/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helping_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 09:21:01 by aheinane          #+#    #+#             */
/*   Updated: 2024/02/17 15:22:14 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] > s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else if (s1[i] < s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
int	ft_words(const char *str, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			j++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
	}
	return (j);
}

char	*ft_wd(const char *str, char c)
{
	size_t	i;
	char	*wd;

	i = 0;
	while (*str && *str == c)
		str++;
	while (str[i] && str[i] != c)
		i++;
	wd = malloc(sizeof(char) * (i + 1));
	if (wd == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		wd[i] = str[i];
		i++;
	}
	wd[i] = '\0';
	return (wd);
}

void	free_w(size_t i, char **ptr)
{
	while (i > 0)
	{
		free(ptr[i - 1]);
		i--;
	}
	free(ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	words;
	size_t	i;

	words = ft_words (s, c);
	ptr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s && *s == c)
			s++;
		ptr[i] = ft_wd(s, c);
		if (ptr[i] == NULL)
		{
			free_w(i, ptr);
			return (NULL);
		}
		while (*s && *s != c)
			s++;
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
