#include "pipex.h"

void	multiple_cmd(char ***cmd, t_file *file, int fd, int ac)
{
	int fd2[2];
	int prev_pipe;
	int i;
	char *arg;

	i = 0;
	pipe(fd2);
	prev_pipe = dup(fd2[0]);
	pid_t pid;
	while (i < ac)
	{
		if (i > 0)
			pipe(fd2);
		 pid = fork();
		if ( pid== 0)
		{
			dup2(fd, 0);
			if (i > 0)
				dup2(prev_pipe, 0);
			arg = path_check(cmd[i][0]);
			dup2(fd2[1], 1);
			if ((i + 1) == ac)
				dup2(file->ou_fd, 1);
			execve(arg, cmd[i], NULL);
			perror("error: ");
			printf("error_multiple\n");
		}
		if (i > 0)
			prev_pipe = dup(fd2[0]);
		wait(NULL);
		close(fd);
		close(fd2[1]);
		close(fd2[0]);
		i++;
	}
}

void	do_the_cmd(char ***cmd, t_file *file, int ac)
{
	int	fd[2];
	char	*arg;

	pipe(fd);
	pid_t pid = fork();
	if (pid == 0)
	{
		arg = path_check(cmd[0][0]);
		close(fd[0]);
		dup2(file->in_fd, 0);
		dup2(fd[1], 1);
		execve(arg, cmd[0], NULL);
	}
	wait(NULL);
	close(fd[1]);
	multiple_cmd(&cmd[1], file, fd[0], (ac - 4));
}

void	take_cmd(int ac, char **av, t_file *file)
{
	int	i;
	char ***cmd;
	int	j;

	cmd = malloc((ac -3) * sizeof(char **));
	j = 0;
	i = 2;
	while (i < (ac - 1))
		cmd[j++] = ft_split(av[i++], ' ');
	do_the_cmd(cmd, file, ac);
}

int main(int ac, char **av)
{ 
	t_file file;

	file.in_fd = 0;
	if (ac < 5)
		error();
	check_files(ac, av, &file);
	take_cmd (ac, av, &file);
} 
