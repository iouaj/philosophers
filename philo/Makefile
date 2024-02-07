NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

FILES =	philo \
		ft_atoi \
		exit \
		action \
		utils

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
