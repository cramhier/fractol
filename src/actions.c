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
	Exiting the program safely.
	MLX functions to memory free up the window.
*/
int	exitWindow(t_info *info)
{
	mlx_destroy_image(info->mlx_ptr, info->mlx_img);
	mlx_destroy_window(info->mlx_ptr, info->window);
	exit(0);
}

/*
	Modifies the edge values by 0.8x(zooms) and 1.3x(zooms out) and
	redraws the fractal.
*/
int	zoom(int key, int x, int y, t_info *info)
{
	double	centerImaginaryAxis;
	double	centerRealAxis;
	double	zoomMultiplier;

	(void) x;
	(void) y;
	centerImaginaryAxis = info->max_i - info->min_i;
	centerRealAxis = (info->min_r - info->max_r);
	zoomMultiplier = 0.0;
	if (key == K_PLUS || key == MWDOWN)
		zoomMultiplier = 0.8;
	else if (key == K_MINUS || key == MWUP)
		zoomMultiplier = 1.3;
	else
		return (0);
	info->min_r = info->max_r + (zoomMultiplier * centerRealAxis);
	info->max_r = info->max_r + (centerRealAxis
			-(zoomMultiplier * centerRealAxis)) / 2;
	info->max_i = info->min_i + (zoomMultiplier * centerImaginaryAxis);
	info->min_i = info->min_i + (centerImaginaryAxis
			- (zoomMultiplier * centerImaginaryAxis)) / 2;
	if (key == MWDOWN || key == MWUP)
		draw(info);
	return (0);
}

/*
	Handles Movement with the arrow keys.
	Shifts x(for horizontal movement) and y(for vertical movement) edge values
	from the center of the coordinated system by 0.05 times. Then redraw the
	fractal.
*/
static void	shifting(int key, t_info *info)
{
	double	centerImaginaryAxis;
	double	centerRealAxis;

	centerImaginaryAxis = info->max_i - info->min_i;
	centerRealAxis = (info->min_r - info->max_r);
	if (key == R_ARROW)
	{
		info->min_r -= (centerRealAxis * 0.05);
		info->max_r -= (centerRealAxis * 0.05);
	}
	else if (key == L_ARROW)
	{
		info->min_r += (centerRealAxis * 0.05);
		info->max_r += (centerRealAxis * 0.05);
	}
	else if (key == UP_ARROW)
	{
		info->min_i -= (centerImaginaryAxis * 0.05);
		info->max_i -= (centerImaginaryAxis * 0.05);
	}
	else if (key == DW_ARROW)
	{
		info->min_i += (centerImaginaryAxis * 0.05);
		info->max_i += (centerImaginaryAxis * 0.05);
	}
}

/*
	Increases iteration value and redraws the fractal.
	Max Number of interations is setup to 420 and minimum to 60.
*/
static void	increaseIterations(int key, t_info *info)
{
	if (info->max_it >= 420 && key == Q_KEY)
		ft_putendl_fd("Max Iterations reached", 1);
	else if ((info->max_it - 60) < 0 && key == E_KEY)
		ft_putendl_fd("Can't go below 60 intereactions", 1);
	else
	{
		if (key == Q_KEY)
			info->max_it += 60;
		if (key == E_KEY)
			info->max_it -= 60;
		ft_putstr_fd("Iterations: ", 1);
		ft_putnbr_fd(info->max_it, 1);
		ft_putchar_fd('\n', 1);
	}
}

/*
	Handles all key input actions.
*/
int	listener(int key, t_info *info)
{
	if (key == K_ESC)
		exitWindow(info);
	else
	{
		if (key == K_PLUS || key == K_MINUS)
			zoom(key, 0, 0, info);
		else if (key == R_ARROW || key == L_ARROW || key == UP_ARROW
			|| key == DW_ARROW)
			shifting(key, info);
		else if (key == Q_KEY || key == E_KEY)
			increaseIterations(key, info);
		else if (key == R_COLOR || key == G_COLOR || key == B_COLOR
			|| key == R_COLOR_M || key == G_COLOR_M || key == B_COLOR_M)
			changeColorValues(key, info);
		draw(info);
	}
	return (0);
}
