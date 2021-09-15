/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesalle <mdesalle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:52:33 by mdesalle          #+#    #+#             */
/*   Updated: 2021/09/15 12:54:39 by mdesalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* handles the directory changes */

static void	change_dir(t_shell *shell, char *pwd, char *nstr)
{
	if (!chdir(nstr))
	{
		if (!change_var(shell, "OLDPWD", pwd))
			exit(EXIT_FAILURE);
		pwd = getcwd(NULL, 0);
		if (!pwd)
			exit(EXIT_FAILURE);
		if (!change_var(shell, "PWD", pwd))
			exit(EXIT_FAILURE);
	}
	else
		printf("bash: cd: %s: %s\n", nstr, strerror(errno));
}

/* goes to a specific directory when using the tilde */
/* example: "cd ~/some-directory" */

void	tilde(t_shell *shell, char *cmd, char *str)
{
	char	*pwd;
	char	*tmp;
	char	*nstr;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		exit(EXIT_FAILURE);
	tmp = ft_substr(cmd, 1, ft_strlen(cmd));
	if (!tmp)
		malloxit();
	nstr = ft_join(str, tmp);
	if (!nstr)
		malloxit();
	if (!shell->tilde)
		free(shell->tilde);
	shell->tilde = cmd;
	change_dir(shell, pwd, nstr);
	free(pwd);
	free(tmp);
	free(nstr);
}
