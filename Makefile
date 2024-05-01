CFILES = pipex.c split_cmd.c utils.c utils2.c
CFLAGS = -Wall -Werror -Wextra
CC = cc 
NAME = pipex

all : $(NAME)

$(NAME) : $(CFILES)
	$(CC) $(CFLAGS) $(CFILES) -o $(NAME)

clean:

fclean: 

out : 
	./pipex "ls"