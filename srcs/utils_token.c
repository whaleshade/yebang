/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeblee <yeblee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 02:56:32 by yeblee            #+#    #+#             */
/*   Updated: 2022/08/26 04:26:16 by yeblee           ###   ########.fr       */
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

void	insert_token(t_token *tokens, char *content)
{
	t_token	*buf;
	t_token	*new;

	new = new_token(content);
	buf = tokens;
	// 첫 번째 
	if (!tokens)
		tokens = new;
	else
	{
		buf = last_token(buf);
		buf->next = new;
	}
	printf("token(%p)\tbuf(%p) : %s, %d, %p\n", tokens, buf, buf->data, buf->type, buf->next);
}

t_token	*last_token(t_token *tokens)
{
	while (tokens)
		tokens = tokens->next;
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