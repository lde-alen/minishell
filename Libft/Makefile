# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/19 09:20:19 by lde-alen          #+#    #+#              #
#    Updated: 2022/05/17 12:42:11 by lde-alen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=	libft.a

OBJS_DIR_N	=	../objs/

SRCS		= 	ft_bzero.c				\
				ft_isalpha.c			\
				ft_isalnum.c			\
				ft_isascii.c 			\
				ft_isdigit.c 			\
				ft_isprint.c 			\
				ft_memcpy.c				\
				ft_memmove.c 			\
				ft_memset.c 			\
				ft_strlcat.c 			\
				ft_strlcpy.c 			\
				ft_strlen.c 			\
				ft_toupper.c			\
				ft_tolower.c 			\
				ft_strchr.c				\
				ft_strrchr.c			\
				ft_strncmp.c			\
				ft_memchr.c				\
				ft_memcmp.c				\
				ft_strnstr.c			\
				ft_atoi.c				\
				ft_calloc.c				\
				ft_strdup.c				\
				ft_substr.c				\
				ft_strjoin.c			\
				ft_strtrim.c			\
				ft_split.c				\
				ft_itoa.c				\
				ft_strmapi.c 			\
				ft_striteri.c 			\
				ft_putchar_fd.c 		\
				ft_putstr_fd.c			\
				ft_putendl_fd.c 		\
				ft_putnbr_fd.c			\
				ft_printf_putchar.c		\
				ft_putchar.c			\
				ft_putstr.c				\
				ft_printf_putstr.c		\
				ft_printf_hexa.c		\
				ft_printf_hexo.c		\
				ft_strlen_hex.c			\
				ft_asc_to_hex.c			\
				ft_printf_percentage.c	\
				ft_printf_ptr.c			\
				ft_printf_putnbr.c		\
				ft_printf_putnbr_u.c	\
				ft_putnbr_un_base.c		\
				ft_putnbr.c				\
				ft_printf.c				\
				ft_lstnew.c				\
				ft_lstadd_front.c		\
				ft_lstsize.c			\
				ft_lstlast.c			\
				ft_lstadd_back.c		\
				ft_lstdelone.c			\
				ft_lstclear.c			\
				ft_lstiter.c			\
				ft_lstmap.c				\

CC			=	gcc
LIB			=	ar rcs

OBJS		=	$(SRCS:.c=.o)

OBJS_B		=	$(SRCS_B:.c=.o)

CFLAGS		+= -Wall -Werror -Wextra -g3

$(NAME)		:	$(OBJS)
				$(LIB) $(NAME) $(OBJS)
				mkdir -p $(OBJS_DIR_N)
				mv $(OBJS) $(OBJS_DIR_N)

all			:	$(NAME)

clean		:
				rm -rf $(OBJS) $(OBJS_B)

fclean		:	clean
				rm -rf $(NAME)

re			:	fclean all

.PHONY		: all bonus clean fclean re
