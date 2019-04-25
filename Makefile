# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgorold- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/22 10:09:18 by dgorold-          #+#    #+#              #
#    Updated: 2019/03/27 14:28:45 by dgorold-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc

FLAGS=-Wall -Wextra -Werror
MLX_FINGS=-I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

NAME=fdf

ANOTH_L=./libft/
NAME_L=libft.a

PATH_SRC=./src/
FILES=main.c dda.c delete.c file_mlx.c file_spin.c get_next_line.c gradient.c reading_file.c validation.c
PR_FILES=$(addprefix $(PATH_SRC), $(FILES))

PATH_OBJ=./obj/
OBJ=$(patsubst %.c,%.o,$(FILES))
PR_OBJ=$(addprefix $(PATH_OBJ), $(OBJ))

COLOR=\x1b[33;02m

INC=./includes/

.PHONY: all

all: $(NAME)


$(NAME): create_obj make_lib $(PR_OBJ)
	@$(CC) $(FLAGS) $(MLX_FINGS) $(ANOTH_L)$(NAME_L) $(PR_OBJ) -I $(INC) -o $(NAME)


$(PATH_OBJ)%.o: $(PATH_SRC)%.c
	@echo "$(COLOR)"$<
	@$(CC) -c $(FLAGS) $< -o $@ -I $(INC)


make_lib:
	@echo "$(COLOR)"$<
	@make -C $(ANOTH_L)


create_obj:
	@mkdir -p $(PATH_OBJ)


clean_lib:
	@make -C $(ANOTH_L) clean


fclean_lib:
	@make -C $(ANOTH_L) fclean


clean:
	@rm -rf obj

fclean: clean
	@rm -f $(NAME)

re: fclean all
