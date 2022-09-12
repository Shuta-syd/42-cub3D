# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/07 15:22:14 by shogura           #+#    #+#              #
#    Updated: 2022/09/10 18:24:31 by shogura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c\
			 ft_isprint.c ft_itoa.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c\
			 ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c\
			 ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_split.c ft_strchr.c\
			 ft_strcmp.c ft_strcpy.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strcat.c\
			 ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnew.c\
			 ft_strnstr.c ft_strrchr.c ft_strstr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c\
			 ft_strchr_rev.c ft_strnlen.c gnl/get_next_line.c

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
				 ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS_M = ${SRCS:.c=.o}

OBJS_B = ${BONUS:.c=.o} ${SRCS:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror

NR = norminette -R CheckForbiddenSourceHeader

ifdef BONUS_FLAG
	OBJS = ${OBJS_B}
else
	OBJS = ${OBJS_M}
endif

all: ${NAME}

${NAME}: ${OBJS}
	@ar cr $@ $^

.o:.c
	@${CC} ${CFLAGS} -c $< $@

bonus:
	@make BONUS_FLAG=1 all

xx: ${SRCS} ${BONUS}
	@${CC} $^

nr: ${SRCS} ${BONUS}
	${NR} $^

clean:
	rm -f ${OBJS_M} ${OBJS_B}

fclean: clean
	rm -rf ${NAME}

re: fclean all
