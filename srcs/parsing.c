#include "../includes/minishell.h"

static t_token	*is_and_or_pipe(t_token	*tokens);
static t_token	*pass_parens(t_token *tokens);

void	parsing(t_node	*node)
{
	t_token	*root;

	if (node)
	{
		root = is_and_or_pipe(node->tokens);
		if (root && (root->type == TK_AND || root->type == TK_OR || root->type == TK_PIPE))
		{
			insert_node(node->tokens, root);
			node->left = create_node(node->tokens);
			node->tokens = NULL;
			node->right = create_node(root->next);
			del_token(root);
			parsing(node->left);
			parsing(node->right);
		}
		else 
		{
			insert_node(node->tokens, root);
			node->right = create_node(root);
			parsing(node->right); 
		}
	}
}

static t_token	*is_and_or_pipe(t_token	*tokens)
{
	t_token	*buf;

	buf = tokens;
	while (buf)
	{
		if (buf->type == AND || buf->type == OR)
			return (buf);
		if (buf->type == PIPE)
			return (buf);
		if (buf->type == L_PARENS)
			buf = pass_parens(buf);
		buf = buf->next;
	}
	return (NULL);
}

static t_token	*pass_parens(t_token *tokens)
{
	t_token	*buf;

	buf = tokens;
	while (buf)
	{
		if (buf->type != L_PARENS)
			break ;
		buf = buf->next;
	}
	return (buf);
}