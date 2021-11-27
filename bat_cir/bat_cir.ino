#include <INA226.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display;

#define INA226_ADDRESS 0x40
#define OLED_ADDRESS 0x3C

INA226 ina;

char bline[17] = "                ";
const int deltat= 500;
unsigned long cmilli, pmilli;

void setup() {
  ina.begin(INA226_ADDRESS);
  ina.configure(INA226_AVERAGES_1, INA226_BUS_CONV_TIME_1100US, INA226_SHUNT_CONV_TIME_1100US, INA226_MODE_SHUNT_BUS_CONT);
  ina.calibrate(0.004, 20.48);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  Wire.begin();
}

void loop() {
  cmilli = millis();
  if (cmilli - pmilli > deltat) {
    pmilli = cmilli;
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0,0);
    float volts= ina.readBusVoltage();
    float current = ina.readShuntCurrent();
    float Vshunt= ina.readShuntVoltage();
    display.print("V=");
    display.println(volts);
    display.print("A=");
    display.println(current);
    display.display();
    display.clearDisplay();
  }
}
