#ifndef __HUE_BRIDGE_H
#define __HUE_BRIDGE_H

#include <HttpClient.h>

class HueBridge {
public:
    HueBridge(const String& ip, const String& user);

    int find_group(const char *group, const char *type);
    int groupOn(int groupNumber);
    int groupOff(int groupNumber);

private:
    HttpClient http;
    http_request_t request;
    http_response_t response;
    String request_prefix;

    int groupCommand(int groupNumber, const char *command);
};

#endif // __HUE_BRIDGE_H
