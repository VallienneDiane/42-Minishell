/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:44:41 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/29 18:03:37 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_minishell(t_list *list, t_cmd *cmd, char **envp)
{
    while (list)
    {
        ft_start_exec(list, cmd, envp);
        ft_execution(cmd, envp);
    }
}

void    ft_start_exec(t_list *list, t_cmd *cmd, char **envp)
{
    int i;
    int j;
    int count;
    (void)envp;
	(void)cmd;

    i = 0;
    j = 0;
    count = 0;
    while (list)
    {
		if (ft_strncmp("str", list->type, 3) == 0)
			i++;
		else
			j++;
        printf("content : %s\n", list->content);
		list = list->next;
        count++;
    }
    // ft_create_tabs(cmd, i, j);
    while (count > 0 && list)
    {
        list = list->previous;
        count--;
		printf("count : %d\n", count);
    }
    // ft_fill_tabs(cmd, list);
}

// void    ft_create_tabs(t_cmd *cmd, int i, int j)
// {
//     if (!cmd->tab_str = malloc(sizeof(char *) * (i + 1)))
//     {
//         free(cmd->tab_str);
//         exit(EXIT_FAILURE);
//     }
//     if (!cmd->tab_redir = malloc(sizeof(char *) * (j + 1)))
//     {
//         free(cmd->tab_redir);
//         exit(EXIT_FAILURE);
//     }
// }

// void ft_fill_tabs(t_cmd *cmd, t_list *list)
// {
//     int i;

//     i = 0;
//     while (list->next)
//     {
//         if (ft_strcmp("str", list->type, 3) == 0)
//         {
//             if (!cmd->tab_str[i] = malloc(sizeof(char) * ft_strlen(list->content)))
//             {
//                 free(cmd->tab_str);
//                 exit(EXIT_FAILURE);
//             }
//             cmd->tab_str = list->content;
//             i++;
//         }
//         else
//             ft_tab_redir(cmd, list);
//         list = list->next;
//     }
// }

void ft_execution(t_cmd *cmd, char **envp)
{
    // if (cmd->redir_in || cmd->redir_out1 || cmd->redir_out2)
    //     ft_redir_dup(cmd, envp);
    // else
        ft_execute(cmd, envp);
}
