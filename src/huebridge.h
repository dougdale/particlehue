#ifndef __HUE_BRIDGE_H
#define __HUE_BRIDGE_H

#include <HttpClient.h>

class HueBridge {
public:
    HueBridge(const String& ip, const String& user);

    int set_group(const String& group);
private:
    HttpClient http;
    http_request_t request;
    http_response_t response;
    String request_prefix;
};

#endif // __HUE_BRIDGE_H
