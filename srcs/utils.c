#include "../includes/minishell.h"

void	ft_perror(char *str)
{
	printf("%s %s\n", str, strerror(errno));
}

int	whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != 32 && !(line[i] >= 9 && line[i] <= 13))
			return (0);
		i++;
	}
	return (1);
}

// 스페이스 빼고
// 괄호 짝수 안맞는거
// 백슬레스 확인
// 엔드 하나인경우 특수문자 등 맨 마지막 실행 단계에서 확인 하는 걸로.

// 1. 토크나이저 -> t_list 함수 사용 -> 
// 2. t_token에 t_list contents 삽입 -> 스페이스 등 공백 삭제
// 3. 서브쉘 ?? 어떻게 
// 4. 트리 확인

