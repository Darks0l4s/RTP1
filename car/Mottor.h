#include "Arduino.h"

class Mottor {
  public:
    Mottor(int mA1, int mB1, int mA2, int mB2, int mA3, int mB3, int mA4, int mB4);
    void go(int x, int y, int w);
  private:
    int _mA1, _mB1, _mA2, _mB2, _mA3, _mB3, _mA4, _mB4;
    int _x, _y, _w;
    int _min;
    int _micros=100;
    void stop()
    {
      digitalWrite (_mA1, LOW);
      digitalWrite (_mA2, LOW);
      digitalWrite (_mA3, LOW);
      digitalWrite (_mA4, LOW);
      digitalWrite (_mB1, LOW);
      digitalWrite (_mB2, LOW);
      digitalWrite (_mB3, LOW);
      digitalWrite (_mB4, LOW);
      delay(500);
    }
};