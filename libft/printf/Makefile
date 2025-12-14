CC      := cc
FLAGS   := -Wall -Wextra -Werror -I./includes

NAME    := libftprintf.a

SRCS    := ft_printf.c \
           ft_hexadec.c \
           ft_int_putstr_fd.c \
           ft_unsigned_itoa.c \
           ft_voidptr.c \
           ft_write.c

OBJS    := $(SRCS:.c=.o)
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	cp $(LIBFT) $(NAME)
	ar -qs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
