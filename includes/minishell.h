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
	E_OR,
	E_AND,
	E_PIPE,
	E_CMD,
	// 홀수일 경우 fail, 짝수일 경우 짝이 맞는 것. 또한 따옴표에 묶인 채 토큰에 저장된다.(변수 따로 지정할 것)
	// ' : 안의 변수 등 무시 그대로 출력 된다.
	// " : $이용해서 환경변수 사용할 경우 환경변수 출력되야 한다.
	E_QUOTE,
	// echo, redirection 뒤에 오는 모든 토큰은 띄어쓰기 기준으로 str로 간주, 이후 명령어에 따라 예외처리, 한 토큰에 저장됩니다.
	E_STR,
	E_INP_RD,
	E_OUT_RD,
	E_APP_RD,
	E_HRERDOC,
	// 홀수일 경우 fail, 짝수일 경우 짝이 맞는 것, 뿐만 아니라 괄호 짝이 순서대로 맞는지 확인합니다. 한 토큰에 저장 됩니다.
	E_BRACKET
};

enum	e_type
{
	ET_OR,
	ET_AND,
	ET_PIPE,
	ET_WORD,
	ET_REDIR,
	// 해당 타입의 경우 -> subshell동작할 수 있도록 합니다.
	ET_BRACKET
};

// token : 가장 작은 단위로 나눔
typedef struct s_token
{
	enum e_token	type;
	char			*data;
	struct s_token	*next;
}				t_token;

// tree 설정 root노드를 설정한 후 left, right를 통해서 트리 이동 가능.
typedef struct s_contents
{
	enum e_type		type;
	t_token			*contents;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_contens;

// root노드를 가리키는 더미노드
typedef	struct s_tree
{
	t_contens	*root;
}				t_tree;

// 필요한 데이터 묶음.
// typedef struct s_shinfo
// {
// }				t_shinfo;

int	g_status;

extern char	**env;
void	welcome_screen(void);

#endif