/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:07:34 by arekoune          #+#    #+#             */
/*   Updated: 2024/05/10 19:39:55 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_bonus(t_file *file, char ***cmd, int i, int ac)
{
	char	*arg;

	close(file->new_pipe[0]);
	dup2(file->prev_pipe, 0);
	close(file->prev_pipe);
	dup2(file->new_pipe[1], 1);
	close(file->new_pipe[1]);
	if (i + 1 == ac)
		dup2(file->ou_fd, 1);
	arg = path_check(cmd[i][0], file);
	execve(arg, cmd[i], file->env);
	perror("Error: ");
}

void	do_cmd_bonus(t_file *file, char ***cmd, int ac)
{
	int	i;

	i = 0;
	file->pid = malloc(ac * sizeof(pid_t));
	while (i < ac)
	{
		pipe(file->new_pipe);
		file->pid[i] = fork();
		if (file->pid[i] == 0)
			child_bonus(file, cmd, i, ac);
		close(file->prev_pipe);
		file->prev_pipe = dup(file->new_pipe[0]);
		close(file->new_pipe[0]);
		close(file->new_pipe[1]);
		i++;
	}
	i = 0;
	while (i < ac)
		if (waitpid(file->pid[i++], NULL, 0) == -1)
			perror("Error: ");
	free(file->pid);
}

char	*add_nw(char *str)
{
	char	*limeter;
	int		i;

	i = 0;
	limeter = malloc(str_len(str, '\0') + 2);
	while (str[i])
	{
		limeter[i] = str[i];
		i++;
	}
	limeter[i++] = '\n';
	limeter[i] = '\0';
	return (limeter);
}

void	here_doc(char ***cmd, t_file *file, int ac)
{
	char	*line;
	char	*limeter;
	int		i;

	i = 0;
	limeter = add_nw(file->limeter);
	pipe(file->new_pipe);
	line = get_next_line(0);
	while (line && compare(line, limeter) != 0)
	{
		write(file->new_pipe[1], line, str_len(line, '\0'));
		free(line);
		line = get_next_line(0);
	}
	free(limeter);
	free(line);
	file->prev_pipe = dup(file->new_pipe[0]);
	close(file->new_pipe[0]);
	close(file->new_pipe[1]);
	do_cmd_bonus(file, cmd, ac);
}
