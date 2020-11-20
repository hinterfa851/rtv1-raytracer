# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glychest <glychest@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 06:44:55 by glychest          #+#    #+#              #
#    Updated: 2020/11/20 16:18:19 by hinterfa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

SRC_DIR		:= 	sources/main \
 				sources/parser \
 				sources/algos \

SRC			:=	sources/main/main.c \
              	sources/parser/error.c \
              	sources/parser/hook.c \
              	sources/parser/init.c \
              	sources/parser/light.c \
              	sources/parser/object.c \
              	sources/parser/parse.c \
              	sources/parser/read.c \
              	sources/parser/utils.c \
              	sources/algos/cone.c \
				sources/algos/cylinder.c \
				sources/algos/helpers.c \
				sources/algos/normals.c \
				sources/algos/plane.c \
				sources/algos/sphere.c \
				sources/algos/rotation.c \
				sources/algos/small_func.c \
				sources/algos/render.c \
				
FLAGS			=	-Wall -Werror -Wextra
framework		=	-L minilibx_macos -lmlx -framework OpenCL -framework OpenGL -framework AppKit -L libft -lft -O2
OBJECTS			=	$(notdir $(patsubst %.c,%.o, $(wildcard $(SRC))))
LIB_DIR			=	./libft/
LIB_OBJS		=	$(addprefix $(LIB_DIR), $(LIB_OBJ))
LIB_OBJ			=	*.o
RT_INC			=	includes/rtv1.h
LIB_INC			=	libft/libft.h
LIB_MLX_FILE	=	minilibx_macos/libmlx.a

all: $(NAME)

$(NAME): $(LIB_OBJS) $(LIB_MLX_FILE) $(OBJECTS)
	gcc $(OBJECTS) -o $@ $(framework)

VPATH := $(SRC_DIR)

$(LIB_MLX_FILE):
	make -C minilibx_macos

$(LIB_DIR)%.o: $(LIB_DIR)%.c $(LIB_INC) libft/Makefile
	make -C $(LIB_DIR)

%.o: %.c $(RT_INC) Makefile
	gcc $(FLAGS) -c $< -I include/

clean:
	make clean -C $(LIB_DIR)
	make clean -C minilibx_macos
	rm -rf *.o

fclean: clean
	make fclean -C $(LIB_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
