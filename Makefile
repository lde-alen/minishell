# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 11:58:42 by lde-alen          #+#    #+#              #
#    Updated: 2022/07/30 06:43:48 by asanthos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		minishell

LIBFT_NAME	=		libft.a
LIBFT_DIR	=		./Libft

SRCS_DIR	=		./srcs/

BUILT_DIR	=		builtins/

TOKEN_DIR	=		tokens/

UTILS_DIR	=		utils/

SRCS		=		main.c		\
					prompt.c	\
					execute.c	\
					expand.c	\
					minishell.c	\
					cmd_list.c	\
					parser.c	\
					ft_free.c	\
					exec.c		\

BUILTINS	=		ft_env.c	\
					ft_echo.c	\
					ft_cd.c		\
					ft_exit.c	\
					ft_export.c	\
					ft_pwd.c	\
					ft_unset.c	\

TOKENS		=		pipe.c		\
					redirect.c	\

UTILS		=		len.c		\
					print.c		\

SRCS_OBJ	=		$(addprefix $(SRCS_DIR),$(SRCS:.c=.o))

BUILT_OBJ	=		$(addprefix $(SRCS_DIR)$(BUILT_DIR),$(BUILTINS:.c=.o))

TOKEN_OBJ	=		$(addprefix $(SRCS_DIR)$(TOKEN_DIR),$(TOKENS:.c=.o))

UTILS_OBJ	=		$(addprefix $(SRCS_DIR)$(UTILS_DIR),$(UTILS:.c=.o))

OBJS		=		$(SRCS_OBJ) $(BUILT_OBJ) $(TOKEN_OBJ) $(UTILS_OBJ)

OBJS_DIR_N	=		objs

OBJS_DIR	=		./objs

RM			=		rm -f

CP			=		cp

CFLAGS		+=		-Wall -Wextra -Werror -g3
	
RFLAGS		+=		-lreadline -I/usr/local/Cellar/readline/8.1/include

INCLUDES	+=		-I./includes/

CC			=		gcc

.c.o		:
					$(CC) $(CFLAGS) -I/usr/local/Cellar/readline/8.1/include -c $< -o $(<:.c=.o)

$(LIBFT_C)	:		$(MAKE) -C ./Libft
					$(CP) $(LIBFT_DIR)/libft.h ./includes/

$(NAME)		:		$(OBJS)
					$(MAKE) -C ./Libft
					$(CC) $(CFLAGS) $(RFLAGS) -L/usr/local/Cellar/readline/8.1/lib  $(OBJS) $(LIBFT_DIR)/$(LIBFT_NAME) $(INCLUDES) -o $(NAME)
					mkdir -p $(OBJS_DIR_N)
					mv $(OBJS) $(OBJS_DIR)

all			:		$(NAME)

clean		:
					$(MAKE) clean -C $(LIBFT_DIR)
					$(RM) -r $(OBJS_DIR)/


fclean		:		clean
					$(MAKE) fclean -C $(LIBFT_DIR)
					$(RM) $(NAME)
					$(RM) $(LIBFT_DIR)/$(LIBFT_NAME)


re			:		fclean all

.PHONY		:		all bonus clean fclean re
