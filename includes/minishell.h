#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>

# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_global
{
	int		status;
	char	**env;
} t_global;

# include "../libft/libft.h"

# define LOOP 1

# define ON 1
# define OFF 0

# define SUCCESS 0
# define ERROR -1

/* for error fix */
void	rl_replace_line (const char *text, int clear_undo);

enum	e_token
{
	NONE,
	OR,
	AND,
	PIPE,
	CMD,
	S_QUOTE,
	D_QUOTE,
	STR,
	INP_RD,
	OUT_RD,
	APP_RD,
	HERE_DOC,
	PARENS,
	L_PAREN,
	R_PAREN
};

enum	e_type
{
	TK_OR,
	TK_AND,
	TK_PIPE,
	TK_WORD,
	TK_REDIR,
	TK_PARENS
};

// token : 가장 작은 단위로 나눔
typedef struct s_token
{
	enum e_token	type;
	char			*data;
	struct s_token	*next;
}				t_token;

typedef struct s_node
{
	enum e_type		type;
	t_token			*tokens;
	struct s_node	*left;
	struct s_node	*right;
}				t_node;

typedef struct s_minishell
{
	t_node		*root;
	t_token		*tokens;
}				t_minishell;

/* token_lst_func.c */
t_token	*token_lstlast(t_token *lst);
void	token_lstadd_back(t_token **lst, t_token *new);
t_token	*token_lstnew(void *data, enum e_token type);

#endif
