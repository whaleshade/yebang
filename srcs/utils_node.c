#include "../includes/minishell.h"

t_node	*create_node(t_token *tokens)
{
	int		type;
	t_node	*root;

	root = NULL;
	if (tokens == NULL)
		return (NULL);
	root = ft_calloc(1, sizeof(t_node));
	if (!root)
	{
		printf("Error\n");
		exit(1);
	}
	// printf("input token type = %d\n", tokens->type); //뭔가 이상함. 다 3으로 입력
	type = node_type(tokens->type);

	root->type = type;
	root->tokens = tokens;
	root->state = TRUE; //실행을 위한 초기 세팅
	// show_node_data(root);
	return (root);
}

void	insert_node(t_token **tokens, t_token *root)
{
	t_token	*token;

	token = NULL;
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
	// printf("@@@ inseted node type : %d\n", root->type);
}

void	del_node(t_node *node)
{
	if (!node)
		return ;
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
	// else if (token_type == HERE_DOC || token_type == APP_RD || token_type == INP_RD || token_type == OUT_RD)
	// 	node_type = TK_REDIR;
	else if (token_type == PARENS) //|| token_type == R_PARENS)
		node_type = TK_PARENS;
	else
		node_type = TK_WORD;
	return (node_type);
}
