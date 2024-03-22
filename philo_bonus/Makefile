NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror

FILES =	philo_bonus \
		ft_atoi \
		action \
		utils \
		check \
		init

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
