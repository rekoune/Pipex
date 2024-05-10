/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:53:35 by arekoune          #+#    #+#             */
/*   Updated: 2024/05/10 10:21:44 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_pross(t_file *file, char ***cmd, int i, int ac)
{
	char	*arg;

	if (i == 0)
	{
		close(file->new_pipe[0]);
		if (file->in_fd == -1)
			exit(1);
		dup2(file->in_fd, 0);
		close(file->in_fd);
	}
	else
	{
		dup2(file->prev_pipe, 0);
		close(file->prev_pipe);
	}
	arg = path_check(cmd[i][0], file);
	dup2(file->new_pipe[1], 1);
	close(file->new_pipe[1]);
	if ((i + 1) == ac)
		dup2(file->ou_fd, 1);
	if ((i + 1) == ac)
		close(file->ou_fd);
	close(file->new_pipe[0]);
	execve(arg, cmd[i], file->env);
	perror("execve ");
}

void	do_the_cmd(char ***cmd, t_file *file, int ac)
{
	int	i;

	i = 0;
	file->pid = malloc(ac * sizeof(pid_t));
	while (i < ac)
	{
		pipe(file->new_pipe);
		file->pid[i] = fork();
		if (file->pid[i] == 0)
			child_pross(file, cmd, i, ac);
		if (i > 0)
			close(file->prev_pipe);
		file->prev_pipe = dup(file->new_pipe[0]);
		close(file->new_pipe[1]);
		close(file->new_pipe[0]);
		i++;
	}
	close(file->prev_pipe);
	close(file->in_fd);
	ac = i;
	i = 0;
	while (i < ac)
		if (waitpid(file->pid[i++], NULL, 0) == -1)
			perror("waitpid");
}

void	take_cmd(int ac, char **av, t_file *file, char c)
{
	int		i;
	char	***cmd;

	cmd = malloc((ac + 1) * sizeof(char **));
	i = 0;
	while (i < ac)
	{
		cmd[i] = ft_split(av[i], ' ');
		i++;
	}
	cmd[i] = NULL;
	if (c == 'h')
		here_doc(cmd, file, ac);
	else
		do_the_cmd(cmd, file, ac);
	free_3d(cmd);
}

int	main(int ac, char **av, char **env)
{
	t_file	file;

	file.in_fd = 0;
	file.env = env;
	if (ac < 5)
		error("Error\n", 'A');
	check_files(ac, av, &file);
	if (compare(av[1], "here_doc") == 0)
	{
		file.limeter = av[2];
		take_cmd(ac - 4, &av[3], &file, 'h');
	}
	else
		take_cmd(ac - 3, &av[2], &file, '\0');
	close(file.ou_fd);
}
