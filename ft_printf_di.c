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
	if (flags->left_justify != 0)
	{
		ft_putstr_fd(string, 1);
		padding(flags);
		flags->printed_chars += flags->len;
	}
	else
	{
		padding(flags);
		ft_putstr_fd(string, 1);
		flags->printed_chars += flags->len;
	}
	(*str)++;
}
