# Makefile for raycaster project

# Program name
NAME = raycaster

# Source files
SRCS = raycaster.c \
		ray_init_stuff.c \
		ray_mlx_stuff.c \
		ray_render_stuff.c \
		ray_utils.c \
		ray_game_mechanics.c \

# Object files
OBJS = $(SRCS:.c=.o)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -O0
INCLUDES = -I./minilibx-linux

# MinilibX settings
MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

# Colors for output
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m # No Color

# Default target
all: $(MLX_LIB) $(NAME)

# Build MinilibX first (silenced)
$(MLX_LIB):
	@echo "$(YELLOW)Building MinilibX...$(NC)"
	@make -sC $(MLX_DIR) > /dev/null
	@echo "$(GREEN)MinilibX built successfully!$(NC)"

# Compile object files
%.o: %.c raycaster.h
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link the final executable
$(NAME): $(OBJS) $(MLX_LIB)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(NC)"

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -f $(OBJS)
	@make -sC $(MLX_DIR) clean > /dev/null

# Clean everything including executable
fclean: clean
	@echo "$(RED)Cleaning executable...$(NC)"
	@rm -f $(NAME)

# Rebuild everything
re: fclean all

# Run the program
run: $(NAME)
	./$(NAME)

# Debug build
debug: CFLAGS += -g -fsanitize=address
debug: $(NAME)

# Test compilation without linking
test: $(OBJS)
	@echo "$(GREEN)Compilation test passed!$(NC)"

.PHONY: all clean fclean re run debug test