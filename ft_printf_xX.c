#include "ft_printf.h"

void	print_hex(char **str, va_list args, t_flags *flags)
{
	unsigned int	decimal;
	char			*hexadecimal;

	if (**str == 'x')
		flags->hex_case = "0123456789abcdef";
	else
		flags->hex_case = "0123456789ABCDEF";
	decimal = va_arg(args, unsigned int);
	hexadecimal = hex_converter(decimal, flags);
	flags->len = ft_strlen(hexadecimal);
	if (flags->precision >= 0)
		hexadecimal = check_precision(hexadecimal, flags);
	if (flags->left_justify != 0)
	{
		ft_putstr_fd(hexadecimal, 1);
		padding(flags);
		flags->printed_chars += flags->len;
	}
	else
	{
		padding(flags);
		ft_putstr_fd(hexadecimal, 1);
		flags->printed_chars += flags->len;
	}
	(*str)++;
	free(hexadecimal);
}
