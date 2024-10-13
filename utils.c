#include "minishell.h"

char	*str_no_char(char *str, char del)
{
	int				a;
	int				b;
	char			*new_str;

	a = 0;
	b = 0;
	new_str = malloc(str_size(str, '\0') + 1);
	if (!new_str)
		return (NULL);
	while (str[a])
	{
		if (str[a] != del)
			new_str[b++] = str[a];
		a++;
	}
	new_str[b] = '\0';
	return (new_str);
}

int	count_digits(int number)
{
	int	i;

	i = 0;
	if (!number)
		return (1);
	while (number)
	{
		number = number / 10;
		i++;
	}
	return (i);
}

void	free_env_var(char ***arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i][0]);
		free(arr[i][1]);
		free(arr[i]);
		i++;
	}
}

void	cleanup_exit(t_env *env, int stat)
{
	if (env)
	{
		free_str_arr(env->original_env);
		free_env_var(env->parsed_env);
		free(env);
	}
	exit(stat);
}