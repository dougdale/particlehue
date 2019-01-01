// This #include statement was automatically added by the Particle IDE.
#include "huebridge.h"

HueBridge bridge("192.168.1.15", "ol9m2fds1fAsmDDD0mdp33myAt3ZIi6txh6-NJGU");
int groupNumber;

int lightsOnOff(String command);

void setup() {
    Serial.begin(9600);

    // Set up a cloud function to turn lights on and off
    Particle.function("lights", lightsOnOff);

    groupNumber = bridge.find_group("Living Room", "Room");
}

void loop() {

}

int lightsOnOff(String command) {
    if (command == "on") {
        bridge.groupOn(groupNumber);
        return 1;
    }
    else if (command == "off") {
        bridge.groupOff(groupNumber);
        return 0;
    }
    else {
        return -1;
    }
}
