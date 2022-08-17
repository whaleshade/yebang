/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:39:55 by jibang            #+#    #+#             */
/*   Updated: 2022/08/17 19:52:13 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lstadd_token_node(char *token, t_list **token_list);

void	make_alpha_token(char *line, int *i, t_list **token_list)
{
	int		len;

	len = 0;
	while (line[*i] && ft_isalpha(line[*i]))
	{
		len++;
		(*i)++;
	}
	lstadd_token_node(ft_substr(line, *i - len, len), token_list);
}

void	make_d_quote_token(char *line, int *i, t_list **token_list)
{
	int		len;

	(*i)++;
	len = 0;
	while (line[*i] && line[*i] != '\"')
	{
		len++;
		(*i)++;
	}
	if (line[*i] == '\"')
	{
		len++;
		(*i)++;
	}
	lstadd_token_node(ft_substr(line, *i - len - 1, len + 1), token_list);
}

void	make_s_quote_token(char *line, int *i, t_list **token_list)
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
	lstadd_token_node(ft_substr(line, *i - len - 1, len + 1), token_list);
}

void	make_parenthesis_token(char *line, int *i, t_list **token_list)
{
	int		len;
	int		lcnt;
	int		rcnt;

	lcnt = 1;
	rcnt = 0;
	(*i)++;
	len = 0;
	while (line[*i] && line[*i] != ')')
	{
		len++;
		(*i)++;
		if (line[*i] == '(')
			lcnt++;
	}
	if (line[*i] == ')')
	{
		rcnt++;
		while (line[*i] && (lcnt != rcnt))
		{
			len++;
			(*i)++;
			if (line[*i] == ')')
				rcnt++;
		}
		len++;
		(*i)++;
	}
	lstadd_token_node(ft_substr(line, *i - len - 1, len + 1), token_list);
}

void	make_tokens_list(const char *str, t_list **token_list)
{
	char	*line;
	int		i;

	line = ft_strtrim(str, " ");
	i = 0;
	while (line[i])
	{
		make_alpha_token(line, &i, token_list);

		while (line[i] && !ft_isalpha(line[i]))
		{
			/* quotation case */
			if (line[i] == '\"')
				make_d_quote_token(line, &i, token_list);
			if (line[i] == '\'')
				make_s_quote_token(line, &i, token_list);
			/* parenthesis case */
			if (line[i] == '(')
				make_parenthesis_token(line, &i, token_list);
			/* | case */
			if (line[i] == '|' && line[i] != '|')
				lstadd_token_node(ft_substr(line, i, 1), token_list);
			if (line[i] == '|' && line[i] == '|')
			{
				lstadd_token_node(ft_substr(line, i, 2), token_list);
				i++;
			}
			/* & case */
			if (line[i] == '&' && line[i] != '&') // -> 예외처리!
				lstadd_token_node(ft_substr(line, i, 1), token_list);
			if (line[i] == '&' && line[i] == '&')
			{
				lstadd_token_node(ft_substr(line, i, 2), token_list);
				i++;
			}
			/* < case */
			if (line[i] == '<' && line[i] != '<')
				lstadd_token_node(ft_substr(line, i, 1), token_list);
			if (line[i] == '<' && line[i] == '<')
			{
				lstadd_token_node(ft_substr(line, i, 2), token_list);
				i++;
			}
			/* > case */
			if (line[i] == '>' && line[i] != '>')
				lstadd_token_node(ft_substr(line, i, 1), token_list);
			if (line[i] == '>' && line[i] == '>')
			{
				lstadd_token_node(ft_substr(line, i, 2), token_list);
				i++;
			}
			/* else */
			lstadd_token_node(ft_substr(line, i, 1), token_list);
			i++;
		}
	}
}

void	lstadd_token_node(char *token, t_list **token_list)
{
	t_list	*tmp;

	tmp = ft_lstnew(token);
	if (!tmp)
	{
		ft_printf("Error\n");
		exit(1);
	}
	ft_lstadd_back(token_list, tmp);
}

t_list	*get_token_list(char *line)
{
	t_list	*token_list;

	token_list = NULL;
	make_tokens_list(line, &token_list);
	return (token_list);
}
