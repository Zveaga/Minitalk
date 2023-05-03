SOURCES = server.c client.c
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: server client

bonus: server client

server: server.o libft printf
	$(CC) -o $@ $< -Llibft -lft -Lprintf -lftprintf

client: client.o libft printf
	$(CC) -o $@ $<  -Llibft -lft -Lprintf -lftprintf

%.o: %.c
	$(CC) -c $(CFLAGS) $?

libft:
	make -C libft

printf:
	make -C printf

clean:
	rm -f $(OBJECTS)
	make -C libft clean
	make -C printf clean
	
fclean: clean
	rm -f server client libft/libft.a printf/libftprintf.a

re: fclean all

.PHONY: all bonus libft printf clean fclean re