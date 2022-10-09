# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 11:58:42 by lde-alen          #+#    #+#              #
#    Updated: 2022/10/09 14:15:32 by asanthos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

SRCS		=		minishell.c					\
					main.c						\

BUILTINS	=		ft_env.c					\
					ft_echo.c					\
					ft_cd.c						\
					ft_exit.c					\
					ft_export.c					\
					ft_pwd.c					\
					ft_unset.c					\

TOKENS		=		pipe.c						\
					redirect.c					\
					exec_check.c				\
					exec_pipe.c					\

UTILS		=		len.c						\
					env_utils.c					\
					exec_utils.c				\
					export_utils.c				\
					redirect_utils.c			\
					exec.c						\
					ft_init.c					\
					expand.c					\
					cmd_list.c					\
					ft_free.c					\
					error.c						\
					ft_print.c					\
					ft_utils.c					\
					f_open.c					\
					add_utils.c					\
					type.c						\
					redir_flags.c				\
					free_utils.c				\
					sig.c						\

PARS		=		parser.c					\
					parser_fill.c				\
					parser_check_p.c			\
					parser_check_quotes.c		\
					parser_check_redirection.c	\
					parser_init.c				\
					parser_expand.c				\
					parser_fill_expand.c		\
					parser_fill_quotes.c		\
					parser_fill_redirections.c	\


SRCS_OBJ	=		$(addprefix $(SRCS_DIR),$(SRCS:.c=.o))

EXPAN_OBJ	=		$(addprefix $(SRCS_DIR)$(EXPAN_DIR),$(EXPAN:.c=.o))

BUILT_OBJ	=		$(addprefix $(SRCS_DIR)$(BUILT_DIR),$(BUILTINS:.c=.o))

TOKEN_OBJ	=		$(addprefix $(SRCS_DIR)$(TOKEN_DIR),$(TOKENS:.c=.o))

UTILS_OBJ	=		$(addprefix $(SRCS_DIR)$(UTILS_DIR),$(UTILS:.c=.o))

PARS_OBJ	=		$(addprefix $(SRCS_DIR)$(PARS_DIR),$(PARS:.c=.o))

OBJS		=		$(SRCS_OBJ) $(EXPAN_OBJ) $(BUILT_OBJ) $(TOKEN_OBJ) $(UTILS_OBJ) $(PARS_OBJ) 

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

make v		:		re
					valgrind --leak-check=full --show-leak-kinds=all --suppressions=file.sup ./minishell

re			:		fclean all

.PHONY		:		all bonus clean fclean re