# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aichida <aichida@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 17:26:28 by aichida           #+#    #+#              #
#    Updated: 2024/06/28 05:55:35 by aichida          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client

SERVER_SRCS = srcs/server.c
CLIENT_SRCS = srcs/client.c
UTILS_SRCS = srcs/utils.c

CC = cc
CFLAGS = -Wall -Wextra -Werror 

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_SRCS) $(UTILS_SRCS)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT): $(CLIENT_SRCS) $(UTILS_SRCS)
	$(CC) $(CFLAGS) -o $@ $^

# not necessary
clean:
	@rm -rf *o

fclean: clean
	@rm -rf $(UTILS) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
