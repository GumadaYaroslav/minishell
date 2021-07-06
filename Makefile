NAME		=	minishell

NAME_PIPEX	=	pipex

SRCS_FILES	= 		envp.c \
					envp_util.c \
					lst_func.c \
					minishell.c \
					parsing.c \
					raise_error.c \
					tests_func.c 

SRCS_PIPEX	= 		p_pipes.c \
					p_utils.c \
					p_raise_error.c \
					p_redirects.c

SRCS_COMMANDS =		exit.c

PARSING_DIR	=	parsing/
LOGIC_DIR	= 	logic/

SRCS		= 	$(addprefix $(PARSING_DIR),$(SRCS_FILES))
SRCS_P		= 	$(addprefix $(LOGIC_DIR),$(SRCS_PIPEX))
SRCS_C		= 	$(addprefix $(LOGIC_DIR),$(SRCS_COMMANDS))

OBJS		=	$(patsubst %.c,%.o,$(SRCS))
OBJS_P		=	$(patsubst %.c,%.o,$(SRCS_P))
OBJS_C		=	$(patsubst %.c,%.o,$(SRCS_C))

INCLUDE		=	-I./include -I./libs/libft/ -I./libs/readline/include/ -I./libs/readline/include/readline

CC			=	gcc
CFLAGS		=	-Wall -Wextra -MMD
# CFLAGS		=	-MMD
RM			=	rm -f

LIB = ./libs/libft/libft.a
# RDL = -L./libs/readline/lib/ -lreadline
RDL = -lreadline


all:		$(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) -c -g $< -o $@ $(INCLUDE)
		
$(NAME):	$(OBJS)
			$(MAKE) -C $(dir $(LIB))
			$(CC) $(INCLUDE) -o $(NAME) $(OBJS)  $(LIB)  $(RDL)

pipex:		$(OBJS_P)
			$(MAKE) -C $(dir $(LIB))
			$(CC) $(INCLUDE) -o $(NAME_PIPEX) $(OBJS_P)  $(LIB) $(RDL)

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
