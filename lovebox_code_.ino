#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1
#define CLK_PIN   18
#define DATA_PIN  23
#define CS_PIN    5
#define BUZZER_PIN 19 // Pin GPIO al quale è collegato il buzzer

// Credenziali Wi-Fi
const char* ssid = "TP-Link_OAC7";
const char* password = "61534759";

// Telegram Bot Token e Chat ID
String botToken = "7606895942:xxxxxxxxxxxxxxx"; (api og your telegram bot here)
String chatID = "7068x06xxxxxxx1";

// Variabili per gestire l'offset dei messaggi
String telegramURL = "https://api.telegram.org/bot" + botToken + "/getUpdates";
int lastUpdateId = 0;

// Configurazione Matrix 8x8
MD_MAX72XX matrix = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Configurazione LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Cuore pieno
uint8_t heartFull[8] = {
  0b00000000,
  0b01100110,
  0b11111111,
  0b11111111,
  0b11111111,
  0b01111110,
  0b00111100,
  0b00011000
};

void displayHeartFull() {
  matrix.clear();
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (heartFull[i] & (1 << j)) {
        matrix.setPoint(i, j, true);
      }
    }
  }
  matrix.update();
}

void displayHeartPointByPoint() {
  matrix.clear();
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (heartFull[i] & (1 << j)) {
        matrix.setPoint(i, j, true);
        matrix.update();
        delay(100);
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.print("Connessione Wi-Fi...");

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print(".");
  }

  lcd.clear();
  lcd.print("Connesso!");
  delay(1000);
  lcd.clear();
  lcd.print("Nessuna notifica");
  

  // Inizializza il display Matrix 8x8
  matrix.begin();
  matrix.control(MD_MAX72XX::INTENSITY, 2);

  // Mostra il cuore pieno all'avvio
  displayHeartFull();
}

unsigned long lastHeartAnimationTime = 0;

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println(" Connesso di nuovo!");
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String urlWithOffset = telegramURL + "?offset=" + String(lastUpdateId + 1);
    http.begin(urlWithOffset);
    http.setTimeout(5000);  // Timeout di 5 secondi
    int httpCode = http.GET();

    if (httpCode == 200) {
      String payload = http.getString();
      Serial.println(payload);  // Debug output

      int lastMessageIndex = payload.lastIndexOf("\"text\":\"");
      if (lastMessageIndex != -1) {
        int messageStart = lastMessageIndex + 8;
        int messageEnd = payload.indexOf("\"", messageStart);
        String message = payload.substring(messageStart, messageEnd);

        int updateIdStart = payload.indexOf("\"update_id\":") + 12;
        int updateIdEnd = payload.indexOf(",", updateIdStart);
        int currentUpdateId = payload.substring(updateIdStart, updateIdEnd).toInt();

        if (currentUpdateId > lastUpdateId) {
          lastUpdateId = currentUpdateId;

          // Attiva il buzzer per notificare
          for (int i = 0; i < 3; i++) {
            digitalWrite(BUZZER_PIN, HIGH);
            delay(100);
            digitalWrite(BUZZER_PIN, LOW);
            delay(100);
          }
          digitalWrite(BUZZER_PIN, LOW);

          // Notifica di nuovo messaggio
          lcd.clear();
          lcd.print("Nuovo messaggio");
          delay(2000);  // Mostra la notifica per 2 secondi

          // Mostra il messaggio ricevuto
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Msg da Cristian:");
          lcd.setCursor(0, 1);
          lcd.print(message);  // Mostra il messaggio

          // Cuore che pulsa per 5 secondi
          for (int t = 0; t < 10; t++) {  // Ciclo per far pulsare il cuore per 5 secondi
            matrix.clear();
            if (t % 2 == 0) {  // Accendi il cuore
              displayHeartFull();
            }
            matrix.update();
            delay(500);
          }

          // Mostra il cuore pieno di nuovo
          displayHeartFull();
        }
      }
    } else {
      Serial.print("HTTP Error: ");
      Serial.println(httpCode);
      lcd.clear();
      lcd.print("Errore HTTP");
      delay(5000);  // Aspetta 5 secondi prima di riprovare
    }

    http.end();
  }

  // Ogni 10 secondi il cuore si costruisce punto per punto
  if (millis() - lastHeartAnimationTime >= 30000) {  // 10 secondi = 10000 ms
    displayHeartPointByPoint();
    lastHeartAnimationTime = millis();
  }

  delay(30000);  // Delay tra i controlli
}

Copyright by Cristian.
