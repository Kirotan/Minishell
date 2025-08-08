#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	len = ft_strlen(s);
	if (write(fd, s, len) == -1)
		return (-1);
	return (len);
}
