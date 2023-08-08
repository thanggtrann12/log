#ifndef __LOG_H__
#define __LOG_H__
void LOG_INIT(SerialName_t serial_name, uint8_t baud_rate);
void LOG_PRINT(LogLevel_t level, size_t line, const char *Fname, const char *input...);
#define LOG_WARN(...) LOG_PRINT(1, __LINE__, __FILE__, __VA_ARGS__)
#define LOG_INFO(...) LOG_PRINT(2, __LINE__, __FILE__, __VA_ARGS__)
#define LOG_DEBUG(...) LOG_PRINT(3, __LINE__, __FILE__, __VA_ARGS__)
#define LOG_ERROR(...) LOG_PRINT(4, __LINE__, __FILE__, __VA_ARGS__)
enum SerialName_t
{
    SERIAL_PORT_0,
    SERIAL_PORT_1,
    SERIAL_PORT_2,
    SERIAL_PORT_3
};

enum LogLevel_t
{
    DEBUG,
    WARN,
    FATAL,
    INFOR
};

#endif // __LOG_H__