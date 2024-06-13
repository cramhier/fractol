NAME	= fractol
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -I ./includes/fractol.h

LPATH	= ./libft/
MLX		= ./mlx/

SRCS	= $(addprefix src/, fractol.c utils.c functions.c ft_atod.c actions.c colors.c drawings.c)
OBJS	= $(SRCS:.c=.o)
MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C $(LPATH)
	$(MAKE) -C $(MLX)
	$(CC) $(OBJS) $(CFLAGS) $(LPATH)libft.a $(MLXFLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LPATH)
	$(MAKE) clean -C $(MLX)

fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(LPATH)

re: fclean all

.phony: all libft clean fclean mlx 