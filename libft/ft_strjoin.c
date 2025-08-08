#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1_length;
	size_t	s2_length;

	if (!s1 || !s2)
		return (0);
	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	result = (char *)malloc(s1_length + s2_length + 1);
	if (!result)
		return (0);
	ft_strlcpy(result, s1, s1_length + 1);
	ft_strlcat(result + s1_length, s2, s2_length + 1);
	return (result);
}
