#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <TaskSchedulerDeclarationsWithSettings.h>
#include <ESP8266WiFi.h>
#include <Controller/Controller.h>

static void IRAM_ATTR buttonIsr();
static void IRAM_ATTR flashIsr();

static const uint8_t FLASH_PIN = 0;
static const uint8_t BUTTON_PIN = 3;

static volatile bool buttonRequest = false;
static volatile bool flashRequest = false;

static Scheduler basePriorityScheduler;

static Controller controller{basePriorityScheduler, flashRequest, buttonRequest};

void setup()
{
  Serial.begin(115200);
  Serial.println(F("\nBooting.."));

  WiFi.persistent(false);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.setAutoReconnect(true);

  pinMode(FLASH_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonIsr, FALLING);
  attachInterrupt(digitalPinToInterrupt(FLASH_PIN), flashIsr, FALLING);

  Serial.println(F("Initialization done! Starting scheduler..."));
}

void loop()
{
  basePriorityScheduler.execute();
}

static void IRAM_ATTR buttonIsr()
{
  buttonRequest = true;
  // Delay the button process task for soft debounce
  controller.interruptOccurred();
}

static void IRAM_ATTR flashIsr()
{
  flashRequest = true;
  // Delay the button process task for soft debounce
  controller.interruptOccurred();
}