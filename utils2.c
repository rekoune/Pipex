/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:09:40 by arekoune          #+#    #+#             */
/*   Updated: 2024/05/08 19:46:33 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find(char *to_find, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == to_find[j] && i + j < 5)
		{
			if (to_find[j + 1] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

char	*get_the_path(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (find("PATH=", env[i]) == 1)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

void	error(char *cmd, char c)
{
	if (c == 'f')
	{
		ft_write(cmd, 2);
		ft_write(": No such file or directory\n", 2);
	}
	else if (c == 'c')
	{
		ft_write(cmd, 2);
		ft_write(": command not found\n", 2);
	}
	else
		ft_write(cmd, 2);
	exit(1);
}

int	compare(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	str_len(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
