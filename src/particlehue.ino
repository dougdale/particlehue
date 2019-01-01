// This #include statement was automatically added by the Particle IDE.
#include "huebridge.h"

unsigned int nextTime = 0;
HueBridge bridge("192.168.1.15", "ol9m2fds1fAsmDDD0mdp33myAt3ZIi6txh6-NJGU");

void setup() {
    Serial.begin(9600);
}

void loop() {
    if (nextTime > millis()) {
        return;
    }

    Serial.println();
    Serial.println("Application>\tStart of Loop.");

    bridge.set_group("Living Room");    

    nextTime = millis() + 10000;
}
