// parameters for google spreadsheet
#define LOG_INTERVAL_MS 60 * 1000 // changing logging frequency here
unsigned long last_log = millis();

char device_name[20];
char date_time[20];
char data[255]; // limit allowed


void setup(void) {

  Serial.begin(9600);
  Time.zone(-5); // depends on local time zone

  // random data reader on pins A0 and A1
  pinMode(A0, INPUT); // setup A0 as analog input
  pinMode(A1, INPUT); // setup A1 as analog input

  Serial.println("setup complete");
}

void loop(void) {

  if (millis() - last_log > LOG_INTERVAL_MS) {

    // get date and time
    Time.format(Time.now(), "%Y-%m-%d %H:%M:%S").toCharArray(date_time, sizeof(date_time));
    Serial.println("Sending data to spreadsheet at " + String(date_time) + "... ");

    // read some data
    int data1 = analogRead(A0); // read some data
    int data2 = analogRead(A1); // some some other data

    // construct data
    sprintf(data,"{\"datetime\":\"%s\",\"data1\":%d,\"data2\":%d}", date_time, data1, data2);
    bool success = Particle.publish("post_to_gs", data);

    // make request and interpret result
    if (!success){
      Serial.println("REQUEST FAILED!");
    } else {
      Serial.println("request succesful.");
    }

    last_log = millis();
  }

}
