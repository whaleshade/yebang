/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeblee <yeblee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 01:52:34 by yeblee            #+#    #+#             */
/*   Updated: 2022/08/26 04:18:47 by yeblee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_space(char *contents);

void	tokenizer(t_minishell *sh)
{
	t_list	*list;
	// t_token	*buf;

	// buf = sh->tokens;
	list = sh->list;
	while (list)
	{
		if (!is_space((char *)list->content))
			insert_token(sh->tokens, (char *)list->content);
		list = list->next;
	}
	printf("sh->tokens %s, %d, %p\n", sh->tokens->data, sh->tokens->type, sh->tokens->next);
	printf("\n");
}

static int	is_space(char *contents)
{
	return (contents[0] == ' ' || contents[0] == '\t' || contents[0] == '\n');
}