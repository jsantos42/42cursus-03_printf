#include "ft_printf.h"

char	*unsigned_itoa(unsigned int n)
{
	int				digits;
	unsigned int	temp;
	char			*string;

	digits = 1;
	temp = n;
	while (temp / 10)
	{
		digits++;
		temp /= 10;
	}
	string = malloc(sizeof(char) * digits);
	string[digits] = '\0';
	while (--digits >= 0)
	{
		string[digits] = (char)((n % 10) + '0');
		n /= 10;
	}
	return (string);
}

void	print_unsigned_int(char **str, va_list args, t_flags *flags)
{
	unsigned int	number;
	char			*string;

	number = va_arg(args, unsigned int);
	string = unsigned_itoa(number);
	flags->len = ft_strlen(string);
	if (flags->precision >= 0)
		string = check_precision(string, flags);
	str_printer(string, flags);
	(*str)++;
	free(string);
}
