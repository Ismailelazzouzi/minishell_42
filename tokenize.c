#include "minishell.h"

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;

	tokens = NULL;
	while (*input)
	{
		while (*input && ft_strchr(" \t\n", *input))
			input++;
		if (ft_strchr("><|", *input))
			found_special_char(&input, &tokens);
		else
			found_word(&input, &tokens);
		input++;
	}
	return (tokens);
}

void	found_special_char(char **input, t_token **tokens)
{
	
}

void	found_word(char **input, t_token **tokens)
{
	
}