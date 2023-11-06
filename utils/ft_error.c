/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:07:29 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/17 19:12:17 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_puterrfree(char *cmd, char *arg, char *msg, int errnum)
{
	write(2, "Minishell: ", ft_strlen("minishell: "));
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	if (!msg)
		perror("");
	else
		write(2, msg, ft_strlen(msg));
	g_status = errnum;
	free(arg);
	return (errnum);
}

void	errors(t_shell *shell, char **paths)
{
	if (shell->cmds[0][0] == 0)
	{
		free_paths(paths);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(shell->cmds[0], 2);
		ft_putstr_fd(": Command not found\n", 2);
		exit(127);
	}
	else if (access(shell->cmd->cmd, F_OK) == 0)
	{
		free_paths(paths);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(shell->cmds[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
}

void	error(char *str, int n)
{
	if (str)
	{
		ft_putstr_fd(strerror(n), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
}

int	ft_perror(char *msg, char *utils)
{
	write(2, msg, ft_strlen(msg));
	if (utils)
		write(2, utils, ft_strlen(utils));
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}

int	ft_puterr(char *cmd, char *arg, char *msg, int errnum)
{
	write(2, "Minishell: ", ft_strlen("minishell: "));
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	if (!msg)
		perror("");
	else
		write(2, msg, ft_strlen(msg));
	g_status = errnum;
	return (errnum);
}
