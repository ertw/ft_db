#!/usr/bin/make -f

LIBS = -L./libft -lftprintf

NAME = ft_db

HEADERS = ft_db.h

OBJECTS = ft_db.o user_login.o display_array_db.o add_array_column.o remove_array_column.o

CFLAGS = -Wall -Werror -Wextra -g -fno-omit-frame-pointer -fsanitize=address

all: information $(NAME)

$(NAME): $(OBJECTS) $(HEADERS)
	make -C ./libft/
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $@

clean:
	rm -f $(OBJECTS)
fclean: clean
	rm -f $(NAME) $(OBJECTS)
re: fclean all

information:
	@printf "Building"
.PHONY:all clean fclean re information
