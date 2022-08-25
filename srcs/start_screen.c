/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeblee <yeblee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 01:25:03 by yeblee            #+#    #+#             */
/*   Updated: 2022/08/26 01:44:18 by yeblee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_start_screen(void)
{
	int		i;
	int		fd;
	char	*line;
	int		color;

	i = 0;
	color = 31;
	fd = open("welcome.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (++i % 8 == 0)
			color++;
		printf("\033[0;%dm%s", color, line);
		free(line);
	}
	free(line);
	printf("\n\033[0;0m\x1b[1A\x1b[M");
}
