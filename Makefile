# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 11:58:42 by lde-alen          #+#    #+#              #
#    Updated: 2022/09/11 17:12:51 by asanthos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		minishell

LIBFT_NAME	=		libft.a
LIBFT_DIR	=		./Libft

SRCS_DIR	=		./srcs/

BUILT_DIR	=		builtins/

TOKEN_DIR	=		tokens/

UTILS_DIR	=		utils/

SRCS		=		main.c				\
					prompt.c			\
					expand.c			\
					minishell.c			\
					cmd_list.c			\
					parser.c			\
					ft_free.c			\
					error.c				\
					execute.c			\
					ft_atol.c			\
					ft_ltoa.c			\

BUILTINS	=		ft_env.c			\
					ft_echo.c			\
					ft_cd.c				\
					ft_exit.c			\
					ft_export.c			\
					ft_pwd.c			\
					ft_unset.c			\

TOKENS		=		pipe.c				\
					redirect.c			\
					exec_check.c		\
					exec_pipe.c			\

UTILS		=		len.c				\
					print.c				\
					env_utils.c			\
					exec_utils.c		\
					export_utils.c		\
					redirect_utils.c	\
					exec.c				\
					ft_init.c			\

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

make v		:		fclean re
					valgrind --leak-check=full --show-leak-kinds=all --suppressions=file.sup ./minishell

re			:		fclean all

.PHONY		:		all bonus clean fclean re