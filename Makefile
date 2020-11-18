# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksean <ksean@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/10 03:38:19 by ksean             #+#    #+#              #
#    Updated: 2020/11/18 22:23:51 by ksean            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = validation.c validation2.c validation3.c functions_free.c init_ways.c \
		addapt_vector.c addapt_vector2.c find_or_insert.c \
			init_node.c main.c solve.c sort_vector.c get_emplace_vector.c push_pop_vector.c \
				init_free_vector.c insert_sort_vector.c error.c parse_map.c cross_group.c \
				    get_ant_step.c work_with_way.c write_ants_path.c

BIN = lem-in
OBJ = $(SRC:.c=.o)
# INC = ./include
LIB = ./libft/libft.a
LIB_PATH = ./libft/

FLAGS = -Wall -Wextra -Werror -g

all: $(BIN)

$(BIN): $(LIB) $(OBJ) $(LIB_PATH)inc/libft.h $(LIB_PATH)src/*.c lem_in.h vector.h
		/usr/bin/gcc $(FLAGS) $(OBJ) -o $(BIN) $(LIB)

$(LIB): $(LIB_PATH)inc/libft.h $(LIB_PATH)src/*.c
		/usr/bin/make -C $(LIB_PATH)

$(OBJ): %.o: %.c
		/usr/bin/gcc $(FLAGS) -I ./ -I $(LIB_PATH) -o $@ -c $^

clean:
		/bin/rm -rf $(OBJ)
		/usr/bin/make clean -C $(LIB_PATH)

fclean: clean
		/bin/rm -rf $(BIN)
		/usr/bin/make fclean -C $(LIB_PATH)

re: fclean all
