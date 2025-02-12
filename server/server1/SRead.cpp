#include "SRead.h"

SRead::SRead(int speed)
{
  Serial.begin(speed);
}

String SRead::StrRead()
{
  _stroka="";
  if(Serial.available() != 0)
  {
    _a=Serial.read();
    while (_a!='\n') {
    _stroka+=_a;
    _a=Serial.read();
    }
  }
  return _stroka;
}

int SRead::IntRead()
{
  _numbear=0;
  _minus=1;
  if(Serial.available() != 0)
  {
    _a=Serial.read();
    if (_a=='-') _minus=-1;
    while (_a!='\n') {
    if (_a>=48 && _a<=57)
    {
      _figure=_a-48;
      _numbear=_numbear*10+_figure;
    }
    _a=Serial.read();
    }
  }
  _numbear*=_minus;
  return _numbear;
}