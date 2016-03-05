#include "HttpClient.h" // script in particle dev (requires local copies of HttpClient.h/.cpp)
// #include "HttpClient/HttpClient.h" // script in particle cloud

// parameters for google spreadsheet
#define LOG_INTERVAL_MS 60 * 1000 // changing logging frequencyt here
unsigned long last_log = millis();

char device_name[20];
char date_time[20];

const String hostname = "api.pushingbox.com";
const String http_forward = "/pushingbox?devid=";
const String device_ID = ""; // set this to your device id from pushingbox scenario
const String var1 = "&datetime="; // adjust variable name to fit input field of your spreadsheet
const String var2 = "&device="; // adjust variable name
const String var3 = "&data="; // adjust variable name

// HTTP client and request parameters
HttpClient http;

http_header_t headers[] = {
    { "Content-Type", "application/x-www-form-urlencoded" },
    { "Connection" , "close" },
    { NULL, NULL }
};

http_request_t request;
http_response_t response;

// url encode for safe data transfer via http
char urlencode_buffer[50];
static char specials[] = "$&+,/:;=?@ <>#%{}|~[]`"; // url special characters
String urlencode (char *src) {
  char *dst = urlencode_buffer;
  const char DEC2HEX[16 + 1] = "0123456789ABCDEF";
	char c, *d = dst;
	while (c = *src++) {
		if (strchr(specials,c)) { // escape these
			*d++ = '%';
			*d++ = DEC2HEX[c >> 4];
			*d++ = DEC2HEX[c & 0x0F];
		} else {
		  *d++ = c;
    }
	}
	*d = '\0';
	return dst;
}

// callback to get device name
void name_handler(const char *topic, const char *data) {
  strncpy ( device_name, data, sizeof(device_name) );
  Particle.unsubscribe();
}


void setup(void) {

  Serial.begin(9600);
  Time.zone(-5); // depends on local time zone

  // device info
  Particle.subscribe("spark/", name_handler);
  Particle.publish("spark/device/name");

  // Http request
  request.hostname = hostname;
  request.port = 80;

  Serial.println("Setup complete");
}

void loop(void) {

  if (millis() - last_log > LOG_INTERVAL_MS) {

    // get time and construct the request
    Time.format(Time.now(), "%Y-%m-%d %H:%M:%S").toCharArray(date_time, sizeof(date_time));
    Serial.print("Sending data to spreadsheet at " + String(date_time) + "... ");

    request.path = http_forward + device_ID +
        var1 + urlencode(date_time) + var2 + device_name +
        var3 + urlencode("I'm alive!");

    // make request and interpret result
    http.get(request, response, headers);
    if (response.status == 400){
      Serial.println("REQUEST FAILED!");
    } else if (response.status == 200) {
      Serial.println("request succesful.");
    } else {
      Serial.println("unknown response status: " + String(response.status));
    }

    last_log = millis();
  }

}
