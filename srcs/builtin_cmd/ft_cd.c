#include "../../includes/minishell.h"

char	*prev_path; //전역 구조체 변수에 저장..혹은 OLDPWD?
//OLDPWD를 getenv()를 이용해 가져오면 될듯?

int	ft_cd(char *path);

int	main(int ac, char **av)
{
	if (ac == 1)
	{
		chdir("~");
		printf("%s\n", getcwd(NULL, 0));
	}
	else
		ft_cd(av[1]);
	return (0);
}


int	ft_cd(char *path)
{
	if (strncmp(path, "-", 2) == 0)
	{
		if (chdir(prev_path) == -1)
		{
			printf("minsh: cd: OLDPWD not set\n");
			return (-1);
		}
		printf("%s\n", getcwd(NULL, 0));
	}
	if (strncmp(path, ".", 2) == 0 || strncmp(path, "./", 3) == 0)
	{
		if (chdir("./") == -1)
			return (-1);
		printf("%s\n", getcwd(NULL, 0));
	}
	else if (strncmp(path, "..", 3) == 0 || strncmp(path, "../", 4) == 0)
	{
		if (chdir("../") == -1)
			return (-1);
		printf("%s\n", getcwd(NULL, 0));
	}
	else
	{
		if (chdir(path) == -1)
		{
			printf("minsh: cd: %s: Not a directory\n", path);
			return (-1);
		}
		printf("%s\n", getcwd(NULL, 0));
	}
	prev_path = getcwd(NULL, 0);
	return (0);
}
