/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 09:00:52 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/08/03 10:10:12 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	spe_case(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (1);
	else if (ft_strcmp(str, ">") == 0)
		return (1);
	else if (ft_strcmp(str, "<") == 0)
		return (1);
	if (ft_strcmp(str, ">>") == 0)
		return (1);
	if (ft_strcmp(str, "<<") == 0)
		return (1);
	return (0);
}

int	ft_quotes(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	while (tmp)
	{
		if (spe_case(tmp->content))
			tmp->is_quote = 1;
		if (ft_strchr(tmp->content, SINGLE_QHOT)
			|| ft_strchr(tmp->content, DOUBLE_QUOT))
		{
			if (!tmp->trimmed)
			{
				tmp->content = handle_quotes(tmp->content);
				if (!tmp->content)
				{
					ft_free_token(*lst);
					return (1);
				}
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	into_quotes(char *input_string, char character)
{
	int		i;
	char	quote;

	i = 0;
	while (input_string[i] && !is_quote(input_string[i]))
		i++;
	if (input_string[i] && is_quote(input_string[i]))
	{
		quote = input_string[i];
		while (input_string[i] && input_string[i] != character)
		{
			if (input_string[i] == quote)
				return (1);
			i++;
		}
	}
	return (0);
}

int	is_arg(char *str)
{
	if (ft_strnstr(str, "\">\"", ft_strlen(str))
		|| ft_strnstr(str, "'>'", ft_strlen(str)))
		return (1);
	if (ft_strnstr(str, "\"<\"", ft_strlen(str))
		|| ft_strnstr(str, "'<'", ft_strlen(str)))
		return (1);
	if (ft_strnstr(str, "\">>\"", ft_strlen(str))
		|| ft_strnstr(str, "'>>'", ft_strlen(str)))
		return (1);
	if (ft_strnstr(str, "\"<<\"", ft_strlen(str))
		|| ft_strnstr(str, "'<<'", ft_strlen(str)))
		return (1);
	if (ft_strnstr(str, "\"|\"", ft_strlen(str))
		|| ft_strnstr(str, "'|'", ft_strlen(str)))
		return (1);
	return (0);
}
