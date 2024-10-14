#include "minishell.h"

t_token	*check_tokenize(char *input)
{
	char	*trimmed_input;
	t_token	*tokens;

	trimmed_input = ft_strtrim(input, " \t\n\v\f\r");
	free(input);
	if (!trimmed_input)
		return (NULL);
	if (check_syntax_error(trimmed_input))
		return (free(trimmed_input), NULL);
	tokens = tokenize_input(trimmed_input);
	free(trimmed_input);
	return (tokens);
}

// void	print_args(char **args)
// {
// 	while (*args)
// 	{
// 		printf("arg = %s\n", *args);
// 		args++;
// 	}
// }

// void	print_ast_type(t_ast_node *ast)
// {
// 		if (ast->type == WORD)
// 			printf("WORD");
// 		else if (ast->type == PIPE)
// 			printf("PIPE");
// 		else if (ast->type == REDIRECTION_IN)
// 			printf("REDIRECTION_IN");
// 		else if (ast->type == REDIRECTION_OUT)
// 			printf("REDIRECTION_OUT");
// 		else if (ast->type == REDIRECTION_APPEND)
// 			printf("REDIRECTION_APPEND");
// 		else if (ast->type == HEREDOC)
// 			printf("HEREDOC");
// 		printf("\n");
// }

// void	print_ast(t_ast_node *ast)
// {
// 	t_ast_node	*ast_left;
// 	t_ast_node	*ast_right;

// 	printf("head = ");
// 	print_ast_type(ast);
// 	if (ast->args)
// 		print_args(ast->args);
// 	ast_right = ast->right;
// 	ast_left = ast->left;
// 	if (ast_left)
// 	{
// 		printf("left\n");
// 		print_ast(ast_left);
// 	}
// 	else
// 		printf("left done !\n");
// 	if (ast_right)
// 	{
// 		printf("right\n");
// 		print_ast(ast_right);
// 	}
// 	else
// 		printf("right done !\n");
// }

void	main_loop(t_env *env)
{
	char		*input;
	t_token		*tokens;
	t_ast_node	*ast;
	int			stat;

	while (1)
	{
		stat = 0;
		input = readline("minishell> ");
		if (!input)
			break ;
		if (check_line(&input))
			continue ;
		add_history(input);
		tokens = check_tokenize(input);
		if (!tokens)
			stat = 258;
		if (!stat)
		{
			ast = parse(&tokens);
			manage_execution_commands(ast, env);
			free_ast(ast);
		}
		update_env_status(env, stat, "?=");
	}
}

// void	print_env(char **original_env)
// {
// 	int	i;

// 	i = 0;
// 	while (original_env[i])
// 	{
// 		printf("%s\n", original_env[i]);
// 		i++;
// 	}
// }

int	main(int argc, char **argv, char **original_env)
{
	t_env	*env;

	setup_signal_handlers();
	env = malloc(sizeof(t_env));
	if (argc == 1 && argv && original_env && shell_initializing_with_env(env, original_env))
	{
		main_loop(env);
		cleanup_exit(env, 0);
	}
}
