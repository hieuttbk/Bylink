/*************************************************************

  You’ll need:
   - Blynk IoT app (download from App Store or Google Play)
   - ESP8266 board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/

#define BUTTON D3 // Chân nối với nút nhấn onboard
#define LED 2 // Chân nối với đèn LED onboard
#define DHTPIN D2
#define DHTTYPE DHT11


// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID           "TMPLcAweEipa"
#define BLYNK_DEVICE_NAME           "IOT Course Template"
#define BLYNK_AUTH_TOKEN            "a7KmjxqdWMzMwEB1DRtbjFYmbCrWgRYp"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "WiFi Mesh";
char pass[] = "1234567890";

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
void sendSensor()
{
  //demo
  long h1 = random(0,100);
  long t1 = random (0,50);
  
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  //demo
  h=h1;
  t=t1;
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, t);
  Serial.print("Nhiet do: " +String(t));
  Serial.println("  Do am: " +String(h));
}

boolean checkData = false;
int lastBtnStatus;
int VIRTUAL_PIN;
BLYNK_CONNECTED() {
Blynk.syncAll();
}
BLYNK_WRITE(V0)
{
VIRTUAL_PIN = param.asInt();
checkData = true;
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  
  lastBtnStatus = digitalRead(BUTTON);


  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
  timer.setInterval(1000L, sendSensor);
  timer.run();
  
  if (checkData == true){
    digitalWrite(LED, VIRTUAL_PIN);
    checkData == false;
  }

  if (digitalRead(BUTTON) == 0){
    delay(100);
    if (digitalRead(BUTTON) != 0)
  {

  VIRTUAL_PIN = !VIRTUAL_PIN;
  digitalWrite(LED, VIRTUAL_PIN);
  Blynk.virtualWrite(V0, VIRTUAL_PIN);
  Serial.println("In Here" + String(VIRTUAL_PIN));
}
}
  
  
}
