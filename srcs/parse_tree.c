
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
	// show_node_data(root);
	return (root);
}


void	insert_node(t_token **tokens, t_token *root)
{
	t_token	*token;

	if (!tokens || !root)
		return ;
	token = *tokens;
	while (token->next)
	{
		if (token->next == root)
			break ;
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
	else if (token_type == PARENS)
		node_type = TK_PARENS;
	else if (token_type == STR || token_type == CMD)
		node_type = TK_WORD;
	return (node_type);
}

static t_token	*is_and_or_pipe(t_token	*tokens);
static t_token	*pass_parens(t_token *tokens);

void	parsing(t_node	*node)
{
	t_token	*left_token;
	t_token	*right_token;
	t_token	*root;

	if (node)
	{
		root = is_and_or_pipe(node->tokens);
		if (root && (root->type == TK_AND || root->type == TK_OR || root->type == TK_PIPE))
		{
			// printf("parsing : root [%d] - %s\n",root->type, root->data);
			insert_node(&node->tokens, root);

			left_token = node->tokens;
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

	buf = tokens;
	while (buf)
	{
		if (buf->type == AND || buf->type == OR)
			return (buf);
		if (buf->type == PIPE)
			return (buf);
		// if (buf->type == PARENS)
		// 	buf = pass_parens(buf);
		buf = buf->next;
	}
	return (NULL);
}

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
