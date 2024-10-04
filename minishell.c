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

void	main_loop(void)
{
	char		*input;
	t_token		*tokens;
	t_ast_node	*ast;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		tokens = check_tokenize(input);
		ast = parse(&tokens);
		// if (ast)
		// 	print_ast(ast);
	}
}

int	main(int argc, char **argv, char **original_env)
{
	t_env	*env;
	int		stat;

	if (argc == 1 && !argv[1])
	{
		stat = init_shell_env(env, original_env);
		main_loop();
	}
}
