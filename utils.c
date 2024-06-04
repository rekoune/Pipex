/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:53:38 by arekoune          #+#    #+#             */
/*   Updated: 2024/06/04 09:59:57 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*str_join(char *s1, char *s2)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = str_len(s1, '\0') + 1;
	str = malloc((len + str_len(s2, '\0') + 1) * sizeof(char));
	len = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = '/';
	while (s2 && s2[len])
		str[i++] = s2[len++];
	str[i] = '\0';
	free(s1);
	return (str);
}

void	ft_write(char *str, int a)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		write(a, &str[i++], 1);
}

void	check_files(int ac, char **av, t_file *file)
{
	if (compare(av[1], "here_doc") != 0)
	{
		file->in_fd = open(av[1], O_RDWR);
		if (file->in_fd == -1)
			perror(av[1]);
		file->ou_fd = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (file->ou_fd == -1)
			perror(av[ac - 1]);
	}
	else
	{
		file->ou_fd = open(av[ac - 1], O_CREAT | O_RDWR | O_APPEND, 0666);
		if (file->ou_fd == -1)
			perror(av[ac - 1]);
	}
}

char	*path_check(char *cmd, t_file *file)
{
	char	*path;
	char	**str;
	int		i;
	char	*arg;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	path = get_the_path(file->env);
	if (!path)
		error(cmd, 'f');
	str = ft_split(path, ':');
	while (str && str[i])
	{
		arg = str_join(str[i], cmd);
		if (access(arg, X_OK) == 0)
			return (arg);
		free(arg);
		i++;
	}
	error(cmd, 'c');
	return (NULL);
}

void	free_3d(char ***cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
			free(cmd[i][j++]);
		free(cmd[i++]);
	}
	free(cmd);
}
