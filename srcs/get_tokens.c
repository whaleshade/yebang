/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:39:55 by jibang            #+#    #+#             */
/*   Updated: 2022/08/27 01:35:45 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lstadd_token_node(char *token, t_token **token_list, enum e_token type);

void	make_alnum_token(char *line, int *i, t_token **token_list)
{
	int		len;

	len = 0;
	while (line[*i] && ft_isalnum(line[*i]))
	{
		len++;
		(*i)++;
	}
	if (len > 0)
		lstadd_token_node(ft_substr(line, *i - len, len), token_list, CMD);
}

void	make_d_quote_token(char *line, int *i, t_token **token_list)
{
	int		len;

	(*i)++;
	len = 0;
	while (line[*i] && line[*i] != '\"')
	{
		len++;
		(*i)++;
		if (line[*i - 1] == '\\' && line[*i] == '\"')
		{
			len++;
			(*i)++;
		}
	}
	if (line[*i] == '\"')
	{
		len++;
		(*i)++;
	}
	lstadd_token_node(ft_substr(line, *i - len - 1, len + 1), token_list, D_QUOTE);
	(*i)--;
}

void	make_s_quote_token(char *line, int *i, t_token **token_list)
{
	int		len;

	(*i)++;
	len = 0;
	while (line[*i] && line[*i] != '\'')
	{
		len++;
		(*i)++;
	}
	if (line[*i] == '\'')
	{
		len++;
		(*i)++;
	}
	lstadd_token_node(ft_substr(line, *i - len - 1, len + 1), token_list, S_QUOTE);
	(*i)--;
}

void	make_parenthesis_token(char *line, int *i, t_token **token_list)
{
	int		len;
	int		paren_cnt;
	int		line_len;
	int		sign;

	sign = 0;
	paren_cnt = 1;
	line_len = ft_strlen(line);
	if (*i + 1 <= line_len)
	{
		sign = 1;
		(*i)++;
	}
	len = 0;
	while (line[*i] && *i < line_len && paren_cnt != 0)
	{
		if (line[*i] == '(')
			paren_cnt++;
		if (line[*i] == ')')
			paren_cnt--;
		len++;
		(*i)++;
	}
	lstadd_token_node(ft_substr(line, *i - len - 1, len + 1), token_list, PARENS);
	if (sign == 1)
		(*i)--;
}


void	make_tokens_list(const char *str, t_token **token_list)
{
	char	*line;
	int		i;

	line = ft_strtrim(str, " ");
	i = 0;
	while (line[i])
	{
		make_alnum_token(line, &i, token_list);

		while (line[i] && !ft_isalnum(line[i]))
		{
			/* quotation case */
			if (line[i] == '\"')
				make_d_quote_token(line, &i, token_list);
			else if (line[i] == '\'')
				make_s_quote_token(line, &i, token_list);
			/* parenthesis case */
			else if (line[i] == '(')
				make_parenthesis_token(line, &i, token_list);
			/* | case */
			else if (line[i] == '|' && line[i + 1] != '|')
				lstadd_token_node(ft_substr(line, i, 1), token_list, PIPE);
			else if (line[i] == '|' && line[i + 1] == '|')
			{
				lstadd_token_node(ft_substr(line, i, 2), token_list, OR);
				i++;
			}
			/* & case */
			else if (line[i] == '&' && line[i + 1] != '&') // -> 예외처리!
				lstadd_token_node(ft_substr(line, i, 1), token_list, NONE);
			else if (line[i] == '&' && line[i + 1] == '&')
			{
				lstadd_token_node(ft_substr(line, i, 2), token_list, AND);
				i++;
			}
			/* < case */
			else if (line[i] == '<' && line[i + 1] != '<')
				lstadd_token_node(ft_substr(line, i, 1), token_list, INP_RD);
			else if (line[i] == '<' && line[i + 1] == '<')
			{
				lstadd_token_node(ft_substr(line, i, 2), token_list, HERE_DOC);
				i++;
			}
			/* > case */
			else if (line[i] == '>' && line[i + 1] != '>')
				lstadd_token_node(ft_substr(line, i, 1), token_list, OUT_RD);
			else if (line[i] == '>' && line[i + 1] == '>')
			{
				lstadd_token_node(ft_substr(line, i, 2), token_list, APP_RD);
				i++;
			}
			/* space outside quote to be excluded */
			else if (line[i] == ' '){}
			/* else */
			else
				lstadd_token_node(ft_substr(line, i, 1), token_list, NONE); //백슬래시, 달러 케이스 추가해줘야 하나?
			i++;
		}
	}
}

void	lstadd_token_node(char *token, t_token **token_list, enum e_token type)
{
	t_token	*tmp;

	tmp = token_lstnew(token, type);
	if (!tmp)
	{
		ft_printf("Error\n");
		exit(1);
	}
	token_lstadd_back(token_list, tmp);
}

t_token	*get_token_list(char *line)
{
	t_token	*token_list;

	token_list = NULL;
	make_tokens_list(line, &token_list);
	return (token_list);
}
