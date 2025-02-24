#include "Arduino.h"

class manipulator
{
  public:
  manipulator(int step_pin, int dir_pin, int step_on_360, int time);
  void stepMotor(int alpha);

  private:
  int _step_pin, _dir_pin, _step360, _time;
  long long _i;
  long long _step1=0, _alpha;
};