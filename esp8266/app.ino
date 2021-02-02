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
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SPI.h>
#include <MFRC522.h>

// Pin Configuration
#define READER_SS_PIN D2
#define READER_RESET_PIN D3
#define BUZZER_PIN D0
#define STATUS_LED_PIN D8

// WiFi Configuration
#define WIFI_SSID "XuxusHaus"
#define WIFI_PASSWORD "FridaMaria19871992"

MFRC522 mfrc522(READER_SS_PIN, READER_RESET_PIN); // Reader instance

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
  // initializeFirebaseConnection();
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
  Serial.println("");
  Serial.print("Total milliseconds elapsed: ");
  Serial.print(sessionTotalTime);
  Serial.println("");
  Serial.println("");

  // Post to Fisebase
  WiFiClient client;
  HTTPClient http;

  if (http.begin(client, "http://us-central1-focus-box.cloudfunctions.net/postSession?duration=" + String(sessionTotalTime)));
  {

    int httpCode = http.GET();
    if (httpCode > 0)
    {
      String payload = http.getString();
      Serial.println("Successfully added session to Firebase.");
      Serial.println(payload);
    }
    else
    {
      Serial.println("Something went wrong when contacting Firebase.");
      String errorString = http.errorToString(httpCode);
      Serial.println(errorString);
    }
    http.end();
  }

  Serial.println("");

  // Give the board a little slack...
  delay(1000);

  // Disable scanning
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
