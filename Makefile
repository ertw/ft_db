#!/usr/bin/make -f

LIBS = -L./libft -lftprintf

NAME = ft_db

HEADERS = ft_db.h

OBJECTS = ft_db.o user_login.o display_array_db.o add_array_column.o remove_array_column.o add_array_row.o remove_array_row.o modify_array_cell.o dispatch_manager.o db_manager.o ls_cwd.o display_array_db_helpers.o update_db.o help.o

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
