/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:45:02 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/28 15:17:43 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	ft_free_split(char **av)
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

void	ft_init_main(t_cmd *cmd, char **env)
{
	g_status = 0;
	ft_cpy_env(env, cmd);
	signal(SIGINT, ft_signal_handler);
	cmd->stdin_copy = dup(STDIN_FILENO);
}

void	ft_manage_line(t_list **list, char **line, t_cmd *cmd)
{
	if (!*line)
		exit(0);
	if (*line && *line[0])
		add_history(*line);
	if (*line)
		ft_parsing(list, *line, cmd);
	free(*line);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_list	*list;
	t_cmd	cmd;

	ft_init_main(&cmd, env);
	while (1)
	{
		dup2(cmd.stdin_copy, STDIN_FILENO);
		list = NULL;
		ft_term_handler(0);
		line = readline("miniHell$ ");
		ft_term_handler(1);
		ft_manage_line(&list, &line, &cmd);
		cmd.line_path = ft_get_line_path(&cmd);
		cmd.tab_path = ft_split(cmd.line_path, ':');
		if (!cmd.parse_error)
			ft_start_exec(list, &cmd);
		ft_free_split(cmd.tab_path);
		ft_lstclear(&list);
	}
	(void)ac;
	(void)av;
}
