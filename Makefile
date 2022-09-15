# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/15 12:27:27 by gbertin           #+#    #+#              #
#    Updated: 2022/09/15 08:55:28 by gbertin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = clang
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address -I /opt/homebrew/opt/readline/include
RM = rm -f
LIBFT_PATH = sources/libs/libft/
SRCS = minishell.c\
		sources/built-in/_cd.c\
		sources/built-in/_echo.c\
		sources/built-in/_env.c\
		sources/built-in/_exit.c\
		sources/built-in/_export.c\
		sources/built-in/_export2.c\
		sources/built-in/_export_exec.c \
		sources/built-in/_pwd.c\
		sources/built-in/_unset.c\
		sources/built-in/exec_built_in.c\
		sources/execute/browse_cmd.c \
		sources/execute/exec.c \
		sources/execute/get_path.c \
		sources/execute/redir.c \
		sources/execute/step_of_exec.c\
		sources/expand/between_quote.c \
		sources/expand/delete_quotes.c\
 		sources/expand/expand.c\
		sources/expand/expand_arg.c\
		sources/expand/heredoc_expand.c\
		sources/expand/read_var.c\
		sources/expand/replace_var.c\
		sources/open/check_ambiguous.c\
		sources/open/expand_file.c\
		sources/open/heredoc.c \
		sources/open/if_type_file_exist.c\
		sources/open/open_files.c \
		sources/open/open_all.c \
		sources/parsing/add_param.c\
		sources/parsing/check_input.c\
		sources/parsing/parsing.c\
		sources/parsing/search_next_sep.c\
		sources/prompt/get_prompt.c\
		sources/signals/signals.c\
		sources/utils/add_end_list.c\
		sources/utils/add_env_key_value.c\
		sources/utils/add_front.c\
		sources/utils/add_key_with_empty_value.c\
		sources/utils/check_is_directory.c\
		sources/utils/check_key_env.c \
		sources/utils/check_path.c\
		sources/utils/count_elem.c\
		sources/utils/create_error.c\
		sources/utils/do_env_key_exist.c\
		sources/utils/free_tokens.c\
		sources/utils/ft_atoll.c\
		sources/utils/ft_malloc.c\
		sources/utils/ft_strcmp.c\
		sources/utils/ft_superjoin.c\
		sources/utils/get_env_value.c\
		sources/utils/get_pwd.c\
		sources/utils/init_minishell.c\
		sources/utils/is_space.c\
		sources/utils/list_to_tab.c\
		sources/utils/modify_env.c\
		sources/utils/next_arg_parsing.c\
		sources/utils/replace_env_value.c\
		sources/utils/ternaries.c\
		sources/utils/token_is_empty.c\
		sources/copy_env.c

HEAD = includes/minishell.h

OBJ=$(SRCS:.c=.o)

all: $(NAME)

%.o: %.c $(HEAD)
			$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

$(NAME):$(OBJ)
			$(MAKE) -C $(LIBFT_PATH)
			$(CC) $(FLAGS) -o $(NAME) $(OBJ) -lm $(LIBFT_PATH)/libft.a -lreadline -L /opt/homebrew/opt/readline/lib
			
malloc_test: $(OBJ)
			$(MAKE) -C $(LIBFT_PATH)
			$(CC) $(FLAGS) -fsanitize=undefined -rdynamic -o $@ $(OBJ) -lreadline $(LIBFT_PATH)/libft.a -lm -lmallocator -L.
	
clean: 
			$(MAKE) clean -C $(LIBFT_PATH)
			$(RM) $(OBJ)

fclean: clean
			$(MAKE) fclean -C $(LIBFT_PATH)
			$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re
