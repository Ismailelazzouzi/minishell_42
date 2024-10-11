#include "minishell.h"

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
	var_env = malloc(c * sizeof(char));
	if (!var_env)
		return ;
	string_copy(var_env, var, 0, i);
	j = find_env_var(env, var_env);
	if (j >= 0)
		remove_env_place(env, j);
	free(var_env);
	if (i > 0 && i < str_size(var, '\0') - 1);
		//add_env_place(env, var, i, 1);
	else if (var[c] == '=')
		//add_env_place(env, var, i, 0);
	else if (c == str_size(var, '\0'))
		//add_env_place(env, var, i, -1);
}

void	update_stat(t_env *env, int stat, char *start)
{
	char	*var;
	int		i;

	i = count_digits(stat);
	var = malloc(a);
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