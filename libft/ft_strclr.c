/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcrisan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/02 11:13:35 by rcrisan           #+#    #+#             */
/*   Updated: 2015/11/02 11:43:27 by rcrisan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strclr(char *s)
{
	unsigned int i;

	i = 0;
	while (s[i])
		i++;
	ft_memset(s, 0, i);
}