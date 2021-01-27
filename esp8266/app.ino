/*
 * THE FOCUS BOX
 * Advanced Human-Interface Design - Hochschule Rhein-Waal
 * Winter Semester 2020
 * Created by João Lúcio Gomes
 * Email: jlfgomes@gmail.com
 * Github: https://github.com/uxbyjoao
 *
*/
#include "pitches.h"
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MFRC522.h>

// #define SERIAL_BAUD_RATE 115200

// Pin Configuration
// #define INTERNAL_LED_PIN D4
#define READER_SS_PIN D2
#define READER_RESET_PIN D3
#define BUZZER_PIN D0
#define STATUS_LED_PIN D8
// #define PHOTORES_PIN 9

// Firebase App Configuration
// See Firebase documentation at https://github.com/mobizt/Firebase-ESP8266
#define FIREBASE_HOST_URL "focus-box.firebaseio.com"                        // Firebase DB Url
#define FIREBASE_DATABASE_SECRET "5rbetXRIf3lVwI3sYvWO4n05K9xxLVqgbc93hxdu" // Firebase Auth Key

// WiFi Configuration
#define WIFI_SSID "XuxusHaus"
#define WIFI_PASSWORD "FridaMaria19871992"

FirebaseData firebaseData;                        // Firebase data instance
MFRC522 mfrc522(READER_SS_PIN, READER_RESET_PIN); // Reader instance

// For debugging only, delete when done
void printResult(FirebaseData &data);

void setup()
{
  // Pin setup
  // pinMode(INTERNAL_LED_PIN, OUTPUT);

  // Start serial feed
  Serial.begin(115200);

  // Welcome message
  Serial.println("");
  Serial.println("FOCUS BOX v0.1 by Joao Gomes");
  Serial.println("Project for Advanced Human-Interface Design, Hochschule Rhein-Waal");
  Serial.println("Fuck COVID-19.");
  Serial.println("");
  Serial.println("Initializing now...");
  Serial.println("");
  Serial.println("");

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(STATUS_LED_PIN, OUTPUT);
  // pinMode(PHOTORES_PIN, INPUT);

  // Start RFID Reader
  Serial.println("Initializing RFID Reader...");
  SPI.begin();
  mfrc522.PCD_Init();
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);
  Serial.print("RFID Serial Version: ");
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println("");

  // Start WiFi connection
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println("");
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("");

  // Connect to Firebase and set it up
  Firebase.begin(FIREBASE_HOST_URL, FIREBASE_DATABASE_SECRET);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  Firebase.enableClassicRequest(firebaseData, true);

  // Check if stream is available
  // if (!Firebase.beginStream(firebaseData, "/led_status")) {
  //   Serial.println("------------------------------------");
  //   Serial.println("Can't begin stream connection...");
  //   Serial.println("REASON: " + firebaseData.errorReason());
  //   Serial.println("------------------------------------");
  //   Serial.println();
  // }
}

void loop()
{
  digitalWrite(STATUS_LED_PIN, LOW);
  // Do nothing if no cards are found
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  // Phone found and scanned
  Serial.println("Phone is on");
  // Play sound
  tone(BUZZER_PIN, NOTE_C6);
  delay(50);
  tone(BUZZER_PIN, NOTE_C7);
  delay(50);
  noTone(BUZZER_PIN);
  // Turn status LED on
  digitalWrite(STATUS_LED_PIN, HIGH);

  bool cardRemoved = false;
  int counter = 0;
  bool current, previous;
  previous = !mfrc522.PICC_IsNewCardPresent();

  while (!cardRemoved)
  {
    current = !mfrc522.PICC_IsNewCardPresent();

    if (current && previous)
      counter++;

    previous = current;
    cardRemoved = (counter > 20);
    delay(50);
  }

  // Phone removed
  Serial.println("Phone was removed");
  // Play sound
  tone(BUZZER_PIN, NOTE_C7);
  delay(50);
  tone(BUZZER_PIN, NOTE_C6);
  delay(50);
  noTone(BUZZER_PIN);
  // Turn status LED off
  digitalWrite(STATUS_LED_PIN, LOW);

  delay(1000);

  // Disable scanning
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

// !! DELETE THIS WHEN FINISHED WITH PROJECT
// !! PRINT FUNCTION FOR DEBUGGING PURPOSES
void printResult(FirebaseData &data)
{

  if (data.dataType() == "int")
    Serial.println(data.intData());
  else if (data.dataType() == "float")
    Serial.println(data.floatData(), 5);
  else if (data.dataType() == "double")
    printf("%.9lf\n", data.doubleData());
  else if (data.dataType() == "boolean")
    Serial.println(data.boolData() == 1 ? "true" : "false");
  else if (data.dataType() == "string")
    Serial.println(data.stringData());
  else if (data.dataType() == "json")
  {
    Serial.println();
    FirebaseJson &json = data.jsonObject();
    //Print all object data
    Serial.println("Pretty printed JSON data:");
    String jsonStr;
    json.toString(jsonStr, true);
    Serial.println(jsonStr);
    Serial.println();
    Serial.println("Iterate JSON data:");
    Serial.println();
    size_t len = json.iteratorBegin();
    String key, value = "";
    int type = 0;
    for (size_t i = 0; i < len; i++)
    {
      json.iteratorGet(i, type, key, value);
      Serial.print(i);
      Serial.print(", ");
      Serial.print("Type: ");
      Serial.print(type == FirebaseJson::JSON_OBJECT ? "object" : "array");
      if (type == FirebaseJson::JSON_OBJECT)
      {
        Serial.print(", Key: ");
        Serial.print(key);
      }
      Serial.print(", Value: ");
      Serial.println(value);
    }
    json.iteratorEnd();
  }
  else if (data.dataType() == "array")
  {
    Serial.println();
    //get array data from FirebaseData using FirebaseJsonArray object
    FirebaseJsonArray &arr = data.jsonArray();
    //Print all array values
    Serial.println("Pretty printed Array:");
    String arrStr;
    arr.toString(arrStr, true);
    Serial.println(arrStr);
    Serial.println();
    Serial.println("Iterate array values:");
    Serial.println();
    for (size_t i = 0; i < arr.size(); i++)
    {
      Serial.print(i);
      Serial.print(", Value: ");

      FirebaseJsonData &jsonData = data.jsonData();
      //Get the result data from FirebaseJsonArray object
      arr.get(jsonData, i);
      if (jsonData.typeNum == FirebaseJson::JSON_BOOL)
        Serial.println(jsonData.boolValue ? "true" : "false");
      else if (jsonData.typeNum == FirebaseJson::JSON_INT)
        Serial.println(jsonData.intValue);
      else if (jsonData.typeNum == FirebaseJson::JSON_FLOAT)
        Serial.println(jsonData.floatValue);
      else if (jsonData.typeNum == FirebaseJson::JSON_DOUBLE)
        printf("%.9lf\n", jsonData.doubleValue);
      else if (jsonData.typeNum == FirebaseJson::JSON_STRING ||
               jsonData.typeNum == FirebaseJson::JSON_NULL ||
               jsonData.typeNum == FirebaseJson::JSON_OBJECT ||
               jsonData.typeNum == FirebaseJson::JSON_ARRAY)
        Serial.println(jsonData.stringValue);
    }
  }
  else if (data.dataType() == "blob")
  {

    Serial.println();

    for (int i = 0; i < data.blobData().size(); i++)
    {
      if (i > 0 && i % 16 == 0)
        Serial.println();

      if (i < 16)
        Serial.print("0");

      Serial.print(data.blobData()[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
  else if (data.dataType() == "file")
  {

    Serial.println();

    File file = data.fileStream();
    int i = 0;

    while (file.available())
    {
      if (i > 0 && i % 16 == 0)
        Serial.println();

      int v = file.read();

      if (v < 16)
        Serial.print("0");

      Serial.print(v, HEX);
      Serial.print(" ");
      i++;
    }
    Serial.println();
    file.close();
  }
  else
  {
    Serial.println(data.payload());
  }
}