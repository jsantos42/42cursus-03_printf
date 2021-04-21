#include "ft_printf.h"

void	print_int(char **str, va_list args, t_flags *flags)
{
	int		decimal;
	char	*string;

	decimal = va_arg(args, int);
	string = ft_itoa(decimal);
	flags->len = ft_strlen(string);
	if (flags->precision >= 0)
		string = check_precision(string, flags);
	str_printer(string, flags);
	(*str)++;
	free(string);
}
