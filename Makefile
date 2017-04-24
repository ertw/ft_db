#!/usr/bin/make -f

LIBRARY = ./libft/libft.a

NAME = ft_db

HEADERS = ft_db.h

OBJECTS = ft_db.o user_login.o display_array_db.o add_array_field.o remove_array_field.o

ifeq ($(mode),release)
	CFLAGS = -Wall -Werror -Wextra -g
else
	mode = debug
	CFLAGS = -Wall -Werror -Wextra -g -fno-omit-frame-pointer -fsanitize=address
endif

all: information $(NAME)

$(NAME): $(OBJECTS)
	make -C ./libft/ mode=$(mode)
	$(CC) $(CFLAGS) $(OBJECTS) -L. ./libft/libftprintf.a -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
fclean: clean
	rm -f $(NAME) $(OBJECTS)
re: fclean all

information:
	@printf "Build mode "$(mode)" selected\n"
.PHONY:all clean fclean re information
