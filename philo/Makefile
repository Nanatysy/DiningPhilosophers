NAME = philo
FLAG = -Wall -Werror -Wextra
SRC = args_check.c \
	  atoi.c \
	  errors.c \
	  ft_strlen.c \
	  main.c \
	  philo_funcs.c \
	  utils.c 
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAG) $^ -o $(NAME)

%.o: %.c philo_bonus.h
	gcc $(FLAG) -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all