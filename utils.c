#include "printf.h"

int get_number(char **str)
{
    int number;

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

//int     count_digits(int number)
//{
//    int count;
//
//    count = 1;
//    if (number / 10)
//        count += count_digits(number / 10);
//    return (count);
//}


char    *hex_converter(size_t decimal)
{
    char    *hexadecimal;
    size_t  temp;
    int     iter;

    iter = 0;
    temp = decimal;
    while (temp)
    {
        temp /= 16;
        iter++;
    }
    hexadecimal = malloc(sizeof(char) * iter + 1);
    hexadecimal[iter] = 0;
    while (decimal)
    {
        iter--;
        temp = decimal % 16;
        if (temp > 9)
            hexadecimal[iter] = temp + 'a' - 10;
        else
            hexadecimal[iter] = temp + '0';
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
