#include "../../includes/minishell.h"

int	ft_exit();

int	main(int ac, char **av)
{
	ft_exit(av[1]);
}

int	ft_exit(char *exit_code)
{
	int		code;
	code = atoi(exit_code);
	exit(code);
}
