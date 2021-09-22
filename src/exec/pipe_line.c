/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:30:47 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/22 13:38:56 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	last_pipe(t_shell *s)
{
	if (s->file.outfile)
		redir_output(s);
	else
	{
		s->file.fdout = dup(s->file.tmpout);
		if (!s->file.fdout)
			ft_exit(s);
	}
	s->file.fdin = s->pipefd[READ];
	close(s->file.fdin);
}

static void	parent_waits(t_shell *s, int i)
{
	int	status;

	waitpid(g_proc, &status, WUNTRACED | __W_CONTINUED);
	close(s->pipefd[WRITE]);
	if (i != s->pipelen - 1)
		s->file.fdin = s->pipefd[READ];
	else
	{
		close(s->pipefd[READ]);
		close(s->file.fdin);
	}	
	s->cmdretval = WEXITSTATUS(status);
	g_proc = 0;
	free_arr(s->arg);
	reset_shell(s);
}

static void	swap_pipe(t_shell *s, int i)
{
	if (s->file.stopword)
		get_heredoc(s);
	else if (s->file.infile)
		redir_input(s);
	if (dup2(s->file.fdin, READ) < 0)
		exit(EXIT_FAILURE);
	close(s->file.fdin);
	if (i == s->pipelen - 1)
		last_pipe(s);
	else
	{
		if (s->file.outfile)
			redir_output(s);
		else
		{
			s->file.fdout = s->pipefd[WRITE];
			s->file.fdin = s->pipefd[READ];
		}
	}
	if (dup2(s->file.fdout, WRITE) < 0)
		exit(EXIT_FAILURE);
	close(s->file.fdout);
}

static void	child_process(t_shell *s)
{
	int		j;
	char	*cmd;

	j = -1;
	execve(s->arg[0], s->arg, s->minienv);
	while (s->path[++j])
	{
		cmd = ft_join(s->path[j], s->arg[0]);
		if (!cmd)
			malloxit();
		execve(cmd, s->arg, s->minienv);
		free(cmd);
		s->cmdnotfound = 1;
	}
	if (s->cmdnotfound)
		bash_error_cmdNotFound(s, s->arg[0]);
	free_arr(s->arg);
	s->cmdnotfound = 0;
}

void	pipe_line(t_shell *s)
{
	int		i;

	i = -1;
	while (s->cmd[++i] && !s->error_skip)
	{
		if (pipe(s->pipefd) < 0)
			ft_exit(s);
		signal(SIGQUIT, handle_sigquit);
		s->arg = parse_arg(s, i);
		swap_pipe(s, i);
		reset_shell(s);
		g_proc = fork();
		if (g_proc < 0)
		{
			free_arr(s->arg);
			return (perror("Fork"));
		}
		if (!g_proc)
			child_process(s);
		else if (g_proc > 0)
			parent_waits(s, i);
	}
	free_arr(s->cmd);
	while (i--)
		wait(NULL);
}
