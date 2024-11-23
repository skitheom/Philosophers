NAME       = philo
CC         = cc
CFLAGS     = -Wall -Wextra -Werror $(INCLUDES) -pthread
INCLUDES   = -I include
SRC_DIR    = src
OBJS_DIR   = obj

SRCS       = cleanup.c         \
             destroy.c         \
             flag_dead.c       \
             flag_eat.c        \
             flag_error.c      \
             ft_strtol.c       \
             ft_strtol_utils.c \
             health.c          \
             init.c            \
             main.c            \
             philo.c           \
             philo_eat.c       \
             print.c           \
             print_msg.c       \
             supervise.c       \
             threads.c         \
             time.c            \
             utils.c

SRCS       := $(addprefix $(SRC_DIR)/, $(SRCS))
OBJS       = $(SRCS:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: CFLAGS += -g -fsanitize=thread
debug: re

test0: ## Single philosopher should die
	./philo 1 800 200 200

test1: ## Philosophers do not die
	./philo 5 800 200 200

test2: ## Philosophers eat 7 times
	./philo 5 800 200 200 7

test3: ## Philosophers do not die
	./philo 4 410 200 200

test4: ## Single philosopher should die
	./philo 4 310 200 100

.PHONY: all clean fclean re debug test0 test1 test2 test3 test4
