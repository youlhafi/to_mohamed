/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:21:07 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/08/03 12:24:55 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**export_loop(t_pip *p, char **new, char *exp)
{
	int	i;

	i = 0;
	if (p->export)
	{
		while (p->export[i])
		{
			new[i] = ft_strdup(p->export[i]);
			i++;
		}
	}
	new[i++] = ft_strdup(exp);
	new[i] = NULL;
	return (new);
}
