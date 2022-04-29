/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:47:22 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/29 16:32:01 by dvallien         ###   ########.fr       */
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
# include "../libft/libft.h"
# include <dirent.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <limits.h>

# define STR 0
# define REDIR_IN 1
# define HEREDOC 2
# define REDIR_OUT 3
# define REDIR_CONC 4

int	g_status;

typedef struct s_list
{
	char			*content;
	int				type;
	int				block;
	struct s_list	*next;
	struct s_list	*previous;
}	t_list;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*previous;
}	t_env;

typedef struct s_pars_info
{
	int				i;
	int				j;
	int				current_type;
	int				current_block;
	int				d_quote;
	int				bracket;
	int				cur_cont_size;
	int				error;
	struct s_cmd	*cmd;
}	t_pars_info;

typedef struct s_init_index
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	m;
}	t_init_index;

typedef struct s_cmd
{
	int		parse_error;
	int		infile_error;
	char	*line_path;
	char	**tab_path;
	int		path_ok;
	char	*valid_path;
	int		fd_status;
	char	**tab_str;
	char	**tab_redir_in;
	char	**tab_redir_out1;
	char	**tab_redir_out2;
	char	**tab_heredoc;
	int		nb_redir;
	int		nb_str;
	int		nb_in;
	int		nb_out1;
	int		nb_out2;
	int		nb_heredoc;
	int		fd_in;
	int		fd_out_trunc;
	int		fd_out_append;
	int		stdin_copy;
	int		last_in;
	int		last_out;
	int		pipefd[2];
	int		pipe_heredoc_fd[2];
	t_env	*env_list;
	char	*mem_pwd;
	int		pipe_id;
	pid_t	*pipe_pids;
}	t_cmd;

////////////////////
// EXECUTION PART //
////////////////////

// Chained list
void	ft_create_list(t_list **list);
t_list	*ft_lstnew(char *content, int type, int block);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
t_env	*ft_lstnew_env(char *name, char *value);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **alst, t_env *new);
void	ft_print_list(t_list *list);
int		ft_env_lst_size(t_env *env_list);

// Utils
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_strjoin_content(char *s1, char *s2);
char	*ft_strjoin_export(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
void	ft_putstr_fd(char *s, int fd);

// Parse type
int		main(int ac, char **av, char **env);
void	ft_start_exec(t_list *list, t_cmd *cmd);
void	ft_init_exec(t_cmd *cmd, t_list *list);
void	ft_pipex_or_exec(t_cmd *cmd, t_list *list, int *current_block);

// Access path
char	*ft_access_path(t_cmd *cmd);
char	*ft_no_command(t_cmd *cmd);
char	*ft_get_line_path(t_cmd *cmd);
void	ft_absolute_path(t_cmd *cmd, int i, char *tmp_path);

// Create tabs, and get fd files
void	ft_get_args(t_list *list, t_cmd *cmd, int current_block);
void	ft_create_tab(t_cmd *cmd, t_list *list, int current_block);
void	ft_init_tab(t_cmd *cmd);
void	ft_malloc_tab(t_cmd *cmd);
void	ft_fill_tab_str(t_cmd *cmd, t_list *list, int *i);
void	ft_fill_redir_in(t_cmd *cmd, t_list *list, int *j);
void	ft_fill_redir_out1(t_cmd *cmd, t_list *list, int *k);
void	ft_fill_redir_out2(t_cmd *cmd, t_list *list, int *l);
void	ft_fill_heredoc(t_cmd *cmd, t_list *list, int *m);
int		ft_create_file_in(t_cmd *cmd);
int		ft_create_file_out1(t_cmd *cmd);
int		ft_create_file_out2(t_cmd *cmd);
int		ft_create_file_heredoc(t_cmd *cmd);

// Pipe
void	ft_exec_pipex(t_cmd *cmd);
void	ft_pipex_child(t_cmd *cmd);
void	ft_pipex_parent(t_cmd *cmd);

// Redirections
void	ft_redir_dup(t_cmd *cmd);
void	ft_redir_dup_in(t_cmd *cmd, int *in);
void	ft_redir_dup_in(t_cmd *cmd, int *in);
void	ft_redir_clean(t_cmd *cmd, int in, int out1, int out2);

// Builtins exec
int		ft_is_builtin(char *str);
int		ft_exec_builtin(t_cmd *cmd);

// Builtins commands
int		ft_echo(t_cmd *cmd);
void	ft_print_echo(t_cmd *cmd, int *option, int *is_arg, int i);
int		ft_option(char *arg);
int		ft_pwd(t_cmd *cmd);
void	ft_if_delete_parent_folder(t_cmd *cmd);
void	ft_redir_putstr(t_cmd *cmd, char *str);
char	*ft_heredoc_loop(char *stop);
int		ft_env(t_cmd *cmd);
void	ft_export_print(t_cmd *cmd);
int		ft_export(t_cmd *cmd);
int		ft_unset(t_cmd *cmd);
int		ft_cd(t_cmd *cmd);
void	ft_cd_folder(t_cmd *cmd, char *path, char *pwd, char *cwd);
void	ft_cd_without_args(t_cmd *cmd, char *path, char *pwd, char *cwd);
int		ft_cd_no_access(t_cmd *cmd);
int		ft_exit(t_cmd *cmd);

// Execute
void	ft_exec_cmd(t_cmd *cmd);
void	ft_exec_parent_process(pid_t pid);
void	ft_execute(t_cmd *cmd);
void	ft_execution(t_cmd *cmd);

// Signaux
void	ft_signal_handler(int signal);
void	ft_signal_exec_handler(int signal);
void	ft_term_handler(int x);
void	ft_quit_heredoc(int signal);
void	ft_heredoc_child(t_cmd *cmd, t_list *list);
void	ft_heredoc_parent(t_cmd *cmd, pid_t pid);

// Copy Env
void	ft_cpy_env(char **env, t_cmd *cmd);
char	**ft_env_to_tab(t_cmd *cmd);

// Free
void	ft_lstclear(t_list **lst);
void	ft_free_all_tabs(t_cmd *cmd);
void	ft_free_split(char **av);
void	ft_free_tab(char **av);
void	ft_free_exec(t_cmd *cmd, int i);

/////////////////
//   PARSING   //
/////////////////

int		ft_simple_quote(t_list **list, char *line, int *i);
int		ft_double_quote(t_list **list, char *line, int *i);
int		ft_var_env(t_list **list, char *line, int *i);
int		ft_str(t_list **list, char *line, t_pars_info *p_info);

int		ft_s_quote_size(char *line, t_pars_info *p_info);
char	*ft_join_s_quote(char *line, char *content, t_pars_info *p_info);
int		ft_d_quote_size(char *line, t_pars_info *p_info);
char	*ft_join_d_quote(char *line, char *content,
			t_list **list, t_pars_info *p_info);

char	*ft_getenv(char *env_name, t_cmd *cmd);
int		ft_is_valid(char c);
int		ft_env_size(char *line, t_pars_info *p_info);
char	*ft_env_name(char *line, t_pars_info *p_info);
char	*ft_join_env(char *line, char *content,
			t_list **list, t_pars_info *p_info);

void	ft_parsing(t_list **list, char *line, t_cmd *cmd);
void	ft_lexer(t_list **list, char *line, t_pars_info *p_info);
void	ft_redir_out(char *line, t_pars_info *p_info);
void	ft_redir_in(char *line, t_pars_info *p_info);
void	ft_pipe(char *line, t_pars_info *p_info);

int		ft_content_size(char *line, t_pars_info *p_info);

#endif