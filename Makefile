# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 11:58:42 by lde-alen          #+#    #+#              #
#    Updated: 2022/05/25 14:11:05 by asanthos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		minishell

LIBFT_NAME	=		libft.a
LIBFT_DIR	=		./Libft

SRCS_DIR	=		./srcs/

SRCS		=		main.c		\
					prompt.c	\

OBJS		=		$(addprefix $(SRCS_DIR),$(SRCS:.c=.o))

OBJS_DIR_N	=		objs

OBJS_DIR	=		./objs

RM			=		rm -f

CP			=		cp

CFLAGS		+=		-Wall -Wextra -Werror -g3

RFLAGS		+=		-lreadline

INCLUDES	+=		-I./includes/

CC			=		gcc

.c.o		:
					$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(LIBFT_C)	:		$(MAKE) -C ./Libft
					$(CP) $(LIBFT_DIR)/libft.h ./includes/

$(NAME)		:		$(OBJS)
					$(MAKE) -C ./Libft
					$(CC) $(CFLAGS) $(RFLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFT_NAME) $(INCLUDES) -o $(NAME)
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
