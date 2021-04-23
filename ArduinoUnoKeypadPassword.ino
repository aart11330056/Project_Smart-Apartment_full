#include <Keypad.h>

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include<EEPROM.h>

#define I2C_ADDR 0x27 //defining the LCD pins
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

LiquidCrystal_I2C lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

char password[4];

char initial_password[4], new_password[4];

int i = 0;

int relay_pin = 10;

char key_pressed = 0;

const byte rows = 4;

const byte columns = 4;

char hexaKeys[rows][columns] = {

  {'1', '2', '3', 'A'},

  {'4', '5', '6', 'B'},

  {'7', '8', '9', 'C'},

  {'*', '0', '#', 'D'}

};

byte row_pins[rows] = {9, 8, 7, 6};

byte column_pins[columns] = {5, 4, 3, 2};

Keypad keypad_key = Keypad( makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);




void setup()

{
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
  pinMode(relay_pin, OUTPUT);

  lcd.begin(16, 2);

  lcd.setCursor(3, 0);

  lcd.print(" Welcome ");

  lcd.setCursor(0, 1);

  lcd.print("Electronic Lock!");

  delay(2000);

  lcd.clear();

  lcd.setCursor(1, 0);

  lcd.print("Enter Password");

  lcd.setCursor(6, 1);

  initialpassword();

}




void loop()

{

  digitalWrite(relay_pin, LOW);

  key_pressed = keypad_key.getKey();

  if (key_pressed == '#')

    change();

  if (key_pressed)

  {

    password[i++] = key_pressed;

    lcd.print(key_pressed);

  }

  if (i == 4)

  {

    delay(200);

    for (int j = 0; j < 4; j++)

      initial_password[j] = EEPROM.read(j);

    if (!(strncmp(password, initial_password, 4)))

    {

      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Pass Accepted!");

      digitalWrite(relay_pin, HIGH);

      delay(2000);

      lcd.setCursor(0, 1);

      lcd.print("Pres # to change");

      delay(2000);

      lcd.clear();

      lcd.print("Enter Password:");

      lcd.setCursor(6, 1);

      i = 0;




    }

    else

    {

      digitalWrite(relay_pin, LOW);




      lcd.clear();

      lcd.print("Wrong Password");

      lcd.setCursor(0, 1);

      lcd.print("Pres # to Change");

      delay(2000);

      lcd.clear();

      lcd.print("Enter Password");

      lcd.setCursor(6, 1);

      i = 0;




    }

  }

}

void change()

{

  int j = 0;

  lcd.clear();

  lcd.print("Current Password");

  lcd.setCursor(6, 1);

  while (j < 4)

  {

    char key = keypad_key.getKey();

    if (key)

    {

      new_password[j++] = key;

      lcd.print(key);



    }

    key = 0;

  }

  delay(500);




  if ((strncmp(new_password, initial_password, 4)))

  {

    lcd.clear();

    lcd.print("Wrong Password");

    lcd.setCursor(3, 1);

    lcd.print("Try Again");

    delay(1000);

  }

  else

  {

    j = 0;

    lcd.clear();

    lcd.print("New Password:");

    lcd.setCursor(6, 1);

    while (j < 4)

    {

      char key = keypad_key.getKey();

      if (key)

      {

        initial_password[j] = key;

        lcd.print(key);

        EEPROM.write(j, key);

        j++;



      }

    }
    delay(1000);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Pass Changed");


    delay(1500);

  }

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Enter Password");

  lcd.setCursor(6, 1);

  key_pressed = 0;

}




void initialpassword() {

  for (int j = 0; j < 4; j++)

    EEPROM.write(j, j + 49);

  for (int j = 0; j < 4; j++)

    initial_password[j] = EEPROM.read(j);

}
