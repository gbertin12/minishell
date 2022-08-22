# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/15 12:27:27 by gbertin           #+#    #+#              #
#    Updated: 2022/08/22 10:23:22 by gbertin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -g3
RM = rm -f
LIBFT_PATH = sources/libs/libft/
SRCS = minishell.c\
		sources/built-in/_cd.c\
		sources/built-in/_echo.c\
		sources/built-in/_env.c\
		sources/built-in/_export.c\
		sources/built-in/_pwd.c\
		sources/built-in/_unset.c\
		sources/check/check_files.c \
		sources/check/open_output.c \
 		sources/expand/expand.c\
		sources/expand/replace_var.c\
		sources/parsing/add_param.c\
		sources/parsing/parsing.c\
		sources/parsing/search_next_sep.c\
		sources/signals/signals.c\
		sources/utils/add_end_list.c\
		sources/utils/add_env_key_value.c\
		sources/utils/count_elem.c\
		sources/utils/do_env_key_exist.c\
		sources/utils/free_tokens.c\
		sources/utils/ft_malloc.c\
		sources/utils/ft_superjoin.c\
		sources/utils/get_env_value.c\
		sources/utils/init_minishell.c\
		sources/utils/is_space.c\
		sources/utils/list_to_tab.c\
		sources/utils/next_arg_parsing.c\
		sources/utils/replace_env_value.c\
		sources/copy_env.c

HEAD = includes/minishell.h

OBJ=$(SRCS:.c=.o)

all: $(NAME)

%.o: %.c $(HEAD)
			$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

$(NAME):$(OBJ)
			$(MAKE) -C $(LIBFT_PATH)
			$(CC) $(FLAGS) -o $(NAME) $(OBJ) -lm $(LIBFT_PATH)/libft.a -lreadline  -fsanitize=address -g3

clean: 
			$(MAKE) clean -C $(LIBFT_PATH)
			$(RM) $(OBJ)

fclean: clean
			$(MAKE) clean -C $(LIBFT_PATH)
			$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re
