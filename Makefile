# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/15 12:27:27 by gbertin           #+#    #+#              #
#    Updated: 2022/09/23 10:14:36 by gbertin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = clang
FLAGS = -Wall -Wextra -Werror -g -I /opt/homebrew/opt/readline/include
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
		sources/expand/expand_cmd.c\
		sources/expand/heredoc_expand.c\
		sources/expand/read_var.c\
		sources/expand/replace_var.c\
		sources/open/check_ambiguous.c\
		sources/open/complex_var.c\
		sources/open/expand_file.c\
		sources/open/expand_simple_var.c\
		sources/open/heredoc.c \
		sources/open/if_type_file_exist.c\
		sources/open/open_files.c \
		sources/open/open_all.c \
		sources/open/print_err_files.c\
		sources/open/replace_value_key.c\
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
		sources/utils/free_split.c\
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

DEPENDS := $(patsubst %.c,%.d,$(SRCS))
OBJ=$(SRCS:.c=.o)

ifneq (,$(findstring xterm,${TERM}))
	BLACK        := $(shell tput -Txterm setaf 0)
	RED          := $(shell tput -Txterm setaf 1)
	GREEN        := $(shell tput -Txterm setaf 2)
	YELLOW       := $(shell tput -Txterm setaf 3)
	LIGHTPURPLE  := $(shell tput -Txterm setaf 4)
	PURPLE       := $(shell tput -Txterm setaf 5)
	BLUE         := $(shell tput -Txterm setaf 6)
	WHITE        := $(shell tput -Txterm setaf 7)
	RESET := $(shell tput -Txterm sgr0)
else
	BLACK        := ""
	RED          := ""
	GREEN        := ""
	YELLOW       := ""
	LIGHTPURPLE  := ""
	PURPLE       := ""
	BLUE         := ""
	WHITE        := ""
	RESET        := ""
endif

TITLE = "\n $(BLUE)███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██     \n"\
		"$(BLUE)████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██  \n"\
		"$(BLUE)██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██      \n"\
		"$(BLUE)██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██      \n"\
		"$(BLUE)██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████\n"\
        "\n\n $(PURPLE)ᐅ $(YELLOW)Making something like $(GREEN)$(NAME) $(YELLOW)or a shitty thing $(RED)(╯°□°)╯︵ ┻━┻ $(RESET)\n\n"                                                   


.SILENT:

all: title depending $(NAME)

-include $(DEPENDS)

%.o: %.c Makefile
			$(CC) $(FLAGS) -MMD -MP -c $< -o $@

$(NAME): compiling $(OBJ) 
			$(MAKE) -C $(LIBFT_PATH)
			$(CC) $(FLAGS) $(OBJ) -o $@ -lm $(LIBFT_PATH)/libft.a -lreadline -L /opt/homebrew/opt/readline/lib
			
malloc_test: $(OBJ)
			$(MAKE) -C $(LIBFT_PATH)
			$(CC) $(FLAGS) -fsanitize=undefined -rdynamic -o $@ $(OBJ) -lreadline $(LIBFT_PATH)/libft.a -lm -lmallocator -L.
	
clean: cleaning
			$(MAKE) clean -C $(LIBFT_PATH)
			$(RM) $(OBJ) $(DEPENDS)

fclean: cleaning
			$(MAKE) fclean -C $(LIBFT_PATH)
			$(RM) $(OBJ) $(DEPENDS)
			$(RM) $(NAME)

clear:
			clear

title: clear
			echo $(TITLE)

compiling:
			echo "$(PURPLE)ᐅ $(YELLOW)Compiling ...$(RESET)"

depending:
			echo "$(PURPLE)ᐅ $(YELLOW)Generating dependencies ...$(RESET)"

re: fclean all

cleaning:
			echo "$(PURPLE)ᐅ $(YELLOW)Cleaning ...$(RESET)"

.PHONY: clean fclean all re $(NAME)
