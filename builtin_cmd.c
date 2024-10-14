#include "minishell.h"

int echo_cmd(char **cmd, int *out_fd)
{
    int a;
    int i;

    i = 0;
    if(cmd[0] && cmd[1] && is_valid_echo_paran(cmd[1]))
        i = 1;
    a = i + 1;
    while(i && cmd[a] && is_valid_echo_paran(cmd[a]))
        a++;
    if((cmd[0] && cmd[a]) || str_size(cmd[a], '\0'))
    {
        while(1)
        {
            ft_putstr_fd(cmd[a], out_fd[1]);
            a++;
            if(cmd[a])
                write(out_fd[1], "", 1);
            else
                break;

        }
    }
    if(!i)
        write(out_fd[1], "\n", 1);
    return 0;
}

int env_or_pwd_cmd(char *cmd, t_env *env, int c, int *out_fd)
{
	int a;
	char *abs_pwd;

	a = -1;

	if(ft_strcmp(cmd, "env", NULL))
	{
		if(c)
			print_export_declaration_to_fd(env, out_fd);
		else{
			while(env->parsed_env[++a])
				print_env_var_to_fd(env->parsed_env[a][0], env->parsed_env[a][1], out_fd[1]);
			
		}
		return 0;	
	}
	abs_pwd = get_current_working_directory(100, 5,out_fd[1]);
	if(abs_pwd)
	{
		ft_putendl_fd(abs_pwd, out_fd[1]);
		return (free(abs_pwd), 0);
	}
	return 256;
}

char **export_cmd(char **cmd, t_env *env, int *out_fd, int **s)
{
    int a;
    int b;

    a = 1;
    while(cmd[a])
    {
        b = export_statment_check(cmd[a]);
        if(b > 0)
        {
            if(b >= 1 && cmd[a][b] == '+')
                append_env_var(cmd[a], env);
            else
                replace_env_var(cmd[a], env);
        }
        else
        {
            ft_putendl_fd(" err: export(\'", out_fd[1]);
            ft_putstr_fd(cmd[a], out_fd[1]);
            ft_putendl_fd("\' : Not a valid thing", out_fd[1]);
            **s = 256;
        }
        a++;
    }
    return cmd;
}

char **unset_or_export_cmd(char **cmd, t_env *env, int *out_fd, int *s)
{
    int a;
    int c;
    a =1;
    *s = 0;
	
		
    if(cmd[0] && ft_strcmp(cmd[0], "unset", NULL) && env->parsed_env[0])
    {
		//write(out_fd[1],"test\n",5);
		//write(out_fd[1],env->parsed_env[30][0],2);
        while(cmd[a])
        {
            c= find_env_var_index(env, cmd[a]);
			//	write(out_fd[1],"test\n",5);
			
            if(c >= 0)
			{
				//write(out_fd[1],"test2\n",6);
                remove_env_entry(env, c);
			}
            else 
                *s =256;
            a++;
        }
    }
    else if(ft_strcmp(cmd[0], "export", NULL))
    {
        if(export_print_or_export(cmd))
            cmd = export_cmd(cmd, env, out_fd, &s);
        else
            env_or_pwd_cmd("env", env, 1, out_fd);
    }
	return(cmd);
}

int cd_cmd(char **cmd, t_env *env, int *out_fd)
{
    int a;
    char *new_path;

    if(cmd[1] && cmd[2])
        ft_putendl_fd("err: cd(): Not a cd thing", out_fd[1]);
    else{
        if(change_current_directory(cmd[1], env) < 0)
            ft_putendl_fd("err:cd():Only EXISTING destination", out_fd[1]);
        else{
            a = find_env_var_index(env,"PWD");
            if(a >= 0)
                remove_env_entry(env, a);
            new_path = get_current_working_directory(100, 5, out_fd[1]);
            if(new_path)
            {
                set_new_pwd_in_env(new_path,env,a);
			//write(out_fd[1],"test\n",5);
				free(new_path);
            }
			return 0;
        }
    }
	return 256;
}