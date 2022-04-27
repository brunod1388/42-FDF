/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 02:53:29 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/04/26 03:23:00 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>



char *ft_ftoa(double f, int n_dec)
{
	char	*tmp;
	char	*dst;
	char	dec_part[128];
	int		i;

	if (n_dec > 127)
		n_dec = 127;
	tmp = ft_itoa((int) f);
	dst = ft_strjoin(tmp, ".");
	free(tmp);
	f -= (double)(int)f;
	i = 0;
	while (i < n_dec)
	{
		f = f * 10.0;
		dec_part[i++] = '0' + (((int) f) % 10);
	}
	dec_part[i] = 0;
	tmp = dst;
	dst = ft_strjoin(tmp, dec_part);
	free(tmp);
	return (dst);
}