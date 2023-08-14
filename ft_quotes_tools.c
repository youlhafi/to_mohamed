/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:14:26 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/08/03 10:08:27 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calc_word(char *str)
{
	int		count_word;
	int		i;
	char	c;

	i = 0;
	count_word = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			c = str[i++];
			while (str[i] != '\0' && str[i] != c)
				i++;
			if (str[i] == c)
				i++;
			count_word++;
		}
		else
		{
			while (str[i] != '\0' && !is_quote(str[i]))
				i++;
			count_word++;
		}
	}
	return (count_word);
}

char	**get_dst_quotes(char *str)
{
	int		i;
	int		j;
	char	**dst;

	i = 0;
	j = 0;
	dst = malloc(sizeof(char *) * (calc_word(str) + 1));
	if (!dst)
		return (NULL);
	while (str[i])
	{
		if (is_quote(str[i]))
			dst[j] = ret_quote(str, &i);
		else
			dst[j] = ret_arg(str, &i);
		if (!dst[j])
		{
			free(str);
			ft_free_str(dst);
			return (NULL);
		}
		j++;
	}
	dst[j] = NULL;
	return (dst);
}

char	*get_s(char *dst, char *s)
{
	char	*tmp;

	tmp = NULL;
	if (is_quote(dst[0]))
	{
		tmp = ft_substr(dst, 1, ft_strlen(dst) - 1);
		s = ft_strjoin_get(s, tmp);
		free(tmp);
	}
	else
		s = ft_strjoin_get(s, dst);
	return (s);
}

char	*handle_quotes(char *str)
{
	int		j;
	char	**dst;
	char	*tmp;
	char	*s;

	j = 0;
	s = NULL;
	tmp = NULL;
	dst = get_dst_quotes(str);
	if (!dst)
		return (NULL);
	while (dst[j])
	{
		s = get_s(dst[j], s);
		if (!s)
			break ;
		j++;
	}
	free(str);
	ft_free_str(dst);
	return (s);
}
