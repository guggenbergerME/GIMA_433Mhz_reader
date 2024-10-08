/* ***********************************************
copyright by T.Guggenberger
************************************************ */
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <RCSwitch.h>
#include <Ethernet.h>


//************************************************************************** 433 Mhz
int pin; // int for Receive pin.
RCSwitch mySwitch = RCSwitch();

//************************************************************************** LAN Network definieren N
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(10, 100, 3, 50); //comment this line if you are using DHCP
IPAddress server(10, 100, 0, 20); // mqtt Server
EthernetClient ethClient;




//************************************************************************** Funktionsprototypen
void loop                       ();
void setup                      ();
//void reconnect                  ();
//void callback(char* topic, byte* payload, unsigned int length);


void setup() {
  Serial.begin(115200);

// ------------------------------------------------------------------------- Ethernet starten
  Ethernet.begin(mac, ip);
  // Pause Netzwerk Antwort
  delay(1500);  

// ------------------------------------------------------------------------- 433 Mhz Setup
#ifdef ESP32
pin = 4;  // for esp32! Receiver on GPIO pin 4. 
#elif ESP8266
pin = 4;  // for esp8266! Receiver on pin 4 = D2.
#else
pin = 0;  // for Arduino! Receiver on interrupt 0 => that is pin #2
#endif    

  if (ELECHOUSE_cc1101.getCC1101()){       // Check the CC1101 Spi connection.
  Serial.println("Connection OK");
  }else{
  Serial.println("Connection Error");
  }
//CC1101 Settings:                (Settings with "//" are optional!)
  ELECHOUSE_cc1101.Init();            // must be set to initialize the cc1101!
//ELECHOUSE_cc1101.setRxBW(812.50);  // Set the Receive Bandwidth in kHz. Value from 58.03 to 812.50. Default is 812.50 kHz.
//ELECHOUSE_cc1101.setPA(10);       // set TxPower. The following settings are possible depending on the frequency band.  (-30  -20  -15  -10  -6    0    5    7    10   11   12)   Default is max!
  ELECHOUSE_cc1101.setMHZ(433.92); // Here you can set your basic frequency. The lib calculates the frequency automatically (default = 433.92).The cc1101 can: 300-348 MHZ, 387-464MHZ and 779-928MHZ. Read More info from datasheet.
  mySwitch.enableReceive(pin);  // Receiver on
  ELECHOUSE_cc1101.SetRx();  // set Receive on
  
}
void loop() {
 
  if (mySwitch.available()){

    Serial.print("Received ");
    Serial.println( mySwitch.getReceivedValue() );
    /*
    Serial.print(" / ");
    Serial.print( mySwitch.getReceivedBitlength() );
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println( mySwitch.getReceivedProtocol() );
     
    Serial.print("RSSI: ");
    Serial.println(ELECHOUSE_cc1101.getRssi());
    */
    mySwitch.resetAvailable();
  }
}