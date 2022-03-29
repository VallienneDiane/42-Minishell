/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:26:21 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/29 17:27:00 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// int   ft_tab_redir(t_cmd *cmd, t_list *list)
// {
//     if (ft_strcmp("redir_in", list->type, 8) == 0)
//     {
//         if (!(cmd->redir_in = malloc(sizeof(char) * ft_strlen(cmd->nb_redir) + 1)))
//             return (-1);
//         if (create_file(cmd, 0) == -1)
//             return (-1);
//     }
//     else if (ft_strcmp("redir_out1", list->type, 8) == 0)
//     {
//         if (!(cmd->redir_out1 = malloc(sizeof(char) * ft_strlen(cmd->nb_redir) + 1)))
//             return (-1);
//         if (create_file(cmd, 1) == -1)
//             return (-1);
//     }
//     else if (ft_strcmp("redir_out2", list->type, 8) == 0)
//     {
//         if (!(cmd->redir_out2 = malloc(sizeof(char) * ft_strlen(cmd->nb_redir) + 1)))
//             return (-1);
//         if (create_file(cmd, 2) == -1)
//             return (-1);
//     }
//     return (0);
// }

// void    ft_create_file(t_cmd *cmd, int type)
// {
//     if (type == 0) //stdin
//         return (create_file_in(cmd));
//     if (type == 1) //stdout
//         return (create_file_out1(cmd));
//     if (type == 2) //stderr 
//         return (create_file_out2(cmd));
// }

// int ft_create_file_in(t_cmd *cmd)
// {
//     cmd->fd_stdin = open(cmd->redir_in, O_RDONLY);
//     if (!cmd->redir_in || cmd->fd_stdin == -1)
//     {
//         printf("minishell: %s : No such file or directory\n", cmd->redir_in);
//         exit(EXIT_FAILURE);
//     }
//     return (0);
// }

// int ft_create_file_out1(t_cmd *cmd)
// {
//     if (!cmd->redir_out1)
//     {
//         printf("minishell: %s : No such file or directory\n", cmd->redir_out1);
//         exit(EXIT_FAILURE);
//     }
//     cmd->fd_stdout = open(cmd->redir_out1, O_CREAT | O_RDWR | O_TRUNC, 0644);
//     if (!cmd->fd_stdout == -1)
//     {
//         printf("minishell: %s : No such file or directory\n", cmd->redir_out1);
//         exit(EXIT_FAILURE);
//     }
//     return (0):
// }

// int ft_create_file_out2(t_cmd *cmd)
// {
//     if (!cmd->redir_out2)
//     {
//         printf("minishell: %s : No such file or directory\n", cmd->redir_out2);
//         exit(EXIT_FAILURE);
//     }
//     cmd->fd_stderr = open(cmd->redir_out1, O_CREAT | O_RDWR | O_TRUNC, 0644);
//     if (!cmd->fd_stderr == -1)
//     {
//         printf("minishell: %s : No such file or directory\n", cmd->redir_out2);
//         exit(EXIT_FAILURE);
//     }
//     return (0);
// }

// void ft_redir_dup(t_cmd *cmd, char **envp)
// {
//     int in;
//     int out1;
//     int out2;

//     if (!(in = 0) && cmd->redir_in != NULL)
//     {
//         in = dup(0);
//         close(0);
//         dup2(cmd->fd_stdin, 0);
//     }
//     if (!(out1 = 0) && cmd->redir_out1 != NULL)
//     {
//         out1 = dup(1);
//         close(1);
//         dup2(cmd->fd_stdout, 1);
//     }
//     if (!(out2 = 0) && cmd->redir_out2 != NULL)
//     {
//         out2 = dup(2);
//         close(2);
//         dup2(cmd->fd_stderr, 2);
//     }
//     ft_execute(cmd, envp);
//     ft_redir_clean(cmd, in, out1, out2);
// }

// void   ft_redir_clean(t_cmd *cmd, int in, int out1, int out2)
// {
//     if (cmd->redir_in)
//         dup2(in, 0);
//     if (cmd->redir_out1)
//         dup2(out1, 1);
//     if (cmd->redir_out2)
//         dup2(out2, 2);
// }