/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:26:32 by arekoune          #+#    #+#             */
/*   Updated: 2024/05/04 13:23:38 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	counte(char *str, char c)
{
	int	i;
	int	nf;
	int	counter;

	i = 0;
	nf = 1;
	counter = 0;
	if (!str)
		return(0);
	while (str[i])
	{
		if (str[i] == c)
			nf = 1;
		else if (str[i] == 39)
		{
			c = 39;
			nf = 1;
		}
		else if (str[i] != c && str[i] != ' ' && nf == 1)
		{
			nf = 0;
			counter++;
		}
		i++;
	}
	return (counter);
}

char	*sub_str(char *str, int len)
{
	int		i;
	char	*s;

	i = 0;
	s = malloc((len + 1) * sizeof(char));
	while (i < len)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0'; 
	return (s);
}

char	**ft_split(char *str, char c)
{
	int		n_word;
	char	**s;
	int		i;
	char	a;
	int		b;

	i = 0;
	b = 1;
	n_word = counte(str, c);
	s = malloc((n_word + 1) * sizeof(char *));
	a = c;
	while (i < n_word && *str)
	{
		while (*str == c)
			str++;
		if (*str == 39)
		{
			str++;
			if (b == 1)
				c = 39;
			b = 0;
		}
		if (*str && *str != c)
			s[i++] = sub_str(str, str_len(str, c));
		str += str_len(str, c);
		c = a;
	}
	s[i] = NULL;
	return (s);
}

int	compare(char *s1, char *s2)
{
	int	i;

	i = 0;
	while(s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return(s1[i] - s2[i]);
		i++;
	}
		printf("s - s == %d\n", s1[i]-s2[i]);
	return(s1[i] - s2[i]);
}
