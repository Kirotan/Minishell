#include "libft.h"

static int	nblen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;

	len = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = nblen(n);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (n == 0)
		result[0] = '0';
	if (n < 0)
	{
		result[0] = '-';
		n = -n;
	}
	while (n)
	{
		result[--len] = (n % 10) + '0';
		n = n / 10;
	}
	return (result);
}
