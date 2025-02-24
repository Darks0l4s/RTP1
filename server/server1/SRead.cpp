#include "WString.h"
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
    if (_a=='-') _minus*=-1;
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

int SRead::IntInStr(String _str)
{
  _minus=1;
  _numbear=0;
  int i=0;
  _quantity=_str.length();
  while (_str[i]!='=' && i<_quantity) {
  i++;
  }
  for (i=i; i<_quantity; i++)
  {
    if (_str[i]=='-') _minus*=-1;
    if (_str[i]>=48 && _str[i]<=57)
    {
      _figure=_str[i]-48;
      _numbear=_numbear*10+_figure;
    }
  }
  _numbear*=_minus;
  return _numbear;
}

String SRead::StringInStr(String _str)
{
  _NewStr="";
  int i;
  _quantity=_str.length();
  for (i=0; i<_quantity; i++)
  {
    _a=_str[i];
    if(_a>=65 && _a<=90) _a+=32;
    if(_a>=95 && _a<=122) _NewStr+=_a;
  }
  return _NewStr;
}

String SRead::command_read(String _str)
{
  _NewStr="";
  int i;
  _quantity=_str.length();
  for (i=0; i<_quantity; i++)
  {
    _a=_str[i];
    if(_a>=65 && _a<=90) _a+=32;
    if(_a==61) break; 
    if(_a!=' ')_NewStr+=_a;
  }
  return _NewStr;
}