#include "../../includes/minishell.h"

int	exec_parse_tree(t_minishell *sh)
{
	int		result;
	t_node	*node;

	result = SUCCESS;
	if (!sh)
		return (ERROR);
	node = sh->root;
	if (node->type == TK_AND || node->type == TK_OR)
		node = node->left;
	if (node->type == TK_PIPE)
		node = node->left;
	if (node->type == TK_WORD)



	return (result);
}

void	show_node_data(t_node *node, char *str)
{
	t_node	*tmp;

	if (!node)
		return ;
	tmp = node;
	if (!tmp)
		return ;
	printf("\033[0;36m");
	printf("node  - %s :\n", str);
	show_tokens_data(node->tokens);
	show_node_data(tmp->left, "left");
	show_node_data(tmp->right, "right");
	// printf("\n");
	printf("\n\033[0;0m\x1b[1A\x1b[M");
}
