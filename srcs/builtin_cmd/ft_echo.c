#include "../../includes/minishell.h"

int	ft_echo(char *str);

int	main(int ac, char **av)
{
	ft_echo(av[1]);
}

int	ft_echo(char *str)
{
	printf("%s\n", str);
	return (0);
}
