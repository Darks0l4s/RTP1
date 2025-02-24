#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>
#include "manipulator.h"
// 1 - +вверх, -вниз, 400 шаг/об
// 2 - +по часовой, -против часовой, 6400
// 3 - +по часовой, -против часовой, 6400
// 4 - +вниз, -вверх, 3200
static const int servoPin1 = 19;
static const int servoPin2 = 21;
Servo servo1;
Servo servo2;
#define STEP_PIN1 27   // Пин для STEP
#define DIR_PIN1 14  // Пин для DIR
#define STEP_PIN2 25   // Пин для STEP
#define DIR_PIN2 26  // Пин для DIR
#define STEP_PIN3 32   // Пин для STEP
#define DIR_PIN3 33  // Пин для DIR
#define STEP_PIN4 23   // Пин для STEP
#define DIR_PIN4 22  // Пин для DIR

manipulator manipulator1(STEP_PIN1, DIR_PIN1, -1, 500);
manipulator manipulator2(STEP_PIN2, DIR_PIN2, 6400, 1000);
manipulator manipulator3(STEP_PIN4, DIR_PIN4, 6400, 1000);
manipulator manipulator4(STEP_PIN3, DIR_PIN3, -1, 500);

typedef struct struct_message {
  int x_;
  int y_;
  int h1_;
  int h2_;
  int serv1_;
  int serv2_;
} struct_message;
struct_message myData;
float x, y, h1, h2, serv1, serv2;
int a1_now=0, a2_now=180;
int f1=0, f2=180;
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
  if (x!=0 || y!=0 )
  {
    math();
    manipulator2.stepMotor(f1-a1_now);
    delay(100);
    manipulator3.stepMotor(f2-a2_now);
    delay(100);
  }
  manipulator1.stepMotor(h1);
  delay(100);
  manipulator4.stepMotor(-h2);
  f1=a1_now;
  f2=a2_now;
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}

void loop() {
  // put your main code here, to run repeatedly:

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