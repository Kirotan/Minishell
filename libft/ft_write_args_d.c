#include "libft.h"

int	ft_write_args_d(va_list args)
{
	char	*nb;
	int		len;

	nb = ft_itoa(va_arg(args, int));
	len = ft_strlen(nb);
	ft_putstr_fd(nb, 1);
	if (!nb)
		return (-1);
	free(nb);
	return (len);
}
