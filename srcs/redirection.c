#include "../includes/minishell.h"

void	show_wordnode_data(t_node *node, char *str)
{
	t_node	*tmp;

	if (!node)
		return;
	tmp = node;
	if (!tmp)
		return;
	printf("\033[0;36m");
	printf("============== %s :\n", str);
	printf("===node type = %d\n",tmp->type);
	// if (tmp->tokens->type == CMD)
	if (tmp->type == TK_WORD)
	{
		show_tokens_data(node->tokens);
		printf("--------------------------\n");
	}
	show_wordnode_data(tmp->left, "left");
	show_wordnode_data(tmp->right, "right");
	// printf("\n");
	printf("\n\033[0;0m\x1b[1A\x1b[M");
}



/*
static void	show_word_tokens_data(t_token *tokens);
static void	show_word_node_data(t_node *node);


int	redir_parse_tree(t_minishell *sh)
{
	int		result;
	t_node	*node;

	if (!sh)
		return (ERROR);
	node = sh->root;
	recursive(node);
	//recursice(node);
	result = SUCCESS;
	return (result);
}


void	recursive(t_node *node)
{
	if (node->type == TK_WORD)
	{
		show_word_tokens_data(node->tokens);
	}
	recursive(node->left);
	recursive(node->right);
}

static void	show_word_tokens_data(t_token *tokens)
{
	t_token *tmp;

	if (!tokens)
		return;
	tmp = tokens;
	printf("\033[0;33m");
	printf("token : \n");
	while (tmp)
	{
		printf("\033[0;33m");
		printf("[%s]", tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
	printf("\n\033[0;0m\x1b[1A\x1b[M");
}

static void	show_word_node_data(t_node *node)
{
	t_node	*tmp;

	if (!node)
		return ;
	tmp = node;
	if (!tmp)
		return ;
	printf("\033[0;36m");
	printf("word node  - \n");
	show_tokens_data(node->tokens);
	printf("\n\033[0;0m\x1b[1A\x1b[M");
}
*/
