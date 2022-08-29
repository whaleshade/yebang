/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeblee <yeblee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:43:44 by jibang            #+#    #+#             */
/*   Updated: 2022/08/29 22:19:34 by yeblee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*token_lstnew(void *data, enum e_token type)
{
	t_token	*new_lst;

	new_lst = (t_token *) malloc(sizeof(t_token));
	if (!new_lst)
		return (NULL);
	new_lst->data = data;
	new_lst->type = type;
	new_lst->next = NULL;
	return (new_lst);
}

void	token_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	tmp = NULL;
	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = token_lstlast(*lst);
	tmp->next = new;
}

t_token	*token_lstlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
