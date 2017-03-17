#!/usr/bin/make -f

LIBRARY = ./libft/libft.a

NAME = program

HEADERS = program.h

OBJECTS = program.o

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -L. ./libft/libft.a -o $@

%.o: %.c $(HEADERS)
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJECTS)
fclean: clean
	rm -f $(NAME) $(OBJECTS)
re: fclean all

