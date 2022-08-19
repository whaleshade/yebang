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

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/get_next_line/get_next_line.h"

enum	e_token
{
	E_PIPE,
	E_OR,
	E_AND,
	E_S_QUOTE,
	E_D_QUOTE,
	E_STR,
	E_INP_RD,
	E_OUT_RD,
	E_APP_RD,
	E_HRERDOC
};

enum	e_type
{
	ET_PIPE,
	ET_AND,
	ET_OR,
	ET_CMD,
	ET_REDIRECT,
	ET_STR
};

// token : 가장 작은 단위로 나눔
typedef struct s_token
{
	enum e_token	type;
	char			*data;
	struct s_token	*next;
}				t_token;

// word : 명령어를 실행 할 수 있는 가장 작은 단위로 redirect를 제외한 부분
typedef t_list t_world;

// word 와 redirct는 같은 구조를 가지고 있다.
typedef t_list t_redirect;

// 명령어를 실행하는 묶음
typedef struct s_cmd
{
	enum e_type		type;
	t_world			*world;
	t_redirect		*redir;
	struct s_cmd	*left;
	struct s_cmd	*right;
}				t_cmd;

// 필요한 데이터 묶음.
typedef struct s_minishell
{
	t_cmd	*cmd;
}				t_m;

void	welcome_screen(void);

#endif