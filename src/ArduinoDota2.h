#ifndef ArduinoDota2_h
#define ArduinoDota2_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Client.h>

#if defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266WiFi.h>
	#include <ESP8266HTTPClient.h>
  #include <WiFiClientSecure.h>
  #include <WiFiClientSecureBearSSL.h>
  #define BOARD_ESP8266

#elif defined(ARDUINO_ARCH_ESP32)
    #include <WiFi.h>
    #include <HTTPClient.h>
    #include <WiFiClientSecure.h>
    #define BOARD_ESP32
#endif

#define HOST_API "https://api.opendota.com"
#define HOST_PORT 443
#define ENDPOINT_PLAYERS "/api/players/"
#define ENDPOINT_GET_RECENT_MATCH "/recentMatches"

struct Player{
  char *playerName;
  char *realName;
  char *steamId;
  int accountId;
  uint8_t rankTier;
  uint32_t mmrEstimate;
  uint32_t leaderBoardRank;
  uint32_t soloCompetitiveRank;
  uint32_t competitiveRank;
  bool dotaPlus;
};

struct RecentMatch{
  long  matchId;
  uint32_t player_slot;
  bool radiantWin;
  int duration;
  uint16_t gameMode;
  uint16_t lobbyType;
  uint16_t heroId;
  int startTime;
  uint16_t version;
  uint16_t kills;
  uint16_t deaths;
  uint16_t assists;
  uint16_t skill;
  uint16_t  xpm;
  uint16_t gpm;
  int heroDmg;
  int towerDmg;
  int heroHealing;
  uint16_t lastHits;
  uint16_t lane;
  uint16_t laneRole;
  bool isRoaming;
  uint16_t cluster;
  uint16_t leaverStatus;
  uint16_t partySize;
};


class ArduinoDota2{

  private:
  const char *_steamid;
  String createRequest(char* endpoint);
  void clientStop();
  
  public:
    Player player;
    RecentMatch recentMatch;
    WiFiClientSecure client;
    HTTPClient http;
    ArduinoDota2(char *steamid);
    // ~ArduinoDota2();
    bool getPlayerStats();
    bool getRecentMatch();
  };


#endif