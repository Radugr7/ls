/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcrisan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 13:30:56 by rcrisan           #+#    #+#             */
/*   Updated: 2016/01/11 21:14:54 by rcrisan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		g_size;

int		is_flag(const char *format, int *k)
{
	int i;

	i = *k;
	if (ft_strchr(FLAGS, format[i]) != NULL)
		return (1);
	return (0);
}

int		is_specifier(const char *format, int *k)
{
	int i;

	i = *k;
	if (ft_strchr(SPECIFIERS, format[i]) != NULL)
		return (1);
	return (0);
}

char	*chop_format(const char *format, unsigned long int *i)
{
	char	*choped;
	int		j;
	int		k;

	j = 0;
	k = *i;

	k++;
	choped = (char*)malloc(sizeof(choped) * ft_strlen(format));
	while (format[k])
	{
		if (is_flag(format, &k) == 0 && is_specifier(format, &k) == 0)
			return (NULL);
		else if (is_specifier(format, &k))
		{
			choped[j++] = format[k];
			break;
		}
		else if (is_flag(format, &k))
			choped[j++] = format[k];
		k++;
	}
	choped[j] = '\0';
	return (choped);
}

void	init_flags(t_mod *flag)
{
	
	flag->dot_mod = 0;
	flag->h_mod = 0;
	flag->hh_mod = 0;
	flag->l_mod = 0;
	flag->ll_mod = 0;
	flag->z_mod = 0;
	flag->j_mod = 0;
	flag->hash_mod = 0;
	flag->minus_mod = 0;
	flag->zero_mod = 0;
	flag->plus_mod = 0;
	flag->space_mod = 0;
	flag->width = 0;	
	flag->specifier = 48;
	flag->precision = 0;
	flag->procent = 0;
}

void	process_precision(char	*choped, t_mod *data)
{
	int i;

	i = 0;
	while (choped[i])
	{
		if (choped[i] == '.' && ft_isdigit(choped[i + 1]))
			data->precision = 1;
		else if (choped[i] > '0' && choped[i] <= '9')
			data->width = 1;
		i++;
	}
}

void	process_hhll_mods(char	*choped, t_mod	*data)
{
	int i;

	i = 0;
	while (choped[i])
	{
		if (choped[i] == 'h' && choped[i + 1] == 'h')
		{
			data->hh_mod = 1;
			data->h_mod = 0;
		}
		else if (choped[i] == 'l' && choped[i + 1] == 'l')
		{
			data->ll_mod = 1;
			data->l_mod = 0;
		}
		i++;
	}
}

void	process_mods(char *choped, t_mod *data)
{
	int i;

	i = 0;
	while (choped[i])
	{
		if (choped[i] == 'h' && choped[i + 1] != 'h')
			data->h_mod = 1;
		else if (choped[i] == 'l' && choped[i + 1] != 'l')
			data->l_mod = 1;
		else if (choped[i] == 'j')
			data->j_mod = 1;
		else if (choped[i] == 'z')
			data->z_mod = 1;
		i++;
	}
	process_hhll_mods(choped, data);
}

int		is_mod(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	return (0);
}

int		is_double_mod(char	*choped, int *i)
{
	int k;

	k = *i;
	if (choped[k] == 'h' && choped[k + 1] == 'h')
		return (1);
	else if (choped[k] == 'l' && choped[k + 1] == 'l')
		return (1);
	return (0);
}

int		validate_mod(char *choped)
{
	int i;

	i = 0;
	while (choped[i])
	{
		if (!is_double_mod(choped, &i) && is_mod(choped[i]) && \
				ft_strchr(SPECIFIERS, choped[i + 1]) == NULL)
			return (-1);
		else if (is_double_mod(choped, &i) && \
				ft_strchr(SPECIFIERS, choped[i + 2]) == NULL)
			return (-1);
		i++;
	}
	return (1);
}

void	process_specifiers2(char *choped, t_mod *data)
{
	int i;

	i = 0;
	while (choped[i])
	{
		if (choped[i] == 'S')
			data->specifier = 'S';
		else if (choped[i] == 's')
			data->specifier = 's';
		else if (choped[i] == 'C')
			data->specifier = 'C';
		else if (choped[i] == 'c')
			data->specifier = 'c';
		else if (choped[i] == 'p')
			data->specifier = 'p';
		else if (choped[i] == 'X')
			data->specifier = 'X';
		else if (choped[i] == 'x')	
			data->specifier = 'x';
		i++;
	}
}

void	process_specifiers(char *choped, t_mod *data)
{
	int i;

	i = 0;
	while (choped[i])
	{
		if (choped[i] == 'd')
			data->specifier = 'd';
		else if (choped[i] == 'D')
			data->specifier = 'D';
		else if (choped[i] == 'i')
			data->specifier = 'i';
		else if (choped[i] == 'o')
			data->specifier = 'o';
		else if (choped[i] == 'O')
			data->specifier = 'O';
		else if (choped[i] == 'u')
			data->specifier = 'u';
		else if (choped[i] == 'U')
			data->specifier = 'U';
		i++;
	}
	process_specifiers2(choped, data);
}

void	process_flags(char *choped, t_mod *data)
{
	int i;

	i = 0;
	init_flags(data);
	while (choped[i])
	{
		if (choped[i] == '#')
			data->hash_mod = 1;
		else if (choped[i] == '0')
			data->zero_mod = 1;
		else if (choped[i] == '-')
			data->minus_mod = 1;
		else if (choped[i] == '+')
			data->plus_mod = 1;
		else if (choped[i] == ' ')
			data->space_mod = 1;
		i++;
	}
	if (validate_mod(choped) > 0)
		process_mods(choped, data);
	process_precision(choped, data);
	process_specifiers(choped, data);
}

int		get_precision(char *choped)
{
	int		i;
	char	*precision;
	int		k;

	i = 0;
	k = 0;
	precision = (char*)malloc(sizeof(precision) * strlen(choped));
	while (choped[i])
	{
		if (choped[i] == '.')
		{
			i++;
			while (choped[i] >= '0' && choped[i] <= '9')
				precision[k++] = choped[i++];	
		}
		i++;
	}
	precision[k] = '\0';
	return (ft_atoi(precision));
}

int		get_width(char *choped)
{
	int		i;
	char	*width;
	int		k;

	i = ft_strlen(choped) - 1;
	k = 0;
	width = (char*)malloc(sizeof(width) * strlen(choped));
	while (i >= 0)
	{
		if (choped[i] == '0' && !ft_isdigit(choped[i - 1]))
			i--;
		else if (!ft_isdigit(choped[i]))
			i--;
		else
			break;
	}
	while (ft_isdigit(choped[i]) && i >= 0)
		width[k++] = choped[i--];
	width[k] = '\0';
	ft_strrev(width);
	return (ft_atoi(width));
}

int		get_size(char *choped, t_mod *data)
{
	int i;
	int sum;

	i = 0;
	sum = 0;
	if (data->width == 0 && data->precision == 0)
		return (0);	
	else if (data->precision == 1)
		sum = get_precision(choped);
	else if (data->width == 1 && data->precision == 0)
		sum = get_width(choped);
	return (sum);
}
/*
void	hh_case(t_mod *data, va_list *arg)
{
	signed char decimal;
	unsigned char other_base;

	if (data->specifier == 'd' || data->specifier == 'i')
		decimal = va_arg(*arg, signed char);
	else if (data->specifier == 'u' || data->specifier == 'o' || \
			data->specifier == 'x' || data->specifier == 'X')
		other_base = va_arg(*arg, unsigned char);
}

char	*edit_based_on_mods(t_mod *data, va_list *arg)
{
	char *result;

	result = ft_memalloc(300);
	if (data->hh_mod == 1)
		result = ft_strdup(hh_case(data, arg));
	else if (data->h_mod = 1)
		result = ft_strdup(h_case(data, arg));
	else if (data->l_mod = 1)
		result = ft_strdup(l_case(data, arg));
	else if (data->ll_mod = 1)
		result = ft_strdup(ll_case(data, arg));
	else if (data->j_mod = 1)
		result = ft_strdup(j_case(data, arg));
	else if (data->z_mod = 1)
		result = ft_strdup(z_case(data, arg));
	return (result);
}
*/
char	*convert_strings(t_mod *data, va_list *arg)
{
	char	*str;

	str = (char*)malloc(sizeof(str) * 50000);
	if (data->specifier == 's')
		str = va_arg(*arg, char*);
	return (str);
}

char	*edit_decimal(va_list *arg)
{
	int n;

	n = va_arg(*arg, int);
	return (ft_itoa(n));
}

char	*convert_numbers(t_mod *data, va_list *arg)
{
	char *result;

	result = (char*)malloc(sizeof(result) * 150);
	if (data->specifier == 'd' || data->specifier == 'i' || data->specifier == 'D')
		result = ft_strdup(edit_decimal(arg));
	/*else if (data->specifier == 'o' || data->specifier == 'O')
	   result = ft_strdup(edit_octal(arg));
	else if (data->specifier == 'u')
		result  = ft_strdup(edit_unsigned_decimal(arg));
	else if (data->specifier == 'x')
		result = ft_strdup(edit_small_hexa(arg));
	else if (data->specifier == 'X')
		result = ft_strdup(edit_big_hexa(arg));
	else if (data->specifier == 'p')
		result = ft_strdup(edit_adress(arg));
	*/hh_case(data, arg);
	return (result);

}

char	*convert_based_on_flags(t_mod *data, va_list *arg)
{
	char		*text = NULL;

	if (data->specifier == 's')
	{
		text = ft_strdup(convert_strings(data, arg));
	}
	else if (data->specifier == 'd' || data->specifier == 'D' || \
			data->specifier == 'i' || data->specifier == 'o' || \
			data->specifier == 'O' || data->specifier == 'u' || \
			data->specifier == 'x' || data->specifier == 'X' || \
			data->specifier == 'p')
	{
		text = ft_strdup(convert_numbers(data, arg));
	}
	return (text);
}

int		no_procent(const char *format)
{
	if (ft_strchr(format, '%') == NULL)
	{
		ft_putstr(format);
		return (1);
	}
	return (0);
}

void	how_much_to_print(char *choped, char *text, t_mod *data)
{
	int length;

	length = get_size(choped, data);
	if (length != 0)
		ft_putnstr(text, length);
	ft_putstr(text);
}

int		what_to_print(const char *format, va_list *arg)
{
	char	*text;
	char	*choped;
	t_mod	data;
	unsigned long int	i;
	
	i = -1;
	if (no_procent(format))
		return (ft_strlen(format) - 1);
	while (++i < ft_strlen(format))
	{
		if (format[i] == '%' && format[i + 1] != '%' && format[i + 1] != '\0')
		{
			choped = ft_strdup(chop_format(format, &i));
			if (choped != NULL)
			{
				process_flags(choped, &data);
				text = ft_strdup(convert_based_on_flags(&data, arg));
				i = ft_strlen(choped) + i;
				how_much_to_print(choped, text, &data);
			}
		}
		else
			ft_putchar(format[i]);
	}
	return (g_size);
}


int		ft_printf(const char *format, ...)
{
	va_list arg;
	int done;

	va_start(arg, format);
	done = what_to_print(format, &arg);
	va_end(arg);
	return (done);
}

int main (int argc, char **argv)
{
	int n;

	n =	ft_printf(argv[1], "piata", 61);

/*	char	*choped;

	while (argv[1][i])
	{
		if (argv[1][i] == '%')
			choped = strdup(chop_format(argv[1], &i));
		i++;
	}
	printf("%s\n", choped);
	printf("WIDTH = %d\t PRECISION = %d\n", get_width(choped), get_precision(choped));
	process_flags(choped, &flag);

	printf("dot = %d\n", flag.dot_mod);
	printf("h mod = %d\n", flag.h_mod);
	printf("hh mod = %d\n", flag.hh_mod);
	printf("l mod = %d\n", flag.l_mod);
	printf("ll mod = %d\n", flag.ll_mod);
	printf("z mod = %d\n", flag.z_mod);
	printf("j mod = %d\n", flag.j_mod);
	printf("# mod = %d\n", flag.hash_mod);
	printf("minus mod = %d\n", flag.minus_mod);
	printf("0 mod = %d\n", flag.zero_mod);
	printf("+ mod = %d\n", flag.plus_mod);
	printf("space mod = %d\n", flag.space_mod);
	printf("specifier = %c\n", flag.specifier);
	printf("width mod = %d\n", flag.width);
	printf("precision mod = %d\n", flag.precision);
	printf("procent mod = %d\n", flag.procent);
*/	return (0);
}