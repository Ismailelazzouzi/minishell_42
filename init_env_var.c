#include "minishell.h"

char	**duplicate_env(char **env)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i] != NULL)
		i++;
	new = malloc((i + 1) * sizeof(char **));
	if (!new)
		return (NULL);
	while (j < i)
	{
		new[j] = strcopy(env[j]);
		j++;
	}
	new[j] = 0;
	return (new);
}

int	init_structure(t_env *env, char **original_env, int a)
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
		c = str_size(original_env[b], '\0');
		env->parsed_env[b] = malloc(2 * sizeof(char **));
		env->parsed_env[b][0] = malloc(c * sizeof(char *));
		env->parsed_env[b][1] = malloc(
			(str_size(original_env[b], '\0') - c) * sizeof(char *));
	if (!env->parsed_env[b] || !env->parsed_env[b][0]
		|| !env->parsed_env[b][1])
		return (0);
	string_copy(env->parsed_env[b][0], original_env[b], 0, c);
	string_copy(env->parsed_env[b][1], original_env[b], c + 1, str_size(original_env[b], '\0'));
	}
	return (env->parsed_env[b] = 0, 1);
}

int	env_var_init(t_env *env, char **original_env)
{
	int	stat;
	int	index;
	int	i;

	if (!env)
		return (0);
	stat = init_structure(env, original_env, 0);
	i = find_env_var(env, "SHLVL");
	index = 0;
	if (i >= 0)
		index = str_to_int(env->parsed_env[i][1]);
	update_stat(env, index + 1, "SHLVL");
	//init_defaults(env, 0);
	return (stat);
}