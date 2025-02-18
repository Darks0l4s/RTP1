#include "esp32-hal.h"
#include "esp32-hal-gpio.h"
#include "Mottor.h"

Mottor::Mottor(int mA1, int mB1, int mA2, int mB2, int mA3, int mB3, int mA4, int mB4)
{
  _mA1=mA1;
  _mB1=mB1;
  _mA2=mA2;
  _mB2=mB2;
  _mA3=mA3;
  _mB3=mB3;
  _mA4=mA4;
  _mB4=mB4;
  pinMode(_mA1, OUTPUT);
  pinMode(_mB1, OUTPUT);
  pinMode(_mA2, OUTPUT);
  pinMode(_mB2, OUTPUT);
  pinMode(_mA3, OUTPUT);
  pinMode(_mB3, OUTPUT);
  pinMode(_mA4, OUTPUT);
  pinMode(_mB4, OUTPUT);

  digitalWrite (_mA1, LOW);
  digitalWrite (_mA2, LOW);
  digitalWrite (_mA3, LOW);
  digitalWrite (_mA4, LOW);
  digitalWrite (_mB1, LOW);
  digitalWrite (_mB2, LOW);
  digitalWrite (_mB3, LOW);
  digitalWrite (_mB4, LOW);
}

void Mottor::go(int x, int y, int w)
{
  _x=x;
  _y=y;
  _w=w;
  if (_x != 0 && _y != 0)
  {
    _min=min(abs(_x), abs(_y));
    if (x/y>0)
    {
      if (x>0)
      {
        digitalWrite(_mA2, HIGH);
        digitalWrite(_mB2, LOW);
        digitalWrite(_mA3, HIGH);
        digitalWrite(_mB3, LOW);
      }
      else 
      {
        digitalWrite(_mA2, LOW);
        digitalWrite(_mB2, HIGH);
        digitalWrite(_mA3, LOW);
        digitalWrite(_mB3, HIGH);
      }
    }
    else
    {
      if (x>0)
      {
        digitalWrite(_mA1, HIGH);
        digitalWrite(_mB1, LOW);
        digitalWrite(_mA4, HIGH);
        digitalWrite(_mB4, LOW);
      }
      else 
      {
        digitalWrite(_mA1, LOW);
        digitalWrite(_mB1, HIGH);
        digitalWrite(_mA4, LOW);
        digitalWrite(_mB4, HIGH);
      }
    }
    delay(_min*_micros*4);
    _x=(abs(_x)-_min)*abs(_x)/_x;
    _y=(abs(_y)-_min)*abs(_y)/_y;
    stop();
  }
  if (_x>0)
  {
    digitalWrite (_mA1, LOW);
    digitalWrite (_mA2, LOW);
    digitalWrite (_mA3, LOW);
    digitalWrite (_mA4, LOW);
    digitalWrite (_mB1, HIGH);
    digitalWrite (_mB2, HIGH);
    digitalWrite (_mB3, HIGH);
    digitalWrite (_mB4, HIGH);
    delay(_micros*_x);
    stop();
  }
  if (_x<0)
  {
    digitalWrite (_mA1, HIGH);
    digitalWrite (_mA2, HIGH);
    digitalWrite (_mA3, HIGH);
    digitalWrite (_mA4, HIGH);
    digitalWrite (_mB1, LOW);
    digitalWrite (_mB2, LOW);
    digitalWrite (_mB3, LOW);
    digitalWrite (_mB4, LOW);
    delay(-1*_micros*_x);
    stop();
  }
  if (_y>0)
  {
    digitalWrite(_mA1, HIGH);
    digitalWrite (_mB1, LOW);
    digitalWrite(_mA2, LOW);
    digitalWrite (_mB2, HIGH);
    digitalWrite(_mA3, LOW);
    digitalWrite (_mB3, HIGH);
    digitalWrite(_mA4, HIGH);
    digitalWrite (_mB4, LOW);
    delay(_micros*_y);
    stop();
  }
  if (_y<0)
  {
    digitalWrite (_mA1, LOW);
    digitalWrite (_mB1, HIGH);
    digitalWrite (_mA2, HIGH);
    digitalWrite (_mB2, LOW);
    digitalWrite (_mA3, HIGH);
    digitalWrite (_mB3, LOW);
    digitalWrite (_mA4, LOW);
    digitalWrite (_mB4, HIGH);
    delay(-1*_micros*_y);
    stop();
  }
  if (_w>0)
  {
    digitalWrite (_mA1, LOW);
    digitalWrite (_mB1, HIGH);
    digitalWrite (_mA2, LOW);
    digitalWrite (_mB2, HIGH);
    digitalWrite (_mA3, HIGH);
    digitalWrite (_mB3, LOW);
    digitalWrite (_mA4, HIGH);
    digitalWrite (_mB4, LOW);
    delay(_micros*_w);
    stop();
  }
  if (_w<0)
  {
    digitalWrite (_mA1, HIGH);
    digitalWrite (_mB1, LOW);
    digitalWrite (_mA2, HIGH);
    digitalWrite (_mB2, LOW);
    digitalWrite (_mA3, LOW);
    digitalWrite (_mB3, HIGH);
    digitalWrite (_mA4, LOW);
    digitalWrite (_mB4, HIGH);
    delay(-1*_micros*_w);
    stop();
  }
}