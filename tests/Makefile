CC = cc
CFLAGS = -Wall -Wextra -Werror -I../include -I../libs/libft/include -I../libs/unity/src -I../libs/MLX42/include
LDFLAGS = -L../libs/libft -lft -lm

SRCDIR = .
OBJDIR = obj
BINDIR = .

UNITY_PATH = ../libs/unity/src
LIBFT_DIR = ../libs/libft
PROJECT_SRC = ../src

# Test source files
TEST_SRC = test_init_game.c

# Project source files to test (only what you need)
INIT_SRC = allocate_contiguous_map.c \
		   read_file.c \
		   read_map.c \
		   input_mapping.c \
		   init.c \
		   utils.c

VALID_SRC = find_player.c \
			map_is_closed.c

EXIT_SRC = cleanup.c \
		   exit.c

# Combine all source files you want to test
ALL_SRC = $(INIT_SRC) $(VALID_SRC) $(EXIT_SRC)
TESTED_FILES = $(addprefix $(PROJECT_SRC)/, $(ALL_SRC))

TEST_FILES = $(addprefix $(SRCDIR)/, $(TEST_SRC))
TEST_OBJECTS = $(addprefix $(OBJDIR)/, $(TEST_SRC:.c=.o))

TEST_BIN = $(BINDIR)/test_runner

all: $(TEST_BIN)

$(TEST_BIN): $(LIBFT_DIR)/libft.a $(TEST_OBJECTS) | $(OBJDIR)
	$(CC) $(TEST_OBJECTS) $(UNITY_PATH)/unity.c $(TESTED_FILES) $(LDFLAGS) -o $@
	@echo "Running tests..."
	@./$(TEST_BIN)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR) all

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(TEST_BIN)

re: fclean all

.PHONY: all clean fclean re
