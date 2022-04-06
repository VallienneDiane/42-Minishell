/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_diane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:36:32 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/06 17:31:04 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_builtin(char *str)
{
	if (str)
	{
		if (ft_strncmp("echo", str, 4) == 0 || ft_strncmp("pwd", str, 3) == 0)
			return (1);
	}
	return (0);
}

void	ft_start_exec(t_list *list, t_cmd *cmd, char **envp)
{	
	int	i;
	int	current_block;

	i = 0;
	current_block = 1;
	cmd->valid_path = NULL;
	while (list)
	{
		ft_get_args(list, cmd, current_block);
		if (list->next == NULL)
			exit(EXIT_SUCCESS);
		if ((ft_is_builtin(cmd->tab_str[0]) == 0))
			cmd->valid_path = ft_access_path(list, cmd);
		while (list && list->block == current_block)
			list = list->next;
		if (list && list->block != current_block)
		{
			ft_exec_pipex(list, cmd, envp);
			current_block++;
		}
		else
		{
			ft_execution(cmd, envp);
		}
		// free les tabs
	}
}

void	ft_execution(t_cmd *cmd, char **envp)
{
	if (cmd->tab_redir_in[0] || cmd->tab_redir_out1[0] || cmd->tab_redir_out2[0])
	{
		ft_redir_dup(cmd, envp);
	}		
	else
		ft_execute(cmd, envp);
}

void	ft_execute(t_cmd *cmd, char **envp)
{
	if (ft_is_builtin(cmd->tab_str[0]) == 1)
		exit (ft_exec_builtin(cmd));
	if (cmd->valid_path != NULL && ft_is_builtin(cmd->tab_str[0]) == 0)
	{
		// printf("valid path execute : %s\n", cmd->valid_path);
		if (execve(cmd->valid_path, cmd->tab_str, envp) < 0)
		{
			free(cmd->valid_path);
			free(cmd->tab_str);
			printf("Error : %s : failure execve\n", cmd->valid_path);	
		}
	}	
	// si heredoc seul ? si jamais il n'y a pas de nom de commande. exit 0
	// cat makefile | << del | echo hello
}

int	ft_exec_builtin(t_cmd *cmd)
{
	if (ft_strncmp("echo", cmd->tab_str[0], 4) == 0)
		return (ft_echo(cmd));
	if (ft_strncmp("pwd", cmd->tab_str[0], 3) == 0)
		return (ft_pwd(cmd));
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_list	*list;
	t_cmd	cmd;
	// char 	*line;
	
	(void)ac;
	(void)av;
	list = malloc(sizeof(t_list));
	list = NULL;
	// while (1)
	// 	line = readline("minishell > ");
	ft_create_list(&list);
	cmd.line_path = ft_get_line_path(envp);
	cmd.tab_path = ft_split(cmd.line_path, ':');
	ft_start_exec(list, &cmd, envp);
}
