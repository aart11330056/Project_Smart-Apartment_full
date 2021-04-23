#define BLYNK_PRINT Serial
#include <TridentTD_LineNotify.h>

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

int ledPin = D1;
int ledPin1 = D2;
int LED2 = D5;
int LED3 = D6;
int LED4 = D7;

int analogPin = A0; //ประกาศตัวแปร ให้ analogPin
int val = 0;


#define LINE_TOKEN  "nyj7o5haJ6CKAClWIx6V3YGly4VpFx2wTqVH2G2ukDP"
char auth[] = "MSifZl6qLdmXPYRI9OatknqOWqI7q0aX";
char ssid[] = "Areter";
char pass[] = "123456789";

//#define LINE_TOKEN  "MlZ32QhtlyauE0yPp2z8hj8IFRWnpHtruWgkbRkS8pH"
//char auth[] = "MSifZl6qLdmXPYRI9OatknqOWqI7q0aX";
//char ssid[] = "FAMILY";
//char pass[] = "1212312121";


#define DHTPIN D4          // What digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;





// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C \n"));

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup() {
  // Debug console
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);  // sets the pin as output
  pinMode(ledPin1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  Blynk.begin(auth, ssid, pass);

  dht.begin();
  Serial.println(LINE.getVersion());
  // Setup a function to be called every second

  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);
  LINE.notify("connected!");

  timer.setInterval(1000L, sendSensor);
}

void loop() {

  val = analogRead(analogPin);  //อ่านค่าสัญญาณ analog
  Serial.print("val = "); // พิมพ์ข้อมความส่งเข้าคอมพิวเตอร์ "val = "
  Serial.println(val); // พิมพ์ค่าของตัวแปร val
  if (val < 500) { // สามารถกำหนดปรับค่าได้ตามสถานที่ต่างๆ
    digitalWrite(ledPin1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);


  } if (val > 501) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);

    String LineText;
    String string1 = "ตรวจพบแก๊ส 🟠 ";
    LineText = string1 + val;
    Serial.print("Line ");
    Serial.println(LineText);
    LINE.notify(LineText);
    //    delay(2000);

  } if (val > 901) {
    digitalWrite(ledPin1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);

    String LineText;
    String string1 = "ตรวจพบแก๊สจำนวนมาก 🔴 ";
    LineText = string1 + val;
    Serial.print("Line ");
    Serial.println(LineText);
    LINE.notify(LineText);
        delay(5000);

  }
//  else {
//    digitalWrite(ledPin1, HIGH);
//    digitalWrite(LED2, LOW);
//    digitalWrite(LED3, LOW);
//    digitalWrite(LED4, LOW);
//  }
  //  if {
  //    digitalWrite(ledPin1, HIGH);
  //    digitalWrite(LED2, LOW);
  //    digitalWrite(LED3, LOW);
  //    digitalWrite(LED4, LOW);
  //  }

  delay(100);
  Blynk.run();
  timer.run();
}
