#include "minishell.h"

void	update_index_val(t_env *env, char *var, int j, int flag)
{
	int	m;
	int	n;

	m = str_size(var, '=');
	n = str_size(var, '\0') - m;
	if (flag > 0)
	{
		env->parsed_env[j][1] = malloc(n + 1);
		if (!env->parsed_env[j][1])
			return ;
		string_copy(env->parsed_env[j][1], var, m + 1, m + n);
	}
	else
	{
		env->parsed_env[j][1] = malloc(3);
		if (!env->parsed_env[j][1])
			return ;
		if (!flag)
			env->parsed_env[j][1][0] = '\0';
		else
			string_copy(env->parsed_env[j][1], "F1", 0, 2);
	}
}

char	***duplicate_env_struct(t_env *env, int j, int k, int l)
{
	char	***new_parsed;
	int		m;
	int		n;

	m = 0;
	n = 0;
	new_parsed = malloc((j + k) * sizeof(char ***));
	if (!new_parsed)
		return (NULL);
	while (m < j)
	{
		if (m != l)
		{
			new_parsed[n] = malloc(2 * sizeof(char **));
			if (!new_parsed[n])
				return (NULL);
			new_parsed[n][0] = strcopy(env->parsed_env[m][0]);
			new_parsed[n][1] = strcopy(env->parsed_env[m][1]);
			n++;
		}
		m++;
	}
	if (l >= 0)
		new_parsed[m] = 0;
	if (k != 'F')
		free_env_var(env->parsed_env);
	return (new_parsed);
}

char	**copy_without_index(char **original_env, int j, int k, int l)
{
	char	**new_original;
	int		m;
	int		n;

	m = 0;
	n = 0;
	new_original = malloc((j + k) * sizeof(char **));
	if (!new_original)
		return (NULL);
	while (m < j)
	{
		if (m != l)
			new_original[n++] = strcopy(original_env[m]);
		m++;
	}
	if (l >= 0)
		new_original[n] = 0;
	free_str_arr(original_env);
	return (new_original);
}

void	remove_env_place(t_env *env, int i)
{
	int	j;

	j = 0;
	while (env->parsed_env[j] != 0)
		j++;
	if (j > 0)
	{
		env->parsed_env = duplicate_env_struct(env, j, 0, i);
		env->original_env = copy_without_index(env->original_env, j, 0, i);
	}
}

void	add_env_place(t_env *env, char *var, int i, int flag)
{
	int	j;
	int	k;

	j = 0;
	k = 2;
	if (flag)
		k = str_size(var, '\0');
	while (env->parsed_env[j] != 0)
		j++;
	env->parsed_env = duplicate_env_struct(env, j, 2, -1);
	env->original_env = copy_without_index(env->original_env, j, 2, -1);
	env->original_env[j] = malloc(i + k + 1);
	env->parsed_env[j] = malloc(2 * sizeof(char *));
	env->parsed_env[j][0] = malloc(i + 1);
	if (!env->parsed_env[j] || !env->parsed_env[j][0] || !env->original_env[j])
		return ;
	string_copy(env->parsed_env[j][0], var, 0, i);
	if (flag > 0)
		string_copy(env->original_env[j], var, 0, str_size(var, '\0'));
	else
		string_copy(env->original_env[j], "	", 0, 1);
	update_index_val(env, var, j, flag);
	env->original_env[j + 1] = 0;
	env->parsed_env[j + 1] = 0;
}