# Makefile for the shell project

# Compiler and flags
CC := cc
CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address
INCLUDE := -Iinclude -Ilib/libft -Ilib/printf -Ilib/dprintf
#cacca
# Directories
SRC_DIR := src
OBJ_DIR := obj
LIB_DIR := lib
LIBFT_DIR := $(LIB_DIR)/libft
PRINTF_DIR := $(LIB_DIR)/printf
DPRINTF_DIR := $(LIB_DIR)/dprintf

LIBFT_OBJ_DIR := $(LIBFT_DIR)/obj
PRINTF_OBJ_DIR := $(PRINTF_DIR)/obj
DPRINTF_OBJ_DIR := $(LIB_DIR)/dprintf

# Libraries
LIBFT := $(LIBFT_DIR)/libft.a
PRINTF := $(PRINTF_DIR)/libprintf.a
DPRINTF := $(DPRINTF_DIR)/libdprintf.a

# Executable name
NAME := minishellO

# Source files and object files
SRC := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(DPRINTF) $(OBJ)
	@if [ ! -f $(PRINTF) ]; then \
		echo "Error: libftprintf.a not found in $(PRINTF_DIR)"; exit 1; \
	fi
	@if [ ! -f $(DPRINTF) ]; then \
		echo "Error: libftdprintf.a not found in $(DPRINTF_DIR)"; exit 1; \
	fi
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(PRINTF) $(DPRINTF) -lreadline -o $(NAME)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Build libft
$(LIBFT):
	$(MAKE) OBJ_DIR=$(LIBFT_OBJ_DIR) -C $(LIBFT_DIR)

# Build printf
$(PRINTF):
	@echo "Building libprintf.a in $(PRINTF_DIR)"
	$(MAKE) OBJ_DIR=$(PRINTF_OBJ_DIR) -C $(PRINTF_DIR)

$(DPRINTF):
	@echo "Building libdprintf.a in $(DPRINTF_DIR)"
	$(MAKE) OBJ_DIR=$(DPRINTF_OBJ_DIR) -C $(DPRINTF_DIR)

# Clean rules
clean:
	$(MAKE) clean OBJ_DIR=$(LIBFT_OBJ_DIR) -C $(LIBFT_DIR)
	$(MAKE) clean OBJ_DIR=$(PRINTF_OBJ_DIR) -C $(PRINTF_DIR)
	$(MAKE) clean OBJ_DIR=$(DPRINTF_OBJ_DIR) -C $(DPRINTF_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean OBJ_DIR=$(LIBFT_OBJ_DIR) -C $(LIBFT_DIR)
	$(MAKE) fclean OBJ_DIR=$(PRINTF_OBJ_DIR) -C $(PRINTF_DIR)
	$(MAKE) fclean OBJ_DIR=$(DPRINTF_OBJ_DIR) -C $(DPRINTF_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
