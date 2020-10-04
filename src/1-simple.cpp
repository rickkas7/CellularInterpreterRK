#include "CellularInterpreterRK.h"

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);

SerialLogHandler logHandler(LOG_LEVEL_TRACE);
CellularInterpreter cellularInterpreter;
CellularInterpreterBlinkManager blinkManager;

void setup() {
    waitFor(Serial.isConnected, 10000);

    cellularInterpreter.setup();
    blinkManager.setup();

    CellularInterpreterCheckNcpFailure::check();

    // Register a URC handler
    cellularInterpreter.addUrcHandler("CREG", [](unsigned long reason, const char *command) {
        Log.info("URC handler for +CREG URC called!");
        CellularInterpreterParser parser;
        parser.parse(command);

        Log.info("command=%s numParts=%u", parser.getCommand().c_str(), parser.getNumArgs());

        for(size_t ii = 0; ii < parser.getNumArgs(); ii++) {
            Log.info("ii=%u s=%s", ii, parser.getArgString(ii).c_str());
        }
    });

    // Monitor DTLS messages
    cellularInterpreter.addLogMonitor("comm.dtls", NULL, NULL, [](long ts, const char *category, const char *level, const char *msg) {
        Log.info("got a comm.dtls message! ts=%lu category=%s level=%s msg=%s", ts, category, level, msg);
    });

    Particle.connect();
}

void loop() {
    cellularInterpreter.loop();
    blinkManager.loop();
}
