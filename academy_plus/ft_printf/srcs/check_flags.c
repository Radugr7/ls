/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcrisan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 14:27:22 by rcrisan           #+#    #+#             */
/*   Updated: 2016/01/06 15:13:03 by rcrisan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		check_flags(char *format, t_mod *mod)
{
	int i;

	i = 0;
	while (format[i])
	{
		if (ft_strchr(FLAGS, format[i]) != NULL)
		{
			if (format[i + 1] >= '0' && format[i + 1] <= '9')
			{
				if (format[i] == '-')
					mod->minus_mod = 1;
				else if (format[i] == '+')
					mod->plus_mod = 1;
				else if (format[i] == ' ')
					mod->space_mod = 1;
				else if (format[i] == '#')
					mod->hash_mod = 1;
				else if (format[i] == '0')
					mod->zero_mod = 1;
			}
			else
				return (0);
		}
		i++;
	}
	return (1);
}
