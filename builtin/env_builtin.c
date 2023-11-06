/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:44:55 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/17 19:12:17 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_builtin(char **cmd, t_env *env)
{
	int			i;
	t_env_elem	*elem;

	elem = env->head;
	i = 0;
	if (!cmd[1])
	{
		while (i < env->size)
		{
			if ((ft_strchr(env->env[i], '=') != -1) || elem->equal == 1)
				printf("%s\n", env->env[i]);
			i++;
			elem = elem->next;
		}
		g_status = EXIT_SUCCESS;
	}
	else
	{
		g_status = EXIT_FAILURE;
		ft_putstr_fd("Minishell: env: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(EXIT_FAILURE);
	}
	return (g_status);
}
