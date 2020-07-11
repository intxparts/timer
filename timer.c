#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BUFFER_SIZE 512

#ifdef _WIN32
	#define popen _popen
	#define pclose _pclose
#endif

#ifdef linux
#endif

#define TICK(T) clock_t T = clock()
#define TOCK(T) printf("timer::execution time: %.10f.\n", (double)(clock() - (T)) / CLOCKS_PER_SEC)

char* concat(char* s1, char* s2)
{
	char* new_str = (char*)malloc(strlen(s1) + strlen(s2) + 1);
	new_str[0] = '\0';
	strcat(new_str, s1);
	strcat(new_str, s2);
	return new_str;
}

void start_process(char* command)
{
	FILE* process = popen(command, "r");
	if (process == NULL)
	{
		printf("timer::Failed to execute command: %s\n", command);
		return;
	}
	printf("timer::executing command: %s\n", command);

	char buffer[BUFFER_SIZE];
	while (fgets(buffer, BUFFER_SIZE, process))
	{
		printf("%s", buffer);
	}

	int process_result = pclose(process);
	printf("\ntimer::process exit code: %d\n", process_result);
}

char* process_args(int argc, char* argv[])
{
	char* buffer = (char*)malloc(1*sizeof(char));
	buffer[0] = '\0';
	for (int i = 1; i < argc; ++i)
	{
		char * c = concat(buffer, argv[i]);
		free(buffer);
		buffer = c;
	}
	return buffer;
}

int main(int argc, char* argv[])
{
	char* command = process_args(argc, argv);
	TICK(t);
	start_process(command);
	TOCK(t);
	free(command);
	return 0;

}

