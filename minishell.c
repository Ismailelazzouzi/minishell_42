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
	}
}

int	main(int argc, char **argv)
{
	if (argc == 1 && !argv[1])
	{
		main_loop();
	}
}
