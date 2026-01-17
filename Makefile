CC	:= cc
FLAGS	:= -Wall -Wextra -Werror -Ilibft

NAME	:= minishell

UDIR	:= utils
CDIR	:= $(UDIR)/commands
EDIR	:= $(UDIR)/errors

UTILS	:= $(UDIR)/input_utils.c \
		 $(UDIR)/input_utils2.c \
		 $(UDIR)/list_utils.c \
		 $(UDIR)/list_ops.c \
		 $(UDIR)/expand.c \
		 $(UDIR)/expand_utils.c \
	   $(UDIR)/sig_handlers.c \
	   $(UDIR)/string_utils.c \
	   $(UDIR)/string_utils2.c \
	   $(UDIR)/exit_handler.c \
	   $(UDIR)/parse.c \
	   $(UDIR)/parse_redir.c
COMMANDS:= $(CDIR)/cd.c \
	   $(CDIR)/pwd.c \
	   $(CDIR)/env.c \
	   $(CDIR)/unset.c \
	   $(CDIR)/export.c \
	   $(CDIR)/echo.c \
	   $(CDIR)/exec_main.c \
	   $(CDIR)/exec_utils.c \
	   $(CDIR)/exec_redir.c \
	   $(CDIR)/exec_builtin.c \
	   $(CDIR)/exec_pipe.c \
	   $(CDIR)/exec_pipe2.c \
	   $(CDIR)/exec_pipe3.c
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
