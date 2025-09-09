NAME = cub3D

CC = cc

FLAGS = -Werror -Wextra -Wall -Wunreachable-code -O3 -ffast-math
LDFLAGS = -ldl -lglfw -pthread -lm

HEADERS = -I./include -I./lib/libft -I./lib/MLX42/include

#Paths
MLX_PATH = ./lib/MLX42
MLXLIB = $(MLX_PATH)/build/libmlx42.a
MLX_REPO = https://github.com/codam-coding-college/MLX42.git

LIBFT_PATH = ./lib/libft
LIBFT = $(LIBFT_PATH)/libft.a

OBJS_PATH = obj

SRCS = src/main.c src/parsing/validate_arg.c src/parsing/handle_err.c\
# add under SRCS paths like this - src/parsing/utils.c

OBJS = $(SRCS:src/%.c=$(OBJS_PATH)/%.o)

all: $(LIBFT) $(MLXLIB) $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLXLIB)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(MLXLIB) $(LDFLAGS) $(HEADERS) -o $(NAME)

#Clone and build MLX42
$(MLXLIB): $(MLX_PATH)
	cmake -B $(MLX_PATH)/build -S $(MLX_PATH) -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_EXAMPLES=OFF
	cmake --build $(MLX_PATH)/build

$(MLX_PATH):
	git clone $(MLX_REPO) $(MLX_PATH)

# Build libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(OBJS_PATH)/%.o: src/%.c | $(OBJS_PATH)
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_PATH) clean
	@rm -rf $(MLX_PATH)/build

fclean: clean
	rm -f $(NAME)
	@rm -rf $(OBJS_PATH)
	$(MAKE) -C $(LIBFT_PATH) fclean
	@rm -rf $(MLX_PATH)

re:	fclean all

.PHONY: all clean fclean re