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
        Error printing handler.
*/
void errorprint(int error, t_info *info)
{
	if (error == 9)
	{
		ft_putendl_fd("**Wrong input**\n\ne.g:\n"
		"./fractol m(fractal) r g b(color) "
		"for Mandelbrot\n./fractol m 255 255 0\n./fractol j(fractal) "
		"kr ki(complex values) r g b(color)\n"
		"./fractol j 0.285 0.01 0 255 255\n",
		1);
		exit(0);
	}
	else if (error == 8)
	{
		if (info->k.r < -2.0 || info->k.r > 2.0 || info->k.i < -2.0 ||
			info->k.i > 2.0)
		{
			ft_putendl_fd("complex values have to be between -2 and 2!", 1);
			exit(0);
		}
	}
	else if (error == 7)
	{
		ft_putendl_fd("Error creating color palette.", 1);
		exit(0);
	}
}

/*
        Mandelbrot and Julia fractals are corelated. While mandelbrot calculates
        with z = 0 and c is defined by the pixel we evaluate, Julia calculates
        with z = our pixel and c(in this case changed to k for contrast) is the
        constant we give as input.
*/
static void changevalues(t_complex *z, t_info *info, double *cr, double *ci)
{
	z->r = *cr;
	z->i = *ci;
	*cr = info->k.r;
	*ci = info->k.i;
}

/*
        Function to calculate fractal of Mandelbrot and Julia. Only changes
        starting values if it's supposed to calculate Julia. Otherwise is the
        same principle. The absolute value of a complex number (in this case Z)
        is determined by its vector lenght in the imaginary and real axis
        which would be sqrt(zr^2 + zi^2) which for the Mandelbrot and Julia
        sets should by definition not exceed the value of 2.
*/
int isItFractal(double cr, double ci, t_info *info)
{
	int n;
	t_complex z;
	double tmp;
	
	z.r = 0;
	z.i = 0;
	n = -1;
	if (info->type == 2)
		changevalues(&z, info, &cr, &ci);
	while (++n < info->max_it)
	{
		if ((z.r * z.r + z.i * z.i) > 4.0)
			break;
		tmp = (2 * z.r * z.i) + ci;
		z.r = z.r * z.r - z.i * z.i + cr;
		z.i = tmp;
	}
	if (n == info->max_it)
		return (0);
	return (n);
}
