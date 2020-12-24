#include "ArduinoDota2.h"

char steamID[] =  "147089663";
char ssid[] = "ARIF";         // your network SSID (name)
char password[] = ""; // your network password

ArduinoDota2 dota(steamID);

unsigned long delayRequest = 60000; // 1minute
unsigned long nowDelayRequest;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  delay(100);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress IP = WiFi.localIP();
  Serial.println(IP);
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) {
    if(millis() > delayRequest + nowDelayRequest){
          Serial.print("Free Heap: ");
          Serial.println(ESP.getFreeHeap());

        if(dota.getPlayerStats()){
          Serial.println("------Get Player Stats------");
          Serial.print("Player Name : ");
          Serial.println(dota.player.playerName);
        //   // Serial.print("acc : ");
        //   // Serial.println(dota.player.accountId);
        //   // Serial.print("DotaPlus : ");
        //   // Serial.println(dota.player.dotaPlus);
        //   // Serial.println("----------------------------");
        }

        if(dota.getRecentMatch()){
          Serial.print("match id ");
          Serial.println(dota.recentMatch.matchId);
          Serial.print("Radiant Win ");
          Serial.println(dota.recentMatch.radiantWin);
          Serial.print("Duration ");
          Serial.println(dota.recentMatch.duration);
        }
        nowDelayRequest = millis();
    }
  }
}