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

#include "../includes/fractol.h"

/*
	Initializes the structure
*/
void	initializeInfo(t_info *info)
{
	info->mlx_ptr = NULL;
	info->window = NULL;
	info->mlx_img = NULL;
	info->type = 0;
	info->palette = 0;
	info->min_r = -2.0;
	info->max_r = 1.0;
	info->max_i = -1.5;
	info->min_i = 1.5;
	info->img.addr = NULL;
	info->img.bpp = 0;
	info->img.endian = 0;
	info->img.line_len = 0;
	info->color.r = 0;
	info->color.g = 0;
	info->color.b = 0;
	info->k.r = 0;
	info->k.i = 0;
	info->max_it = MAX_IT;
}

/*
	Like mlx_put_pixel but for images
*/
void	colorOnePixel(int color, int x, int y, t_img *img)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

/*
	Turns rgb values to an int color value by bitshifting the number 0
*/
int	rgbToColor(int r, int g, int b)
{
	return (0 << 24 | r << 16 | g << 8 | b);
}

/*
	Sets the color shade of the palette. It starts from black to the desired color
	by changing each time its rgb values by 9. If the value exceeds the desired
	rgb values it resets them to the desired value.
*/
void	createColorPalette(t_info *info, int tr, int tg, int tb)
{
	t_color	black;
	int		i;

	black.r = 0;
	black.g = 0;
	black.b = 0;
	i = -1;
	while (++i <= info->max_it)
	{
		black.r += 9;
		if (black.r > tr)
			black.r = tr;
		black.g += 9;
		if (black.g > tg)
			black.g = tg;
		black.b += 9;
		if (black.b > tb)
			black.b = tb;
		info->palette[i] = rgbToColor(black.r, black.g, black.b);
	}
	info->palette[info->max_it] = 0;
}
