# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 11:58:42 by lde-alen          #+#    #+#              #
#    Updated: 2022/05/17 15:30:57 by lde-alen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		minishell

LIBFT_NAME	=		libft.a
LIBFT_DIR	=		./Libft

SRCS_DIR	=		./srcs/

SRCS		=		main.c	\

OBJS		=		$(addprefix $(SRCS_DIR),$(SRCS:.c=.o))

OBJS_DIR_N	=		objs

OBJS_DIR	=		./objs

RM			=		rm -f

CP			=		cp

CFLAGS		+=		-Wall -Wextra -Werror -g3

INCLUDES	+=		-I./includes/

CC			=		gcc

.c.o		:
					$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(LIBFT_C)	:
					$(MAKE) -C ./Libft
					$(CP) $(LIBFT_DIR)/libft.h ./includes/

$(NAME)		:		$(OBJS)
					$(CC) $(FLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFT_NAME) $(INCLUDES) -o $(NAME)
					mkdir -p $(OBJS_DIR_N)
					mv $(OBJS) $(OBJS_DIR)

all			:		$(LIBFT_C)$(NAME)

clean		:
					$(MAKE) clean -C $(LIBFT_DIR)
					$(RM) -r $(OBJS_DIR)/


fclean		:		clean
					$(MAKE) fclean -C $(LIBFT_DIR)
					$(RM) $(NAME)
					$(RM) $(LIBFT_DIR)/$(LIBFT_NAME)

re			:		fclean all

.PHONY		:		all bonus clean fclean re
