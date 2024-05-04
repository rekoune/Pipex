#include "pipex.h"

int	find(char *to_find, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] )
	{
		j = 0;
		while(str[i + j] == to_find[j] )
		{
			if (to_find[j + 1] == '\0')
				return(1);
			j++;
		}
		i++;
	}
	return(0);
}

char *get_the_path(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return(NULL);
	while (env[i])
	{
		if (find("PATH=", env[i]) == 1)
			return(env[i] + 5);
		i++;
	}
	return(NULL);
}

void	error(char *cmd, char c)
{
	if(c == 'f')
	{
		ft_write(cmd, 2);
		ft_write(": No such file or directory\n", 2);
	}
	else if(c == 'c')
	{
		ft_write(cmd, 2);
		ft_write(": command not found\n", 2);
	}
	else
		ft_write(cmd, 2);
	exit(1);
}
