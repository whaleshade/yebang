#include "../../includes/minishell.h"

//이렇게 하면 안 되고 env list를 만들어서 관리해야 할듯...getenv() 사용 못하기 때문
int	ft_env(char **env);

int	main(int ac, char **av, char **env)
{
	ft_env(env);
}

int	ft_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
