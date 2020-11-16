/*
 * THE FOCUS BOX
 * Advanced Human-Interface Design - Hochschule Rhein-Waal
 * Winter Semester 2020
 * Created by João Lúcio Gomes
 * Email: jlfgomes@gmail.com
 * Github: https://github.com/uxbyjoao
 *
*/
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

// App Configuration
// See documentation at https://github.com/mobizt/Firebase-ESP8266
#define FIREBASE_HOST_URL "focus-box.firebaseio.com"                        // Firebase DB Url
#define FIREBASE_DATABASE_SECRET "5rbetXRIf3lVwI3sYvWO4n05K9xxLVqgbc93hxdu" // Firebase Auth Key
#define WIFI_SSID "XuxusHaus"
#define WIFI_PASSWORD "FridaMaria19871992"
#define INTERNAL_LED_PIN D4

FirebaseData firebaseData; // Global object where all data from Firebase will live

// For debugging only, delete when done
void printResult(FirebaseData &data);

void setup()
{
  // Pin setup
  pinMode(INTERNAL_LED_PIN, OUTPUT);

  // Start serial feed
  Serial.begin(115200);

  // Start WiFi connection
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Connect to Firebase and set it up
  Firebase.begin(FIREBASE_HOST_URL, FIREBASE_DATABASE_SECRET);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  Firebase.enableClassicRequest(firebaseData, true);
}

void loop()
{
  // Reading database flag and setting it to LED indicator
  // See https://github.com/mobizt/Firebase-ESP8266#read-data
  Serial.println();
  Serial.print("Attemting to read boolean from Firebase...");
  if (Firebase.getBool(firebaseData, "/led_status"))
  {
    if (firebaseData.dataType() == "boolean")
    {
      if (firebaseData.boolData() == true)
      {
        digitalWrite(INTERNAL_LED_PIN, LOW); // it is active low on the ESP-01)
      }
      else
      {
        digitalWrite(INTERNAL_LED_PIN, HIGH);
      }
    }
  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }
  delay(500);
}

// ! Delete this when development is done!
void printResult(FirebaseData &data)
{
  // See code at https://github.com/mobizt/Firebase-ESP8266/blob/master/examples/Basic/Basic.ino
  // This function prints results from Firebase's responses
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
