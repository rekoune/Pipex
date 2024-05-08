/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:26:32 by arekoune          #+#    #+#             */
/*   Updated: 2024/05/08 11:06:06 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	coun_ter(char *str, char c, int i, int *counter)
{
	int	nf;
	int	a;

	nf = 1;
	a = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			a++;
		}
		if (str[i] == c)
			nf = 1;
		else if (str[i] != c && nf == 1)
		{
			(*counter)++;
			nf = 0;
		}
		if (a == 2)
		{
			a = 0;
			c = ' ';
		}
	}
}

int	counte(char *str, char c)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	if (!str)
		return (0);
	coun_ter(str, c, i, &counter);
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

void	skip_delimiter(char **str, char *c, char j)
{
	while (**str == *c)
		(*str)++;
	*c = j;
	while (**str == *c)
		(*str)++;
	if (**str == '\'' || **str == '"')
	{
		*c = **str;
		(*str)++;
	}
}

char	**ft_split(char *str, char c)
{
	int		n_word;
	char	**s;
	int		i;
	char	j;

	i = 0;
	j = c;
	n_word = counte(str, c);
	s = malloc((n_word + 1) * sizeof(char *));
	while (i < n_word && *str)
	{
		skip_delimiter(&str, &c, j);
		while (*str == c)
			str++;
		if (*str && *str != c)
			s[i++] = sub_str(str, str_len(str, c));
		str += str_len(str, c);
	}
	s[i] = NULL;
	return (s);
}
