/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:45:02 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/11 14:33:56 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_list  *ft_lstlast(t_list *lst)
// {
// 	t_list  *temp;
// 	t_list  *actual;

// 	temp = lst;
// 	actual = lst;
// 	while (temp)
// 	{
// 		actual = temp;
// 		temp = temp->next;
// 	}
// 	return (actual);
// }

// void    ft_lstadd_back(t_list **alst, t_list *new)
// {
// 	t_list  *last;

// 	if (!*alst)
// 		*alst = new;
// 	else
// 	{
// 		last = ft_lstlast(*alst);
// 		last->next = new;
// 	}
// }

// t_list  *ft_lstnew(void *str, void *type)
// {
// 	t_list  *newlist;

// 	newlist = malloc(sizeof(t_list));
// 	if (!newlist)
// 		return (NULL);
// 	newlist->str = str;
// 	newlist->type = type;
// 	newlist->next = NULL;
// 	return (newlist);
// }

// void	ft_create_list(t_list **list)
// {
// 	ft_lstadd_back(list, ft_lstnew("cat", "cmd"));
// 	ft_lstadd_back(list, ft_lstnew("test.txt", "str"));
// 	ft_lstadd_back(list, ft_lstnew("|", "pipe"));
// 	ft_lstadd_back(list, ft_lstnew("wc", "cmd"));
// 	ft_lstadd_back(list, ft_lstnew("-n", "option"));
// 	ft_lstadd_back(list, ft_lstnew(">", "redir"));
// 	ft_lstadd_back(list, ft_lstnew("result", "str"));
// }

// void	ft_print_list(t_list *list)
// {
// 		// printf("COUCOUOCUO\n");
// 	while (list->next) // 
// 	{
// 		printf("\033[93m%s | %s\n\033[0m", list->str, list->type);
// 		list = list->next;
// 	}
// 	printf("\033[93m%s | %s\n\033[0m", list->str, list->type);
// 	// sleep(1);
// 	// while (list)
// 	// {
// 	// 	printf("'%s' | '%s'\n", list->str, list->type);
// 	// 	list = list->previous;
// 	// }
// }

void	ft_pipe(char *line, t_pars_info *p_info)
{
	int	j;

	j = p_info->i + 1;
	while (line[j] == ' ')
		j++;
	if (!line[j] || line[j] == '|')
	{
		printf("Pipe error\n");
		exit(EXIT_FAILURE);
	}
	p_info->current_block++;
	p_info->i += 1;
}

void	ft_lexer(t_list **list, char *line, t_pars_info *p_info)
{
	if (line[p_info->i] == '<')
		ft_redir_in(line, p_info);
	else if (line[p_info->i] == '>')
		ft_redir_out(line, p_info);
	else if (line[p_info->i] == '|')
		ft_pipe(line, p_info);
	else
		p_info->i = ft_str(list, line, p_info);
}

void	ft_parsing(t_list **list, char *line)
{
	t_pars_info	p_info;

	p_info.i = 0;
	p_info.current_type = STR;
	p_info.current_block = 1;
	p_info.d_quote = 0;
	while (line[p_info.i])
	{
		while (line[p_info.i] && line[p_info.i] == ' ')
			p_info.i++;
		if (line[p_info.i])
			ft_lexer(list, line, &p_info);
	}
}

int	main(int ac, char **av, char **env)
{
	char 	*line;
	pid_t	pid;
	t_list	*list;
	t_cmd	cmd;
	
	errno = 0;
	while (1)
	{
		list = malloc(sizeof(t_list));
		list = NULL;
		line = readline("> ");
		// if line n'est pas vide > add_history
		add_history(line);
		ft_parsing(&list, line);
		free(line);
		// ft_print_list(list);
		cmd.line_path = ft_get_line_path(env);
		cmd.tab_path = ft_split(cmd.line_path, ':');
		pid = fork();
		if (pid < 0)
		{
			perror("");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			ft_start_exec(list, &cmd, env);
		else
			waitpid(pid, NULL, 0);
		free(list);
	}
	(void)ac;
	(void)av;
	(void)env;
}
