#include "esp32-hal-gpio.h"
#include "manipulator.h"

manipulator::manipulator(int step_pin, int dir_pin, int step_on_360, int time)
{
  _time=time;
  _step360=step_on_360;
  _step_pin=step_pin;
  _dir_pin=dir_pin;
  pinMode(_step_pin, OUTPUT);
  pinMode(_dir_pin, OUTPUT);
}
void manipulator::stepMotor(int alpha)
{
  _alpha=alpha;
  if (_alpha == 0) return;
  _step1 = _step360 / (360 / _alpha);
  digitalWrite(_dir_pin, (_alpha>0));
  _step1=_step360/(360/_alpha);
  int i;
  for (i = 0; i < abs(_step1); i++) {
    digitalWrite(_step_pin, HIGH);
    delayMicroseconds(500); // Ширина импульса (500 мкс)
    digitalWrite(_step_pin, LOW);
    delayMicroseconds(_time);
    yield();
  }
}
