#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>
#include "manipulator.h"
// 1 - +вверх, -вниз, 400 шаг/об
// 2 - +по часовой, -против часовой, 6400
// 3 - +по часовой, -против часовой, 6400
// 4 - +вниз, -вверх, 3200
#define STEP_PIN1 27   // Пин для STEP
#define DIR_PIN1 14  // Пин для DIR
#define STEP_PIN2 25   // Пин для STEP
#define DIR_PIN2 26  // Пин для DIR
#define STEP_PIN3 32   // Пин для STEP
#define DIR_PIN3 33  // Пин для DIR
#define STEP_PIN4 23   // Пин для STEP
#define DIR_PIN4 22  // Пин для DIR
manipulator manipulator1(STEP_PIN1, DIR_PIN1, 360, 100);
manipulator manipulator2(STEP_PIN2, DIR_PIN2, 6400, 2000);
manipulator manipulator3(STEP_PIN4, DIR_PIN4, 6400, 2000);
manipulator manipulator4(STEP_PIN3, DIR_PIN3, 360, 100);

static const int servoPin1 = 19;
static const int servoPin2 = 21;
Servo servo1;
Servo servo2;
int rot1=30, rot2=30;

typedef struct struct_message {
  int x_;
  int y_;
  int h1_;
  int h2_;
  int serv1_;
  int serv2_;
  int scen;
} struct_message;
struct_message myData;
float x, y, h1, h2, serv1, serv2;
int a1_now=0, a2_now=180;
int f1=0, f2=180;
bool send=false;
int scena=0;
int h0=15;
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Print: ");
  Serial.println(myData.x_);
  Serial.println(myData.y_);
  Serial.println(myData.h1_);
  Serial.println(myData.h2_);
  Serial.println(myData.serv1_);
  Serial.println(myData.serv2_);
  x=myData.x_;
  y=myData.y_;
  h1=myData.h1_;
  h2=myData.h2_;
  serv1=myData.serv1_;
  serv2=myData.serv2_;
  scena=myData.scen;
  send=true;
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo1.write(rot1);
  servo2.write(rot2);
}

void loop() {
  if (send)
  {
    if (x!=0 || y!=0 )
    {
      math();
      manipulator2.stepMotor(f1-a1_now);
      delay(500);
      manipulator3.stepMotor(f2-a2_now);
      delay(100);
    }
    manipulator1.stepMotor(h1*2000);
    delay(100);
    manipulator4.stepMotor(-h2*2000);
    h0+=h1;
    h0+=h2;
    f1=a1_now;
    f2=a2_now;
    send=false;
    if(serv2==2) servo2.write(90);
    if(serv2==1) servo2.write(30);
    rot1+=serv1;
    servo1.write(rot1);
    if (scena!=0) circus();
  }

}
void circus()
{
  if(scena==1)
  {
    manipulator4.stepMotor(-6000);
    h0+=3;
    x=17; y=20;
    math2();
    manipulator2.stepMotor(f1-a1_now);
    delay(500);
    manipulator3.stepMotor(f2-a2_now);
    f1=a1_now;
    f2=a2_now;
    manipulator1.stepMotor(-(h0-5)*2000);
    manipulator4.stepMotor(10000);
    servo2.write(90);
    manipulator4.stepMotor(-10000);
    manipulator1.stepMotor((h0-5)*2000);
    y=-10;
    math2();
    manipulator2.stepMotor(f1-a1_now);
    delay(500);
    manipulator3.stepMotor(f2-a2_now);
    f1=a1_now;
    f2=a2_now;
    manipulator4.stepMotor(5000);
    servo2.write(30);
    manipulator4.stepMotor(1000);
    h0-=3;
  }
  if(scena==2)
  {
    manipulator4.stepMotor((h0-18)*2000);
    x=17; y=-10;
    math2();
    manipulator2.stepMotor(f1-a1_now);
    delay(500);
    manipulator3.stepMotor(f2-a2_now);
    f1=a1_now;
    f2=a2_now;
    manipulator4.stepMotor((18-h0)*2000);
    manipulator1.stepMotor((15-h0)*2000);
    servo2.write(90);
    manipulator4.stepMotor(-6000);
    h0+=3;
    x=17; y=20;
    math2();
    manipulator2.stepMotor(f1-a1_now);
    delay(500);
    manipulator3.stepMotor(f2-a2_now);
    f1=a1_now;
    f2=a2_now;
    manipulator1.stepMotor(-(h0-8)*2000);
    manipulator4.stepMotor(16000);
    servo2.write(30);
    manipulator4.stepMotor(-16000);
    manipulator1.stepMotor((h0-8)*2000);
    y=-10;
    math2();
    manipulator2.stepMotor(f1-a1_now);
    delay(500);
    manipulator3.stepMotor(f2-a2_now);
    f1=a1_now;
    f2=a2_now;
    manipulator4.stepMotor(5000);
    servo2.write(30);
    manipulator4.stepMotor(1000);
    h0-=3;
  }
}
void math()
{
  int i,j;
  float x0,y0;
  float delta=5.0, delta_now;
  int a1=-1, a2=-1;
  float x1= 12 * cos(a1_now / 180.0 * M_PI) - 15 * cos((a1_now + a2_now) / 180.0 * M_PI);
  float y1 = 12 * sin(a1_now / 180.0 * M_PI) - 15 * sin((a1_now + a2_now) / 180.0 * M_PI);
  for (i = 0; i < 180; i++)
  {
    for (j = 0; j < 360; j++)
    {
      x0 = 12 * cos(i / 180.0 * M_PI) - 15 * cos((i + j) / 180.0 * M_PI);
      y0 = 12 * sin(i / 180.0 * M_PI) - 15 * sin((i + j) / 180.0 * M_PI);
      delta_now = abs(x0 - (x+x1)) + abs(y0 - (y+y1));
      if (delta>delta_now || delta_now==0)
      {
        a1 = i;
        a2 = j;
        delta = delta_now;
      }
    }
  }
  if (a1!=-1)
  {
    a1_now=a1;
    a2_now=a2;
  }
  Serial.print(f1-a1_now);
  Serial.print(" ");
  Serial.print(f2-a2_now);
}

void math2()
{
  int i,j;
  float x0,y0;
  float delta=5.0, delta_now;
  int a1=-1, a2=-1;
  for (i = 0; i < 180; i++)
  {
    for (j = 0; j < 360; j++)
    {
      x0 = 12 * cos(i / 180.0 * M_PI) - 15 * cos((i + j) / 180.0 * M_PI);
      y0 = 12 * sin(i / 180.0 * M_PI) - 15 * sin((i + j) / 180.0 * M_PI);
      delta_now = abs(x0 - x) + abs(y0 - y);
      if (delta>delta_now || delta_now==0)
      {
        a1 = i;
        a2 = j;
        delta = delta_now;
      }
    }
  }
  if (a1!=-1)
  {
    a1_now=a1;
    a2_now=a2;
  }
  Serial.print(f1-a1_now);
  Serial.print(" ");
  Serial.print(f2-a2_now);
}