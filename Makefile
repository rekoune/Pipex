CFILES = pipex.c split_cmd.c utils.c
CFLAGS = -Wall -Werror -Wextra
CC = cc 
NAME = pipex

all : $(NAME)

$(NAME) : $(CFILES)
	$(CC) $(CFLAGS) -fsanitize=address -g $(CFILES) -o $(NAME)

out : 
	./pipex "ls"