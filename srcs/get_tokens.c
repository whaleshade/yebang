/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:39:55 by jibang            #+#    #+#             */
/*   Updated: 2022/08/17 17:09:09 by jibang           ###   ########.fr       */
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


void	make_tokens_list(const char *str, t_list **token_list)
{
	char	*line;
	int		i;
	// int		len;

	line = ft_strtrim(str, " ");
	i = 0;
	while (line[i])
	{
		make_alpha_token(line, &i, token_list);
		//yeblee - "" '' () 처리
		//jibang - 나머지
		while (line[i] && !ft_isalpha(line[i]))
		{
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
