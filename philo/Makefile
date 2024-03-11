NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror

FILES =	philo \
		ft_atoi \
		utils \
		test \
		action \
		one \
		error

SRC = $(addsuffix .c, $(FILES))

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
