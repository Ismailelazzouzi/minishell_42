#include "minishell.h"

void	found_special_char(char **input, t_token **tokens)
{
	if (**input == '>')
	{
		if (*(*input + 1) == '>')
		{
			add_token(tokens, generate_token(REDIRECTION_APPEND, ">>"));
			(*input)++;
		}
		else
			add_token(tokens, generate_token(REDIRECTION_OUT, ">"));
	}
	else if (**input == '<')
	{
		if (*(*input + 1) == '<')
		{
			add_token(tokens, generate_token(HEREDOC, "<<"));
			(*input)++;
		}
		else
			add_token(tokens, generate_token(REDIRECTION_IN, "<"));
	}
	else if (**input == '|')
		add_token(tokens, generate_token(PIPE, "|"));
	(*input)++;
}

void	found_word(char **input, t_token **tokens)
{
	char	*start;
	char	quote;
	int		quoted;

	quote = '\0';
	quoted = 0;
	start = *input;
	while (**input)
	{
		quote_status(**input, &quoted, &quote);
		if (!quoted && ft_strchr(" \t\n><|", **input))
			break ;
		(*input)++;
	}
	add_word_token(&start, input, tokens);
}

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
	}
	return (tokens);
}
