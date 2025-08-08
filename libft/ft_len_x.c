#include "libft.h"

size_t	ft_len_x(int fd)
{
	size_t	len;
	char	*s;

	if (fd == -1)
		return (0);
	len = 0;
	s = get_next_line(fd);
	len = ft_count_words(s, 32);
	free(s);
	close (fd);
	return (len);
}
