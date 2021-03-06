#include "ft_printf.h"

int		compute_x_flag(va_list *ap, t_arg args)
{
	char			*text;

	if (args.mod_l)
		text = get_unsigned_long(ap, 16, "0123456789abcdef");
	else if (args.mod_ll)
		text = get_unsigned_longlong(ap, 16, "0123456789abcdef");
	else if (args.mod_hh)
		text = get_unsigned_hh(ap, 16, "0123456789abcdef");
	else if (args.mod_h)
		text = get_unsigned_h(ap, 16, "0123456789abcdef");
	else if (args.mod_z)
		text = get_unsigned_size_t(ap, 16, "0123456789abcdef");
	else if (args.mod_j)
		text = get_unsigned_intmax_t(ap, 16, "0123456789abcdef");
	else
		text = get_unsigned(ap, 16, "0123456789abcdef");
	return (ft_print_str(text, args, 2));
}

int		compute_bigx_flag(va_list *ap, t_arg args)
{
	char			*text;

	if (args.mod_l)
		text = get_unsigned_long(ap, 16, "0123456789ABCDEF");
	else if (args.mod_ll)
		text = get_unsigned_longlong(ap, 16, "0123456789ABCDEF");
	else if (args.mod_hh)
		text = get_unsigned_hh(ap, 16, "0123456789ABCDEF");
	else if (args.mod_h)
		text = get_unsigned_h(ap, 16, "0123456789ABCDEF");
	else if (args.mod_z)
		text = get_unsigned_size_t(ap, 16, "0123456789ABCDEF");
	else if (args.mod_j)
		text = get_unsigned_intmax_t(ap, 16, "0123456789ABCDEF");
	else
		text = get_unsigned(ap, 16, "0123456789ABCDEF");
	return (ft_print_str(text, args, 3));
}
