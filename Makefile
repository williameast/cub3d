#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: weast <weast@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/01 14:24:45 by weast             #+#    #+#              #
#    Updated: 2025/10/14 17:08:13 by weast            ###   ########.fr        #
#                                                                              #
#******************************************************************************#
#
NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include -I./libs/libft/include -I./libs/MLX42/include
LDFLAGS = -L./libs/libft -L./libs/MLX42/build -lft -lmlx42 -lglfw -lGL -ldl -lm

SRCDIR = src
OBJDIR = obj
OBJDIR_DBG	= obj_dbg
OBJDIR_SAN	= obj_san
BINDIR = bin
LIBFT_DIR = libs/libft
MLX42_DIR = libs/MLX42

MAIN_SRC	= main.c\
			  _debug.c
INIT_SRC	= allocate_contiguous_map.c \
			  read_file.c \
			  read_map.c \
			  input_mapping.c \
			  init.c \
				utils.c

VALID_SRC	= find_player.c \
			  map_is_closed.c
EXIT_SRC	= cleanup.c \
			  exit.c

SRC_FILES	= $(MAIN_SRC) $(INIT_SRC) $(VALID_SRC) $(EXIT_SRC)
SRCS		= $(addprefix $(SRCDIR)/, $(SRC_FILES))
OBJECTS		= $(addprefix $(OBJDIR)/, $(SRC_FILES:.c=.o))
OBJS_DBG	= $(addprefix $(OBJDIR_DBG)/, $(SRC_FILES:.c=.o))
OBJS_SAN	= $(addprefix $(OBJDIR_SAN)/, $(SRC_FILES:.c=.o))

all: $(BINDIR)/$(NAME) $(BINDIR)/maps submodules

$(BINDIR)/$(NAME): $(LIBFT_DIR)/libft.a $(MLX42_DIR)/build/libmlx42.a $(OBJECTS) | $(BINDIR)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

# Debug build (with -g, separate object files)
debug: CFLAGS += -g
debug: submodules $(LIBFT_DIR)/libft.a $(MLX42_DIR)/build/libmlx42.a $(OBJS_DBG) | $(BINDIR)
	$(CC) $(OBJS_DBG) $(LDFLAGS) -o $(BINDIR)/$(NAME)


san: CFLAGS += -g -fsanitize=address
san: LDFLAGS += -fsanitize=address
san: submodules $(LIBFT_DIR)/libft.a $(MLX42_DIR)/build/libmlx42.a $(OBJS_DBG) | $(BINDIR)
	$(CC) $(OBJS_SAN) $(LDFLAGS) -o $(BINDIR)/$(NAME)

$(BINDIR)/maps: | $(BINDIR)
	ln -sf ../maps $(BINDIR)/maps

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Debug objects
$(OBJDIR_DBG)/%.o: $(SRCDIR)/%.c | $(OBJDIR_DBG)
	$(CC) $(CFLAGS) -c $< -o $@

# San objects
$(OBJDIR_SAN)/%.o: $(SRCDIR)/%.c | $(OBJDIR_SAN)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR) all

$(MLX42_DIR)/build/libmlx42.a: | $(MLX42_DIR)/build
	cd $(MLX42_DIR)/build && cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON && make

$(MLX42_DIR)/build:
	mkdir -p $(MLX42_DIR)/build

# Initialize git submodules
submodules:
	@git submodule update --init --recursive

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR_DBG):
	mkdir -p $(OBJDIR_DBG)

$(OBJDIR_SAN):
	mkdir -p $(OBJDIR_SAN)

$(BINDIR):
	mkdir -p $(BINDIR)

compile_commands:
	@cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	@ln -sf build/compile_commands.json compile_commands.json
	@echo "compile_commands.json generated and linked"

test: $(LIBFT_DIR)/libft.a $(TEST_OBJECTS) | $(BINDIR)
	$(CC) $(TEST_OBJECTS) libs/Unity/src/unity.c $(TEST_SRC_FILES) $(CFLAGS) -L./libs/libft -lft -lm -o $(TEST_BIN)
	@echo "Running tests..."
	@./$(TEST_BIN)

obj_test/%.o: tests/%.c | obj_test
	$(CC) $(CFLAGS) -c $< -o $@

obj_test:
	mkdir -p obj_test

clean:
	rm -rf $(OBJDIR)
	rm -rf $(OBJDIR_DBG)
	rm -rf $(OBJDIR_SAN)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(BINDIR)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(MLX42_DIR)/build

re: fclean all

.PHONY: all clean fclean re tests compile_commands
