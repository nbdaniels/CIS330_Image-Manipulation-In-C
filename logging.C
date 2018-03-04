#include <logging.h>
#include <string.h>

DataFlowException::DataFlowException(const char *type, const char *error)
{
    sprintf(msg,"Throwing exception: (%s): ", type);
    strcat(msg,error);
    Logger::LogEvent(msg);
}
FILE *Logger::logger = fopen("logger.txt", "wb");
Logger::Logger()
{
    const char *filename = "logger.txt";
    if (Logger::logger == NULL)
    {
        fprintf(stderr, "Unable to open file %s\n", filename);
        return;
    }
}

void Logger::LogEvent(const char *event)
{
    fwrite(event, sizeof(char), strlen(event), Logger::logger);
    char *newLine = "\n";
    fwrite(newLine, sizeof(char), strlen(newLine), Logger::logger);
}

void Logger::Finalize()
{
    fclose(Logger::logger);
}