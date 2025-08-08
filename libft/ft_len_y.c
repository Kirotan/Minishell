#include "libft.h"

size_t	ft_len_y(int fd)
{
	size_t	len;
	char	*s;

	if (fd == -1)
		return (0);
	len = 0;
	s = get_next_line(fd);
	while (s)
	{
		s = get_next_line(fd);
		free(s);
		len++;
	}
	close (fd);
	return (len);
}
