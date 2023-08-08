#include <Arduino.h>
#include <stdarg.h>

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

Stream *_serial_port; // Pointer to the selected serial port
uint8_t _baud_rate;

void LOG_INIT(SerialName_t serial_name, uint8_t baud_rate)
{
    _baud_rate = baud_rate;

    switch (serial_name)
    {
    case SERIAL_PORT_0:
        _serial_port = &Serial;
        break;
    case SERIAL_PORT_1:
        _serial_port = &Serial1;
        break;
    case SERIAL_PORT_2:
        _serial_port = &Serial2;
        break;
    case SERIAL_PORT_3:
        _serial_port = &Serial3;
        break;
    default:
        break;
    }

    _serial_port->begin(_baud_rate);
}

void LOG_PRINT(LogLevel_t level, size_t line, const char *Fname, const char *input, ...)
{
    va_list args;
    va_start(args, input);

    switch (level)
    {
    case DEBUG:
        _serial_port->print(GRN "[DEBUG] File " + String(Fname) + " Line " + String(line) + ": ");
        break;
    case WARN:
        _serial_port->print(YEL "[WARN] File " + String(Fname) + " Line " + String(line) + ": ");
        break;
    case FATAL:
        _serial_port->print(RED "[FATAL] File " + String(Fname) + " Line " + String(line) + ": ");
        break;
    case INFOR:
        _serial_port->print(CYN "[INFO] File " + String(Fname) + " Line " + String(line) + ": ");
        break;
    default:
        break;
    }

    for (const char *i = input; *i != 0; ++i)
    {
        if (*i != '%')
        {
            _serial_port->print(*i);
            continue;
        }
        switch (*(++i))
        {
        case '%':
            _serial_port->print('%');
            break;
        case 's':
            _serial_port->print(va_arg(args, char *));
            break;
        case 'd':
            _serial_port->print(va_arg(args, int), DEC);
            break;
        case 'b':
            _serial_port->print(va_arg(args, int), BIN);
            break;
        case 'o':
            _serial_port->print(va_arg(args, int), OCT);
            break;
        case 'x':
            _serial_port->print(va_arg(args, int), HEX);
            break;
        case 'f':
            _serial_port->print(va_arg(args, double), 2);
            break;
        }
    }

    _serial_port->print(RESET);
    _serial_port->println();
    va_end(args);
}
