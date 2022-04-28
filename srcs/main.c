/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:45:02 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/28 10:20:06 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pipe(char *line, t_pars_info *p_info)
{
	int	j;

	j = p_info->i + 1;
	while (line[j] == ' ')
		j++;
	if (!line[j] || line[j] == '|')
	{
		if (!p_info->error)
		{
			printf("miniHell: syntax error near unexpected token `|'\n");
			g_status = 258;
		}
		p_info->error = 1;
		// return ;
		// exit(EXIT_FAILURE); ///////
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

void	ft_parsing(t_list **list, char *line, t_cmd *cmd)
{
	t_pars_info	p_info;

	p_info.i = 0;
	p_info.current_type = STR;
	p_info.current_block = 1;
	p_info.d_quote = 0;
	p_info.error = 0;
	p_info.cmd = cmd;
	while (line[p_info.i])
	{
		while (line[p_info.i] && line[p_info.i] == ' ')
			p_info.i++;
		if (line[p_info.i])
			ft_lexer(list, line, &p_info);
	}
	if (p_info.error)
		cmd->parse_error = 1;
	else
		cmd->parse_error = 0;
}

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	temp = *lst;
	while (*lst)
	{
		*lst = temp->next;
		free(temp->content);
		free(temp);
		temp = *lst;
	}
}

void	ft_free_path(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

int	main(int ac, char **av, char **env)
{
	char 	*line;
	t_list	*list;
	t_cmd	cmd;
	
	g_status = 10;
	ft_cpy_env(env, &cmd);
	signal(SIGINT, ft_signal_handler);
	cmd.stdin_copy = dup(STDIN_FILENO);
	while (1)
	{
		dup2(cmd.stdin_copy, STDIN_FILENO);
		list = malloc(sizeof(t_list));
		list = NULL;
		ft_term_handler(0);
		line = readline("miniHell$ ");
		ft_term_handler(1);
		if (line && line[0])
			add_history(line);
		if (!line)
			exit(0);
		if (line)
			ft_parsing(&list, line, &cmd);
		free(line);
		// ft_print_list(list);
		cmd.line_path = ft_get_line_path(&cmd);
		cmd.tab_path = ft_split(cmd.line_path, ':');
		if (!cmd.parse_error)
			ft_start_exec(list, &cmd);
		ft_free_path(cmd.tab_path);
		ft_lstclear(&list);	
		free(list);
	}
	(void)ac;
	(void)av;
}
