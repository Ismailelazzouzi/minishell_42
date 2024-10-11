#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include "./libft/libft.h"

typedef enum e_typetoken
{
	WORD,
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

typedef struct	s_ast_node
{
	t_typetoken			type;
	int					file_type;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
} 	t_ast_node;

typedef struct	s_env
{
	char	**original_env;
	char	***parsed_env;
}	t_env;

// Input Validation I-V
int		check_syntax_error(char *input);
int		unclosed_quote(char *input);
int		invalid_redirection(char *input);
int		invalid_pipe(char *input);
int		logical_operators(char *input);
//Input-Validation utils
char	*skip_spaces(char *input);
void	quote_count(char c, int *sq_count, int *dq_count);
int		invalid_operator(char **input);
// Tokenization T
t_token	*tokenize_input(char *input);
void	found_special_char(char **input, t_token **tokens);
void	found_word(char **input, t_token **tokens);
// Tokenization utils
t_token	*generate_token(t_typetoken type, char *token_value);
void	add_token(t_token **tokens, t_token *new_token);
void	add_word_token(char **start, char **input, t_token **tokens);
void	free_tokens(t_token *tokens);
void	quote_status(char c, int *quoted, char *quote);
// Parsing
t_ast_node	*parse(t_token **tokens);
t_ast_node	*parse_pipe(t_token **tokens);
t_ast_node	*parse_redirection(t_token **tokens);
t_ast_node	*create_file_node(t_token *token);
t_ast_node	*parse_command(t_token **tokens);
// Parsing utils
t_ast_node *new_ast_node(t_typetoken type);
void		free_ast(t_ast_node *node);
int			count_args(t_token *current);
t_ast_node	*create_redir_node(t_token **tokens, t_token *placeholder);
void		fill_args(t_ast_node *node, t_token **tokens, int args_count);
// Str utils
int			str_size(char *str, char end);
int			array_str_count(char **arr);
char		*rm_quotes(char *str, int s_q_c, int d_q_c, int a);
char		*strcopy(char *src);
void		string_copy(char *s1, char *s2, int st, int en);
int			ft_strcmp(char *s1, char *s2, char *s3);
int			str_to_int(char *str);
void		free_str_arr(char **arr);
// Env
//int	env_var_init(t_env *env, char **original_env);
int	find_env_var(t_env *env, char *name);
void	update_stat(t_env *env, int stat, char *start);
void	replace_env_var(char *var, t_env *env);
void	remove_env_place(t_env *env, int i);
void	add_env_place(t_env *env, char *var, int i, int flag);
char	**copy_without_index(char **original_env, int j, int k, int l);
char	***duplicate_env_struct(t_env *env, int j, int k, int l);
void	update_index_val(t_env *env, char *var, int j, int flag);

// Utils
int	count_digits(int number);
void	free_env_var(char ***arr);
void	cleanup_exit(t_env *env, int stat);
#endif
