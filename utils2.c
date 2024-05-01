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
	while (env[i])
	{
		if (find("PATH=", env[i]) == 1)
			return(env[i] + 5);
		i++;
	}
	return(NULL);
}
