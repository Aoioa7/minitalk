CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = libft/libft.a
LIBFT_SRC = $(shell find libft -name '*.c')
LIBFT_OBJ = $(LIBFT_SRC:.c=.o)
SERVER = server
CLIENT = client
SERVER_SRC = server.c
CLIENT_SRC = client.c

all: $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT): $(LIBFT_OBJ)
	ar rcs $@ $^

$(SERVER): $(SERVER_SRC) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT): $(CLIENT_SRC) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(LIBFT_OBJ)

fclean: clean
	rm -f $(LIBFT) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re