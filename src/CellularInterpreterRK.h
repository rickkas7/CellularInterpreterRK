#ifndef __CELLULARINTERPRETER_H
#define __CELLULARINTERPRETER_H

#include "Particle.h"

#include <deque>
#include <vector>

class CellularInterpreterLineBuffer {
public:
    static const size_t LINE_BUFFER_SIZE = 128;
    char        lineBuffer[LINE_BUFFER_SIZE];
};

typedef std::function<void(uint32_t, const char *)> CellularInterpreterCallback;


/**
 * @brief Class to monitor the debug logs
 */
class CellularInterpreterCommandMonitor {
public:
    CellularInterpreterCommandMonitor();
    virtual ~CellularInterpreterCommandMonitor();

    static const uint32_t REASON_OK             = 0x00000001;
    static const uint32_t REASON_PLUS           = 0x00000002; // Also URC
    static const uint32_t REASON_ERROR          = 0x00000004;
    static const uint32_t REASON_SEND           = 0x00000008;
    static const uint32_t REASON_TIMEOUT        = 0x00000010;

    String command;
    uint32_t reasonFlags = 0;
    CellularInterpreterCallback handler;
    uint32_t timeout = 10000;
    uint64_t nextTimeout = 0;
};

class CellularInterpreterCommand {
public:
    String command;
    unsigned long startTime;
    bool gotPlus;
    bool complete;
};


class CellularInterpreter : public StreamLogHandler, public Print  {
public:
    CellularInterpreter();
    virtual ~CellularInterpreter();

    void setup();

    void loop();

    void addCommandMonitor(CellularInterpreterCommandMonitor *mon);

    /**
     * @brief Add a URC handler
     * 
     * @param urc The URC. Just the text part ("CIEV") without the + or :.
     */
    void addUrcHandler(const char *urc, CellularInterpreterCallback callback);

    /**
     * @brief Handle a line in lineBuffer
     * 
     * As lineBuffer is relatively small, the results may be truncated. This call
     * is made only after the whole line is received.
     */
    void processLine(char *lineBuffer);

    void processCommand(char *command, bool toModem);
   	

    void callCommandMonitors(uint32_t reasonFlags, const char *command);

    void processTimeouts();


    /**
	 * @brief Virtual override for the StreamLogHandler to write data to the log
     * 
     * Declared in class Print, overridden here.
	 */
    virtual size_t write(uint8_t);

    static const size_t MAX_LINES = 16;

protected:
    CellularInterpreterLineBuffer *currentWrite = 0;
    size_t      writeOffset = 0;

    std::deque<CellularInterpreterLineBuffer*> toProcessLines;
    std::deque<CellularInterpreterLineBuffer*> freeLines;
    bool        inLoop = false;
    bool        ignoreNextSend = false;

    std::vector<CellularInterpreterCommandMonitor *> commandMonitors;
};

#endif /* __CELLULARINTERPRETER_H */
