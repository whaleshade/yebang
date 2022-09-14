#include "../includes/minishell.h"

//redir() 함수..

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
		//words와 redir으로 리스트 생성 ... 혹은 바로 redir 설정?
		printf("--------------------------\n");
	}
	show_wordnode_data(tmp->left, "left");
	show_wordnode_data(tmp->right, "right");
	// printf("\n");
	printf("\n\033[0;0m\x1b[1A\x1b[M");
}

