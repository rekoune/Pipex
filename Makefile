CFILES = pipex.c split_cmd.c utils.c
CFLAGS = -Wall -Werror -Wextra
CC = cc 
NAME = pipex

all : $(NAME)

$(NAME) : $(CFILES)
	$(CC) $(CFLAGS) $(CFILES) -o $(NAME)

out : 
	./pipex "ls"