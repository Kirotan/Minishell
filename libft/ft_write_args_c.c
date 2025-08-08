#include "libft.h"

int	ft_write_args_c(va_list args)
{
	char	tmp;

	tmp = (char)va_arg(args, int);
	if (ft_putchar_fd(tmp, 1) == -1)
		return (-1);
	return (1);
}
