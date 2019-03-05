# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgorold- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/22 10:09:18 by dgorold-          #+#    #+#              #
#    Updated: 2019/02/22 10:13:01 by dgorold-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
FILES = main.c
OBJ = *.o

all: $(NAME)

$(NAME): $(OBJ)
	gcc -g -c -Wall -Wextra -Werror $(FILES) -I header.h
	gcc $(OBJ) -o $(NAME)

%.o: %.c header.h
	gcc -g -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
