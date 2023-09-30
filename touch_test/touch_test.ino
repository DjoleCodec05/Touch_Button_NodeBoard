#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define touch_1 5
#define touch_2 6
#define buzzer 4


Adafruit_SSD1306 oled(128, 32, &Wire, -1);

int i = 0;

int touch1;
int touch2;

int btnState;

const int btn =  7;

int count1 = 0;
int count2 = 0;

int freq = 2500;

bool clicked = false;

int pos1 = 5;
int pos2 = 30;

int current_pos = pos1;

int current_count = count1;

String addresses[10];

bool looped = false;

void setup() {
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) for (;;);

  oled.clearDisplay();
  oled.display();

  Serial.begin(9600);

  pinMode(touch_1, INPUT);
  pinMode(touch_2, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
  noTone(buzzer);
}

void loop() {
  touch1 = digitalRead(touch_1);
  touch2 = digitalRead(touch_2);

  btnState = digitalRead(btn);
  
  oled.setTextSize(4);
  oled.setTextColor(WHITE);

  /*
    if (touch1 == HIGH && clicked == false) {
    clicked = true;
    count++;
    tone(buzzer, freq);
    delay(50);
    noTone(buzzer);

    oled.clearDisplay();
    oled.print(count);
    oled.display();
    return;
    } else if (touch2 == HIGH && clicked == false) {
    clicked = true;
    count--;
    tone(buzzer, freq);
    delay(50);
    noTone(buzzer);

    oled.clearDisplay();
    oled.print(count);
    oled.display();
    return;
    } else if (touch1 == LOW && touch2 == LOW) {
    clicked = false;
    }
  */

  refreshDisp();

  if (touch1 == HIGH && clicked == false) {
    clicked = true;
    tone(buzzer, freq);
    delay(50);
    noTone(buzzer);
    if (current_pos == pos1) {
      if (count1 < 9) count1++;
      else count1 = 0;
    } else if (current_pos == pos2) {
      if (count2 < 9) count2++;
      else count2 = 0;
    }

    //refreshDisp();

  } else if (touch2 == HIGH && clicked == false) {
    clicked = true;

    //refreshDisp();
    
    tone(buzzer, freq);
    delay(50);
    noTone(buzzer);

    if (current_pos == pos1) current_pos = pos2;
    else if (current_pos == pos2) current_pos = pos1;
  } else if (touch1 == LOW && touch2 == LOW && btnState == HIGH) clicked = false;

  if (btnState == LOW && clicked == false && i < 10) {
    i++;
    addresses[i] = String(count1) + String(count2);
    clicked = true;
  } else if (btnState == LOW && clicked == false && i > 9) {
    for (int j = 0; j < 10; j++) Serial.println("addresses[j]");
    i = 0;
  }
}

void refreshDisp() {
  oled.clearDisplay();
  oled.setCursor(pos1, 0);
  oled.print(count1);
  oled.setCursor(pos2, 0);
  oled.print(count2);
  oled.fillRect(current_pos, 30, 20, 2, WHITE);
  oled.display();
}
