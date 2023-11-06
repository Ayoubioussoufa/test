/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:28:39 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/17 19:12:17 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_directory(char *str)
{
	if (!ft_strncmp(".", str, 2))
	{
		ft_putstr_fd("Minishell", 2);
		ft_putstr_fd(": .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		g_status = 2;
		return (g_status);
	}
	else if (!ft_strncmp("..", str, 3))
	{
		ft_putstr_fd("Minishell", 2);
		ft_putstr_fd(": ..: command not found\n", 2);
		g_status = 127;
		return (g_status);
	}
	if (!opendir(str))
		return (0);
	ft_putstr_fd("Minishell", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": is a directory\n", 2);
	g_status = 126;
	return (g_status);
}

int	check_builtins(char *cmd)
{
	if (cmd && !ft_strcmp(cmd, "export"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "unset"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "pwd"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "exit"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "cd"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "env"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "echo"))
		return (1);
	return (0);
}

void	ft_which_cmd(char **cmds, t_env *env, int flag, t_shell *shell)
{
	static int	i;

	if (shell)
	{
		i = exec_redir(shell);
		check_fd(shell->cmd);
	}
	if (!i)
	{
		if (cmds[0] && !ft_strcmp(cmds[0], "export"))
			export_builtin(cmds, env);
		else if (cmds[0] && !ft_strcmp(cmds[0], "unset"))
			unset_builtin(cmds, env);
		else if (cmds[0] && !ft_strcmp(cmds[0], "pwd"))
			pwd_builtin(*cmds);
		else if (cmds[0] && !ft_strcmp(cmds[0], "exit"))
			exit_builtin(cmds, flag);
		else if (cmds[0] && !ft_strcmp(cmds[0], "cd"))
			cd_builtin(cmds, env);
		else if (cmds[0] && !ft_strcmp(cmds[0], "env"))
			env_builtin(cmds, env);
		else if (cmds[0] && !ft_strcmp(cmds[0], "echo"))
			echo_builtin(cmds);
	}
}
