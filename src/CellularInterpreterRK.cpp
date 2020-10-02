#include "CellularInterpreterRK.h"



CellularInterpreter::CellularInterpreter() : StreamLogHandler(*this, LOG_LEVEL_TRACE) {

}

CellularInterpreter::~CellularInterpreter() {
    // TODO: Deallocate buffers
}

void CellularInterpreter::setup() {
    // Allocate buffers
    for(size_t ii = 0; ii < MAX_LINES; ii++) {
        CellularInterpreterLineBuffer *b = new CellularInterpreterLineBuffer();
        if (b) {
            freeLines.push_back(b);
        }
    }

	// Add this handler into the system log manager
	LogManager::instance()->addHandler(this);

}

void CellularInterpreter::loop() {
    inLoop = true;
	
    while(!toProcessLines.empty()) {
        CellularInterpreterLineBuffer *currentRead = toProcessLines.front();
        toProcessLines.pop_front();

        processLine(currentRead->lineBuffer);

        freeLines.push_back(currentRead);
    }

    processTimeouts();

    inLoop = false;
}

void CellularInterpreter::addCommandMonitor(CellularInterpreterCommandMonitor *mon) {
    commandMonitors.push_back(mon);
}

void CellularInterpreter::addUrcHandler(const char *urc, CellularInterpreterCallback handler) {
    CellularInterpreterCommandMonitor *mon = new CellularInterpreterCommandMonitor();
    mon->command = urc;
    mon->reasonFlags = CellularInterpreterCommandMonitor::REASON_PLUS;
    mon->timeout = 0;
    mon->handler = handler;

    addCommandMonitor(mon);    
}


size_t CellularInterpreter::write(uint8_t c) {
    // Do not add any Log.* statements in this function!
    if (inLoop) {
        return 1;
    }
    if (currentWrite == 0) {
        // See if a line buffer is available now
        if (!freeLines.empty()) {
            currentWrite = freeLines.front();
            freeLines.pop_front();
        }
        else {
            return 1;
        }
    }

    if ((char)c == '\r') {
        // End of line, process this line
        
        // offset will be at most LINE_BUFFER_SIZE - 1
        // so this is safe to null terminate the (possibly partial) line
        if (writeOffset > 0) {
            currentWrite->lineBuffer[writeOffset] = 0;
            toProcessLines.push_back(currentWrite);

            if (!freeLines.empty()) {
                currentWrite = freeLines.front();
                freeLines.pop_front();
            }
            else {
                currentWrite = 0;
            }
        }
        writeOffset = 0;
    }
    else
    if ((char) c == '\n') {
        // Ignore LFs 
    }
    else
    if (writeOffset < (CellularInterpreterLineBuffer::LINE_BUFFER_SIZE - 1)) {
        // Append other characters to the line if there's room
        currentWrite->lineBuffer[writeOffset++] = (char) c;
    }
    else {
        // Line is too long, ignore the rest 
    }
    return 1;
}

void CellularInterpreter::processLine(char *lineBuffer) {
    // Process the (possibly partial) line in lineBuffer. It's a c-string, always null
    // terminated even if the line is truncated.
    // You only get the beginning of the line, the truncated part is discarded and
    // never copied into lineBuffer.

    // Example: Gen 2
    //     50.750 AT send       4 "AT\r\n"
    //     50.753 AT read OK    6 "\r\nOK\r\n"
    //     50.753 AT send      13 "AT+COPS=3,2\r\n"
    //     50.757 AT read OK    6 "\r\nOK\r\n"
    //     50.757 AT send      10 "AT+COPS?\r\n"
    //     50.763 AT read  +   25 "\r\n+COPS: 0,2,\"310410\",2\r\n"
    //     50.764 AT read OK    6 "\r\nOK\r\n"
    //     50.764 AT send       8 "AT+CSQ\r\n"
    //     50.768 AT read  +   14 "\r\n+CSQ: 16,2\r\n"
    //     50.769 AT read OK    6 "\r\nOK\r\n"
    // col=0 token=50.750
    // col=1 token=AT
    // col=2 token=send
    // col=3 token=4
    // col=4 token="AT
    // 
    // Example with binary data
    //     11.037 AT read  +   78 "\r\n+USORF: 0,\"54.86.198.203\",5684,38,\"\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x9f\x00\x19\x00\x01\x00\x00\x00\x00\x00\x9f\xd0'R@\xf594Rf\xe0g\x89\x85'S\x99\xca\"\r\n"
    // 


    // Example: Gen 3
    // 0000068021 [ncp.at] TRACE: > AT+COPS=3,2
    // 0000068029 [ncp.at] TRACE: < OK
    // 0000068029 [ncp.at] TRACE: > AT+COPS?
    // 0000068039 [ncp.at] TRACE: < +COPS: 0,2,"310410",8
    // 0000068040 [ncp.at] TRACE: < OK
    // 0000068040 [ncp.at] TRACE: > AT+UCGED=5
    // 0000068049 [ncp.at] TRACE: < OK
    // 0000068049 [ncp.at] TRACE: > AT+UCGED?
    // 0000068062 [ncp.at] TRACE: < +RSRP: 476,5110,"-096.50",
    // 0000068062 [ncp.at] TRACE: < +RSRQ: 476,5110,"-20.00",
    // 0000068063 [ncp.at] TRACE: < OK
    // col=0 token=0000068021
    // col=1 token=[ncp.at]
    // col=2 token=TRACE:
    // col=3 token=>
    // col=4 token=AT+COPS=3,2

    // Log.info("processLine %s", lineBuffer);

    bool isGen3 = false;
    bool toModem = false;
    char *command = NULL;
    char *saveptr; 
    char *token = strtok_r(lineBuffer, " ", &saveptr);
    for(int col = 0; token; col++) {
        if (col == 1) {
            if (strcmp(token, "AT") == 0) {
                isGen3 = false;
            }
            else
            if (strcmp(token, "[ncp.at]") == 0) {
                isGen3 = false;
            }
            else {
                // Not a statement we care about, ignore the rest of this line.
                break;
            }
        }

        if (isGen3) {
            // Gen3
            if (col == 3) {
                toModem = token[0] == '>';
                command = &token[2];
            }
        }
        else {
            // Gen2
            if (col == 2) {
                toModem = strcmp(token, "send") == 0;

                char *src = strchr(&token[strlen(token) + 1], '"');
                if (src) {
                    // Command begins after the first double quote
                    command = ++src;

                    // Unescape backslash escapes, remove \r and \n, and end at the unescaped double quote
                    for(char *dst = src; *src; src++) {
                        if (*src == '\\') {
                            if (*++src == '"') {
                                // Literal quote
                                *dst++ = *src;
                            }
                            else {
                                // Probably \r or \n, just ignore
                            }
                        }
                        else
                        if (*src == '"') {
                            // End of string
                            *dst = 0;
                            break;
                        }
                        else {
                            // Copy character
                            *dst++ = *src;
                        }
                    }
                }
            }

            if (command) {
                // We have a parsed command, Gen 2 or Gen 3
                // Direction is in toModem (true = to modem, false = from modem)
                // + response and OK/ERROR are issued in separate lines, so there needs to be additional 
                // surrounding state
                processCommand(command, toModem);
                break;
            }
        }        
        token = strtok_r(NULL, " ", &saveptr);
    }

}

void CellularInterpreter::processCommand(char *command, bool toModem) {
    // Note start of new command, + responses, OK/ERROR responses, and URCs here
    if (toModem) {
        // Sending to modem
        if (ignoreNextSend) {
            // On Gen2, sending binary data with AT+USOST or AT+USOWR, see "@" below
            ignoreNextSend = false;
            return;
        }
        Log.info("send command %s", command);        
        callCommandMonitors(CellularInterpreterCommandMonitor::REASON_SEND, command); 
    }
    else {
        // Receiving data from modem
        if (command[0] == '+') {
            // + response to a command, or a URC
            Log.info("recv + %s", command);        

            callCommandMonitors(CellularInterpreterCommandMonitor::REASON_PLUS, command); 
        }
        else 
        if (strcmp(command, "@") == 0) {
            // On Gen2, sending binary data with AT+USOST or AT+USOWR

            // Example with write binary data after @ response (AT+USOST, AT+USOWR)
            //      5.565 AT send      36 "AT+USOST=0,\"54.86.198.203\",5684,50\r\n"
            //      5.573 AT read  >    3 "\r\n@"
            //      5.573 AT send      50 "\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x99\x00%\x00\x01\x00\x00\x00\x00\x00\x99.\xcc\x9dz\xec\xd54\xeb\x87\xbd{\xb2\xc0$}\x19\xf4\x11\xfc\x85\t\xb4\xe8\xae\xe5\xa6\x0e|\x15"
            //      5.709 AT read  +   16 "\r\n+USOST: 0,50\r\n"
            ignoreNextSend = true;
        }
        else 
        if (strcmp(command, "OK") == 0) {
            Log.info("recv %s", command);        
            callCommandMonitors(CellularInterpreterCommandMonitor::REASON_OK, command); 
        }
        else 
        if (strncmp(command, "ERROR", 5) == 0) {
            Log.info("recv %s", command);       
            callCommandMonitors(CellularInterpreterCommandMonitor::REASON_ERROR, command); 
        }
        else {
            // There are a bunch of other responses here like:
            // CONNECT, RING, NO CARRIER, NO DIALTONE, BUSY, NO ANSWER, CONNECT, ABORTED
            // however we don't need to handle those, so just ignore them
        }
        
    }
}

void CellularInterpreter::callCommandMonitors(uint32_t reasonFlags, const char *command) {
    // Check command monitors
    for (std::vector<CellularInterpreterCommandMonitor *>::iterator it = commandMonitors.begin() ; it != commandMonitors.end(); ++it) {
        CellularInterpreterCommandMonitor *mon = *it;
        if (strncmp(&command[1], mon->command.c_str(), mon->command.length()) == 0) {
            if (command[mon->command.length() + 1] == ':') {
                // Matching command or URC
                if ((reasonFlags & mon->reasonFlags) != 0) {
                    // Handler is interested in this reason
                    if (mon->handler) {
                        mon->handler(reasonFlags, command);
                    }
                }

                if ((reasonFlags & CellularInterpreterCommandMonitor::REASON_SEND) != 0) {
                    // Sending a command, start timeout
                    if (mon->timeout) {
                        mon->nextTimeout = System.millis() + mon->timeout;
                    }
                    else {
                        mon->nextTimeout = 0;
                    }
                }
                else
                if ((reasonFlags & (CellularInterpreterCommandMonitor::REASON_OK | CellularInterpreterCommandMonitor::REASON_ERROR)) != 0) {
                    // On OK or ERROR, clear timeout
                    mon->nextTimeout = 0;
                }                    
            }
        }
    }
}


void CellularInterpreter::processTimeouts() {
    for (std::vector<CellularInterpreterCommandMonitor *>::iterator it = commandMonitors.begin() ; it != commandMonitors.end(); ++it) {
        CellularInterpreterCommandMonitor *mon = *it;

        if (mon->nextTimeout != 0 && mon->nextTimeout < System.millis()) {
            // Timeout occurred
            Log.info("timeout %s", mon->command.c_str());
            callCommandMonitors(CellularInterpreterCommandMonitor::REASON_TIMEOUT, mon->command); 

            mon->nextTimeout = 0;
        }
    }

}




CellularInterpreterCommandMonitor::CellularInterpreterCommandMonitor() {
}

CellularInterpreterCommandMonitor::~CellularInterpreterCommandMonitor() {
}


