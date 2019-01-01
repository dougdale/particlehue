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

int HueBridge::find_group(const char *group, const char *type)
{
    const size_t bufferSize = 1024;
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

        Serial.println(root["type"].as<char*>());
        if ((strcmp(root["name"], group) == 0) &&
            (strcmp(root["type"], type) == 0)) {
            Serial.println("MATCH!");
            return roomNum;
        }

        jsonBuffer.clear();
    }

    return -1;
}

int HueBridge::groupOn(int groupNumber)
{
    return groupCommand(groupNumber, "{\"on\":true}");
}

int HueBridge::groupOff(int groupNumber)
{
    return groupCommand(groupNumber, "{\"on\":false}");
}

int HueBridge::groupCommand(int groupNumber, const char *command)
{
    if (groupNumber < 1) return -1;

    char groupStr[20];
    request.body = command;
    request.path = request_prefix;
    sprintf(groupStr, "/groups/%d/action", groupNumber);
    request.path.concat(groupStr);

    http.put(request, response, headers);

#ifdef LOGGING
    Serial.print("Application>\tResponse status: ");
    Serial.println(response.status);

    Serial.print("Application>\tHTTP Response Body: ");
    Serial.println(response.body);
#endif

    return 0;
}
