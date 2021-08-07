NAME		=	minishell

SRCS_FILES	= 	inicialise.c \
				minishell.c \
				raise_error.c \
				parsing/parsing.c \
				parsing/parsing_utils.c \
				parsing/tests_func.c \
				execute/run_pipes.c \
				execute/run_command.c \
				execute/redirects.c \
				execute/dups.c \
				execute/path_generator.c \
				builtins/exit.c \
				builtins/echo.c \
				builtins/env.c \
				builtins/pwd.c \
				builtins/unset.c \
				builtins/export/export.c \
				builtins/export/export_print.c \
				builtins/export/export_utils.c \
				builtins/cd/cd.c \
				builtins/cd/cd_utils.c \
				signals/sig_chaild.c \
				signals/signal.c \
				list_utils/lst_func.c \
				list_utils/envp.c \
				list_utils/envp_util.c \
				\
				bonus/logical_operator.c \
			

MAIN_DIR	=	source/

SRCS		= 	$(addprefix $(MAIN_DIR),$(SRCS_FILES))

OBJS		=	$(patsubst %.c,%.o,$(SRCS))

INCLUDE		=	-I./include -I./libs/libft/ -I ~/.brew/opt/readline/include

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -MMD
RM			=	rm -f

LIB			= ./libs/libft/libft.a
RDL			= -lreadline
RDL_MAC		= -lreadline -L ~/.brew/opt/readline/lib

all:		$(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) -c -g $< -o $@ $(INCLUDE)
		
$(NAME):	$(OBJS) $(OBJS_C)
			$(MAKE) -C $(dir $(LIB))
			$(CC) $(INCLUDE) -o $(NAME) $(OBJS) $(LIB) $(RDL_MAC)

bonus:		$(NAME)

clean:
			$(RM) $(OBJS) $(OBJS:.o=.d)
			@make -C $(dir $(LIB)) clean

fclean:		clean
			@make -C $(dir $(LIB)) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
-include	$(OBJS:.o=.d)
