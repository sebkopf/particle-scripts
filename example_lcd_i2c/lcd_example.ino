

#include "Display.h"
Display lcd (0x27, 20, 4, 7); // assumes a 20x4 display size

int last_second = 0;

char device_name[20];
char device_public_ip[20];
byte macAddress[6];

#define ONE_DAY_MILLIS (24 * 60 * 60 * 1000)
unsigned long last_sync = millis();

void info_handler(const char *topic, const char *data) {
    if ( strcmp (topic, "spark/device/name") == 0) {
        Serial.println("Device name: " + String(data));
        strncpy ( device_name, data, sizeof(device_name) );
        lcd.print_line(1, "Name: ");
        lcd.print(device_name);
    } else if ( strcmp(topic, "spark/device/ip") == 0) {
        Serial.println("Device public IP: " + String(data));
        strncpy (device_public_ip, data, sizeof(device_public_ip));
        lcd.print_line(3, "IP: ");
        lcd.print(device_public_ip);
    }
    // unsubscribe from events
    if ( strlen(device_name) > 0 && strlen(device_public_ip) > 0) {
        Particle.unsubscribe();
    }
}


void setup(void)
{
  Serial.begin(9600);
  Time.zone(-5); // to get the time correctly

  // LCD screen
  lcd.init();
  lcd.print_line(1, "Date Time:");

  lcd.show_message("temp", "message", 3000); // show an info message for 3 seconds

  // device info
  Particle.subscribe("spark/", info_handler);
  Particle.publish("spark/device/name");
  Particle.publish("spark/device/ip");
}

void loop(void)
{
  if (Time.second() != last_second) {
    lcd.print_line(2, Time.format(Time.now(), "%H:%M:%S %d.%m.%Y"));
    last_second = Time.second();
  }
  lcd.update();
}
