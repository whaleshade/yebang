/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeblee <yeblee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 02:56:32 by yeblee            #+#    #+#             */
/*   Updated: 2022/08/27 23:35:43 by yeblee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
t_token	*new_token(char *data)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
	{
		printf("Error\n");
		exit(1);
	}
	new->data = data;
	new->type = token_type(data);
	return (new);
}

void	insert_token(t_token **tokens, t_token *new)
{
	t_token	*buf;

	buf = NULL;
	if (tokens == NULL || new == NULL)
		return ;
	// 첫 번째 
	if (*tokens == NULL)
	{
		*tokens = new;
		return ;	
	}
	buf = last_token(*tokens);
	buf->next = new;
}

t_token	*last_token(t_token *tokens)
{
	while (tokens)
	{
		if (!tokens->next)
			break ;
		tokens = tokens->next;
	}
	return (tokens);
}

int	token_type(char *content)
{
	int	type;
	
	if (ft_strncmp(content, "&&", 2) == 0)
		type = AND;
	else if (ft_strncmp(content, "||", 2) == 0)
		type = OR;
	else if (ft_strncmp(content, "|", 1) == 0)
		type = PIPE;
	else if (ft_strncmp(content, "<<", 2) == 0)
		type = HERE_DOC;
	else if (ft_strncmp(content, ">>", 2) == 0)
		type = APP_RD;
	else if (ft_strncmp(content, "<", 1) == 0)
		type = INP_RD;
	else if (ft_strncmp(content, ">", 1) == 0)
		type = OUT_RD;
	else if (ft_strncmp(content, "(", 1) == 0)
		type = L_PARENS;
	else if (ft_strncmp(content, ")", 1) == 0)
		type = R_PARENS;
	else if (ft_strncmp(content, "\"", 1) == 0)
		type = STR;
	else if (ft_strncmp(content, "'", 1) == 0)
		type = STR;
	else
		type = CMD;
	return (type);
}