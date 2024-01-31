# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrontey <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 15:55:16 by nrontey           #+#    #+#              #
#    Updated: 2023/11/02 14:27:23 by nrontey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =                 libft.a 
CC =                 gcc
CFLAGS =             -Wall -Wextra -Werror -g
HEA_PATH =             .
HEA_NAME =             libft.h
HEA =                 $(addprefix $(HEA_PATH)/,$(HEA_NAME))
SRC_PATH =             .
SRC_NAME =             ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c
SRC =                 $(addprefix $(SRC_PATH)/,$(SRC_NAME))        
OBJ_PATH =             .
OBJ_NAME =             $(SRC_NAME:.c=.o)
OBJ =                 $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
BONUS_OBJ = $(BONUS:.c=.o)

all: $(NAME)

$(NAME):$(OBJ) 
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "Libft compilation complete."

%.o:	%.c $(HEA)
	@$(CC) $(CFLAGS) -c $< -o $@ 
	
bonus: $(OBJ) $(BONUS_OBJ)
	ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)
	@echo "Libft compilation complete with bonus."

clean:
	@rm -rf $(OBJ) $(BONUS_OBJ)
	@echo "Object files deleted." 

fclean:	clean
	@rm -rf $(NAME) 
	@echo "Executable deleted." 

re:	fclean all

.PHONY:	all clean fclean re
