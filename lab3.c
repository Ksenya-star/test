#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 1024

int ifupp(const char *line, const char *quer)
{
	return strstr(line, quer) != NULL;
}

void search(const char *filename, const char *quer)
{
	FILE *input_file = fopen(filename, "r");

	FILE *output_file = fopen("search.txt", "w");

	if (input_file == NULL)
	{
		perror("Ошибка открытия входного файла");
		return;
	}

	if (output_file == NULL)
	{
		perror("Ошибка создания выходного файла");
		fclose(input_file);
		return;
	}

	char line[MAX];
	int line_num = 0;

	while (fgets(line, sizeof(line), input_file))
	{
		line_num++;

		if (ifupp(line, quer))
		{
			fprintf(output_file, "%d %s", line_num, line);	
			
		}
	}

	fclose(input_file);
	fclose(output_file);
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Использование: %s <имя_файла> <строка_поиска>\n", argv[0]);
		return 1;
	}

	const char *filename = argv[1];
	const char *quer = argv[2];

	for (size_t i = 0; i < strlen(quer); i++)
	{
		if (!isupper(quer[i]))
		{
			printf("Запрос должен быть в верхнем регистре.\n");
			return 1;
		}
	}

	search(filename, quer);
	printf("Окончание поиска. Результаты записаны в файл search.txt.\n");

	return 0;
}




