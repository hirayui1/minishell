CC	:= cc
CFLAGS	:= -Wall -Wextra -Werror -D BUFFER_SIZE=10

NAME	:= gnl.out

SRCS	:= get_next_line.c \
	get_next_line_utils.c \

OBJS	:= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=10 $(SRCS) -o $(NAME)
	@valgrind ./$(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
