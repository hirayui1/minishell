CC	:= cc
FLAGS	:= -Wall -Wextra -Werror -Ilibft

NAME	:= minishell

UDIR	:= utils
CDIR	:= $(UDIR)/commands
EDIR	:= $(UDIR)/errors

UTILS	:= $(UDIR)/input_utils.c \
	   $(UDIR)/sig_handlers.c \
	   $(UDIR)/string_utils.c \
	   $(UDIR)/exit_handler.c
COMMANDS:= $(CDIR)/ls.c \
	   $(CDIR)/cd.c \
	   $(CDIR)/pwd.c \
	   $(CDIR)/env.c \
	   $(CDIR)/echo.c \
		 $(CDIR)/exec.c
ERRORS	:= $(EDIR)/error_prompt.c

SRCS	:= main.c \
	   $(UTILS) \
	   $(ERRORS) \
	   $(COMMANDS) \
	   libft/libft.a

OBJS	:= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): makelibft $(SRCS)
	$(CC) $(FLAGS) $(SRCS) -lreadline -o $(NAME)

makelibft:
	$(MAKE) -C libft
