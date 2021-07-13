NAME		=	minishell

NAME_PIPEX	=	pipex

SRCS_FILES	= 		envp.c \
					envp_util.c \
					inicialise.c \
					lst_func.c \
					minishell.c \
					parsing.c \
					parsing_utils.c \
					run_pipes.c \
					run_command.c \
					redirects.c \
					dups.c \
					path_generator.c \
					raise_error.c \
					tests_func.c \

SRCS_PIPEX	= 		p_pipes.c \
					p_utils.c \
					p_raise_error.c \
					p_redirects.c

SRCS_COMMANDS =		exit.c \
					echo.c \
					env.c \
					pwd.c \
					unset.c \
					export.c \
					export_print.c
					

PARSING_DIR	=	parsing/
LOGIC_DIR	= 	logic/

SRCS		= 	$(addprefix $(PARSING_DIR),$(SRCS_FILES))
SRCS_P		= 	$(addprefix $(LOGIC_DIR),$(SRCS_PIPEX))
SRCS_C		= 	$(addprefix $(LOGIC_DIR),$(SRCS_COMMANDS))

OBJS		=	$(patsubst %.c,%.o,$(SRCS))
OBJS_P		=	$(patsubst %.c,%.o,$(SRCS_P))
OBJS_C		=	$(patsubst %.c,%.o,$(SRCS_C))

INCLUDE		=	-I./include -I./libs/libft/

CC			=	gcc
CFLAGS		=	-Wall -Wextra -MMD
RM			=	rm -f

LIB = ./libs/libft/libft.a
RDL = -lreadline


all:		$(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) -c -g $< -o $@ $(INCLUDE)
		
$(NAME):	$(OBJS) $(OBJS_C)
			$(MAKE) -C $(dir $(LIB))
			$(CC) $(INCLUDE) -o $(NAME) $(OBJS) $(OBJS_C) $(LIB)  $(RDL)

pipex:		$(OBJS_P)
			$(MAKE) -C $(dir $(LIB))
			$(CC) $(INCLUDE) -o $(NAME_PIPEX) $(OBJS_P)  $(LIB) $(RDL)

echo:		$(OBJS_C)
			$(MAKE) -C $(dir $(LIB))
			$(CC) $(INCLUDE) -o echo $(OBJS_C)  $(LIB) $(RDL)

clean:
			$(RM) $(OBJS) $(OBJS:.o=.d)
			$(RM) $(OBJS_P) $(OBJS_P:.o=.d)
			@make -C $(dir $(LIB)) clean

fclean:		clean
			@make -C $(dir $(LIB)) fclean
			$(RM) $(NAME) $(NAME_PIPEX)

re:			fclean all

.PHONY:		all clean fclean re bonus pipex
-include	$(OBJS:.o=.d)
-include	$(OBJS_P:.o=.d)
