#include "Arduino.h"

class SRead {
  public:
    SRead(int speed);
    String StrRead();
    int IntRead();
  private:
    String _str="", _stroka="";
    char _a;
    int _numbear, _figure, _minus;
};