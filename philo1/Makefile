CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g
NAME = philo

# Source files
SRCS = ./srcs/main.c \
       ./srcs/input.c \
       ./srcs/philo.c \
       ./srcs/init.c \
       ./srcs/free.c \
       ./srcs/util.c 

# Object files
OBJS = $(SRCS:.c=.o)

# Remove command
RM = rm -rf

# Default target
all: $(NAME)

# Link object files to create the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Compile each .c file into a .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	$(RM) $(OBJS)

# Clean everything
fclean: clean
	$(RM) $(NAME)

# Rebuild
re: fclean all

# Always execute these targets
.PHONY: all clean fclean re
