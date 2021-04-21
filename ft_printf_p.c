#include "ft_printf.h"

void	print_address(char **str, va_list args, t_flags *flags)
{
	unsigned long int	address;
	char				*hexadecimal;
	char				*temp;

	address = va_arg(args, unsigned long int);
	hexadecimal = hex_converter(address, flags);
	flags->len = ft_strlen(hexadecimal);
	if (flags->precision >= 0)
		hexadecimal = check_precision(hexadecimal, flags);
	if (flags->precision >= flags->min_width)
	{
		ft_putstr_fd("0x", 1);
		flags->printed_chars += 2;
	}
	else
	{
		temp = hexadecimal;
		hexadecimal = ft_strjoin("0x", temp);
		free(temp);
		flags->len += 2;
	}
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
