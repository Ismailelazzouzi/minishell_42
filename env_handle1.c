#include "minishell.h"

void	remove_env_place(t_env *env, int i)
{
	int	j;

	j = 0;
	while (env->parsed_env[j])
		j++;
	if (j > 0)
	{
		//env->parsed_env = duplicate_env_struct(env, j, 0, c);
		//env->original_env = copy_without_index(env->original_env, j, 0, c);
	}
}

void	add_env_place(t_env *env, char *var, int i, int flag)
{
	
}