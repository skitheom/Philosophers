NAME       = philo
CC         = cc
# CFLAGS     = -Wall -Wextra -Werror $(INCLUDES) -lpthread
CFLAGS     = -Wall -Wextra -Werror $(INCLUDES)
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

.PHONY: all clean fclean re debug
