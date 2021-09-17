/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 16:13:39 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/17 16:10:01 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static int	check_dollarsign(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if ((i == 0 && s[i] == DOLLARSIGN)
// 			|| (i > 0 && s[i] == DOLLARSIGN && s[i - 1] != BACKSLASH))
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

static char	*dollar2value(t_shell *shell, char *s, int start)
{
	int		i;
	char	*var;
	char	*var_name;

	i = start;
	while (s[i] && !ft_space(s[i]))
		i++;
	var_name = ft_substr(s, start, i - start);
	if (!var_name)
		malloxit();
	var = get_var(shell, var_name);
	if (!var)
	{
		var = ft_strdup("");
		if (!var)
			malloxit();
	}
	free(var_name);
	return (var);
}

static void	get_lastRetValue(t_shell s, char **arg, int i)
{
	int		j;
	int		k;
	int		l;
	char	*tmp;

	j = 2;
	tmp = malloc(sizeof(char) * MAX + 1);
	if (!tmp)
		malloxit();
	l = ft_numlen(s.cmdretval);
	k = l;
	if (s.cmdretval == 0)
		tmp[0] = 0 + '0';
	while (s.cmdretval != 0 && l > 0)
	{
		tmp[--l] = s.cmdretval % 10 + '0';
		s.cmdretval /= 10;
	}
	while (arg[i][j])
		tmp[k++] = arg[i][j++];
	tmp[k] = 0;
	str_replace(&arg[i], tmp);
}

void	check_echo(t_shell *s, char **arg, int i)
{
	// int 	dollar;
	char	*tmp;

	// dollar = check_dollarsign(arg[i]) + 1;
	if (s->var.single_qts || s->var.double_qts)
		return ;
	if (!ft_strncmp("$?", arg[i], 2))
		get_lastRetValue(*s, arg, i);
	else if (starts_with("$", arg[i]) && !ft_space(arg[i][1]) && ft_strcmp("$", arg[i]))
	{
		// if (!dollar)
		// 	dollar = 1;
		tmp = dollar2value(s, arg[i], 1);
		if (!tmp)
			malloxit();
		str_replace(&arg[i], tmp);
	}
}

// void	check_dollar(t_shell *s, char **arg, int i)
// {
// 	char	*tmp;

// 	if (i > 0)
// 		return ;
// 	if (!ft_strcmp(arg[i], "$?"))
// 		get_lastRetValue(*s, arg, i);
// 	else if (starts_with("$", arg[i]) && ft_strcmp("$", arg[i]))
// 	{
// 		tmp = dollar2value(s, arg[i], 1);
// 		if (!tmp)
// 			malloxit();
// 		str_replace(&arg[i], tmp);
// 	}
// }
