#include "pipex.h"

char *str_join(char *s1, char *s2)
{
	char *str;
	int	len;
	int	i;

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
	return(str);
}

void error()
{
	write(2, "error\n", 6);
	exit(1);
}

void	check_files(int ac, char ** av, t_file *file)
{
	file->in_fd = open(av[1], O_RDWR);
	if (file->in_fd == -1)
		error();
	file->ou_fd = open(av[ac-1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (file->ou_fd == -1)
		error();
}

char *path_check(char *cmd)
{
	char *path;
	char	**str;
	int		i;
	char *arg;

	i = 0;
	path = "/Users/arekoune/goinfre/homebrew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
	str = ft_split(path, ':');
	while (str[i])
	{
		arg = str_join(str[i], cmd);
		//printf("%s\n",arg);
		if (access(arg, X_OK) == 0)
			return (arg);
		i++;
	}
	return(NULL);
}
