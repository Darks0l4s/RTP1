#include <esp_now.h>
#include <WiFi.h>
#include "SRead.h"

SRead Sread0(115200);

uint8_t carAddress[] = {0x10, 0x06, 0x1C, 0x41, 0x9F, 0x18};
typedef struct struct_message {
  int x;
  int y;
  int w;
  int n;
} struct_message;
struct_message myData;
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
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
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
    read_string = Sread0.StringInStr(str);
    command();
  }
  
}

void command()
{
  if(read_string=="fast")
  {
    slow_mode=false;
  }
  if(read_string=="slow")
  {
    slow_mode=true;
  }
  if (read_string=="x")
  {
    myData.x=read_numbear;
    Serial.print("x=");
    Serial.println(myData.x);
    if(!slow_mode)goto send_ESP_NOW;
  }
  if (read_string=="y")
  {
    myData.y=read_numbear;
    Serial.print("y=");
    Serial.println(myData.y);
    if(!slow_mode)goto send_ESP_NOW;
  }
  if (read_string=="w")
  {
    myData.w=read_numbear;
    Serial.print("w=");
    Serial.println(myData.w);
    if(!slow_mode)goto send_ESP_NOW;
  }
  if (read_string=="n")
  {
    myData.n=read_numbear;
    Serial.print("n=");
    Serial.println(myData.n);
    if(!slow_mode)goto send_ESP_NOW;
  }
  if (read_string=="send")
  {
    send_ESP_NOW:
    esp_now_send(carAddress, (uint8_t *) &myData, sizeof(myData));
    myData.x=0;
    myData.y=0;
    myData.w=0;
    myData.n=0;
  }
}