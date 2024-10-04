#include "minishell.h"

char	*strcopy(char *src)
{
	char	*dest;
	int		a;
	int		b;

	a = 0;
	while (src[a])
		a++;
	dest = malloc((a + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	b = 0;
	while (b < a)
	{
		dest[b] = src[b];
		b++;
	}
	dest[b] = '\0';
	return (dest);
}

void	string_copy(char *s1, char *s2, int st, int en)
{
	int	a;

	a = 0;
	while (st < en)
		s1[a++] = s2[st++];
	s1[a] = '\0';
}