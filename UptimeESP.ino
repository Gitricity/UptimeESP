//Including necessary Librarys
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>

//Enter your WiFi credentials below here
const char* ssid     = "YourWiFiName";
const char* password = "YourWiFiPassword";
//Enter the IP adress of the Service to be monitored below here. If you wish to add more Services, duplicate on of the lines, enter a custom name and give it an IP or domain
//Example1 IP based service: IPAddress ExampleService1 (x, x, x, x);
//Example2 Domain based service: IPAdress Server2 (www.example.com);
IPAddress Service1 (1, 1, 1, 1);

//Additional Stuff. Please only tinker with this, if you know, what you are doing. Else you could brake something
bool ret = false;
int avg_time_ms = Ping.averageTime();

void setup() {
 WiFi.begin(ssid, password); //Beginning the WiFi connection
 Serial.begin(9600); //Opening a serial connection at a 9600 baud rate
 Serial.println("Wellcome to UptimeESP");
 Serial.println("Please be patient the device is booting up");
 if (WiFi.status() != WL_CONNECTED) { //Waiting for a WiFi connection
   Serial.println("Connection established!");
   delay(500);
   Serial.println("You are currently monitoring the following services");
   Serial.println(Service1);
   Serial.print("IP address of the Watcher:\t");
   Serial.println(WiFi.localIP());
   Serial.println();
   }

}

void loop() {
  delay(5000); //Waiting 5 seconds
  ServerPing(); //Going to the Ping function

}

void ServerPing() {
  ret = Ping.ping(Service1); //Setting the ret variable to the response of the Pint. True if successfull, false if not
  if(ret==true){ //If Ping was successfull
    Serial.print("Service 1 pinged successfully. Time taken to respond: ");
    Serial.println(avg_time_ms);
  }
  else{ //If Ping failed
    Serial.println("Ping failed. Please check the internet connection of the Monitor and/or check the Server");
  }
}
