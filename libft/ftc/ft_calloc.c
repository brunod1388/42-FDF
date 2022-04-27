/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:33:53 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/29 15:23:15 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pt;

	pt = malloc(count * size);
	if (pt == NULL)
		return (pt);
	ft_bzero(pt, count * size);
	return (pt);
}

void	*ft_realloc(void *pt, size_t size)
{
	void	*dst;
	size_t	len;

	if (size == 0)
	{
		free(pt);
		return (NULL);
	}
	dst = malloc(size);
	if (dst == NULL)
		return (dst);
	if (pt == NULL)
		ft_bzero(dst, size);
	else
	{
		len = ft_strlen((char *) pt);
		ft_memcpy(dst, pt, len);
		ft_bzero((void *)&dst[len], size - len);
		free(pt);
	}
	return (dst);
}
