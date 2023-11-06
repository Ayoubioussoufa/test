/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:12:51 by aybiouss          #+#    #+#             */
/*   Updated: 2023/02/12 18:12:51 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checkings(char **cmd)
{
	int	i;
	int	f;

	f = 0;
	i = 1;
	while (cmd[1][i] == 'n')
		i++;
	if (cmd[1][i] && cmd[1][i] != 'n')
		f = 0;
	else
		f = 1;
	return (f);
}

void	writing(char **cmd, int j, int f)
{
	while (cmd[++j])
	{
		if (cmd[j])
			ft_putstr(cmd[j]);
		if (!cmd[j + 1] && f)
			ft_putchar('\0');
		else if (!cmd[j + 1] && !f)
			ft_putchar('\n');
		else
			ft_putchar(' ');
	}
}

int	echo_builtin(char **cmd)
{
	int	j;
	int	f;
	int	i;

	j = 0;
	i = 1;
	f = 0;
	if (!cmd[1])
	{
		write(1, "\n", 1);
		return (1);
	}
	else if (cmd[1][0] == '-' && cmd[1][1] == 'n')
		f = checkings(cmd);
	if (f)
		j++;
	writing(cmd, j, f);
	g_status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}
