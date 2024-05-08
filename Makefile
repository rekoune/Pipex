CFILES = pipex.c split_cmd.c utils.c utils2.c get_next_line.c get_next_line_utils.c here_doc.c
OFILES = $(CFILES:.c=.o)

CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g
CC = cc 

NAME = pipex
HEADER = pipex.h

all : $(NAME)

$(NAME) : $(OFILES) $(HEADER)
	$(CC) $(CFLAGS)  $(OFILES) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OFILES)

fclean: clean
	rm -rf $(NAME)

bonus: all

re: fclean all

.PHONY : all clean fclean re