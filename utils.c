#include "printf.h"

int get_number(char **str)
{
    int number;
//// * flag exclusive
    number = 0;
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

char    *hex_converter(size_t decimal, t_flags *flags)
{
    char    *hexadecimal;
    int     temp;
    int     digits;
//// 2's complement?
    digits = 1;
    temp = decimal;
    while (temp / 16)
    {
        digits++;
        temp /= 16;
    }
    hexadecimal = malloc(sizeof(char) * digits);
    hexadecimal[digits] = 0;
    while (decimal)
    {
        digits--;
        hexadecimal[digits] = flags->hex_case[decimal % 16];
        decimal /= 16;
    }
    return (hexadecimal);
}

void padding(t_flags *flags)
{
    while (flags->min_width > flags->len)
    {
        write(1, &flags->padding, 1);
        (flags->printed_chars)++;
        flags->min_width--;
    }
}

char    *check_precision(char *string, t_flags *flags)
{
    int     zeros;
    char    *string2;
    char    *string3;

    if (flags->precision <= flags->len)
    {
        flags->padding = ' ';
        return (string);
    }
    else if (flags->precision < flags->min_width)
    {
        flags->padding = ' ';
        zeros = flags->precision - flags->len;
        flags->len += zeros;
        string2 = malloc((zeros + 1)*(sizeof(char)));
        string2[zeros] = '\0';
        while (zeros-- > 0)
            string2[zeros] = '0';
        string3 = ft_strjoin(string2, string);
        free(string);
        free(string2);
        return (string3);
    }
    else
    {
        flags->left_justify = 0;
        flags->padding = '0';
        flags->min_width = flags->precision;
        return (string);
    }
}


char    *unsigned_itoa(unsigned int n)
{
    int         	digits;
    unsigned int	temp;
    char            *string;

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
