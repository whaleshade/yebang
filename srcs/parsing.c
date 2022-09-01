#include "../includes/minishell.h"

static t_token	*is_and_or_pipe(t_token	*tokens);
// static t_token	*pass_parens(t_token *tokens);

void	parsing(t_node	*node)
{
	t_token	*left_token;
	t_token	*right_token;
	t_token	*root;

	if (!node)
		return ;
	left_token = NULL;
	right_token = NULL;
	root = NULL;
	if (node)
	{
		root = is_and_or_pipe(node->tokens);
		if (root && (root->type == AND || root->type == OR || root->type == PIPE))
		{
			// printf("parsing : root [%d] - %s\n",root->type, root->data);
			insert_node(&node->tokens, root);

			left_token = node->tokens;
			node->left = create_node(left_token);

			right_token = root->next;
			node->right = create_node(right_token);

			root->next = NULL;
			node->tokens = root;
			if (node->left == NULL || node->right == NULL)
				return ;
			parsing(node->left);
			parsing(node->right);
		}
		// redirect, parenthesis, world(cmd & str)
	}
}

static t_token	*is_and_or_pipe(t_token	*tokens)
{
	t_token	*buf;

	if (!tokens)
		return (NULL);
	buf = tokens;
	while (buf)
	{
		if (buf->type == AND || buf->type == OR)
			return (buf);
		buf = buf->next;
	}
	buf = tokens;
	while (buf)
	{
		if (buf->type == PIPE)
			return (buf);
		buf = buf->next;
	}
	return (NULL);
}

// static t_token	*is_pipe(t_token *tokens)
// {
// 	t_token	*buf;

// 	buf = tokens;
// 	while (buf)
// 	{
// 		if (buf->type == PIPE)
// 			return (buf);
// 		buf = buf->next;
// 	}

// 	return (NULL);
// }
// static t_token	*pass_parens(t_token *tokens)
// {
// 	t_token	*buf;

// 	buf = tokens;
// 	while (buf)
// 	{
// 		if (buf->type != PARENS)
// 			break ;
// 		buf = buf->next;
// 	}
// 	return (buf);
// }
