/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:17:01 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/03 18:26:07 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* normally it would return srclen + dstlen, 
* function has been modified to return src length only
*/

char *ft_strlcat(char **dst, const char *src, int k)
{
	size_t	j;

	j = 0;
	while (*dst[k] && src[j])
		*dst[k++] = src[j++];
	*dst[k] = '\0';
	return (*dst); 
}