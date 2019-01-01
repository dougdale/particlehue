#include "huebridge.h"
#include <ArduinoJson.h>
#include <stdio.h>
#include <string.h>

#define LOGGING

http_header_t headers[] = {
    //  { "Content-Type", "application/json" },
    //  { "Accept" , "application/json" },
    { "Accept" , "*/*"},
    { "User-agent", "particle"},
    { NULL, NULL } // NOTE: Always terminate headers will NULL
};

HueBridge::HueBridge(const String& ip, const String& user)
{
    request.hostname = ip;
    request.port = 80;
    request_prefix = String("/api");
    request_prefix.concat(user);
    //request_prefix = String("/api/ol9m2fds1fAsmDDD0mdp33myAt3ZIi6txh6-NJGU");
}

int HueBridge::set_group(const String &group)
{
    const size_t bufferSize = JSON_ARRAY_SIZE(0) + JSON_ARRAY_SIZE(2) +
                              JSON_ARRAY_SIZE(4) + JSON_OBJECT_SIZE(2) +
                              JSON_OBJECT_SIZE(8) + JSON_OBJECT_SIZE(9) + 250;
    StaticJsonBuffer<bufferSize> jsonBuffer;
    char groupStr[12];

    for (int roomNum = 1; roomNum <= 20; roomNum++) {
        request.path = request_prefix;
        sprintf(groupStr, "/groups/%d", roomNum);
        request.path.concat(groupStr);
        http.get(request, response, headers);

#ifdef LOGGING
        Serial.print("Application>\tResponse status: ");
        Serial.println(response.status);

        Serial.print("Application>\tHTTP Response Body: ");
        Serial.println(response.body);
#endif

        JsonObject& root = jsonBuffer.parseObject(response.body.c_str());
        for (JsonPair& p : root) {
            Serial.println(p.key); // is a const char* pointing to the key
            //p.value // is a JsonVariant
        }

        // Look for a group of the "Room" type
        Serial.println(root["type"].as<char*>());
        if (strcmp(root["type"], "Room") == 0) {
            Serial.println("--- ROOM TYPE");
            if (strcmp(root["name"], group) == 0) {
                Serial.println("MATCH!");
                return roomNum;
            }
        }

        jsonBuffer.clear();
    }

    return -1;
}
