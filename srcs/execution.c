#include "../includes/minishell.h"

static int	cmd_exec(t_node *node);
void	show_env_list(t_environ *env_list);

void	exec_parse_tree(t_node *node, t_environ *envp)
{
	t_node	*tmp;
	static int		res;

	res = SUCCESS;
	if (!node)
		return ;
	tmp = node;
	exec_parse_tree(node->left, envp);

	// if (node->type == TK_PIPE)
	// {
	// 	// fork()
	// 	// left
	// }
	if (node->type == TK_WORD)
	{
		printf("...EXEC...\n");
		// show_env_list(envp);//잘 출력됨
		res = cmd_exec(node);
		if (res == ERROR)
		{
			printf("EXEC ERROR\n");
		}
	}
	if (res == ERROR && node->type == TK_OR)
		res = SUCCESS;
	else if (res == ERROR && node->type == TK_AND)
		res = ERROR;
	if (res == ERROR && node->type != TK_PIPE)
		return ;

	exec_parse_tree(node->right, envp);
}

static int	cmd_exec(t_node *node)
{
	int		result;

	result = SUCCESS;
	if (ft_strncmp(node->tokens->data, "B", 1) == 0)
		result = ERROR;
	else
		show_tokens_data(node->tokens);
	return (result);
}
