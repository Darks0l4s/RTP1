#include <esp_now.h>
#include <WiFi.h>
#include "Mottor.h"

#define MottorA1 32 //левое заднее, HIGH вперёд
#define MottorB1 33 

#define MottorA2 25 //левое переднее, HIGH вперёд
#define MottorB2 26

#define MottorA3 13 //правое заднее, HIGH вперёд
#define MottorB3 12

#define MottorA4 17 //правое переднее, HIGH вперёд
#define MottorB4 16
Mottor Mottor0(MottorA1, MottorB1, MottorA2, MottorB2, MottorA3, MottorB3, MottorA4, MottorB4);

typedef struct struct_message {
    int x_rec;
    int y_rec;
    int w_rec;
    int scen;
} struct_message;
int scena=0;
struct_message myData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Print: ");
  Serial.println(myData.x_rec);
  Serial.println(myData.y_rec);
  Serial.println(myData.w_rec);
  scena=myData.scen;
  Mottor0.go(myData.x_rec, myData.y_rec, myData.w_rec);
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
  if (scena!=0) test();
}
void test()
{
  if(scena==1)
  {
    Mottor0.go(20, 0, 0);
    Mottor0.go(0, 20, 0);
    Mottor0.go(-20, -20, 0);
  }
  if(scena==2)
  {
    Mottor0.go(0, 20, 0);
    Mottor0.go(0, 0, 80);
    Mottor0.go(20, 0, 0);
    Mottor0.go(0, -20, 0);
    Mottor0.go(0, 0, -80);
    Mottor0.go(20, 0, 0);
  }
  if(scena==3)
  {
    Mottor0.go(20, 0, 0);
    Mottor0.go(0, 20, 0);
    Mottor0.go(-20, 0, 0);
    Mottor0.go(0, -20, 0);
  }
  if(scena==4)
  {
    Mottor0.go(30, 0, 0);
    Mottor0.go(30, 0, 0);
  }
  scena=0;
}