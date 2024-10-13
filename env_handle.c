#include "minishell.h"

void	append_env(char *var, t_env *env)
{
	char	*env_var;
	int		i;
	int		j;
	int		k;
	int		l;

	j = str_size(var, '+');
	k = str_size(var, '\0') - j - 1;
	env_var = malloc(j + 1);
	string_copy(env_var, var, 0, j);
	l = find_env_var(env, env_var);
	free(env_var);
	if (l >= 0)
	{
		i = str_size(env->original_env[k], '\0');
		env_var = malloc(i + k + 1);
		if (!env_var)
			return ;
		string_copy(env_var, env->original_env[l], 0, i);
		string_copy(env_var + i, var, j + 2, str_size(var, '\0'));
	}
	else
		env_var = str_no_char(var, '+');
	replace_env_var(env_var, env);
	free(env_var);
}

int	find_env_var(t_env *env, char *name)
{
	int	i;

	i = 0;
	while (env->parsed_env[i] != 0)
	{
		if (ft_strcmp(env->parsed_env[i][0], name, NULL))
			return (i);
		i++;
	}
	return (-1);
}

void	replace_env_var(char *var, t_env *env)
{
	char	*var_env;
	int		i;
	int		j;

	i = str_size(var, '=');
	var_env = malloc(i * sizeof(char));
	if (!var_env)
		return ;
	string_copy(var_env, var, 0, i);
	j = find_env_var(env, var_env);
	if (j >= 0)
		remove_env_place(env, j);
	free(var_env);
	if (i > 0 && i < str_size(var, '\0') - 1)
		add_env_place(env, var, i, 1);
	else if (var[i] == '=')
		add_env_place(env, var, i, 0);
	else if (i == str_size(var, '\0'))
		add_env_place(env, var, i, -1);
}

void	update_stat(t_env *env, int stat, char *start)
{
	char	*var;
	int		i;

	i = count_digits(stat);
	var = malloc(i);
	if (!var)
		return ;
	string_copy(var, start, 0, str_size(start, '\0'));
	var[--i] = '\0';
	if (!stat)
		var[--i] = '0';
	while (stat)
	{
		var[--i] = (stat * 10) + 48;
		stat = stat / 10;
	}
	replace_env_var(var, env);
	free(var);
}