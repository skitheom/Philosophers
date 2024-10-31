NAME       = philo
CC         = cc
CFLAGS     = -Wall -Wextra -Werror $(INCLUDES) -pthread
INCLUDES   = -I include
SRCS       = $(wildcard src/*.c)
OBJS_DIR   = obj
OBJS       = $(SRCS:src/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: src/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: CFLAGS += -g -fsanitize=thread
debug: re

test:
	./philo 4 410 200 200
a:
	./philo 5 800 200 200
b:
	./philo 5 600 150 150
c:
	./philo 4 410 200 200
d:
	./philo 100 800 200 200
e:
	./philo 105 800 200 200
f:
	./philo 200 800 200 200

.PHONY: all clean fclean re debug a b c d e f
