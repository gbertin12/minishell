CC=cc
CFLAGS= -Wall -Wextra -Werror
NAME=libft.a
SRC=ft_atoi.c\
	ft_bzero.c\
	ft_calloc.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_itoa.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memset.c\
	ft_putchar_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_putstr_fd.c\
	ft_split_set.c\
	ft_split.c\
	ft_strchr.c\
	ft_strdup.c\
	ft_striteri.c\
	ft_strjoin.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_strmapi.c\
	ft_strncmp.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_strtrim.c\
	ft_substr.c\
	ft_tolower.c\
	ft_toupper.c

DEPENDS := $(patsubst %.c,%.d,$(SRC))
OBJ= $(SRC:.c=.o)
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

TITLE= "$(PURPLE)ᐅ $(YELLOW)Compiling $(RED)libft$(YELLOW)...$(RESET)"
.SILENT:

all : title $(NAME)

$(NAME) : $(OBJ)
	ar -cq $(NAME) $(OBJ)

-include $(DEPENDS)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -MMD -MP -o $@ -c $< 

fclean : clean
	rm -rf $(NAME)

clean : cleaning
	rm -rf $(OBJ)
	rm -rf $(DEPENDS)

re : fclean all

title:
	echo $(TITLE)



cleaning:
	echo "$(PURPLE)ᐅ $(YELLOW)Cleaning $(RED)libft$(YELLOW)...$(RESET)"

mrproper: clean
	rm -rf $(NAME)

.PHONY: $(NAME)

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRC)
	gcc -nostartfiles -shared -o libft.so $(OBJ)
