/* ************************************************************************** */
/*	                                                                    */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:44:25 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/19 11:58:11 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec_cmd(t_list *list, t_cmd *cmd, char **envp)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (list->next && ft_strncmp("pipe", list->type, 4) != 0)
	{
		if (ft_strncmp("redir", list->type, 5) != 0)
			i++;
		// else	
		// 	ft_redir(list, cmd, envp);
		list = list->next;
		count++;
	}
	ft_create_tab_args(list, cmd, i);
	while (count > 0)
	{
		list = list->previous;
		count--;
	}
	ft_fill_args(list, cmd, envp);
}

void	ft_create_tab_args(t_list *list, t_cmd *cmd, int i)
{
	if (ft_strncmp("redir", list->type, 5) != 0 && \
	ft_strncmp("pipe", list->type, 4) != 0)
		i++;
	cmd->tab_args = malloc(sizeof(char *) * (i + 1));
	if (!cmd->tab_args)
	{
		free (cmd->tab_args);
		exit(EXIT_FAILURE);
	}
}

void	ft_fill_args(t_list *list, t_cmd *cmd, char **envp)
{
	int	i;

	i = 0;
	while (list->next && ft_strncmp("pipe", list->type, 4) != 0)
	{
		if (ft_strncmp("redir", list->type, 5) != 0)
		{
			cmd->tab_args[i] = malloc(sizeof(char) * ft_strlen(list->content));
			if (!cmd->tab_args[i])
			{
				free (cmd->tab_args);
				exit(EXIT_FAILURE);
			}
			cmd->tab_args[i] = list->content;
			printf("tab args %s\n", cmd->tab_args[i]);
			i++;
		}
		list = list->next;
	}
	ft_fill_args_bis(list, cmd, i, envp);
}

// ------------ si c'est un pipe alors renvoie vers pipex et execute
// ------------ sinon execute directement
void	ft_fill_args_bis(t_list *list, t_cmd *cmd, int i, char **envp)
{
	if (ft_strncmp("redir", list->type, 5) != 0 && \
	ft_strncmp("pipe", list->type, 4) != 0)
	{
		cmd->tab_args[i] = malloc(sizeof(char) * ft_strlen(list->content));
		if (!cmd->tab_args[i])
		{
			free (cmd->tab_args);
			exit(EXIT_FAILURE);
		}
		cmd->tab_args[i] = list->content;
		printf("tab args %s\n", cmd->tab_args[i]);
		i++;
	}
	cmd->tab_args[i] = 0;
	if (ft_strncmp("pipe", list->type, 4) == 0)
	{
		list = list->next;
		ft_exec_pipex(list, cmd, envp);
		ft_parse_type(list, cmd, envp);
	}
	else
		ft_execute(cmd, envp);
}

void	ft_execute(t_cmd *cmd, char **envp)
{
	// fprintf(stderr, "fin fd1 %d\n", cmd->fd1);
	if (execve(cmd->valid_path, cmd->tab_args, envp) < 0)
	{
		free(cmd->valid_path);
		free(cmd->tab_args);
		printf("Error : failure execve\n");
	}
}
