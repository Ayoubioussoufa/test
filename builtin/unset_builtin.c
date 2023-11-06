/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:09:29 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/17 19:12:17 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**convert_arrayfree_unset(t_env *env)
{
	t_env_elem	*tmp;
	char		**arr;
	int			i;

	i = -1;
	tmp = env->head;
	arr = malloc((env->size + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (++i < env->size)
	{
		arr[i] = ft_strdup(tmp->key);
		if (tmp->value)
		{
			arr[i] = ft_strjoinfree(arr[i], "=");
			arr[i] = ft_strjoinfree(arr[i], tmp->value);
		}
		free(env->env[i]);
		tmp = tmp->next;
	}
	free(env->env[i]);
	arr[i] = 0;
	return (arr);
}

void	unset_env(char *cmd, t_env *env)
{
	t_env_elem	*elem;

	elem = NULL;
	if (cmd && !ft_isalpha(cmd[0]))
	{
		printf("minishell: unset: `%s`: not a valid identifier\n",
			cmd);
		g_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	else
	{
		elem = search_env_elem(env, cmd);
		if (elem)
			del_env_elem(env, elem);
	}
}

int	unset_builtin(char **cmd, t_env *env)
{
	int		i;
	char	**arr;

	i = 0;
	while (cmd[i])
	{
		unset_env(cmd[i], env);
		i++;
	}
	arr = convert_arrayfree_unset(env);
	if (arr)
	{
		free(env->env);
		env->env = arr;
	}
	g_status = EXIT_SUCCESS;
	return (g_status);
}
