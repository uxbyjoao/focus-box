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
#include <FirebaseESP8266.h>
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

/**
 * Initializes the RFID Reader
 **/
void initializeRFIDReader()
{
  Serial.println("Initializing RFID Reader...");
  SPI.begin();
  mfrc522.PCD_Init();
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);
  Serial.print("RFID Serial Version: ");
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println("");
}

/**
 * Initializes the WiFi connection
 **/
void initializeWiFiConnection()
{
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
}

/**
 * Initializes Firebase connection
 **/
void initializeFirebaseConnection()
{
  Firebase.begin(FIREBASE_HOST_URL, FIREBASE_DATABASE_SECRET);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  Firebase.enableClassicRequest(firebaseData, true);
  Serial.println("Firebase connection done.");
  Serial.println("");
}

/**
 * Post session duration to Firebase
 * @param duration Duration of focus session in milliseconds (from millis())
 **/
void postSessionToFirebase(void duration)
{
  Serial.println("Sending this to the webz -- they'll know what to do.");
}

/**
 * ARDUINO SETUP
 **/
void setup()
{
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

  // Pin setup
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(STATUS_LED_PIN, OUTPUT);

  // Initialize components
  initializeRFIDReader();
  initializeWiFiConnection();
  initializeFirebaseConnection();
}

/**
 * ARDUINO LOOP
 **/
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

  /**
   * PHONE FOUND AND SCANNED
   **/

  // Get current date & time
  int startTime = millis();
  // Play sound
  tone(BUZZER_PIN, NOTE_C6);
  delay(50);
  tone(BUZZER_PIN, NOTE_C7);
  delay(50);
  noTone(BUZZER_PIN);
  // Turn status LED on
  digitalWrite(STATUS_LED_PIN, HIGH);
  // Log stuff
  Serial.println("Phone is on, starting new focus session.");

  /**
 * CHECKS IF PHONE IS STILL IN THE BOX
 **/
  bool cardRemoved = false;
  int counter = 0;
  bool current, previous;
  previous = !mfrc522.PICC_IsNewCardPresent();

  while (!cardRemoved)
  {
    // Phone is in box -- do nothing until phone is removed
    current = !mfrc522.PICC_IsNewCardPresent();

    if (current && previous)
      counter++;

    previous = current;
    cardRemoved = (counter > 20);
    delay(50);
  }

  /**
   * PHONE HAS BEEN REMOVED FROM THE BOX
   **/

  // Get current date & time, calculate difference
  int endTime = millis();
  int sessionTotalTime = endTime - startTime;
  // Play sound
  tone(BUZZER_PIN, NOTE_C7);
  delay(50);
  tone(BUZZER_PIN, NOTE_C6);
  delay(50);
  noTone(BUZZER_PIN);
  // Turn status LED off
  digitalWrite(STATUS_LED_PIN, LOW);
  // Log stuff
  Serial.println("Phone was removed, now stopping focus session.");
  Serial.println("")
      Serial.print("Total milliseconds elapsed: ");
  Serial.print(sessionTotalTime);
  Serial.println("");

  // Post to Fisebase
  postSessionToFirebase(sessionTotalTime)

      Serial.println("");

  // Give the board a little slack...
  delay(1000);

  // Disable scanning
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
