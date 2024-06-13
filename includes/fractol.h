/*                                                                 /L'-,
            ▄████▄   ██▀███   ▄▄▄       ███▄ ▄███▓. .             /  L '-,
      .     ▒██▀ ▀█  ▓██ ▒ ██▒▒████▄    ▓██▒▀█▀ ██▒`..           /       '-,
      :     ▒▓█    ▄ ▓██ ░▄█ ▒▒██  ▀█▄  ▓██    ▓██░ ,<>         /_      '-,'
      ;     ▒▓▓▄ ▄██▒▒██▀▀█▄  ░██▄▄▄▄██ ▒██    ▒██,',.;      .-'* ;     .'
      |     ▒ ▓███▀ ░░██▓ ▒██▒ ▓█   ▓██▒▒██▒   ░█< ,; `.      )`--'    /
      |     ░ ░▒ ▒  ░░ ▒▓ ░▒▓░ ▒▒   ▓▒█░░ ▒░   ░  `  `. `.   /__,    ,'
      |     ░  ▒     ░▒ ░ ▒░  ▒   ▒▒ ░░  ░      ░      `. `-,_\     /
      |     ░          ░░   ░   ░   ▒   ░      ░         `./ .\----.___
      |     ░ ░         ░           ░  ░       ░           `.__) . .F. )-.
      |     ░                                               J . . . J-'-. `-.,
      |                                                     |. . . . \   `-.  F
      |                                                     F . . . . \     '`
      |     @github.com/cramhier                       __,-J . . . . . \
      |                                          __,--'    |. .__.----,'
      |     ***   ***                      __,--'          `.-;;;;;;;;;\
      |                              __,--'                 /;;;;;;;;;;;;.
      |                        __,--'                      /;;;;;;;;;;;;;;\
  \   |                  __,--'                            `--;;/     \;-'\
   \  |            __,--'                                  /  /         \  \
    \ |      __,--'                                       /  /           \  \
     \|__,--'                                         _,-;M-K,           ,;-;\
                                                     <;;;;;;;;           '-;;;;*/

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "keys.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

/*	size */
# define WIDTH 900
# define HEIGHT 900
# define MAX_IT 60

typedef struct s_color {
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_img {
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_complex {
	double	r;
	double	i;
}	t_complex;

typedef struct s_info {
	void		*mlx_ptr;
	void		*window;
	void		*mlx_img;
	int			type;
	int			*palette;
	int			max_it;
	double		min_r;
	double		max_r;
	double		min_i;
	double		max_i;
	t_img		img;
	t_color		color;
	t_complex	k;
}	t_info;

void	initializeInfo(t_info *info);
void	draw(t_info *info);
void	errorprint(int error, t_info *info);
void	changeColorValues(int key, t_info *info);
void	validRGBvalues(char **av, int ac);
void	colorOnePixel(int color, int x, int y, t_img *img);
void	createColorPalette(t_info *info, int tr, int tg, int tb);
double	ft_atod(char *str);
int		isItFractal(double cr, double ci, t_info *info);
int		listener(int key, t_info *info);
int		exitWindow(t_info *info);
int		zoom(int key, int x, int y, t_info *info);
int		rgbToColor(int r, int g, int b);

#endif
