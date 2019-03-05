# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/22 13:09:48 by dgorold-          #+#    #+#              #
#    Updated: 2019/01/14 18:42:06 by dgorold-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror
FILES = *.c
OBJ = ft_*.o

all: $(NAME)

$(NAME):
			gcc -g -c $(FLAGS) $(FILES) -I /includes
			ar rc $(NAME) $(OBJ)
			ranlib $(NAME)

clean:
			rm -rf $(OBJ)

fclean:	clean
			rm -rf $(NAME)

re:	fclean all


