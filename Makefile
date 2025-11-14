NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include -I./libs/libft/include -I./libs/minilibx-linux
LDFLAGS = -L./libs/libft -L./libs/minilibx-linux -lft -lmlx -lXext -lX11 -lm
HEADERS = include/cub3d.h libs/libft/include/libft.h

SRCDIR = src
OBJDIR = obj
OBJDIR_DBG = obj_dbg
BINDIR = bin

LIBFT_DIR = libs/libft
MINILIBX_DIR = libs/minilibx-linux

MAIN_SRC = main.c
INIT_SRC = allocate_contiguous_map.c \
		   read_file.c \
		   read_map.c \
		   read_utils.c \
		   read_store.c \
		   read_validate.c \
		   input_mapping.c \
		   init.c \
		   utils.c
VALID_SRC = find_player.c \
			map_is_closed.c \
			render_frame.c \
			render_utils.c \
			render_minimap.c \
			cast_ray.c \
			draw_wall.c \
			movement.c
EXIT_SRC = cleanup.c

SRC_FILES = $(MAIN_SRC) $(INIT_SRC) $(VALID_SRC) $(EXIT_SRC)
SRCS = $(addprefix $(SRCDIR)/, $(SRC_FILES))
OBJECTS = $(addprefix $(OBJDIR)/, $(SRC_FILES:.c=.o))
OBJS_DBG = $(addprefix $(OBJDIR_DBG)/, $(SRC_FILES:.c=.o))

all: $(BINDIR)/$(NAME) $(BINDIR)/maps

bonus: all

$(BINDIR)/$(NAME): $(LIBFT_DIR)/libft.a $(MINILIBX_DIR)/libmlx.a $(OBJECTS) | $(BINDIR)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

# Debug build (with -g, separate object files)
debug: CFLAGS += -g
debug: $(BINDIR)/$(NAME)_debug $(BINDIR)/maps

$(BINDIR)/$(NAME)_debug: $(LIBFT_DIR)/libft.a $(MINILIBX_DIR)/libmlx.a $(OBJS_DBG) | $(BINDIR)
	$(CC) $(OBJS_DBG) $(LDFLAGS) -o $@

$(BINDIR)/maps: | $(BINDIR)
	ln -sf ../maps $(BINDIR)/maps

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Debug objects
$(OBJDIR_DBG)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR_DBG)
	$(CC) $(CFLAGS) -g -c $< -o $@

$(LIBFT_DIR)/libft.a: submodules
	$(MAKE) -C $(LIBFT_DIR) all

$(MINILIBX_DIR)/libmlx.a: submodules
	$(MAKE) -C $(MINILIBX_DIR)

# Initialize git submodules
submodules:
	@git submodule update --init --recursive
	@touch submodules

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR_DBG):
	mkdir -p $(OBJDIR_DBG)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(OBJDIR_DBG)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(BINDIR)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MINILIBX_DIR) clean
	rm -f submodules

re: fclean all

.PHONY: all bonus clean fclean re debug submodules
