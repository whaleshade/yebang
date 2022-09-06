#include "../includes/minishell.h"



t_environ	*get_envp_list(char *line)
{
	t_environ	*env_list;

	env_list = NULL;
	make_env_list(line, &env_list);
	return (env_list);
}

void	make_env_list(char *line, t_environ **env_list)
{
	int		i;
	t_dict	dict;
	char	**tmp;

	printf("find $ : %s\n", line);
	tmp = NULL;
	i = 0;
	while (g_var.env[i])
	{
		tmp = ft_split(g_var.env[i], '=');
		dict.key = tmp[0];
		dict.value = tmp[1];
		lstadd_env_node(&dict, env_list);
		tmp = NULL;
		i++;
	}
}

void	lstadd_env_node(t_dict *dict, t_environ **env_list)
{
	t_environ	*tmp;

	tmp = env_lstnew(dict);
	if (!tmp)
	{
		printf("Error\n");
		exit(1);
	}
	env_lstadd_back(env_list, tmp);
}

t_environ	*env_lstnew(t_dict *dict)
{
	t_environ	*new_lst;

	new_lst = (t_environ *) malloc(sizeof(t_environ));
	if (!new_lst)
		return (NULL);
	new_lst->dict = dict;
	new_lst->next = NULL;
	return (new_lst);
}

void	env_lstadd_back(t_environ **lst, t_environ *new)
{
	t_environ	*tmp;

	tmp = NULL;
	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = env_lstlast(*lst);
	if (!tmp)
		return ;
	tmp->next = new;
}

t_environ	*env_lstlast(t_environ *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
