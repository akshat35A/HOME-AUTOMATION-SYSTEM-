#include <ESP8266WiFi.h>

#define BLYNK_TEMPLATE_NAME "Smart Home Automation"
#define BLYNK_AUTH_TOKEN "J4n4gbz556Ljged82V0zTR-Z1oar1S-l"
#define BLYNK_TEMPLATE_ID "TMPL3pYQCHICw"

const char* ssid = "Akshat's S24 FE";
const char* password = "olay1234";

WiFiServer server(80);

String dataFromMega = "T:0,F:0,D:0,S:0,B:0,L:0";

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected Successfully!");
  Serial.print("ESP8266 IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {

  if (Serial.available()) {
    dataFromMega = Serial.readStringUntil('\n');
  }

  WiFiClient client = server.available();
  if (!client) return;

  float temp = 0;
  int fan = 0, door = 0, smoke = 0, buzzer = 0, led = 0;

  sscanf(dataFromMega.c_str(),
         "T:%f,F:%d,D:%d,S:%d,B:%d,L:%d",
         &temp, &fan, &door, &smoke, &buzzer, &led);

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();

  client.println("<!DOCTYPE html><html>");
  client.println("<head>");
  client.println("<meta http-equiv='refresh' content='3'>");
  client.println("<title>Smart Home Dashboard</title>");
  client.println("<style>");
  client.println("body { font-family: Arial; text-align: center; background: #111; color: white; }");
  client.println(".card { background: #222; padding: 20px; margin: 15px; border-radius: 10px; }");
  client.println(".on { color: lime; font-weight: bold; font-size: 20px; }");
  client.println(".off { color: red; font-weight: bold; font-size: 20px; }");
  client.println("</style>");
  client.println("</head><body>");

  client.println("<h1>🏠 SMART HOME AUTOMATION</h1>");

  client.println("<div class='card'>");
  client.println("<h2>🚪 Door Status</h2>");
  client.println(door ? "<span class='on'>OPEN</span>" : "<span class='off'>CLOSED</span>");
  client.println("</div>");

  client.println("<div class='card'>");
  client.println("<h2>🌡 Temperature</h2>");
  client.print("<span class='on'>");
  client.print(temp);
  client.println(" °C</span>");
  client.println("</div>");

  client.println("<div class='card'>");
  client.println("<h2>💨 Fan Status</h2>");
  client.println(fan ? "<span class='on'>ON</span>" : "<span class='off'>OFF</span>");
  client.println("</div>");

  client.println("<div class='card'>");
  client.println("<h2>🔥 Smoke Detection</h2>");
  client.println(smoke ? "<span class='off'>SMOKE DETECTED</span>" : "<span class='on'>SAFE</span>");
  client.println("</div>");

  client.println("<div class='card'>");
  client.println("<h2>🔔 Buzzer Status</h2>");
  client.println(buzzer ? "<span class='off'>ON</span>" : "<span class='on'>OFF</span>");
  client.println("</div>");

  client.println("<div class='card'>");
  client.println("<h2>💡 Room LED</h2>");
  client.println(led ? "<span class='on'>ON</span>" : "<span class='off'>OFF</span>");
  client.println("</div>");

  client.println("</body></html>");

  client.stop();
}
