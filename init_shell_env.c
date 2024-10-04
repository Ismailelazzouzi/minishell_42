#include "minishell.h"

char	**duplicate_env(char **original_env)
{
	char	**new_old;
	int		a;
	int		b;

	a = 0;
	b = 0;
	while (original_env[a])
		a++;
	new_old = malloc((a + 1) * sizeof(char **));
	while (b < a)
	{
		new_old[b] = ft_strcopy(original_env[b]);
		b++;
	}
	new_old[b] = NULL;
	return[new_old];
}

int	env_handle_structure(t_env env, char **original_env, int a)
{
	int	b;
	int	c;

	env->original_env = duplicate_env(original_env);
	while (original_env[a])
		a++;
	env->parsed_env = malloc((a + 1) * sizeof(char ***));
	if (!env->parsed_env)
		return (0);
	b = -1;
	while (++b < a)
	{
		// unfinished func //
	}
}

int	init_shell_env(t_env *env, char **original_env)
{
	int	stat;

	env = malloc(sizeof(t_env));
	if (!env)
		return (0);
	stat = env_handle_structure(env, original_env, 0); // unfinished func //
}