#include "../includes/minishell.h"

static int	is_forbidden_char(char *c);
static int	is_invalid_opt_syntax(t_list *node);

//syntax error 리턴값별로 perror 문구 다르게
int	syntax_error(t_list *list)
{
	while (list)
	{
		if (is_forbidden_char((char *)list->content))
			return (ERROR);
		if (is_invalid_opt_syntax(list))
			return (ERROR);
		list = list->next;
	}
	return (SUCCESS);
}

static int	is_forbidden_char(char *c)
{
	int		result;

	result = FALSE;
	if (*c == '!' || *c == '@' || *c == '~' || *c == '#'\
		|| *c == '%' || *c == '^' || *c == '+' || *c == '{'\
		|| *c == '}' || *c == '[' || *c == ']' || *c == ':'\
		|| *c == ';' || *c == ',' || *c == '\\')
	{
		result = TRUE;
	}
	return (result);
}

static int	is_invalid_opt_syntax(t_list *list)
{
	int		result;

	result = FALSE;
	while (list)
	{
		if (list->next != NULL && ft_strncmp(list->next->content, "-", 1) == 0)
		{
			if (ft_strncmp(list->content, " ", 1) != 0)
				result = TRUE;
		}
		if (ft_strncmp(list->content, "-", 1) == 0)
		{
			if (list->next != NULL && ft_strncmp(list->next->content, " ", 1) == 0)
				result = TRUE;
		}
		list = list->next;
	}
	return (result);
}
