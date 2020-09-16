#include <hid.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include <avr/pgmspace.h>
#include <Usb.h>
#include <usbhub.h>
#include <avr/pgmspace.h>
#include <hidboot.h>
USB     Usb;
USBHub     Hub(&Usb);
String codeString, KODE;
char z;
int cont = 0;
String readString;
HIDUniversal      Hid(&Usb);
HIDBoot<HID_PROTOCOL_KEYBOARD> Keyboard(&Usb);
class KbdRptParser : public KeyboardReportParser {
    void PrintKey(uint8_t mod, uint8_t key);
  protected:
    virtual void OnKeyDown	(uint8_t mod, uint8_t key);
    virtual void OnKeyPressed(uint8_t key);
};
void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key) {
  uint8_t c = OemToAscii(mod, key);
  if (c)
    OnKeyPressed(c);
}
void KbdRptParser::OnKeyPressed(uint8_t key) {
  static uint32_t next_time = 0;      //watchdog
  static uint8_t current_cursor = 0;  //tracks current cursor position
  z = ((char)key); // Read characters that arrive from serial port
  codeString += z;         //each character builds in a string
  cont = cont + 1;

  if (char(key) == 19) {   //verify the las digit of the scanner
    codeString.remove(cont - 1); //Remove the last digit
    //    Serial.println(codeString); //Printing the complete code
    KODE = codeString;
    codeString = "";
    cont = 0;                    // Reset the counter
  }

}
KbdRptParser Prs;

void codeBegin(){
  Serial.println("Jalankan Barcode dan QRCode Scanner");
  if (Usb.Init() == -1) {
    Serial.println("Barcode dan QRCode Tidak Terdeteksi");
  }
  Hid.SetReportParser(0, (HIDReportParser*)&Prs);
  delay( 200 );
}