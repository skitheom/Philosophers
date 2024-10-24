NAME       = philo
NAME_BONUS = philo_bonus
CC       = cc
CFLAGS   = -Wall -Wextra -Werror $(INCLUDES)
# CFLAGS   = $(INCLUDES) -g -fsanitize=address
INCLUDES = -I include -I$(RLDIR)/include
SRCS     = src/main.c
OBJS     = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
