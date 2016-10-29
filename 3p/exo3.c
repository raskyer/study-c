/*
 * TP3 Exercice 3 - Convertisseur base 26 - int
 * @author Vincent Rasquier et un peu google pour stradd
 * ESIPE IR 1
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Vérifie si c est minuscule
 * 1 si c est minuscule, 0 dans le cas contraire
 */
int is_lower(char c)
{
	if (c >= 'a' && c <= 'z')
		return 1;

	return 0;
}

/*
 * Vérifie si c est numéric
 * 1 si c'est un entier, 0 dans le cas contraire
 */
int is_numeric(char c)
{
	if (c >= '0' && c <= '9')
		return 1;

	return 0;
}

/*
 * Convertis une chaine minuscule interprété en base26 en entier
 * tmp = stoque l'entier que représente la lettre (a = 0)
 */
int base26_to_int(char *str)
{
	int result, current, tmp;
	int len;

	result = 0;
	current = 1;
	len = strlen(str);

	while (len > 0)
	{
		tmp = str[len-1] - 97;
		result = result + (tmp * current);
		current = current * 26;
		len--;
	}

	return result;
}

/*
 * Merci google ... c'est vrai que faire r = a + b pour une concaténation
 * de chaine c'était trop simple ! Let's go to malloc!
 * je suis pas censé free ret en plus ? :/
 */
char* stradd(char *a, char *b)
{
	size_t len;
	char   *ret;

	len = 1 + strlen(b);
	ret = (char*)malloc(len * sizeof(char) + 1);
	*ret = '\0';

	return strcat(strcat(ret, a), b);
}

/*
 * Convertis un entier en une chaine base26
 * b10 = l'entier représenter par str
 */
char* int_to_b26(char *str)
{
	int  b10, rest;
	char *result;
	char digit[2];

	b10 = atoi(str);
	result = "";
	digit[1] = '\0';

	while (b10 > 0)
	{
		rest = b10 % 26;
		digit[0] = (char)(rest + 97);

		result = stradd(digit, result);

		b10 = (b10 - rest) / 26;
	}

	return result;
}

/*
 * Le chef d'orchestre !
 */
int main(int argc, char *argv[])
{
	char *str, *b26;
	int  i, len, b10;
	int  lower, integer;

	str     = argv[1];
	lower   = 1;
	integer = 1;
	len     = strlen(str);

	for (i = 0; i < len; i++)
	{
		if (lower)
			lower = is_lower(str[i]);

		if (integer)
			integer = is_numeric(str[i]);
	}

	if (lower)
	{
		b10 = base26_to_int(str);
		printf("(%s)base26 = (%d)base10\n", str, b10);
	}
	else if (integer)
	{
		b26 = int_to_b26(str);
		printf("(%d)base10 = (%s)base26\n", atoi(str), b26);
	}
	else
	{
		return 1;
	}

	return 0;
}
