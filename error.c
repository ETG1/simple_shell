#include "shell.h"

/**
 *_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */

void _eputs(char *str)
{
	int e = 0;

	if (!str)
		return;
	while (str[e] != '\0')
	{
		_eputchar(str[e]);
		e++;
	}
}

/**
 * _eputchar - writes the character k to stderr
 * @k: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _eputchar(char k)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (k == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(2, buf, e);
		e = 0;
	}
	if (k != BUF_FLUSH)
		buf[e++] = k;
	return (1);
}

/**
 * _putfd - writes the character k to given fd
 * @k: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putfd(char k, int fd)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (k == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(fd, buf, e);
		e = 0;
	}
	if (k != BUF_FLUSH)
		buf[e++] = k;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */

int _putsfd(char *str, int fd)
{
	int e = 0;

	if (!str)
		return (0);
	while (*str)
	{
		e += _putfd(*str++, fd);
	}
	return (e);
}



/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * 
 * Return: 0 if no numbers in string,
 * converted number otherwise -1 on error
 */

int _erratoi(char *s)
{
	int e = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (e = 0;  s[e] != '\0'; e++)
	{
		if (s[e] >= '0' && s[e] <= '9')
		{
			result *= 10;
			result += (s[e] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * 
 * Return: 0 if no numbers in string,
 * converted number otherwise -1 on error
 */

void print_error(info_t *info, char *estr)
{
	
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int e, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (e = 1000000000; e > 1; e /= 10)
	{
		if (_abs_ / e)
		{
			__putchar('0' + current / e);
			count++;
		}
		current %= e;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, a clone of itoa,
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */

char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */

void remove_comments(char *buf)
{
	int e;

	for (e = 0; buf[e] != '\0'; e++)
		if (buf[e] == '#' && (!e || buf[e - 1] == ' '))
		{
			buf[e] = '\0';
			break;
		}
}

