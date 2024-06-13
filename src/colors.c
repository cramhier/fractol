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
	Keeps the values that are being increased/decreased inside the RGB range.
*/
static int	checkIfMaxValuesReached(int key, t_info *info)
{
	if ((info->color.r + 25 > 255) && key == R_COLOR)
	{
		ft_putstr_fd("Max R_Color Value reached: ", 1);
		ft_putnbr_fd(info->color.r, 1);
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else if ((info->color.g + 25 > 255) && key == G_COLOR)
	{
		ft_putstr_fd("Max G_Color Value reached: ", 1);
		ft_putnbr_fd(info->color.g, 1);
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else if ((info->color.b + 25 > 255) && key == B_COLOR)
	{
		ft_putstr_fd("Max B_Color Value reached: ", 1);
		ft_putnbr_fd(info->color.b, 1);
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else if ((info->color.r - 25 < 0) && key == R_COLOR_M)
	{
		ft_putstr_fd("R_Color Value can't go below 0: ", 1);
		ft_putnbr_fd(info->color.r, 1);
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else if ((info->color.g - 25 < 0) && key == G_COLOR_M)
	{
		ft_putstr_fd("G_Color Value can't go below 0: ", 1);
		ft_putnbr_fd(info->color.g, 1);
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else if ((info->color.b - 25 < 0) && key == B_COLOR_M)
	{
		ft_putstr_fd("B_Color Value can't go below 0: ", 1);
		ft_putnbr_fd(info->color.b, 1);
		ft_putchar_fd('\n', 1);
		return (1);
	}
	return (0);
}

/*
	Checks if the values given are valid inside the RGB range.
*/
void	validRGBvalues(char **av, int ac)
{
	int	a;

	a = 2;
	if (ac == 7)
		a = 4;
	if ((ft_atoi(av[a]) > 255) || (ft_atoi(av[a]) < 0))
	{
		ft_putendl_fd("R Value has to be between 0 - 255", 1);
		exit (0);
	}
	if ((ft_atoi(av[a + 1]) > 255) || (ft_atoi(av[a + 1]) < 0))
	{
		ft_putendl_fd("G Value has to be between 0 - 255", 1);
		exit (0);
	}
	if ((ft_atoi(av[a + 2]) > 255) || (ft_atoi(av[a + 2]) < 0))
	{
		ft_putendl_fd("B Value has to be between 0 - 255", 1);
		exit (0);
	}
}

/*
	Handles color change in the RGB range with the intuitive R, G and B keys
	to increase the value of each individual range. The keys to reduce its 
	value are T, H and N in according order.
	The values are limited by the range itself (0-255).
*/
void	changeColorValues(int key, t_info *info)
{
	if (checkIfMaxValuesReached(key, info))
		return ;
	else
	{
		if (key == R_COLOR)
			info->color.r += 25;
		else if (key == R_COLOR_M)
			info->color.r -= 25;
		else if (key == G_COLOR)
			info->color.g += 25;
		else if (key == G_COLOR_M)
			info->color.g -= 25;
		else if (key == B_COLOR)
			info->color.b += 25;
		else if (key == B_COLOR_M)
			info->color.b -= 25;
	}
}
