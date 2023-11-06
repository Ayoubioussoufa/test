/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:13:14 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/17 19:12:17 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_dir(t_env *ev, char *cwd, char *owd)
{
	t_env_elem	*env_elem;
	t_env_elem	*env_elem2;

	env_elem = search_env_elem(ev, "PWD");
	if (!env_elem)
	{
		free(env_elem);
		return ;
	}
	free(env_elem->value);
	env_elem->value = ft_strdup(cwd);
	env_elem2 = search_env_elem(ev, "OLDPWD");
	if (!env_elem2)
	{
		free(env_elem2);
		return ;
	}
	free(env_elem2->value);
	env_elem2->value = ft_strdup(owd);
}

int	nocmd1(char **cmd, t_env *env)
{
	char	*value;

	value = NULL;
	if (!cmd[1])
	{
		value = expand_env("$HOME", env->env);
		if (chdir(value) != 0)
		{
			free(value);
			return (ft_puterrfree(cmd[0],
					expand_env("$HOME", env->env), NULL, 1));
		}
	}
	free(value);
	return (0);
}

int	home(char **cmd, t_env *env)
{
	char	*value;

	value = NULL;
	if (!ft_strcmp(cmd[1], "~") || !ft_strncmp(cmd[1], "--", ft_strlen(cmd[1])))
	{
		value = expand_env("$HOME", env->env);
		if (chdir(value) != 0)
		{
			free(value);
			return (ft_puterrfree(cmd[0],
					expand_env("$HOME", env->env), NULL, 1));
		}
	}
	return (0);
}

int	cd_continuation(char **cmd, t_env *env)
{
	char	*value;

	value = NULL;
	if (!ft_strcmp(cmd[1], "~") || !ft_strncmp(cmd[1], "--", ft_strlen(cmd[1])))
		home(cmd, env);
	else if (!ft_strncmp(cmd[1], "-", ft_strlen(cmd[1])))
	{
		value = expand_env("$OLDPWD", env->env);
		if (chdir(value) != 0)
		{
			free(value);
			return (ft_puterrfree(cmd[0],
					expand_env("$OLDPWD", env->env), NULL, 1));
		}
	}
	else if (chdir(cmd[1]) != 0)
		return (ft_puterr(cmd[0], cmd[1], NULL, 1));
	free(value);
	return (0);
}

int	cd_builtin(char **cmd, t_env *env)
{
	char	cwd[2000];
	char	owd[2000];
	char	**arr;

	getcwd(owd, sizeof(owd));
	if (!cmd[1])
		nocmd1(cmd, env);
	else
		cd_continuation(cmd, env);
	getcwd(cwd, sizeof(cwd));
	set_dir(env, cwd, owd);
	arr = convert_arrayfree(env);
	if (arr)
	{
		free(env->env);
		env->env = arr;
	}
	g_status = EXIT_SUCCESS;
	return (0);
}
