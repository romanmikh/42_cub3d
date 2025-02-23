#include "mlx_int.h"

int	mlx_destroy_display(t_xvar *xvar)
{
	XCloseDisplay(xvar->display);
}
