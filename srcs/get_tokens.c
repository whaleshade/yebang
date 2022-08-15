/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:39:55 by jibang            #+#    #+#             */
/*   Updated: 2022/08/15 19:36:35 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	isthere_quote(char *str)
// {
// 	int		i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\"')
// 			return (TRUE);
// 		i++;
// 	}
// 	return (FALSE);
// }

// char	**get_splited_args(char *line)
// {
// 	char	**tmp1;
// 	char	**tmp2;
// 	char	**arg;

// 	tmp1 = ft_split(line, '\"');
// 	int		i;
// 	i = 0;
// 	while (tmp1[i])
// 	{
// 		if (isthere_quote(tmp1[i]) == TRUE)
// 		{

// 		}
// 		i++;
// 	}
// 	return (arg);
// }

void	make_token_list(char *token, t_list **token_list)
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
	char	**arg;
	t_list	*token_list;
	int		i;

	token_list = NULL;
	arg = ft_split(line, ' ');
	i = 0;
	while (arg[i])
	{
		make_token_list(arg[i], &token_list);
		i++;
	}
	return (token_list);
}
