#include <Arduino.h>
#include <log.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
#include <stdarg.h>
uint8_t _serial_name;
uint8_t _baud_rate;
void LOG_INIT(uint8_t serial_name, uint8_t baud_rate){
   _serial_name = serial_name;
   _baud_rate = baud_rate;
   _serial_name.begin(_baud_rate);
   
}

void LOG_PRINT(uint8_t LOG_CASE, size_t line, const char *Fname ,const char* input...) {
  va_list args;
  va_start(args, input);
  switch (LOG_CASE)
  {
  case 1:
    _serial_name.print(YEL"[WARN] File "+String(Fname)+" Line "+ String(line) + ": ");
    break;
  case 2:
    _serial_name.print(CYN"[INFO] File "+String(Fname)+" Line "+ String(line) + ": ");
    break;
  case 3:
    _serial_name.print(GRN"[DEBUG] File "+String(Fname)+" Line "+ String(line) + ": ");
    break;
  case 4:
    _serial_name.print(RED"[ERROR] File "+String(Fname)+" Line "+ String(line) + ": ");
    break;
  default:
    break;
  }
  
  for(const char* i=input; *i!=0; ++i) {
    if(*i!='%') { _serial_name.print(*i); continue; }
    switch(*(++i)) {
      case '%': _serial_name.print('%'); break;
      case 's': _serial_name.print(va_arg(args, char*)); break;
      case 'd': _serial_name.print(va_arg(args, int), DEC); break;
      case 'b': _serial_name.print(va_arg(args, int), BIN); break;
      case 'o': _serial_name.print(va_arg(args, int), OCT); break;
      case 'x': _serial_name.print(va_arg(args, int), HEX); break;
      case 'f': _serial_name.print(va_arg(args, double), 2); break;
    }
  }
  _serial_name.print(RESET);
  _serial_name.println("\n");
  va_end(args);
}