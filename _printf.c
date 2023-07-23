#include "main.h"

void print_buffer(char buffer[], int *buff_ind);
/**
 * _printf - Custom implementation of printf function.
 *
 * This function prints the formatted output based on the given format
 * string and additional arguments. It supports various format specifiers
 * such as %c, %s, %d, %i, %u, %x, %X, and %%.
 *
 * @format: A pointer to a constant character array (format string)
 *          that contains the text to be printed along with optional
 *          format specifiers.
 *
 * Return: The number of characters printed (excluding the null
 *         terminator) on success, or -1 if an error occurs.
 */

int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
					flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}
/**
 * print_buffer - Prints the contents of the buffer if it exists.
 *
 * This function prints the characters stored in the buffer array up to
 * the current buffer index (buff_ind) to the standard output (stdout).
 * After printing, the buffer index is reset to zero, ready for further use.
 *
 * @buffer: Array of characters to be printed.
 * @buff_ind: A pointer to an integer representing the current index in
 *            the buffer. This index is updated by the function after
 *            printing the contents.
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

