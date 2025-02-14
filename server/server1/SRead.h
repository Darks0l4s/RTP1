#include "Arduino.h"

class SRead {
  public:
    SRead(int speed);
    String StrRead(), StringInStr(String _str);
    int IntRead(), IntInStr(String _str);
  private:
    String _str="", _stroka="",_NewStr="";
    char _a;
    int _numbear, _figure, _minus, _quantity;
};
// StrRead() - прочитать строку
// IntRead() - прочитать число
// IntInStr() - найти число в строке
// StringInStr() -найти строку в строке