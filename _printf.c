#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Custom printf function
 * @format: Format string.
 * Return: Number of chars printed.
 */

int _printf(const char *format, ...)
{
	int n, prints = 0, printed_char = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (n = 0; format && format[n] != '\0'; n++)
	{
		if (format[n] != '%')
		{
			buffer[buff_ind++] = format[n];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			printed_char++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &n);
			width = get_width(format, &n, list);
			precision = get_precision(format, &n, list);
			size = get_size(format, &n);
			++n;
			prints = handle_print(format, &n, list, buffer,
					flags, width, precision, size);
			if (prints == -1)
				return (-1);
			printed_char += prints;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_char);
}

/**
 * print_buffer - Write the contents of buffer to stdout if it exists
 * @buffer: Array of chars.
 * @buff_ind: Pointer to the next char index, representing the length.
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
