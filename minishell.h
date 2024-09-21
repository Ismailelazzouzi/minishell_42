#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
#include "./libft/libft.h"

typedef enum e_typetoken
{
	COMMAND,
	PIPE,
	REDIRECTION_IN,
	REDIRECTION_OUT,
	REDIRECTION_APPEND,
	HEREDOC
}	t_typetoken;

typedef struct s_token
{
	t_typetoken			token_type;
	char				*value;
	struct s_token		*next;
}	t_token;

// Input Validation I-V
int	check_syntax_error(char *input);
int	unclosed_quote(char *input);
int	invalid_redirection(char *input);
int	invalid_pipe(char *input);
int	logical_operators(char *input);
//I-V utils
char	*skip_spaces(char *input);
void	quote_count(char c, int *sq_count, int *dq_count);
int	invalid_operator(char **input);
// tokenization
t_token *tokenize_input(char *input);
void	found_special_char(char **input, t_token **tokens);
void	found_word(char **input, t_token **tokens);
#endif