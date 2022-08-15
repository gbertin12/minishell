# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/15 12:27:27 by gbertin           #+#    #+#              #
#    Updated: 2022/08/15 13:41:18 by gbertin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -f
LIBFT_PATH = libft/
SRCS = minishell.c 

HEAD = includes/minishell.h

OBJ=$(SRCS:.c=.o)

all: $(NAME)

%.o: %.c $(HEAD)
			$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

$(NAME):$(OBJ)
			$(MAKE) -C $(LIBFT_PATH)
			$(CC) $(FLAGS) -o $(NAME) $(OBJ) -lm libft/libft.a

clean: 
			$(MAKE) clean -C $(LIBFT_PATH)
			$(RM) $(OBJ)

fclean: clean
			$(MAKE) clean -C $(LIBFT_PATH)
			$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re