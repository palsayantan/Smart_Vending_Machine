//libraries
#include <WiFi.h>     // default library for ESP32
#include <HTTPClient.h>

//wifi credentials 
const char* ssid = "********";         // wifi accesspoint name
const char* password = "********";    // wifi accesspoint password

/* RFID Define
  SCK     - D18
  MISO    - D19
  MOSI    - D23
*/
#include "MFRC522.h"
#define SS_PIN  21     // SDA - D21
#define RST_PIN 22    // RST - D22
MFRC522 mfrc522(SS_PIN, RST_PIN);

// LCD Define

#include <LiquidCrystal.h>
const int en = 2, rs = 15, d4 = 4, d5 = 16, d6 = 17, d7 = 5;    // pins for 16x2 LCD display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Keypad Define

#include <Keypad.h>
const byte ROWS = 3; 
const byte COLS = 3; 
char hexaKeys[ROWS][COLS] = {
  {'1','2','A'},
  {'4','5','B'},
  {'*','0','D'}
};

byte rowPins[COLS] = {32, 33, 25};     // connect to the row pinouts of the keypad
byte colPins[ROWS] = {26, 27, 14};    // connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

char customKey;      // variable to store keypad value
String id = "";     // variable to store RFID card ID
char mod;          // variable to store selected modes (1 = product 1, 2 = product 2, B = Balance ,D = Cancel)

int M1=12;     // connect motor 1
int M2=13;    // connect motor 2

void setup () {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  SPI.begin();
  
  lcd.begin(16, 2);
  lcd.print("   Welcome to   ");
  lcd.setCursor(0, 1);
  lcd.print("  ESP32 Based  ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("     Smart     ");
  lcd.setCursor(0, 1);
  lcd.print("Vending Machine");
  delay(2000);
  lcd.clear();
  
  mfrc522.PCD_Init();

  pinMode(M1,OUTPUT);
  pinMode(M2,OUTPUT);
  digitalWrite(M1,LOW);
  digitalWrite(M2,LOW);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting..");
  }
}                                         
// end of setup



void card(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Swipe your Card");                                                 // ask for swiping the card
    
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      delay(50);
      return;
    }
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      delay(50);
      return;
    }
                                                                                 // Read & store card id
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      id.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      id.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    id.toUpperCase();
    Serial.println(id);
    
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    
    lcd.setCursor(0, 1);
    lcd.print(id);
    delay(2000);
    lcd.clear();
    key();
  }



void key(){
  lcd.clear();  
  lcd.setCursor(0, 0);
  lcd.print("Make Your Choice");                                    // ask for mode selection

  char customKey = customKeypad.getKey();                          // store selected key value

  if (!customKey){
    delay(50);
    key();
  }

  Serial.println(customKey);
   
   while (customKey == '1')
  {  
    lcd.setCursor(0, 1);
    lcd.print(">>1");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Processing...");
    lcd.setCursor(0, 1);
    lcd.print("Amount : Rs.5");
    delay(2000);
    mod='a';
    process();
  }
  while (customKey == '2')
  {  
    lcd.setCursor(0, 1);
    lcd.print(">>2");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Processing...");
    lcd.setCursor(0, 1);
    lcd.print("Amount : Rs.10");
    delay(2000);
    mod='b';
    process();
  }
  while (customKey == 'B')                                //Show balence
  {  
    lcd.setCursor(0, 1);
    lcd.print(">>B");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Your Balance  ");
    lcd.setCursor(0, 1);
    lcd.print("is Processing...");
    delay(2000);
    mod='x';
    process();
  }
  while (customKey == 'D')                              //reset
  {
    lcd.setCursor(0, 1);
    lcd.print(">>D");
    delay(500);
    lcd.clear();  
    lcd.setCursor(0, 0);
    lcd.print("  Transaction");
    lcd.setCursor(0, 1);
    lcd.print("   Canceled!!");
    delay(2000);
    lcd.clear();
    ESP.restart();
  }
}



void process() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    if(id==" 35 29 EE 2B" && mod>0){
      String urla = ("http://iot-svm.ml/php/data.php"); //Send request to the server with usre_id and Mode >> http://iot-svm.ml/php/data.php?uid=user1/2/3/4&mod=a/b/x
      String url = (urla + "?uid=" + "user1" + "&mod=" + mod);
      Serial.println(url);
      http.begin(url);
      int httpCode = http.GET(); // response comes >> "lb" = low balance ; "balance" = remaining Amount
      String response = "";

      if (httpCode > 0) {
        // start of fetching get process
        response = http.getString();
        int balance=response.toInt();
        Serial.println(balance);
        
        if (response=="lb"){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(" Sorry, Payment ");
          lcd.setCursor(0, 1);
          lcd.print("  Unsuccessful!  ");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("  Insufficient  ");
          lcd.setCursor(0, 1);
          lcd.print("    Balance!    ");
          delay(2000);
          lcd.clear();
          ESP.restart();
        }
        else if (balance){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Request Complete");
          lcd.setCursor(0, 1);
          lcd.print("Balance : ");
          lcd.setCursor(10, 1);
          lcd.print(balance);
          delay(2000);
      
          while(mod== 'a'){
            digitalWrite(M1,HIGH);
            delay(6000);
            digitalWrite(M1,LOW);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    Thank You    ");
            lcd.setCursor(0, 1);
            lcd.print("Collect the Item"); 
            delay(3000);
            lcd.clear();
            ESP.restart();
          }
          while(mod== 'b'){
            digitalWrite(M2,HIGH);
            delay(6000);
            digitalWrite(M2,LOW);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    Thank You    ");
            lcd.setCursor(0, 1);
            lcd.print("Collect the Item"); 
            delay(3000);
            lcd.clear();
            ESP.restart();
          }
          while(mod== 'x'){
            delay(3000);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    Thank You    "); 
            delay(3000);
            lcd.clear();
            ESP.restart();
          }
        }   
        else
        Serial.println(httpCode);
        http.end();
        delay(500);
      }
    }
    else if(id==" A7 6D 2F BE" && mod>0){
      String urla = ("http://iot-svm.ml/php/data.php"); //Send request to the server with usre_id and Mode >> http://iot-svm.ml/php/data.php?uid=user1/2/3/4&mod=a/b/x
      String url = (urla + "?uid=" + "user2" + "&mod=" + mod);
      Serial.println(url);
      http.begin(url);
      int httpCode = http.GET(); // response comes >> "lb" = low balance ; "balance" = remaining Amount
      String response = "";

      if (httpCode > 0) {
        // start of fetching get process
        response = http.getString();
        int balance=response.toInt();
        Serial.println(balance);
        
        if (response=="lb"){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(" Sorry, Payment ");
          lcd.setCursor(0, 1);
          lcd.print("  Unsuccessful!  ");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("  Insufficient  ");
          lcd.setCursor(0, 1);
          lcd.print("    Balance!    ");
          delay(2000);
          lcd.clear();
          ESP.restart();
        }
        else if (balance){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Request Complete");
          lcd.setCursor(0, 1);
          lcd.print("Balance : ");
          lcd.setCursor(10, 1);
          lcd.print(balance);
          delay(2000);
        
          while(mod== 'a'){
            digitalWrite(M1,HIGH);
            delay(6000);
            digitalWrite(M1,LOW);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    Thank You    ");
            lcd.setCursor(0, 1);
            lcd.print("Collect the Item"); 
            delay(3000);
            lcd.clear();
            ESP.restart();
          }
          while(mod== 'b'){
            digitalWrite(M2,HIGH);
            delay(6000);
            digitalWrite(M2,LOW);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    Thank You    "); 
            lcd.setCursor(0, 1);
            lcd.print("Collect the Item");
            delay(3000);
            lcd.clear();
            ESP.restart();
          }
          while(mod== 'x'){
            delay(3000);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    Thank You    "); 
            delay(3000);
            lcd.clear();
            ESP.restart();
          }
        }  
        else
        Serial.println(httpCode);
        http.end();
        delay(500);
      }
    }
    else if(id==" C7 A1 38 BE" && mod>0){
      String urla = ("http://iot-svm.ml/php/data.php"); //Send request to the server with usre_id and Mode >> http://iot-svm.ml/php/data.php?uid=user1/2/3/4&mod=a/b/x
      String url = (urla + "?uid=" + "user3" + "&mod=" + mod);
      Serial.println(url);
      http.begin(url);
      int httpCode = http.GET(); // response comes >> "lb" = low balance ; "balance" = remaining Amount
      String response = "";

      if (httpCode > 0) {
        // start of fetching get process
        response = http.getString();
        int balance=response.toInt();
        Serial.println(balance);
        
        if (response=="lb"){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(" Sorry, Payment ");
          lcd.setCursor(0, 1);
          lcd.print("  Unsuccessful!  ");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("  Insufficient  ");
          lcd.setCursor(0, 1);
          lcd.print("    Balance!    ");
          delay(2000);
          lcd.clear();
          ESP.restart();
        }
        else if (balance){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Request Complete");
          lcd.setCursor(0, 1);
          lcd.print("Balance : ");
          lcd.setCursor(10, 1);
          lcd.print(balance);
          delay(2000);
          
          while(mod== 'a'){
            digitalWrite(M1,HIGH);
            delay(6000);
            digitalWrite(M1,LOW);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    Thank You    "); 
            lcd.setCursor(0, 1);
            lcd.print("Collect the Item");
            delay(3000);
            lcd.clear();
            ESP.restart();
          }
          while(mod== 'b'){
            digitalWrite(M2,HIGH);
            delay(6000);
            digitalWrite(M2,LOW);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    Thank You    "); 
            lcd.setCursor(0, 1);
            lcd.print("Collect the Item");
            delay(3000);
            lcd.clear();
            ESP.restart();
          }
          while(mod== 'x'){
            delay(3000);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    Thank You    "); 
            delay(3000);
            lcd.clear();
            ESP.restart();
          }
        }  
        else
        Serial.println(httpCode);
        http.end();
        delay(500);
      }
    }
    else if(id==" 61 D5 9D 0A" && mod>0){
      String urla = ("http://iot-svm.ml/php/data.php"); //Send request to the server with usre_id and Mode >> http://iot-svm.ml/php/data.php?uid=user1/2/3/4&mod=a/b/x
      String url = (urla + "?uid=" + "user4" + "&mod=" + mod);
      Serial.println(url);
      http.begin(url);
      int httpCode = http.GET(); // response comes >> "lb" = low balance ; "balance" = remaining Amount
      String response = "";

      if (httpCode > 0) {
        // start of fetching get process
        response = http.getString();
        int balance=response.toInt();
        Serial.println(balance);
        
        if (response=="lb"){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(" Sorry, Payment ");
          lcd.setCursor(0, 1);
          lcd.print("  Unsuccessful!  ");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("  Insufficient  ");
          lcd.setCursor(0, 1);
          lcd.print("    Balance!    ");
          delay(2000);
          lcd.clear();
          ESP.restart();
        }
        else if (balance){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Request Complete");
          lcd.setCursor(0, 1);
          lcd.print("Balance : ");
          lcd.setCursor(10, 1);
          lcd.print(balance);
          delay(2000);
          
          while(mod== 'a'){
            digitalWrite(M1,HIGH);
            delay(6000);
            digitalWrite(M1,LOW);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    Thank You    "); 
            lcd.setCursor(0, 1);
            lcd.print("Collect the Item");
            delay(3000);
            lcd.clear();
            ESP.restart();
          }
          while(mod== 'b'){
            digitalWrite(M2,HIGH);
            delay(6000);
            digitalWrite(M2,LOW);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    Thank You    "); 
            lcd.setCursor(0, 1);
            lcd.print("Collect the Item");
            delay(3000);
            lcd.clear();
            ESP.restart();
          }
          while(mod== 'x'){
            delay(3000);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    Thank You    "); 
            delay(3000);
            lcd.clear();
            ESP.restart();
          }
        }
        else
        Serial.println(httpCode);
        http.end();
        delay(500);
      }
    }
    else if (id && mod>0){
      String urla = ("http://iot-svm.ml/php/data.php"); //Send request to the server with usre_id and Mode >> http://iot-svm.ml/php/data.php?uid=user1/2/3/4&mod=a/b/x
      String url = (urla + "?uid=" + "user5" + "&mod=" + mod);
      Serial.println(url);
      http.begin(url);
      int httpCode = http.GET(); // response comes >> "lb" = low balance ; "balance" = remaining Amount
      String response = "";

      if (httpCode > 0) {
        // start of fetching get process
        response = http.getString();
        int balance=response.toInt();
        Serial.println(response);

        if (response=="lb"){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(" Sorry, Payment ");
          lcd.setCursor(0, 1);
          lcd.print("  Unsuccessful!  ");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("  Insufficient  ");
          lcd.setCursor(0, 1);
          lcd.print("    Balance!    ");
          delay(2000);
          lcd.clear();
          ESP.restart();
        }
        else if(response=="nd"){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("     Sorry     ");
          lcd.setCursor(0, 1);
          lcd.print(" No data found!");
          delay(3000);
          lcd.clear();
          ESP.restart();
        }
        else if (balance){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Request Complete");
          lcd.setCursor(0, 1);
          lcd.print("Balance : ");
          lcd.setCursor(10, 1);
          lcd.print(balance);

          while(mod== 'a'){
            digitalWrite(M1,HIGH);
            delay(6000);
            digitalWrite(M1,LOW);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    Thank You    "); 
            lcd.setCursor(0, 1);
            lcd.print("Collect the Item");
            delay(3000);
            lcd.clear();
            ESP.restart();
          }
          while(mod== 'b'){
            digitalWrite(M2,HIGH);
            delay(6000);
            digitalWrite(M2,LOW);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    Thank You    "); 
            lcd.setCursor(0, 1);
            lcd.print("Collect the Item");
            delay(3000);
            lcd.clear();
            ESP.restart();
          }
          while(mod== 'x'){
            delay(3000);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    Thank You    "); 
            delay(3000);
            lcd.clear();
            ESP.restart();
          }
        }
        else
        Serial.println(httpCode);
        http.end();
        delay(500);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("     Sorry     ");
        lcd.setCursor(0, 1);
        lcd.print(" No data found!");
        delay(3000);
        lcd.clear();
        ESP.restart();
      }
    }
  }
}


  void loop(){
    card();  
  }
