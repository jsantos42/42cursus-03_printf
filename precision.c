#include "ft_printf.h"

int	get_precision(char **str, va_list args)
{
	int	number;

	number = 0;
	if (**str == '*')
	{
		number = va_arg(args, int);
		(*str)++;
		if (number < 0)
			return (-1);
	}
	while (**str >= '0' && **str <= '9')
	{
		number = number * 10 + **str - '0';
		if (number > 2147483647)
			return (-1);
		else
			(*str)++;
	}
	return (number);
}

char	*check_precision(char *string, t_flags *flags)
{
	if (flags->precision <= flags->len + flags->negative)
	{
		flags->padding = ' ';
		if (ft_strncmp(string, "", 2) == '0' && flags->precision == 0)
		{
			free(string);
			flags->len = 0;
			return (ft_strdup(""));
		}
		else
			return (string);
	}
	else if (flags->precision < flags->min_width)
		return (precision_smaller(string, flags));
	else
		return (precision_not_smaller(string, flags));
}

char	*precision_smaller(char *string, t_flags *flags)
{
	int		zeros;
	char	*string2;
	char	*string3;

	flags->padding = ' ';
	zeros = flags->precision - flags->len;
	if (flags->negative < 0)
		zeros++;
	flags->len += zeros;
	string2 = malloc((zeros + 1) * (sizeof(char)));
	string2[zeros] = '\0';
	while (zeros-- > 0)
		string2[zeros] = '0';
	string3 = ft_strjoin(string2, string);
	free(string);
	free(string2);
	return (string3);
}

char	*precision_not_smaller(char *string, t_flags *flags)
{
	flags->left_justify = 0;
	flags->padding = '0';
	flags->min_width = flags->precision;
	if (flags->negative < 0)
	{
		flags->len--;
		flags->printed_chars += 1;
	}
	sign_printer(flags);
	return (string);
}
