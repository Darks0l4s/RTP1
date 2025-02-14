#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
    int x_rec;
    int y_rec;
    int w_rec;
} struct_message;

struct_message myData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Print: ");
  Serial.println(myData.x_rec);
  Serial.println(myData.y_rec);
  Serial.println(myData.w_rec);
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

}