GCC = gcc -Wall -Wextra -Werror

SRCS = srcs/snake.c srcs/termios.c srcs/utils.c srcs/render.c srcs/main.c
OBJS = $(SRCS:.c=.o)

NAME = start

INCLUDES = -I includes/

all: $(NAME)

$(NAME): $(OBJS)
	$(GCC) $(OBJS) $(INCLUDES) -o $(NAME)

%.o: %.c
	$(GCC) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) *~ srcs/*~ includes/*~ srcs/*#

game: all
	clear && ./$(NAME)

re: fclean all
.PHONY: all clean fclean game re
