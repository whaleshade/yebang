/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeblee <yeblee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 01:52:34 by yeblee            #+#    #+#             */
/*   Updated: 2022/08/28 00:25:57 by yeblee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_space(t_minishell *sh);

void	tokenizer(t_minishell *sh)
{
	sh->tokens = NULL;
	while (sh->list)
	{
		if (!is_space(sh))
			insert_token(&sh->tokens, new_token((char *)sh->list->content));
		sh->list = sh->list->next;
	}
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
	if (contents[0] == ' ' || contents[0] == '\t' || contents[0] == '\n')
		return (TRUE);
	return (FALSE);
}