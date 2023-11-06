/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:43:39 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/17 19:12:17 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_b(char **cmd, int i)
{
	if (!cmd[1])
		exit(EXIT_SUCCESS);
	while (cmd[1][i])
	{
		if (cmd[1][0] == '+' || cmd[1][0] == '-')
			i++;
		if (ft_isdigit(cmd[1][i]) && (long)atoi(cmd[1]) <= LLONG_MAX)
			i++;
		else
			exit_error(cmd, 1);
	}
	if (cmd[2])
		exit_error(cmd, 0);
}

int	exit_builtin(char **cmd, int flag)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[j])
	{
		cmd[j] = ft_strtrimfree(cmd[j], " ");
		j++;
	}
	if (flag)
		exit_flag(cmd, i);
	else
		exit_b(cmd, i);
	return (1);
}
