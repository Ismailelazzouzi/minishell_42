#include "minishell.h"

int	find_env_index(t_env env, char *name)
{
	int	i;

	i = 0;
	while (env->parsed_env[i] != 0)
	{
		if (strcmp(env->parsed_env[i][0], name, NULL))
			return (i);
		i++;
	}
	return (-1);
}

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
	return (new_old);
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
		c = str_size(original_env[b], '=');
		env->parsed_env[b] = malloc(2 * sizeof(char **));
		env->parsed_env[b][0] = malloc(c * sizeof(char *));
		env->parsed_env[b][1] = malloc(
				(str_size(original_env[b], '\0') - c) * sizeof(char *));
		if (env->parsed_env[b] || env->parsed_env[b][0]
			|| env->parsed_env[b][1])
			return (0);
		string_copy(env->parsed_env[b][0], original_env[b], 0, c);
		string_copy(env->parsed_env[b][1],
			original_env[b], c + 1, str_size(original_env[b], '\0'));
	}
	return (env->parsed_env[b] = 0, 1);
}

int	init_shell_env(t_env *env, char **original_env)
{
	int	stat;
	int	x;
	int	i;

	env = malloc(sizeof(t_env));
	if (!env)
		return (0);
	stat = env_handle_structure(env, original_env, 0);
	x = find_env_index(env, "SHLVL");
	if (x >= 0)
		i = str_to_int(env->parsed_env[a][1]);
	//update_stat(env, i + 1, "SHLVL=");
	//init_def_var(env, 0);
	return (stat);
}
