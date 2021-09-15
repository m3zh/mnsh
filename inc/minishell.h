/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:16:49 by mdesalle          #+#    #+#             */
/*   Updated: 2021/09/15 15:16:46 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "struct.h"
# include "../libft/libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define READ 0
# define WRITE 1
# define BASH 1
# define PATH 5
# define START 6
# define SINGLEQTS 39
# define DOLLARSIGN 36
# define DOUBLEQTS 34
# define BACKSLASH 92
# define LEN 100
# define MAX 1000

# define TMPFILE "tmpfile"

/*
 * PARSING
 */

void	init_shell(t_shell *s, char **envp);
void	reinit_shell(t_shell *s);
int		preparse_shell(t_shell *shell, char *line);
char	**parse_arg(t_shell *s, int i);
void	precheck_redir(t_shell *S, int last);
void	check_quotes(t_shell *s, char **arg, int i);
void	check_echo(t_shell *s, char **arg, int i);
void	check_user(t_shell *s, char **arg, int i);

/*
 * EXECUTION
 */

int		check_cmd(t_shell *s);
void	cd(t_shell *shell);
void	exec_shell(t_shell *s);
void	pipe_line(t_shell *s);
void	redir_input(t_shell *s);
void	redir_output(t_shell *s);
void	redir_heredoc(t_shell *s);
void	get_heredoc(t_shell *s);
void	stop(t_shell *shell);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	handle_sigusr1(int sig);

/*
 * ENVIRONMENT
 */

int		change_var(t_shell *shell, char *var, char *value);
char	*get_var(t_shell *shell, char *str);
void	enver(t_shell *shell);
void	expoort(t_shell *shell, char *str);
void	unset(t_shell *shell, char *str);
char	*get_val(char *str);
int		alpharank(t_shell *shell, char *str);
void	ranker(t_shell *shell);
int		sorter(char *s1, char *s2);
void	dollar(t_shell *shell);
void	sheller(t_shell *shell);
void	exporter(t_shell *shell, int l, int start);
void	tilde(t_shell *shell, char *cmd, char *str);

/*
 * SIGNALS
 */

void	shell_signal(void);

/*
 * UTILS
 */

void	free_arr(char **path);
int		ft_exit(t_shell *shell);
int		starts_with(char *s1, char *s2);
int		not_doublequote(char *s, int j);
int		cpystr_wQuotes(char *s, char *arr, int i);
int		cpystr_wChar(char *s, char *arr, int i, int c);
void	reset_string(char **s, int i);
void	reset_shell(t_shell *s);
void	free_struct(t_shell *s);
void	ft_free(char *s);
void	bash_error_unexpectedToken(t_shell *s);
void	bash_error_wFilename(t_shell *s, char *file);
void	bash_error_cmdNotFound(t_shell *s, char *cmd);
void	bash_syntaxError(void);
void	str_replace(char **dst, char *src);
void	swap_file(char **file, char **arg, int i);
void	malloxit(void);
char	**ft_specialsplit(char *s, char c);

#endif
