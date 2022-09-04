#include "../includes/minishell.h"

static int	is_space(t_minishell *sh);

int		tokenizer(t_minishell *sh)
{
	if (syntax_error(sh->list) == ERROR)
	{
		while (sh->list)
			sh->list = sh->list->next;
		ft_perror("syntax error!");
		return (ERROR);
	}

	sh->tokens = NULL;
	while (sh->list)
	{
		if (!is_space(sh))
			insert_token(&sh->tokens, new_token((char *)sh->list->content));
		sh->list = sh->list->next;
	}
	return (SUCCESS);
}

/*
* 공백제거, 마지막 token이 -가 아닐경우에만
* : ls - al 과 같은 경우 에러처리를 위해서 수정
*/
static int	is_space(t_minishell *sh)
{
	char	*contents;

	contents = (char *)sh->list->content;
	if (sh->tokens && last_token(sh->tokens)->data[0] == '-')
		return (FALSE);
	if (contents[0] == ' ')
		return (TRUE);
	return (FALSE);
}
