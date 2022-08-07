# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 11:58:42 by lde-alen          #+#    #+#              #
#    Updated: 2022/08/07 00:19:03 by lde-alen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		minishell

LIBFT_NAME	=		libft.a

LIBFT_DIR	=		./Libft

SRCS_DIR	=		./srcs/

BUILT_DIR	=		builtins/

TOKEN_DIR	=		tokens/

PARS_DIR	=		parser/

MINI_BIN	=		miniswag_bin/

UTILS_DIR	=		utils/

SRCS		=		prompt.c					\
					minishell.c					\
					main.c						\

BUILTINS	=

TOKENS		=

UTILS		=		ft_print.c					\

PARS		=		parser.c					\
					parser_fill.c				\
					parser_check_p.c			\
					parser_check_quotes.c		\
					parser_check_redirection.c	\
					parser_init.c				\


SRCS_OBJ	=		$(addprefix $(SRCS_DIR),$(SRCS:.c=.o))

BUILT_OBJ	=		$(addprefix $(SRCS_DIR)$(BUILT_DIR),$(BUILTINS:.c=.o))

TOKEN_OBJ	=		$(addprefix $(SRCS_DIR)$(TOKEN_DIR),$(TOKENS:.c=.o))

UTILS_OBJ	=		$(addprefix $(SRCS_DIR)$(UTILS_DIR),$(UTILS:.c=.o))

PARS_OBJ	=		$(addprefix $(SRCS_DIR)$(PARS_DIR),$(PARS:.c=.o))

OBJS		=		$(SRCS_OBJ) $(BUILT_OBJ) $(TOKEN_OBJ) $(UTILS_OBJ) $(PARS_OBJ)

OBJS_DIR_N	=		objs

OBJS_DIR	=		./objs

RM			=		rm -rf

CP			=		cp

CFLAGS		+=		-Wall -Wextra -Werror -g3
	
RFLAGS		+=		-lreadline -I/usr/local/Cellar/readline/8.1/include

INCLUDES	+=		-I./includes

CC			=		gcc

.c.o		:
					$(CC) $(CFLAGS) -I/usr/local/Cellar/readline/8.1/include $(INCLUDES) -c $< -o $(<:.c=.o)

$(LIBFT_C)	:		$(MAKE) -C ./Libft
					$(CP) $(LIBFT_DIR)/libft.h ./includes/

$(NAME)		:		$(OBJS)
					$(MAKE) -C ./Libft
					$(CC) $(CFLAGS) $(RFLAGS) -L/usr/local/Cellar/readline/8.1/lib  $(OBJS) $(LIBFT_DIR)/$(LIBFT_NAME) -o $(NAME)
					mkdir -p $(OBJS_DIR_N)
					mv $(OBJS) $(OBJS_DIR)

all			:		$(NAME)

clean		:
					$(RM) $(OBJS_DIR)/$(OBJS)
					$(MAKE) clean -C $(LIBFT_DIR)


fclean		:		clean
					$(RM) $(NAME)
					$(RM) $(LIBFT_DIR)/$(LIBFT_NAME)
					$(MAKE) fclean -C $(LIBFT_DIR)


re			:		fclean all

.PHONY		:		all bonus clean fclean re
