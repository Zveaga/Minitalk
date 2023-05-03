NAME = libftprintf.a

SRC = \
ft_print_ch_str.c \
ft_print_d_i.c \
ft_print_hex.c \
ft_print_ptr.c \
ft_print_u.c \
ft_printf.c \

OBJ_FILES = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

CC = cc

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar rcs $(NAME) $(OBJ_FILES)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean re fclean all
