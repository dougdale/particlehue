#include "huebridge.h"

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
    Serial.print("PREFIX: ");
    Serial.println(request_prefix);

    request.path = request_prefix;
    request.path.concat("/groups/1");
    Serial.print("REQUEST: ");
    Serial.println(request.path);
    http.get(request, response, headers);

#ifdef LOGGING
    Serial.print("Application>\tResponse status: ");
    Serial.println(response.status);

    Serial.print("Application>\tHTTP Response Body: ");
    Serial.println(response.body);
#endif
}
