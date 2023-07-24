#include "main.h"
/**
 * handle_print - Print argument based on type.
 * @fmt: Formatted string.
 * @list: List of arguments.
 * @ind: Index.
 * @buffer: Buffer array.
 * @flags: Active flags.
 * @width: Get width.
 * @precision: Precision.
 * @size: Size specifier.
 * Return: 1 or 2.
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
		int flags, int width, int precision, int size)
{
	int n, len_value = 0, printed_char = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (n = 0; fmt_types[n].fmt != '\0'; n++)
		if (fmt[*ind] == fmt_types[n].fmt)
			return (fmt_types[n].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[n].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		len_value += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			len_value += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		len_value += write(1, &fmt[*ind], 1);
		return (len_value);
	}
	return (printed_char);
}
