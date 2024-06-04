/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:53:40 by arekoune          #+#    #+#             */
/*   Updated: 2024/06/04 10:02:26 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include "get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct t_files
{
	int		in_fd;
	int		ou_fd;
	int		new_pipe[2];
	int		prev_pipe;
	pid_t	*pid;
	char	**env;
	char	*limeter;

}			t_file;

// utils2.c
int			find(char *to_find, char *str);
char		*get_the_path(char **env);
void		error(char *cmd, char c);
int			compare(char *s1, char *s2);
int			str_len(char *str, char c);

// utils.c
void		check_files(int ac, char **av, t_file *file);
void		ft_write(char *str, int a);
char		*str_join(char *s1, char *s2);
char		*path_check(char *cmd, t_file *file);
void		free_3d(char ***cmd);

// split_cmd.c
int			counte(char *str, char c);
char		*sub_str(char *str, int len);
char		**ft_split(char *str, char c);
void		coun_ter(char *str, char c, int i, int *counter);
void		skip_delimiter(char **str, char *c, char j);

// pipex.c
void		take_cmd(int ac, char **av, t_file *file, char c);
void		do_the_cmd(char ***cmd, t_file *file, int ac);
void		child_pross(t_file *file, char ***cmd, int i, int ac);

// here_doc.c
void		here_doc(char ***cmd, t_file *file, int ac);
void		child_bonus(t_file *file, char ***cmd, int i, int ac);
void		do_cmd_bonus(t_file *file, char ***cmd, int ac);
char		*add_nw(char *str);

#endif