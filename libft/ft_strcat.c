/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 13:50:53 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/03 18:22:05 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dstlen;
	size_t	srclen;

	i = 0;
	j = 0;
	srclen = ft_strlen(src);
	while (dst[i] && i < size)
		i++;
	dstlen = i;
	while (src[j] && i + 1 < size)
		dst[i++] = src[j++];
	if (dstlen < size)
		dst[i] = '\0';
	return (srclen + dstlen);
}