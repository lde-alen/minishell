# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 11:58:42 by lde-alen          #+#    #+#              #
#    Updated: 2022/09/11 03:06:23 by lde-alen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME		:= $(shell uname)

NAME		=		minishell

LIBFT_NAME	=		libft.a

LIBFT_DIR	=		./Libft

SRCS_DIR	=		./srcs/

BUILT_DIR	=		builtins/

TOKEN_DIR	=		tokens/

PARS_DIR	=		parser/

UTILS_DIR	=		utils/

EXPAN_DIR	=		expansion/

EXPAN		=		expansion.c					\

SRCS		=		prompt.c					\
					minishell.c					\
					main.c						\

BUILTINS	=		ft_env.c					\

TOKENS		=

UTILS		=		ft_print.c					\
					ft_utils.c					\

PARS		=		parser.c					\
					parser_fill.c				\
					parser_check_p.c			\
					parser_check_quotes.c		\
					parser_check_redirection.c	\
					parser_init.c				\
					env.c						\
					parser_expand.c				\
					parser_fill_expand.c		\
					parser_fill_quotes.c		\
					parser_fill_redirections.c	\


SRCS_OBJ	=		$(addprefix $(SRCS_DIR),$(SRCS:.c=.o))

EXPAN_OBJ	=		$(addprefix $(SRCS_DIR)$(EXPAN_DIR),$(EXPAN:.c=.o))

SRCS_OBJ	=		$(addprefix $(SRCS_DIR),$(SRCS:.c=.o))

BUILT_OBJ	=		$(addprefix $(SRCS_DIR)$(BUILT_DIR),$(BUILTINS:.c=.o))

TOKEN_OBJ	=		$(addprefix $(SRCS_DIR)$(TOKEN_DIR),$(TOKENS:.c=.o))

UTILS_OBJ	=		$(addprefix $(SRCS_DIR)$(UTILS_DIR),$(UTILS:.c=.o))

PARS_OBJ	=		$(addprefix $(SRCS_DIR)$(PARS_DIR),$(PARS:.c=.o))

OBJS		=		$(SRCS_OBJ) $(EXPAN_OBJ) $(BUILT_OBJ) $(TOKEN_OBJ) $(UTILS_OBJ) $(PARS_OBJ) 

OBJS_DIR_N	=		objs

OBJS_DIR	=		./objs

RM			=		rm -rf

CP			=		cp

CFLAGS		+=		-Wall -Wextra -Werror -g3
	
RFLAGS		+=		-I/usr/local/Cellar/readline/8.1/include

LDFLAGS 	=		-lreadline -L /usr/local/Cellar/readline/8.1/lib/

INCLUDES	+=		-I./includes

CC			=		gcc

.c.o		:
					$(CC) $(CFLAGS) $(RFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

$(LIBFT_C)	:		$(MAKE) -C ./Libft
					$(CP) $(LIBFT_DIR)/libft.h ./includes/

$(NAME)		:		$(OBJS)
					$(MAKE) -C ./Libft
					$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBFT_DIR)/$(LIBFT_NAME) -o $(NAME)

all			:		$(NAME)

clean		:
					$(RM) $(OBJS)
					$(MAKE) clean -C $(LIBFT_DIR)


fclean		:		clean
					$(RM) $(NAME)
					$(RM) $(LIBFT_DIR)/$(LIBFT_NAME)
					$(MAKE) fclean -C $(LIBFT_DIR)

make v		:		all clean
					valgrind --leak-check=full --show-leak-kinds=all --suppressions=file.sup ./minishell

re			:		fclean all

.PHONY		:		all bonus clean fclean re
