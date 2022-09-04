#include "../includes/minishell.h"

static int	is_forbidden_char(char *c);
static int	is_invalid_opt_syntax(t_list *list);
static int	is_paired_parens(char *str);
static int	is_unclosed_quote(char *str);

//syntax error 리턴값별로 perror 문구 다르게
int	syntax_error(t_list *list)
{
	while (list)
	{
		if (is_forbidden_char((char *)list->content) == TRUE)
			return (ERROR);
		if (ft_strncmp(list->content, "&", 2) == 0)
			return (ERROR);
		if (ft_strncmp(list->content, ")", 2) == 0)
			return (ERROR);
		if (ft_strncmp(list->content, "(", 1) == 0 && is_paired_parens(list->content) == FALSE)
			return (ERROR);
		if (is_invalid_opt_syntax(list) == TRUE)
			return (ERROR);
		if ((ft_strncmp(list->content, "\"", 1) == 0 || ft_strncmp(list->content, "\'", 1) == 0)\
			&& is_unclosed_quote(list->content) == TRUE)
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

static int	is_paired_parens(char *str)
{
	int		i;
	int		par_cnt;

	par_cnt = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '(')
			par_cnt++;
		if (str[i] == ')')
			par_cnt--;
		i++;
	}
	if (par_cnt != 0)
		return (FALSE);
	return (TRUE);
}

static int	is_unclosed_quote(char *str)
{
	int		i;
	int		len;
	int		result;

	len = ft_strlen(str);
	i = 0;
	result = TRUE;
	if (str[i] == '\'')
	{
		if (str[len - 1] == '\'')
			result = FALSE;
	}
	else if (str[i] == '\"')
	{
		if (str[len - 1] == '\"')
			result = FALSE;
	}
	return (result);
}
