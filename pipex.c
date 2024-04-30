#include "pipex.h"

void	child_pross(t_file *file, char ***cmd, int i, int ac)
{
	char *arg;

	if (i == 0)
	{
		close(file->new_pipe[0]);
		dup2(file->in_fd, 0);
		close(file->in_fd);
	}
	if (i > 0)
		dup2(file->prev_pipe, 0);
	arg = path_check(cmd[i][0]); 
	dup2(file->new_pipe[1], 1);
	close(file->new_pipe[1]);
	if ((i + 1) == ac)
	{
		dup2(file->ou_fd, 1);
		close(file->ou_fd);
	}
	execve(arg, cmd[i], NULL);
	perror("error: ");
	printf("error_multiple\n");
}


void	do_the_cmd(char ***cmd, t_file *file, int ac)
{
	int i;

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

void	take_cmd(int ac, char **av, t_file *file)
{
	int	i;
	char ***cmd;
	int	j;

	cmd = malloc((ac - 2) * sizeof(char **));
	j = 0;
	i = 2;
	while (i < (ac - 1))
		cmd[j++] = ft_split(av[i++], ' ');
	cmd[j] = NULL;
	do_the_cmd(cmd, file, ac - 3);
	free_3D(cmd);
}

int main(int ac, char **av)
{ 
	t_file file;

	file.in_fd = 0;
	if (ac < 5)
		error();
	check_files(ac, av, &file);
	take_cmd (ac, av, &file);
	close (file.ou_fd);
	//while (1);
	//system("leaks pipex");
} 
