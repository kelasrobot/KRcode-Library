#include<KRcode.h>

void setup(){
  Serial.begin(115200);
  codeBegin();
}
void loop(){
  Usb.Task();
  if(KODE != ""){
    Serial.println(KODE);
    KODE = "";
  }
}
