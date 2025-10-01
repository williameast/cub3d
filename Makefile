#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: weast <weast@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/01 14:24:45 by weast             #+#    #+#              #
#    Updated: 2025/10/01 14:24:49 by weast            ###   ########.fr        #
#                                                                              #
#******************************************************************************#
#
NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include -I./libs/libft/include -I./libs/MLX42/include
LDFLAGS = -L./libs/libft -L./libs/MLX42/build -lft -lmlx42 -lglfw -lGL -ldl -lm

SRCDIR = src
OBJDIR = obj
BINDIR = bin
LIBFT_DIR = libs/libft
MLX42_DIR = libs/MLX42

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(BINDIR)/$(NAME)

$(BINDIR)/$(NAME): $(LIBFT_DIR)/libft.a $(MLX42_DIR)/build/libmlx42.a $(OBJECTS) | $(BINDIR)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

$(MLX42_DIR)/build/libmlx42.a: | $(MLX42_DIR)/build
	cd $(MLX42_DIR)/build && cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON && make

$(MLX42_DIR)/build:
	mkdir -p $(MLX42_DIR)/build

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

compile_commands:
	@cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	@ln -sf build/compile_commands.json compile_commands.json
	@echo "compile_commands.json generated and linked"

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(BINDIR)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(MLX42_DIR)/build

re: fclean all

dev: CFLAGS += -g -fsanitize=address
dev: LDFLAGS += -fsanitize=address
dev: all

.PHONY: all clean fclean re dev compile_commands
