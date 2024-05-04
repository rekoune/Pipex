// #include "pipex.h"

// int main ()
// {
// 	// int fd[2];
// 	// char *cmd[] = {"adf", NULL};
// 	// char *cmd2[] = {"asdf", NULL};
// 	// int fj = open("hona.txt", O_RDWR | O_CREAT, 0777);
	
// 	// pipe(fd);
// 	// pid_t pid[2];

// 	// if (fork() == 0)
// 	// {
// 	// 	pid[0] = getpid();
// 	// 	dup2(fj, 0);
// 	// 	close(fj);
// 	// 	dup2(fd[1], 1);
// 	// 	close (fd[1]);
		
// 	// 	execve("/bin/cat", cmd, NULL);
// 	// }
// 	// // if (access("/usr/bin/DF", W_OK) == -1)
// 	// // 	perror("access : ");
// 	// if (fork() == 0)
// 	// {
// 	// 	//dup2(fd[1], 1);
// 	// 	close(fd[1]);
// 	// 	dup2(fd[0], 0);
// 	// 	pid[1] = getpid();
// 	// 	execve("/usr", cmd2, NULL);
// 	// 	perror("hona: ");
// 	// }

// 	int fd = open("hona", O_CREAT | O_RDWR , 0777);
// 	char str[10];

// 	close(fd);
// 	read(fd, str, 9);
// 	printf("%s\n", str);
// 	printf("%d\n", fd);
// }