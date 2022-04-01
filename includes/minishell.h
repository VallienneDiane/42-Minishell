/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:47:22 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/01 17:42:58 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_list
{
	char			*content;
	char			*type;
	int				block;
	struct s_list	*next;
	struct s_list	*previous;
}	t_list;

typedef struct s_cmd
{
	char	*line_path;
	char	**tab_path;
	char	*valid_path;
	int		fd1;
	int		fd2;
	int		fd_status;
	char	**tab_str;
	char	**redir_in;
	char	**redir_out1;
	char	**redir_out2;
	int		nb_redir;
	int		nb_str;
	int		nb_in;
	int		nb_out1;
	int		nb_out2;
	int		fd_stdin;
	int		fd_stdout;
	int		fd_stdout2;
	int		last_out;
}	t_cmd;

// DIANE //

int		main(int ac, char **av, char **env);

// Chained list
void	ft_create_list(t_list **list);
t_list	*ft_lstnew(void *content, void *type, int block);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_print_list(t_list *list);

// Utils
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
void	ft_putstr_fd(char *s, int fd);

// Parse type
void	ft_parse_type(t_list *list, t_cmd *cmd, char **envp);

// Access path
char	*ft_access_path(t_list *list, t_cmd *cmd);
char	*ft_get_line_path(char **envp);

// Execution
void    ft_get_args(t_list *list, t_cmd *cmd, char **envp, int current_block);
void	ft_execute(t_cmd *cmd, char **envp);
void	ft_execution(t_cmd *cmd, char **envp);
void	ft_redir_dup(t_cmd *cmd, char **envp);
void    ft_create_tab(t_cmd *cmd, t_list *list, int current_block);
void    ft_init_tab(t_cmd *cmd);
void    ft_malloc_tab(t_cmd *cmd);
void    ft_fill_tab_str(t_cmd *cmd, t_list *list, int *i);
void    ft_fill_redir_in(t_cmd *cmd, t_list *list, int *j);
void    ft_fill_redir_out1(t_cmd *cmd, t_list *list, int *k);
void    ft_fill_redir_out2(t_cmd *cmd, t_list *list, int *l);
void 	ft_redir_dup(t_cmd *cmd, char **envp);
void	ft_redir_clean(t_cmd *cmd, int in, int out1, int out2);
int		ft_create_file(t_cmd *cmd, int type);
int		ft_create_file_in(t_cmd *cmd);
int 	ft_create_file_out1(t_cmd *cmd);
int 	ft_create_file_out2(t_cmd *cmd);
void    ft_error_create_file(void);

int	ft_is_builtin(char *str);
int ft_echo(t_cmd *cmd);
int ft_option(char *arg);
int ft_pwd(t_cmd *cmd);

// Stdin stdout when pipe
void	ft_exec_pipex(t_list *list, t_cmd *cmd, char **envp);

// Execute builtins
void	ft_exec_builtin(t_list *list, t_cmd *cmd, char **envp);

// Redirections

#endif