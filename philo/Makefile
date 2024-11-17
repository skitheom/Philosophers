NAME       = philo
CC         = cc
CFLAGS     = -Wall -Wextra -Werror $(INCLUDES) -pthread
INCLUDES   = -I include
SRC_DIR    = src
OBJS_DIR   = obj

SRCS       = cleanup.c         \
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
             utils.c           \
             validate_arg.c

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

# Test cases
test0:
	./philo 199 320 100 100

test1:
	./philo 100 500 200 200

test2:
	./philo 5 300 200 60

test3:
	./philo 5 600 150 150

test4:
	./philo 4 410 200 200

test5:
	./philo 5 800 200 200 7

test6:
	./philo 5 510 200 200

test7:
	./philo 5 300 200 60

test8:
	./philo 4 400 200 200

test9:
	./philo 199 700 200 200

testA:
	./philo 100 800 200 200

testB:
	./philo 105 800 200 200

testC:
	./philo 200 800 200 200

testD:
	./philo 2 400 200 200

testE:
	./philo 2 200 100 100

# Error case test
testF:
	./philo 8 500 200 200

# Philosopher should die after 121ms
testG:
	./philo 2 120 60 61

# PHONY targets
.PHONY: all clean fclean re debug test0 test1 test2 test3 test4 test5 \
        test6 test7 test8 test9 testA testB testC testD testE testF testG
