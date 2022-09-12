# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shogura <shogura@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/09 20:13:30 by shogura           #+#    #+#              #
#    Updated: 2022/09/10 18:25:28 by shogura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
LDFLAGS	=	-Lmlx -lmlx_Darwin -Llibft
XFLAGS	=	-L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit
NAME	=	miniRT
SRCDIR	=	src
OBJDIR	=	obj
INCDIR	=	inc
LIBXDIR	=	mlx

SRCS	=	$(shell find $(SRCDIR) -name "*.c" -type f)
OBJS	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
IFLAGS	=	$(addprefix -I,$(INCDIR))

all: libx libft $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) $(IFLAGS) -o $(@) -c -g $(<)
	@echo "$(<)\n     \
	$(MGN)--->$(RES) \
	$(GRN)$(@)$(RES)"

$(NAME): $(OBJS)
	@$(CC) $(LDFLAGS) $(XFLAGS) -o $(NAME) $(OBJS)
	@echo "$(CYN)\n=====link=====$(RES)"
	@echo "$(YEL)Objects$(RES): $(OBJS)\n"
	@echo "$(YEL)Flags$(RES): $(CFLAGS) $(LDFLAGS) $(XFLAGS)\n"
	@echo "     $(MGN)--->$(RES) $(GRN)$(NAME)$(RES)"
	@echo "$(CYN)==============$(RES)"

libx:
	@make -C libft
	@make -C $(LIBXDIR)

clean:
	$(RM) -rf $(OBJDIR)
	@make clean -C mlx
	@make fclean -C libft

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all libx clean fclean re

RED = \033[31m
GRN = \033[32m
YEL = \033[33m
BLU = \033[34m
MGN = \033[35m
CYN = \033[36m
RES = \033[m
