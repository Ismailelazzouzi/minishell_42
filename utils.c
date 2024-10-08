#include "minishell.h"

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