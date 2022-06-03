/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_idx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:30:45 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/03 23:10:05 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_strchr_idx(const char *str, int c)
{
	char	chrc;
	size_t	i;
	size_t	len;

	len = ft_strlen(str) + 1;
	i = 0;
	chrc = (char)c;
	while (i < len)
	{
		if (str[i] == chrc)
			return ((ssize_t)i);
		i++;
	}
	return (-1);
}
