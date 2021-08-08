#include <ESP8266WiFi.h>
#include <LiquidCrystal.h>
const int rs = D0, en = D1, d4 = D4, d5 = D5, d6 = D6, d7 = D7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const char *ssid = "Shashi"; // Enter your WiFi Name
const char *pass = "Shashi1234569"; // Enter your WiFi Password

WiFiServer server(80);

double air_quality;
void setup() {
pinMode(0, OUTPUT);
pinMode(4, OUTPUT);
pinMode(15, OUTPUT);
Serial.begin(115200);
lcd.begin(16, 2);
delay(10);

Serial.println("Connecting to ");
lcd.print("Connecting.... ");
Serial.println(ssid);
WiFi.begin(ssid, pass);
while (WiFi.status() != WL_CONNECTED)
{
delay(550);
Serial.print(".");
lcd.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
Serial.print("IP Address: ");
Serial.println(WiFi.localIP());
server.begin();
}

void loop() {
 

delay(500);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Pollution=");
air_quality = ((analogRead(A0)/1024.0)*100.0);
lcd.print(air_quality);
lcd.print("%");
Serial.println("Pollution content (MQ-9) : ");
Serial.println(air_quality);


//// put your main code here, to run repeatedly:

WiFiClient client = server.available();
if ( client.connected()) { // loop while the client's connected
// HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
client.println("HTTP/1.1 200 OK");
client.println("Content-type:text/html");
client.println("Connection: close");
client.println("Refresh: 3"); // update the page after 4 sec
client.println();

// turns the GPIOs on and off
lcd.setCursor(0,1);
lcd.print("Sending Data" );

// Display the HTML web page
client.println("<!DOCTYPE html><html>");
client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
client.println("<link rel=\"icon\" href=\"data:,\">");

// Web Page Heading
client.println("<body style=\" text-align:center;background-color:#a89ab8;\"><h1 style=\"color:black; font-size: 27px; text-decoration:underline\"> IOT Mini Project </h1>");
client.println("<body><h1 style=\"color:black; font-size: 24px;\"> Air Pollution Monitoring System </h1>");
client.println("<body><p style=\"text-align: center;color:white; font-size: 30px\">Group Members</p>");
client.println("<body><p style=\"text-align: center;color:black; font-size: 20px;\">Shashi Prajapati(46)</p>");
client.println("<body><p style=\"text-align: center;color:black; font-size: 20px;\">Janhavi Gangurde(78)</p>");
client.println("<body><p style=\"text-align: center;color:black; font-size: 20px;\">Jagdish Dhanjal(13)</p>");
client.println("<body><br>");
client.println("<body><p style=\"font-size:30px;text-align: center;color:white;\">Using MQ-6</p>");

if(air_quality <= 20.0 ){
digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
delay(1000);                       // wait for a second
digitalWrite(0, LOW);    // turn the LED off by making the voltage LOW
client.println("<body><p style=\"color:blue;\"> Pollution Content(in percentage)</p>");
client.println("<body><h1> = " + String(air_quality) +" %"+ "</h1>");
client.println("<body><p style=\"color:#14fc90;font-size:40px;\"> Normal </p>");

} else if (air_quality > 20.0 && air_quality < 70.0){
digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
delay(1000);                       // wait for a second
digitalWrite(4, LOW);    // turn the LED off by making the voltage LOW
client.println("<body><p style=\"color:blue;\"> Pollution Content(in percentage)</p>");
client.println("<body><h1> = " + String(air_quality) +" %"+ "</h1>");
client.println("<body><p style=\"color:#ebd82f;font-size:40px;\"> Medium </p>");
} else {
digitalWrite(15, HIGH);   // turn the LED on (HIGH is the voltage level)
delay(1000);                       // wait for a second
digitalWrite(15, LOW);    // turn the LED off by making the voltage LOW
client.println("<body><p style=\"color:blue;\"> Pollution Content(in percentage)</p>");
client.println("<body><h1> = " + String(air_quality) +" %"+ "</h1>");
client.println("<body><p style=\"font-size:50px; color:red\"> Danger!!! </p>");
}

client.println("</body></html>");
delay(1000);

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Pollution=");
lcd.print(air_quality);
lcd.print("%");
}
}
