NAME = fractol
CC = gcc
INCLUDESDIR = includes/
SRCSDIR = srcs/
MLXDIR = minilibx-linux/
LIBFTDIR = libft/
LIBFT = libft.a
MLX = libmlx.a
MLXFLAGS = -L $(MLXDIR) -l mlx -lXext -lX11 -lm
LIBFTFLAGS = -L $(LIBFTDIR) -l ft
CFLAGS = -Wall -Werror -Wextra

_SRCS = main.c \
		rendering.c \
		handlers.c \
		sets.c \
		state.c \
		utils.c

SRCS = $(addprefix $(SRCSDIR), $(_SRCS))

.PHONY: all fclean re

all: $(NAME)

$(LIBFTDIR)/$(LIBFT):
	make -C $(LIBFTDIR)

$(MLXDIR)/$(MLX):
	make -C $(MLXDIR)

$(NAME): $(SRCS) $(MLXDIR)/$(MLX) $(LIBFTDIR)/$(LIBFT)
	$(CC) -o $(NAME) $(CFLAGS) -I $(INCLUDESDIR) $(SRCS) $(MLXFLAGS) $(LIBFTFLAGS)

fclean:
	rm -f $(NAME)
	make fclean -C $(LIBFTDIR)

clean:
	make clean -C $(LIBFTDIR)

re: clean fclean all
