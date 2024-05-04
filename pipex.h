/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:53:40 by arekoune          #+#    #+#             */
/*   Updated: 2024/05/04 19:57:41 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#include "get_next_line.h"

typedef struct t_files
{
	int		in_fd;
	int		ou_fd;
	int		new_pipe[2];
	int		prev_pipe;
	pid_t	*pid;

	char	**env;

}			t_file;

//utils2.c
int			find(char *to_find, char *str);
char		*get_the_path(char **env);
void		error(char *cmd, char c);

// utils.c
void		check_files(int ac, char **av, t_file *file);
void		ft_write(char *str, int a);
char		*str_join(char *s1, char *s2);
char		*path_check(char *cmd, t_file *file);
void		free_3D(char ***cmd);

// split_cmd.c
int			str_len(char *str, char c);
int			counte(char *str, char c);
char		*sub_str(char *str, int len);
char		**ft_split(char *str, char c);
int			compare(char *s1, char *s2);

// pipex.c
void		take_cmd(int ac, char **av, t_file *file);
void		do_the_cmd(char ***cmd, t_file *file, int ac);
void		child_pross(t_file *file, char ***cmd, int i, int ac);
void		her_doc(int ac, char **av, t_file *file);

#endif