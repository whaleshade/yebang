#include "../includes/minishell.h"

static int	is_forbidden_char(char *c);

int	syntax_error(t_list *list)
{
	t_list	*node;

	node = list;
	while (node)
	{
		if (is_forbidden_char((char *)node->content))
			return (ERROR);
		node = node->next;
	}
	return (SUCCESS);
}

static int	is_forbidden_char(char *c)
{
	int		result;

	result = FALSE;
	// if (*c != '$' || *c != '&' || *c != '*' || *c != '('
	// 	|| *c != ')' || *c != '=' || *c != '|' || *c != '\"'
	// 	|| *c != '\'' || *c != '.' || *c != '?' || *c != '/'
	// 	|| *c != '\\' || *c != '-' || *c != '<' || *c != '>'
	// 	|| *c != ' ' || !ft_isalnum(*c) || *c != '\0' || *c != '\n')
	// if (*c == '!' || *c == '@' || *c == '~' || *c == '#' || *c == '%' || *c == '^' || *c == '+' || *c == '{' || *c == '}' || *c == '[' || *c == ']' || *c == ':' || *c == ';' || *c == ',' || *c == '\\')

	if (*c == '!')
	{
		result = TRUE;
	}
	return (result);
}
