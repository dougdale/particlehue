// This #include statement was automatically added by the Particle IDE.
#include "huebridge.h"

// Define HUEUSER in this file (a Hue user ID string) and HUEIP (IP addr string)
#include "particlehue_config.h"

#define LOGGING
typedef struct {
    char bridge_ip[16];
    char bridge_user[50];
    char room[40];
    struct {
        uint8_t hour;
        uint8_t minute;
        char scene[40];
    } daySegments[4];
} particlehue_config_t;

// FIXME: Read/Write this to EEPROM
particlehue_config_t particlehue_config = {
    { .bridge_ip = HUEIP },
    { .bridge_user = HUEUSER },
    { .room = "Living Room" },
    .daySegments = {
        {
            .hour = 5,
            .minute = 30,
            { .scene = "Bright" },
        },
        {
            .hour = 17,
            .minute = 0,
            { .scene = "none" },
        },
        {
            .hour = 22,
            .minute = 30,
            { .scene = "Night Light" }
        },
        {
            .hour = 0xff,
            .minute = 0xff,
            { .scene = "none" }
        }
    }
};

HueBridge bridge;

int groupNumber;

int motionWeb(String command);

void setup() {
    Serial.begin(9600);

    // FIXME: Don't hardcode. Perhaps calculate using 'config' info from
    // Hue bridge and subtracting UTC from localtime.
    Time.zone(-7);
    Time.endDST();

    // Set up a cloud function to simulate motion
    Particle.function("motion", motionWeb);

    bridge.config(particlehue_config.bridge_ip, particlehue_config.bridge_user);

    groupNumber = bridge.findGroup("Living Room", "Room");
}

void loop() {

}

int motionStart(void)
{
#ifdef LOGGING
    Serial.print("motionStart at ");
    Serial.println(Time.timeStr());
#endif

    return bridge.groupOn(groupNumber);
}

int motionStop(void)
{
#ifdef LOGGING
    Serial.print("motionStop at  ");
    Serial.println(Time.timeStr());
#endif

    return bridge.groupOff(groupNumber);
}

int motionWeb(String command) {
    if (command == "start") {
        motionStart();
        return 1;
    }
    else if (command == "stop") {
        motionStop();
        return 0;
    }
    else {
        return -1;
    }
}
