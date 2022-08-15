/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:39:55 by jibang            #+#    #+#             */
/*   Updated: 2022/08/15 13:39:56 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	printf("test: %s\n", arg[i]);
	return (token_list);
}
