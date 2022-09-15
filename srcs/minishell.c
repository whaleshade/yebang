#include "../includes/minishell.h"

static void	shell_loop(void);
static void	sig_handler(int signo);
static void	show_list_contents(t_list *ist);
static void	ft_nodisplay_ctrlx_set(void);
static void	ft_display_ctrlx_set(void);
static void	parse_exec(char *cli_str);
void	show_env_list(t_environ *env_list);

int	main(int ac, char **av, char **envp)
{
	/* START SCREEN */
	ft_start_screen();

	/* READ ENV */
	(void)ac;
	(void)av;
	g_var.status = 0;
	g_var.env = envp;

	/* TERMINAL INIT SETTINGS */
	ft_nodisplay_ctrlx_set();

	/* CMD LOOP */
	shell_loop(); // READ, PARSE, EXEC
	/* TERMINATE PROC */
	// YOUR CODE HERE

	ft_display_ctrlx_set();
	return (0);
}

static void	shell_loop()
{
	char 		*cli_str;

	while (LOOP)
	{
		signal(SIGINT, sig_handler); // ctrl + c ... before fork(), set default
		signal(SIGQUIT, SIG_IGN);	 // ctrl +'\'
		cli_str = readline("minsh$ ");
		if (cli_str)
		{
			parse_exec(cli_str);
		}
		else
		{
			printf("\033[1A");
			printf("\033[7C");
			printf("exit\n");
			free(cli_str);
			ft_display_ctrlx_set();
			exit(1);
		}
	}
}

static void	parse_exec(char *cli_str)
{
	t_minishell	sh;
	int			result;

	sh.envp = NULL;
	sh.list = NULL;
	sh.root = NULL;
	sh.tokens = NULL;
	sh.envp = get_envp_list();  //export 혹은 unset 실행할 때마다 env_list를 조작해야 함.
	show_env_list(sh.envp); //env list check..
	ft_lstadd_back(&sh.list, get_token_list(cli_str));
	// show_list_contents(sh.list);

	result = tokenizer(&sh);
	if ( result == ERROR)
	{
		add_history(cli_str); // shows the history of lines, by pressing arrows
		free(cli_str);
		cli_str = NULL;
	}
	else
	{
		// show_tokens_data(sh.tokens);
		sh.root = create_node(sh.tokens);
		parsing(sh.root);
		// show_node_data(sh.root, "root");
		show_wordnode_data(sh.root, "......FOR REDIRECTIONS......"); //for redirection
		exec_parse_tree(sh.root, sh.envp); //for execution
		add_history(cli_str); // shows the history of lines, by pressing arrows
		free(cli_str);
		cli_str = NULL;

		/* REDIR CODE */
		// if (redir_parse_tree(&sh) == ERROR)
		// 	ft_perror("Redirection");
		/*	EXEC CODE	*/
		// if (exec_parse_tree(sh) == ERROR)
		// 	ft_perror("Execution");
	}
}

static void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();		 // make new prompt line
		rl_replace_line("", ON); // replace the contents of rl_line_buffer with text in line, If clear_undo is non-zero, the undo list associated with the current line is cleared.
		rl_redisplay();			 // show the current content of rl_line_buffer;
	}
	return;
}

void	show_env_list(t_environ *env_list)
{
	t_environ *tmp;

	tmp = env_list;
	while (tmp)
	{
		printf("show : %s === %s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

static void	show_list_contents(t_list *list)
{
	t_list	*tmp;

	if (!list)
		return;
	tmp = list;
	printf("\033[0;31m");
	printf("list : \n");
	while (tmp)
	{
		printf("\033[0;31m");
		printf("[%s]", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("\n");
	printf("\n\033[0;0m\x1b[1A\x1b[M");
}

void	show_tokens_data(t_token *tokens)
{
	t_token *tmp;

	if (!tokens)
		return;
	tmp = tokens;
	printf("\033[0;33m");
	printf("token : \n");
	printf("token type = %d\n", tmp->type);
	while (tmp)
	{
		printf("\033[0;33m");
		printf("[%s]", tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
	printf("\n\033[0;0m\x1b[1A\x1b[M");
}

void	show_node_data(t_node *node, char *str)
{
	t_node	*tmp;

	if (!node)
		return;
	tmp = node;
	if (!tmp)
		return;
	printf("\033[0;36m");
	printf("node  - %s :\n", str);
	show_tokens_data(node->tokens);
	show_node_data(tmp->left, "left");
	show_node_data(tmp->right, "right");
	// printf("\n");
	printf("\n\033[0;0m\x1b[1A\x1b[M");
}
// use tcsetattr and tcgetattr to modify your terminal settings.
// clear the ECHOCTL bit flag to suppress output from Ctrl-based signals.

static void	ft_nodisplay_ctrlx_set(void)
{
	if (tcgetattr(STDIN_FILENO, &g_var.settings) == ERROR)
		ft_perror("minsh: tcgetattr");
	g_var.settings.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_var.settings) == ERROR)
		ft_perror("minsh: tcsetattr");
}

static void	ft_display_ctrlx_set(void)
{
	if (tcgetattr(STDIN_FILENO, &g_var.settings) == ERROR)
		ft_perror("minsh: tcgetattr");
	g_var.settings.c_lflag &= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_var.settings) == ERROR)
		ft_perror("minsh: tcsetattr");
}

void	ft_perror(char *str)
{
	printf("%s %s\n", str, strerror(errno));
}
