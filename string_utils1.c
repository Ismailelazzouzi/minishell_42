#include "minishell.h"

int	ft_strcmp(char *s1, char *s2, char *s3)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != s2[i])
		i++;
	if (i == str_size(s1, '\0') && i == str_size(s2, '\0'))
		return (1);
	if (s3)
		return (ft_strcmp(s1, s3, NULL));
	return (0);
}

int	str_to_int(char *str)
{
	int					number;
	int					i;

	number = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] <= '9' && str[i] >= '0')
			number = (number * 10) + (str[i] - 48);
		i++;
	}
	return (number);
}

void	free_str_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}