NAME = pipex

SRC = pipex_bonus.c ft_split_bonus.c util1_bonus.c util2_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
