#include "ft_printf.h"

char	*hex_converter(size_t decimal, t_flags *flags)
{
	char	*hexadecimal;
	size_t	temp;
	int		digits;

	digits = 1;
	temp = decimal;
	while (temp / 16)
	{
		digits++;
		temp /= 16;
	}
	hexadecimal = malloc(sizeof(char) * (digits + 1));
	hexadecimal[digits] = 0;
	while (decimal)
	{
		digits--;
		hexadecimal[digits] = flags->hex_case[decimal % 16];
		decimal /= 16;
	}
	return (hexadecimal);
}

void	print_hex(char **str, va_list args, t_flags *flags)
{
	unsigned int	decimal;
	char			*hexadecimal;

	if (**str == 'X')
		flags->hex_case = "0123456789ABCDEF";
	decimal = va_arg(args, unsigned int);
	hexadecimal = hex_converter(decimal, flags);
	flags->len = ft_strlen(hexadecimal);
	if (flags->precision >= 0)
		hexadecimal = check_precision(hexadecimal, flags);
	str_printer(hexadecimal, flags);
	(*str)++;
	free(hexadecimal);
}
