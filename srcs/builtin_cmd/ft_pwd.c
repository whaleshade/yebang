#include "../../includes/minishell.h"

int	ft_pwd(void);

int	main()
{
	ft_pwd();
	return (0);
}

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		printf("path not found\n");
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}
