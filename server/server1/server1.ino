#include <esp_now.h>
#include <WiFi.h>
#include "SRead.h"

SRead Sread0(115200);

uint8_t carAddress[] = {0x10, 0x06, 0x1C, 0x41, 0x9F, 0x18};
uint8_t maniAddress[] = {0xA0, 0xA3, 0xB3, 0x2B, 0xEC, 0x64};

typedef struct struct_message1 {
  int x;
  int y;
  int w;
} struct_message1;
struct_message1 myData1;

typedef struct struct_message2 {
  int x;
  int y;
  int h1;
  int h2;
  int serv1;
  int serv2;
} struct_message2;
struct_message2 myData2;

esp_now_peer_info_t peerInfo;

String str;
int read_numbear;
String read_string;

bool slow_mode=false;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  memcpy(peerInfo.peer_addr, carAddress, 6);
  esp_now_add_peer(&peerInfo);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  memcpy(peerInfo.peer_addr, maniAddress, 6);
  esp_now_add_peer(&peerInfo);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  if(Serial.available() != 0)
  {
    str = Sread0.StrRead();
    Serial.print("Read: ");
    Serial.println(str);
    Serial.println("//////////////////////////////////////////////////////////////");
    read_numbear = Sread0.IntInStr(str);
    read_string = Sread0.command_read(str);
    command();
  }
  
}

void command()
{
  //Общее
  {
    if(read_string=="fast")
    {
      slow_mode=false;
      Serial.println("Включен быстрый режим");
    }
    if(read_string=="slow")
    {
      slow_mode=true;
      Serial.println("Включен медленный режим");
    }
  }
  //Машинка
  {
    if (read_string=="x")
    {
      myData1.x=read_numbear;
      Serial.print("x=");
      Serial.println(myData1.x);
      if(!slow_mode)goto send_ESP_NOW1;
    }
    if (read_string=="y")
    {
      myData1.y=read_numbear;
      Serial.print("y=");
      Serial.println(myData1.y);
      if(!slow_mode)goto send_ESP_NOW1;
    }
    if (read_string=="w")
    {
      myData1.w=read_numbear;
      Serial.print("w=");
      Serial.println(myData1.w);
      if(!slow_mode)goto send_ESP_NOW1;
    }
    if (read_string=="send")
    {
      send_ESP_NOW1:
      esp_now_send(carAddress, (uint8_t *) &myData1, sizeof(myData1));
      myData1.x=0;
      myData1.y=0;
      myData1.w=0;
    }
  }
  //Манипулятор
  {
    if (read_string=="mx")
    {
      myData2.x=read_numbear;
      Serial.print("ManipulatorX=");
      Serial.println(read_numbear);
      if(!slow_mode)goto send_ESP_NOW2;
    }
    if (read_string=="my")
    {
      myData2.y=read_numbear;
      Serial.print("ManipulatorY=");
      Serial.println(read_numbear);
      if(!slow_mode)goto send_ESP_NOW2;
    }
    if (read_string=="mh1")
    {
      myData2.h1=read_numbear;
      Serial.print("ManipulatorH1=");
      Serial.println(read_numbear);
      if(!slow_mode)goto send_ESP_NOW2;
    }
    if (read_string=="mh2")
    {
      myData2.h2=read_numbear;
      Serial.print("ManipulatorH2=");
      Serial.println(read_numbear);
      if(!slow_mode)goto send_ESP_NOW2;
    }
    if (read_string=="ms")
    {
      myData2.serv1=read_numbear;
      Serial.print("ManipulatorServo=");
      Serial.println(read_numbear);
      if(!slow_mode)goto send_ESP_NOW2;
    }
    if (read_string=="mon")
    {
      myData2.serv2=2;
      Serial.println("Servo ON");
      if(!slow_mode)goto send_ESP_NOW2;
    }
    if (read_string=="moff")
    {
      myData2.serv2=1;
      Serial.print("Servo OFF");
      if(!slow_mode)goto send_ESP_NOW2;
    }
    if (read_string=="msend")
    {
      send_ESP_NOW2:
      esp_now_send(maniAddress, (uint8_t *) &myData2, sizeof(myData2));
      myData2.x=0;
      myData2.y=0;
      myData2.h1=0;
      myData2.h2=0;
      myData2.serv1=0;
      myData2.serv2=0;
    }
  }
}