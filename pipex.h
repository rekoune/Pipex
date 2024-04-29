#ifndef PIPEX_H
# define PIPEX_H


# include <stdio.h>

# include <stdlib.h>
# include <unistd.h>
#include <fcntl.h>

typedef struct t_files{

	int in_fd;
	int ou_fd;

}t_file;


//utils.c
void	check_files(int ac, char ** av, t_file *file);
void	error();
char 	*str_join(char *s1, char *s2);
char 	*path_check(char *cmd);


//split_cmd.c
int		str_len(char *str, char c);
int		counte(char *str, char c);
char	*sub_str(char *str, int len);
char	**ft_split(char *str, char c);


//pipex.c
void	take_cmd(int ac, char **av, t_file *file);
void	do_the_cmd(char ***cmd, t_file *file, int ac);
void	multiple_cmd(char ***cmd, t_file *file, int fd, int ac);

# endif