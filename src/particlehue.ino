// This #include statement was automatically added by the Particle IDE.
#include "huebridge.h"

#define LOGGING

HueBridge bridge("192.168.1.15", "ol9m2fds1fAsmDDD0mdp33myAt3ZIi6txh6-NJGU");
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

    groupNumber = bridge.find_group("Living Room", "Room");
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
