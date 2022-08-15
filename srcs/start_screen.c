#include "../includes/minishell.h"

void	ft_start_screen(void)
{
	int		i;
	int		fd;
	char	*line;
	int		color;

	i = 0;
	color = 31;
	fd = open("yebang_shell.txt", O_RDONLY);
	// fd = open("vaccine_shell.txt", O_RDONLY);
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
