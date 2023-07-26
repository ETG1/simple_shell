#include "shell.h"

/**
 * main - entry point
 * @bc: arg count
 * @cv: arg vector
 *
 * Return: 0 on success, 1 on error
 */

int main(int bc, char **cv)
{
	info_t info[] = { INFO_INIT };
	int df = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (df)
		: "r" (df));

	if (bc == 2)
	{
		df = open(cv[1], O_RDONLY);
		if (df == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(cv[0]);
				_eputs(": 0: Failed to open ");
				_eputs(cv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = df;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, cv);
	return (EXIT_SUCCESS);
}

