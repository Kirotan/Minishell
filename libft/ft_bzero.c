#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	if (!s)
		return ;
	str = s;
	while (n > 0)
	{
		*str = '\0';
		str++;
		n--;
	}
}
