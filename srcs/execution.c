#include "../../includes/minishell.h"

static int	cmd_exec(t_node *words);

void	exec_parse_tree(t_node *node, t_environ *envp)
{
	t_node	*tmp;
	int		res;

	if (!node)
		return ;
	tmp = node;
	exec_parse_tree(node->left, envp);
	if (node->type == TK_WORD)
	{
		res = cmd_exec(node->words);
		if (res == SUCCESS)
			exec_parse_tree(node->right, envp);
		else
		{
			//ERROR CODE
			;
		}
	}
}

static int	cmd_exec(t_node *words)
{

}
