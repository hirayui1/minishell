CC	:= cc
FLAGS	:= -Wall -Wextra -Werror -Ilibft
#TODO: -Iminishell
NAME	:= minishell

SDIR	:= src
UDIR	:= $(SDIR)/utils
CDIR	:= $(SDIR)/commands
EDIR	:= $(CDIR)/exec

UTILS	:= $(UDIR)/input_utils.c \
		 $(UDIR)/input_utils2.c \
		 $(UDIR)/list_utils.c \
		 $(UDIR)/list_ops.c \
		 $(UDIR)/expand.c \
		 $(UDIR)/expand_utils.c \
		 $(UDIR)/expand_utils2.c \
	   $(UDIR)/sig_handlers.c \
	   $(UDIR)/string_utils.c \
	   $(UDIR)/string_utils2.c
COMMANDS:= $(CDIR)/cd.c \
	   $(CDIR)/pwd.c \
	   $(CDIR)/env.c \
	   $(CDIR)/unset.c \
	   $(CDIR)/export.c \
	   $(CDIR)/echo.c
EXEC	:= $(EDIR)/exec_main.c \
	   $(EDIR)/exec_utils.c \
	   $(EDIR)/exec_redir.c \
	   $(EDIR)/exec_redir2.c \
	   $(EDIR)/exec_builtin.c \
	   $(EDIR)/exec_builtin2.c \
	   $(EDIR)/exec_pipe.c \
	   $(EDIR)/exec_pipe2.c \
	   $(EDIR)/exec_pipe3.c
SRCS	:= main.c \
		$(SDIR)/exit_handler.c \
		$(SDIR)/parse.c \
		$(SDIR)/parse_redir.c \
		$(SDIR)/parse_redir2.c \
	   $(UTILS) \
	   $(COMMANDS) \
	   $(EXEC) \
	   libft/libft.a

OBJS	:= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): makelibft $(SRCS)
	$(CC) $(FLAGS) $(SRCS) -lreadline -o $(NAME)

makelibft:
	$(MAKE) -C libft
