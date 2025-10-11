# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 21:53:12 by dimachad          #+#    #+#              #
#    Updated: 2025/10/08 21:56:25 by dimachad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d
CC			= gcc
INCLUDES    = -Iinclude -I$(LIBFT_DIR)/include -I$(MLX42_DIR)/include
CFLAGS		= -Wall -Wextra -Werror $(INCLUDES)
LDFLAGS		= -L$(LIBFT_DIR) -L$(MLX42_DIR)/build -L$(MLX42_DIR)/build/_deps/glfw-build/src \
			  -lft -lmlx42 -lglfw3 -lGL -lX11 -lXext -lXrandr -lXi -lXcursor -lXinerama -ldl -lm -lpthread

SRCDIR		= src
OBJDIR		= obj
OBJDIR_DBG	= obj_dbg
BINDIR		= bin
LIBFT_DIR	= libs/libft
MLX42_DIR	= libs/MLX42

# SOURCES

MAIN_SRC	= main.c\
			  _debug.c
INIT_SRC	= allocate_contiguous_map.c \
			  read_file.c \
			  read_map.c \
			  input_mapping.c \
			  init.c
VALID_SRC	= find_player.c \
			  map_is_closed.c
EXIT_SRC	= cleanup.c \
			  exit.c

SRC_FILES	= $(MAIN_SRC) $(INIT_SRC) $(VALID_SRC) $(EXIT_SRC)
SRCS		= $(addprefix $(SRCDIR)/, $(SRC_FILES))
OBJS		= $(addprefix $(OBJDIR)/, $(SRC_FILES:.c=.o))
OBJS_DBG	= $(addprefix $(OBJDIR_DBG)/, $(SRC_FILES:.c=.o))

# **************************************************************************** #
#                               MAIN TARGETS                                   #
# **************************************************************************** #

# Default build
all: submodules $(BINDIR)/$(NAME)

# Regular build
$(BINDIR)/$(NAME): $(LIBFT_DIR)/libft.a $(MLX42_DIR)/build/libmlx42.a $(OBJS) | $(BINDIR)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

# Debug build (with -g, separate object files)
debug: CFLAGS += -g -fsanitize=address
debug: LDFLAGS += -fsanitize=address
debug: submodules $(LIBFT_DIR)/libft.a $(MLX42_DIR)/build/libmlx42.a $(OBJS_DBG) | $(BINDIR)
	$(CC) $(OBJS_DBG) $(LDFLAGS) -o $(BINDIR)/$(NAME)

# **************************************************************************** #
#                           OBJECT FILE RULES                                  #
# **************************************************************************** #

# Normal objects
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Debug objects
$(OBJDIR_DBG)/%.o: $(SRCDIR)/%.c | $(OBJDIR_DBG)
	$(CC) $(CFLAGS) -c $< -o $@

# **************************************************************************** #
#                           LIBRARY DEPENDENCIES                               #
# **************************************************************************** #

# Build libft with make
$(LIBFT_DIR)/libft.a: submodules
	$(MAKE) -C $(LIBFT_DIR)

# Build MLX42 with cmake (only if not already built)
$(MLX42_DIR)/build/libmlx42.a: submodules
	@if [ ! -f $@ ]; then \
		mkdir -p $(MLX42_DIR)/build && \
		cd $(MLX42_DIR)/build && \
		cmake .. -DCMAKE_BUILD_TYPE=Release && \
		$(MAKE) -j; \
	fi

# Ensure MLX42 build directory exists
$(MLX42_DIR)/build:
	mkdir -p $(MLX42_DIR)/build

# **************************************************************************** #
#                               UTILITY TARGETS                                #
# **************************************************************************** #

# Initialize git submodules
submodules:
	@git submodule update --init --recursive

# Ensure object directories exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR_DBG):
	mkdir -p $(OBJDIR_DBG)

# Ensure binary directory exists
$(BINDIR):
	mkdir -p $(BINDIR)

# Clean only object files
clean:
	rm -rf $(OBJDIR) $(OBJDIR_DBG)
	$(MAKE) -C $(LIBFT_DIR) clean || true

# Full clean: objects + binaries + MLX42 + libft
fclean: clean
	rm -rf $(BINDIR)
	$(MAKE) -C $(LIBFT_DIR) fclean || true
	rm -rf $(MLX42_DIR)/build

# Rebuild everything from scratch
re: fclean all

# **************************************************************************** #
#                                PHONY TARGETS                                 #
# **************************************************************************** #

.PHONY: all debug clean fclean re submodules
