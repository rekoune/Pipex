#include "pipex.h"

int main ()
{
	int fd[2];
	char *cmd[] = {"cat", NULL};
	char *cmd2[] = {"wc -l", NULL};
	int fj = open("hona.txt", O_RDWR | O_CREAT, 0777);
	
	pipe(fd);
	pid_t pid[2];

	if (fork() == 0)
	{
		pid[0] = getpid();
		printf("%d]\n", pid[0]);
		dup2(fj, 0);
		close(fj);
		dup2(fd[1], 1);
		close (fd[1]);
		
		execve("/bin/cat", cmd, NULL);
	}
		
	// char g[100];
	// read(fd[0], g, 100);
	// printf("%s", g);
	// wait(NULL);
	if (fork() == 0)
	{
		//dup2(fd[1], 1);
		close(fd[1]);
		dup2(fd[0], 0);
		pid[1] = getpid();
		printf("hona\n");
		printf("%d]\n", pid[1]);
		execve("/usr/bin/wc", cmd2, NULL);
	}
	printf(">> %d\n", pid[0]);
	printf(">> %d\n", pid[1]);
	// wait(NULL);




	// int fd;
	// int fd2;
	// char *test[] = {"wc", "-l", NULL};
	// fd = open("text.txt", O_RDWR | O_TRUNC);
	// fd2 = open("text2.txt", O_RDWR);
	// if (ac > 1)
	// {
	// 	if (fork() == 0)
	// 	{
	// 		dup2(fd, 1);
	// 		execve("/bin/ls", &av[1], NULL);
	// 	}
	// 	wait(NULL);
	// 	lseek(fd, 0, SEEK_SET);
	// 	if (fork() == 0)
	// 	{
	// 		dup2(fd, 0);
	// 		dup2(fd2, 1);
	// 		execve("/usr/bin/wc", test, NULL);
	// 	}
	// }	
}