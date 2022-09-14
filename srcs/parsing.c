#include "../includes/minishell.h"

static t_token	*is_and_or_pipe(t_token	*tokens);
// static t_token	*pass_parens(t_token *tokens);

// int	tokens_counter(t_token *tokens)
// {
// 	int		cnt;

// 	cnt	= 0;
// 	if (tokens == NULL)
// 		return (0);
// 	while (tokens != NULL)
// 	{
// 		cnt++;
// 		tokens = tokens->next;
// 	}
// 	return (cnt);
// }


void	parsing(t_node	*node)
{
	t_token	*left_token;
	t_token	*right_token;
	t_token	*root;

	if (node == NULL)
		return ;
	left_token = NULL;
	right_token = NULL;
	root = NULL;
	if (node)
	{
		root = is_and_or_pipe(node->tokens);

		if (!root)
			return ;
		if (root && (root->type == AND || root->type == OR || root->type == PIPE))
		{
			node->type = node_type(root->type); //노드가 root일때 자체의 타입
			insert_node(&node->tokens, root);
			left_token = node->tokens;
			if (left_token == root)
			{
				right_token = root->next;
				node->right = create_node(right_token);
				root->next = NULL;
				node->tokens = root;
				parsing(node->right);
				return ;
			}
			node->left = create_node(left_token);
			right_token = root->next;
			node->right = create_node(right_token);

			root->next = NULL;
			node->tokens = root;

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
