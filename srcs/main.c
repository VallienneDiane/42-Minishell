/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:45:02 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/22 16:45:37 by dvallien         ###   ########.fr       */
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
		printf("Pipe error\n");
		exit(EXIT_FAILURE); ///////
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
	p_info.cmd = cmd;
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
	t_list	*list;
	t_cmd	cmd;
	
	g_status = 0;
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
		ft_start_exec(list, &cmd);
		free(list);
	}
	(void)ac;
	(void)av;
}
