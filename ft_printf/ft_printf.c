#include    <unistd.h>
#include    <stdarg.h>

int printf_str(char *str)
{
    int len = 0;

    if (!str)
        str = "(null)";
    while (str[len])
        len += write(1, &str[len], 1);
    return (len);
}

int printf_number(long nb, int base)
{
    int len = 0;
    char *number = "0123456789abcdef";

    if (nb < 0 && base == 10)
    {
        len += write(1, "-", 1);
        nb = -nb;
    }
    if (nb / base != 0)
        len += printf_number(nb / base, base);
    len += write(1, &number[nb % base], 1);
    return (len);
}

int printf_format(const char *av, va_list ptr)
{
    int i = 0;
    int len = 0;

    while(av[i])
    {
        if (av[i] == '%' && av[i+1])
        {
            i++;
            if(av[i] == 's')
                len += printf_str(va_arg(ptr, char *));
            if(av[i] == 'd')
                len += printf_number(va_arg(ptr, int), 10);
            if(av[i] == 'x')
                len += printf_number(va_arg(ptr, unsigned int), 16);
        }
        else
            len += write(1, &av[i], 1);
        i++;
    }
    return (len);
}

int ft_printf(const char *av, ... )
{
    va_list ptr;
    int len;

    va_start(ptr, av);
    len = printf_format(av, ptr);
    va_end(ptr);
    return (len);
}