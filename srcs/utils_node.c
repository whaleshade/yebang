#include "../includes/minishell.h"

t_node	*create_node(t_token *tokens)
{
	int		type;
	t_node	*root;

	root = ft_calloc(1, sizeof(t_node));
	if (!root)
	{
		printf("Error\n");
		exit(1);
	}
	type = node_type(tokens->type);
	root->type = type;
	root->tokens = tokens;
	return (root);
}

void	insert_node(t_token *token, t_token *root)
{
	if (!token || root)
		return ;
	while (token->next)
	{
		if (token->next == root)
			break;
		token = token->next;
	}
	token->next = NULL;
}

void	del_node(t_node *node)
{
	if (node)
	{
		del_node(node->left);
		del_node(node->right);
		del_token(node->tokens);
		free(node);
		node = NULL;
	}
}

int	node_type(int token_type)
{
	int	node_type;

	node_type = 0;
	if (token_type == AND)
		node_type = TK_AND;
	else if (token_type == OR)
		node_type = TK_OR;
	else if (token_type == PIPE)
		node_type = TK_PIPE;
	else if (token_type == HERE_DOC || token_type == APP_RD || token_type == INP_RD || token_type == OUT_RD)
		node_type = TK_REDIR;
	else if (token_type == L_PARENS || token_type == R_PARENS)
		node_type = TK_PARENS;
	else if (token_type == STR || token_type == CMD)
		node_type = TK_WORD;
	return (node_type);
}