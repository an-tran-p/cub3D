/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:36:48 by ikozhina          #+#    #+#             */
/*   Updated: 2025/10/02 09:52:49 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	len_s;
	size_t	i;

	i = 0;
	len_s = ft_strlen(s);
	while (i <= len_s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
		i++;
	}
	return (NULL);
}
