#include <Arduino.h>

#define RXD2 16
#define TXD2 17

#define PIN_TX 27
#define PIN_RX 26

#define MODEM_RST 5       // SIM800 RESET but also IP5306 IRQ: use IRQ Analyzing signals IP5306 It is in working condition or in standby mode: IRQ = 1 Work, IRQ = 0 When in standby
#define MODEM_PWRKEY 4    // PWRKEY SIM800
#define MODEM_POWER_ON 23 // EN SY8089 4v4 regulator for SIM800
#define MODEM_TX 27
#define MODEM_RX 26
#define MODEM_DTR 32
#define MODEM_RI 33

HardwareSerial serialGsm(1);

void setup()
{
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(115200);
  // Serial.begin(115200, SERIAL_8N1, 15, 2);
  Serial2.begin(115200, SERIAL_8N1, PIN_RX, PIN_TX);
  Serial.println("Serial Txd is on pin: " + String(TX));
  Serial.println("Serial Rxd is on pin: " + String(RX));

  pinMode(MODEM_RST, OUTPUT);
  pinMode(MODEM_PWRKEY, OUTPUT);
  pinMode(MODEM_DTR, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);

  digitalWrite(MODEM_RST, HIGH);    //SIM800 RESET - Negative pulse active Reset
  digitalWrite(MODEM_PWRKEY, HIGH); // turning modem ON - Negative pulse active ON/OFF
  digitalWrite(MODEM_DTR, LOW);
  digitalWrite(MODEM_POWER_ON, HIGH); //Enabling SY8089 4V4 for SIM800 (crashing when in battery)

  digitalWrite(MODEM_PWRKEY, LOW); // turning modem OFF
  delay(1000);
  digitalWrite(MODEM_PWRKEY, HIGH); // turning modem OFF
  delay(2000);
}

void loop()
{ //Choose Serial1 or Serial2 as required
    if (Serial.available())
    {
      Serial2.print(char(Serial.read()));
    }
    delay(10);
    if(Serial2.available())
    {
      Serial.print(char(Serial2.read()));
    }
  
}