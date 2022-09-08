#include "../includes/minishell.h"

void	env_lstadd_back(t_environ **lst, t_environ *new);
void	make_env_list(t_environ **env_list);
void	lstadd_env_node(char *key, char *value, t_environ **env_list);
t_environ	*env_lstnew(char *key, char *value);
t_environ	*env_lstlast(t_environ *lst);

t_environ	*get_envp_list(void)
{
	t_environ	*env_list;

	env_list = NULL;
	make_env_list(&env_list);
	return (env_list);
}

void	make_env_list(t_environ **env_list)
{
	int		i;
	char	*key;
	char	*value;
	char	**tmp;

	tmp = NULL;
	i = 0;
	while (g_var.env[i])
	{
		tmp = ft_split(g_var.env[i], '=');
		key = tmp[0];
		value = tmp[1];
		lstadd_env_node(key, value, env_list);
		tmp = NULL;
		i++;
	}
}

void	lstadd_env_node(char *key, char *value, t_environ **env_list)
{
	t_environ	*new;

	new = env_lstnew(key, value);
	if (!new)
	{
		printf("Error\n");
		exit(1);
	}
	env_lstadd_back(env_list, new);
}

t_environ	*env_lstnew(char *key, char *value)
{
	t_environ	*new_lst;

	new_lst = (t_environ *) malloc(sizeof(t_environ));
	if (!new_lst)
		return (NULL);
	new_lst->key = key;
	new_lst->value = value;
	new_lst->next = NULL;
	return (new_lst);
}

void	env_lstadd_back(t_environ **env_list, t_environ *new)
{
	t_environ	*tmp;
	t_environ	*tmp2;

	tmp = NULL;
	if (env_list == NULL || new == NULL)
		return ;
	if (*env_list == NULL)
	{
		*env_list = new;
		return ;
	}
	tmp2 = *env_list;
	tmp = env_lstlast(tmp2);
	tmp->next = new;
}

t_environ	*env_lstlast(t_environ *env_list)
{
	t_environ	*tmp;

	tmp = env_list;
	if (tmp == NULL)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}
