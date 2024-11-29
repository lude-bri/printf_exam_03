#include <unistd.h>
#include <stdarg.h>

/**
 * ft_printf
 * Custom implementation of printf-like functionality.
 * 
 * @param s: The format string containing characters and format specifiers (e.g., %s, %d, %x).
 * @param ...: Variable arguments matching the format specifiers in the format string.
 * 
 * @return: The total number of characters written.
 */
int ft_printf(static char *s, ...)
{
    va_list args;    // List to hold the variable arguments.
    int len;         // Counter to track the number of characters written.

    len = 0;
    va_start(args, s); // Initialize the variable arguments.
    while (*s)
    {
        if ((*s == '%') && (*(s + 1) != '\0')) // Check for format specifiers.
        {
            ++s;
            if (*s == 's')  // String format specifier.
                ft_putstr(va_arg(args, char *), &len);
            if (*s == 'd')  // Decimal integer format specifier.
                ft_putnbr(va_arg(args, int), 10, &len);
            if (*s == 'x')  // Hexadecimal integer format specifier.
                ft_putnbr(va_arg(args, int), 16, &len);
        }
        else  // If no format specifier, write the character as is.
            len += write(1, s, 1);
        ++s;
    }
    va_end(args); // Clean up the variable argument list.
    return (len); // Return the total number of characters written.
}

/**
 * ft_putstr
 * Writes a string to the standard output.
 * 
 * @param str: The string to be written.
 * @param len: Pointer to the character count, updated as the string is written.
 * 
 * Handles null strings by writing "(null)".
 */
void ft_putstr(char *str, int *len)
{
    if (!str)  // Handle null string.
        str = "(null)";
    while (*str)  // Write each character of the string.
        *len += write(1, str++, 1);
}

/**
 * ft_putnbr
 * Writes a number to the standard output in a given base (decimal or hexadecimal).
 * 
 * @param nbr: The number to be written.
 * @param base: The numeric base to be used (e.g., 10 for decimal, 16 for hexadecimal).
 * @param len: Pointer to the character count, updated as the number is written.
 * 
 * Handles negative numbers for base 10 by writing a '-' sign and converting the number to positive.
 */
void ft_putnbr(long nbr, int base, int *len)
{
    char *hex = "0123456789abcdef"; // Character set for hexadecimal digits.

    if (nbr < 0)
    {
        nbr *= -1;  // Convert the number to positive.
        *len += write(1, "-", 1);  // Write the negative sign.
    }
    if (nbr >= base)  // Recursive call for digits beyond the base.
        ft_putnbr((nbr / base), base, len);
    *len += write(1, &hex[(nbr % base)], 1);  // Write the remainder digit.
}
