/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:21:53 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/20 12:11:21 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	preparse_shell(t_shell *shell, char *line)
{
	reinit_shell(shell);
	shell->cmd = ft_presplit(shell, line, '|');
	if (!shell->cmd)
		return (ft_exit(shell));
	shell->pipelen = ft_tablen(shell->cmd);
	if (shell->error_skip)
		free_arr(shell->cmd);
	free(line);
	return (0);
}
