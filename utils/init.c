/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:20:52 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/17 19:12:17 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_elem	*elem_init(void)
{
	t_env_elem	*elem;

	elem = malloc(sizeof(t_env_elem));
	elem->next = NULL;
	elem->prev = NULL;
	elem->equal = 0;
	if (!elem)
	{
		free(elem);
		return (NULL);
	}
	return (elem);
}
