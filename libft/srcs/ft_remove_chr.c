/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_chr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 22:06:03 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/07 22:07:15 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	new_str_len(char *str, char target);

char	*ft_remove_chr(char *str, char target)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (str == NULL)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (new_str_len(str, target) + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != target)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

static size_t	new_str_len(char *str, char target)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] != target)
			len++;
		i++;
	}
	return (len);
}
