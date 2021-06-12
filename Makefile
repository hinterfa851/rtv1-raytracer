NAME = rtv1

framework		=	-L/usr/X11/lib -lmlx -lXext -lX11 -lpthread -lm -g

SRC = main.c test_drawing.c vector_functions.c	\
		parser/error.c	parser/hook.c parser/init.c parser/light.c	\
		parser/object.c parser/parse.c parser/read.c parser/utils.c	\
		sources/cone.c sources/cylinder.c sources/light_functions.c \
		sources/plane.c sources/render.c sources/sphere.c sources/vector_math.c \
		sources/vector_rotation.c sources/color_calculations.c \

all: $(NAME)
$(NAME):
	gcc $(SRC) $(framework) libft/libft.a

.PHONY: all 