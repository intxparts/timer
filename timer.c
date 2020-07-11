#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32

#endif

#ifdef linux

#endif

#define TICK(T) clock_t T = clock()
#define TOCK(T) printf("timer::execution time: %.10f.\n", (double)(clock() - (T)) / CLOCKS_PER_SEC)

#ifdef _WIN32
void start_process(char* command)
{

}
#endif

#ifdef linux
void start_process(char* command)
{
	FILE* process = popen(command, "r");
	if (process == NULL)
	{
		printf("timer::Failed to execute command: %s\n", command);
		return;
	}
	printf("timer::executing command: %s\n", command);

	const int BUFFER_SIZE = 128;
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, BUFFER_SIZE, process))
	{
		printf("%s", buffer);
	}

	int process_result = pclose(process);
	printf("\ntimer::process exit code: %d\n", process_result);
}
#endif

char* process_args(int argc, char* argv[])
{
	const int BUFFER_SIZE = 512;
	char* buffer = (char*) malloc(BUFFER_SIZE*sizeof(char));
	int t_len = 0;

	for (int i = 1; i < argc; ++i)
	{
		int len = strlen(argv[i]);
		t_len += len;
		if (t_len >= BUFFER_SIZE)
		{
			printf("timer::invalid command: exceeds buffer size of: %d\n", BUFFER_SIZE);
			free(buffer);
			return NULL;
		}

		strcat(buffer, argv[i]);	
	}
	return buffer;
}

int main(int argc, char* argv[])
{
	char* command = process_args(argc, argv);
	if (command == NULL)
	{
		return 1;
	}
	TICK(t);
	start_process(command);
	TOCK(t);
	free(command);
	return 0;

}
