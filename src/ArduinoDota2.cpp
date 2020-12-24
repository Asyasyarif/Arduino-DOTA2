#include "ArduinoDota2.h"

ArduinoDota2::ArduinoDota2(char *steamid){
  this->_steamid = steamid;
   client.setInsecure();
}

bool ArduinoDota2::getRecentMatch(){
  
  char buf[100];
  strcpy(buf, HOST_API);
  strcat(buf, ENDPOINT_PLAYERS);
  strcat(buf, _steamid);
  strcat(buf, ENDPOINT_GET_RECENT_MATCH);
 
  const size_t capacity = JSON_ARRAY_SIZE(20) + 20*JSON_OBJECT_SIZE(25) + 5520;
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, this->createRequest(buf));

  JsonObject array = doc[0];
  recentMatch.matchId = array["match_id"].as<long>();
  recentMatch.player_slot = array["player_slot"];
  recentMatch.radiantWin = array["radiant_win"].as<bool>();
  recentMatch.duration  = array["duration"];

  return true;
} 


bool ArduinoDota2::getPlayerStats(){

  char buf[100];
  strcpy(buf, HOST_API);
  strcat(buf, ENDPOINT_PLAYERS);
  strcat(buf, _steamid);
  const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(13) + 800;
  DynamicJsonDocument doc(capacity);
  DeserializationError error = deserializeJson(doc, this->createRequest(buf));
    if (!error) {
        JsonObject profile          = doc["profile"];
        player.mmrEstimate          = doc["mmr_estimate"]["estimate"]; 
        player.soloCompetitiveRank  = doc["solo_competitive_rank"];
        player.competitiveRank      = doc["competitive_rank"];
        player.leaderBoardRank      = doc["leaderboard_rank"];
        player.rankTier             = doc["rank_tier"];
        player.steamId              = (char *) profile["steamid"].as<char *>();
        player.playerName           = (char *) profile["personaname"].as<char *>();
        player.realName             = (char *) profile["name"].as<char *>();
        player.accountId            = profile["account_id"];
        player.dotaPlus             = profile["plus"].as<bool>();
        return true;
    } else {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(error.c_str());
        return false;
    }
   
  return false;
}

String ArduinoDota2::createRequest(char* endpoint){
    #ifdef BOARD_ESP8266
        yield();
    #endif
    http.setTimeout(30000);
    http.begin(client, endpoint);
    int httpCode = http.GET();
    this->http.end();
    if (httpCode > 0) {
      if(httpCode == HTTP_CODE_OK){
        String payload = http.getString();
        Serial.println(payload);
        return payload;
      }
    } else {
      Serial.println("Error on HTTP request");
    }
    Serial.printf("[HTTPsS] GET... failed, error: %s", http.errorToString(httpCode).c_str());
    // client->print(F("GET "));
    // client->print(endpoint);
    // client->println(F(" HTTP/1.1"));

    // client->print(F("Host: "));
    // client->println(HOST_API);
    // client->println(F("Accept: application/json"));
    // client->println(F("Content-Type: application/json"));
    // client->println(F("Cache-Control: no-cache"));

    //  if (client->println() == 0){
    //   Serial.println(F("Failed to send request"));
    //   return false;
    // }
    // char status[32] = {0};
    // client->readBytesUntil('\r', status, sizeof(status));
    // if (strcmp(status, "HTTP/1.1 200 OK") != 0){
    //     Serial.print(F("Unexpected response: "));
    //     Serial.println(status);
    //     return false;
    // }
    //  // Skip HTTP headers
    // char endOfHeaders[] = "\r\n\r\n";
    // if (!client->find(endOfHeaders)){
    //     Serial.println(F("Invalid response"));
    //     return false;
    // }

    // if (client->available()){
    //   String line = client->readStringUntil('\n');
    // }

    // Was getting stray characters between the headers and the body
    // This should toss them away
    // while (client->available() && client->peek() != '{'){
    //     char c = 0;
    //     client->readBytes(&c, 1);
    //     Serial.print(F("Tossing an unexpected character: "));
    //     Serial.println(c);
    // }

    // Let the caller of this method parse the JSon from the client
    
  return "";
}


void ArduinoDota2::clientStop(){

}