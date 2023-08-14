/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:12:54 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/08/05 10:19:49 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	if (c == DOUBLE_QUOT || c == SINGLE_QHOT)
		return (1);
	return (0);
}

int	skip(const char *str, int i)
{
	char	quote;

	while (str[i] && str[i] != SPACE && str[i] != TAB)
	{
		if (is_quote(str[i]))
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
		}
		i++;
	}
	return (i);
}

int	count_words(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] && str[i] != c && str[i] != '\t')
		{
			i = skip(str, i);
			count++;
		}
		else
			i++;
	}
	return (count);
}

int	into(char *str, int n)
{
	int		first;
	int		second;
	char	c;

	first = 0;
	second = 0;
	if (str[n] == DOUBLE_QUOT)
		c = SINGLE_QHOT;
	else if (str[n] == SINGLE_QHOT)
		c = DOUBLE_QUOT;
	while (str[first] && str[first] != c)
		first++;
	second = first + 1;
	while (str[second] && str[second] != c)
		second++;
	if (n > first && n + 1 > first)
	{
		if (n < second && n + 1 < second)
			return (0);
	}
	return (1);
}
