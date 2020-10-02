#include "CellularInterpreterRK.h"

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);

SerialLogHandler logHandler(LOG_LEVEL_INFO);
CellularInterpreter cellularInterpreter;

void setup() {
    waitFor(Serial.isConnected, 10000);

    cellularInterpreter.setup();

    // Register a URC handler
    cellularInterpreter.addUrcHandler("UUSORD", [](unsigned long reason, const char *command) {
        Log.info("URC handler for +UUSORD URC called!");
    });
    cellularInterpreter.addUrcHandler("CIEV", [](unsigned long reason, const char *command) {
        Log.info("URC handler for +CIEV URC called!");
    });

    Particle.connect();
}

void loop() {
    cellularInterpreter.loop();
}

/*

Serial connection closed.  Attempting to reconnect...
Serial monitor opened successfully:
     5.553 AT read  +   14 "\r\n+CIEV: 5,1\r\n"
0000005564 [app] INFO: recv + +CIEV: 5,1


Serial connection closed.  Attempting to reconnect...
Serial monitor opened successfully:
     1.781 AT send       4 "AT\r\n"
0000001781 [app] INFO: send command AT
     2.550 AT read OK    6 "\r\nOK\r\n"
     2.550 AT send       9 "AT+CGMM\r\n"
0000002550 [app] INFO: recv OK
0000002551 [app] INFO: send command AT+CGMM
     2.555 AT read UNK  13 "\r\nSARA-U260\r\n"
     2.556 AT read OK    6 "\r\nOK\r\n"
0000002556 [app] INFO: recv OK
     2.757 AT send       6 "ATE0\r\n"
     2.761 AT read OK    6 "\r\nOK\r\n"
     2.761 AT send      11 "AT+CMEE=2\r\n"
0000002761 [app] INFO: recv OK
0000002762 [app] INFO: send command AT+CMEE=2
     2.766 AT read OK    6 "\r\nOK\r\n"
     2.766 AT send      19 "AT+CMER=1,0,0,2,1\r\n"
     2.773 AT read OK    6 "\r\nOK\r\n"
     2.773 AT send      15 "AT+IPR=115200\r\n"
     2.778 AT read OK    6 "\r\nOK\r\n"
     2.878 AT send      10 "AT+CPIN?\r\n"
0000002878 [app] INFO: send command AT+CPIN?
     2.884 AT read  +   16 "\r\n+CPIN: READY\r\n"
0000002884 [app] INFO: recv + +CPIN: READY
     2.885 AT read OK    6 "\r\nOK\r\n"

[ Modem::init ] = = = = = = = = = = = = = = =
     2.886 AT send       9 "AT+CGSN\r\n"
0000002887 [app] INFO: recv OK
     2.907 AT read UNK  19 "\r\n353162070907929\r\n"
     2.908 AT read OK    6 "\r\nOK\r\n"
     2.908 AT send       9 "AT+CGMI\r\n"
     2.912 AT read UNK  10 "\r\nu-blox\r\n"
     2.913 AT read OK    6 "\r\nOK\r\n"
     2.913 AT send       9 "AT+CGMR\r\n"
     2.917 AT read UNK   9 "\r\n23.20\r\n"
0000002917 [app] INFO: send command AT+     2.917 AT read UNK   9 
     2.918 AT read OK    6 "\r\nOK\r\n"
     2.918 AT send       6 "ATI9\r\n"
     2.933 AT read UNK  16 "\r\n23.20,A01.00\r\n"
     2.934 AT read OK    6 "\r\nOK\r\n"
     2.934 AT send       9 "AT+CCID\r\n"
0000002934 [app] INFO: recv OK
0000002935 [app] INFO: send command AT+CCID
     2.940 AT read  +   30 "\r\n+CCID: 8934076500002814028\r\n"
0000002942 [app] INFO: recv + +CCID: 8934076500002814028
     2.943 AT read OK    6 "\r\nOK\r\n"
     2.943 AT send      11 "AT+CMGF=1\r\n"
     2.947 AT read OK    6 "\r\nOK\r\n"
     2.947 AT send      13 "AT+CNMI=2,1\r\n"
     2.952 AT read OK    6 "\r\nOK\r\n"
     2.952 AT send       9 "AT+CIMI\r\n"
     2.958 AT read UNK  19 "\r\n214074300571798\r\n"
     2.959 AT read OK    6 "\r\nOK\r\n"
     2.959 AT send      13 "AT+COPS=3,2\r\n"
0000002959 [app] INFO: recv OK
0000002960 [app] INFO: send command AT+COPS=3,2
     2.964 AT read OK    6 "\r\nOK\r\n"
     2.964 AT send      11 "AT+UPSV=1\r\n"
0000002964 [app] INFO: recv OK
0000002965 [app] INFO: send command AT+UPSV=1
     2.969 AT read OK    6 "\r\nOK\r\n"
0000002969 [system] INFO: Sim Ready
0000002971 [system] INFO: ARM_WLAN_WD 1

[ Modem::register ] = = = = = = = = = = = = = =
     2.971 AT send      12 "AT+CGREG=2\r\n"
0000002973 [app] INFO: send command AT+CGREG=2
     2.977 AT read OK    6 "\r\nOK\r\n"
     2.977 AT send      11 "AT+CREG=2\r\n"
     2.982 AT read OK    6 "\r\nOK\r\n"
     2.982 AT send      10 "AT+CREG?\r\n"
     2.989 AT read  +   33 "\r\n+CREG: 2,5,\"2CF7\",\"8A5A782\",6\r\n"
     2.992 AT read OK    6 "\r\nOK\r\n"
     2.992 AT send      11 "AT+CGREG?\r\n"
0000002992 [app] INFO: recv + +CREG: 2,5,"2CF7","8A5A782",6     2.992 AT read OK    6 
0000002993 [app] INFO: send command AT+CGREG?
     3.000 AT read  +   39 "\r\n+CGREG: 2,5,\"2CF7\",\"8A5A782\",6,\"65\"\r\n"
0000003002 [app] INFO: recv + +CGREG: 2,5,"2CF7","8A5A782",6,"65"
     3.003 AT read OK    6 "\r\nOK\r\n"
     3.003 AT send       4 "AT\r\n"
     3.007 AT read OK    6 "\r\nOK\r\n"
     3.007 AT send      13 "AT+COPS=3,2\r\n"
     3.012 AT read OK    6 "\r\nOK\r\n"
     3.012 AT send      10 "AT+COPS?\r\n"
     3.018 AT read  +   25 "\r\n+COPS: 0,2,\"310410\",2\r\n"
0000003019 [app] INFO: recv + +COPS: 0,2,"310410",2
     3.021 AT read OK    6 "\r\nOK\r\n"
     3.021 AT send       8 "AT+CSQ\r\n"
0000003021 [app] INFO: recv OK
0000003022 [app] INFO: send command AT+CSQ
     3.026 AT read  +   14 "\r\n+CSQ: 15,3\r\n"
     3.027 AT read OK    6 "\r\nOK\r\n"

[ Modem::join ] = = = = = = = = = = = = = = = =
     3.027 AT send       4 "AT\r\n"
0000003028 [app] INFO: recv OK
     3.031 AT read OK    6 "\r\nOK\r\n"
     3.031 AT send      12 "AT+CGATT=1\r\n"
     3.036 AT read OK    6 "\r\nOK\r\n"
     3.036 AT send      14 "AT+UPSND=0,8\r\n"
     3.043 AT read  +   17 "\r\n+UPSND: 0,8,0\r\n"
0000003043 [app] INFO: send command AT     3.043 AT read  +   17 
     3.044 AT read OK    6 "\r\nOK\r\n"
     3.045 AT send      23 "AT+UPSD=0,7,\"0.0.0.0\"\r\n"
0000003046 [app] INFO: recv OK
     3.052 AT read OK    6 "\r\nOK\r\n"
     3.052 AT send      36 "AT+UPSD=0,1,\"spark.telefonica.com\"\r\n"
0000003054 [app] INFO: send command AT+UPSD=0,7,"0.0.0.0k.telefonica.com"
     3.061 AT read OK    6 "\r\nOK\r\n"
     3.061 AT send      15 "AT+UPSD=0,6,0\r\n"
0000003062 [app] INFO: recv OK
0000003062 [app] INFO: send command AT+UPSD=0,6,0
     3.067 AT read OK    6 "\r\nOK\r\n"
     3.067 AT send      14 "AT+UPSDA=0,3\r\n"
0000003067 [app] INFO: recv OK
0000003068 [app] INFO: send command AT+UPSDA=0,3
     5.527 AT read OK    6 "\r\nOK\r\n"
     5.527 AT send      14 "AT+UPSND=0,0\r\n"
0000005528 [app] INFO: recv OK
     5.534 AT read  +   31 "\r\n+UPSND: 0,0,\"10.45.180.180\"\r\n"
     5.537 AT read OK    6 "\r\nOK\r\n"
     5.537 AT send      14 "AT+UPSND=0,1\r0000005538 [app] INFO: send command AT+UPSND=0,0     5.534 AT read  +   31 
\n"
0000005539 [app] INFO: send command AT+UPSND=0,1
     5.547 AT read  +   30 "\r\n+UPSND: 0,1,\"80.58.61.250\"\r\n"
0000005548 [app] INFO: recv + +UPSND: 0,1,"80.58.61.250"
     5.550 AT read OK    6 "\r\nOK\r\n"
     5.550 AT send      14 "AT+UPSND=0,2\r\n"
0000005551 [app] INFO: recv OK
0000005551 [app] INFO: send command AT+UPSND=0,2
     5.557 AT read  +   30 "\r\n+UPSND: 0,2,\"80.58.61.254\"\r\n"
     5.560 AT read OK    6 "\r\nOK\r\n"
0000005560 [system] INFO: ARM_WLAN_WD 2
0000005560 [system] INFO: CLR_WLAN_WD 1, DHCP success
0000005561 [system] INFO: Cloud: connecting
0000005561 [app] INFO: recv OK
0000005563 [system] INFO: Read Server Address = type:1,domain:$id.udp.particle.io
0000005565 [system] ERROR: Failed to load session data from persistent storage
0000005565 [system] INFO: Discarding session data
0000005567 [system] TRACE: Resolving 430034001951343334363036.udp.particle.io
     5.567 AT send       4 "AT\r\n"
0000005569 [app] INFO: send command AT
     5.571 AT read OK    6 "\r\nOK\r\n"
     5.571 AT send      15 "AT+USOCTL=0,0\r\n"
     5.580 AT read ERR  37 "\r\n+CME ERROR: operation not allowed\r\n"
     5.582 AT send      15 "AT+USOCTL=1,0\r\n"
0000005582 [app] INFO: recv + +CME ERROR: operation not allowed
0000005583 [app] INFO: send command AT+USOCTL=1,0
     5.589 AT read ERR  37 "\r\n+CME ERROR: operation not allowed\r\n"
     5.591 AT send      15 "AT+USOCTL=2,0\r\n"
0000005591 [app] INFO: recv + +CME ERROR: operation not allowed
0000005592 [app] INFO: send command AT+USOCTL=2,0
     5.598 AT read ERR  37 "\r\n+CME ERROR: operation not allowed\r\n"
     5.600 AT send      15 "AT+USOCTL=3,0\r\n"
     5.607 AT read ERR  37 "\r\n+CME ERROR: operation not allowed\r\n"
     5.609 AT send      15 "AT+USOCTL=4,0\r\n"
0000005609 [app] INFO: recv + +CME ERROR: operation not allow     5.607 AT read ERR  37 
0000005610 [app] INFO: send command AT+USOCTL=4,0
     5.616 AT read ERR  37 "\r\n+CME ERROR: operation not allowed\r\n"
     5.618 AT send      15 "AT+USOCTL=5,0\r\n"
0000005618 [app] INFO: send command AT+USOCTL=5,0
     5.625 AT read ERR  37 "\r\n+CME ERROR: operation not allowed\r\n"
     5.627 AT send      15 "AT+USOCTL=6,0\r\n"
0000005627 [app] INFO: send command AT+USOCTL=6,0
     5.634 AT read ERR  37 "\r\n+CME ERROR: operation not allowed\r\n"
socketSocket(UDP)
     5.636 AT send      13 "AT+USOCR=17\r\n"
     5.641 AT read  +   13 "\r\n+USOCR: 0\r\n"
     5.642 AT read OK    6 "\r\nOK\r\n"
Socket 0: handle 0 was created
socketSendTo(0,8.8.8.8,53,,58)
     5.642 AT send      28 "AT+USOST=0,\"8.8.8.8\",53,58\r\n"
0000005644 [app] INFO: recv + +CME ERROR: operation not allo     5.642 AT send      28 
     5.650 AT read  >    3 "\r\n@"
     5.650 AT send      58 "\x00\x01\x01\x00\x00\x01\x00\x00\x00\x00\x00\x00\x18430034001951343334363036\x03udp\bparticle\x02io\x00\x00\x01\x00\x01"
     5.789 AT read  +   16 "\r\n+USOST: 0,58\r\n"
0000005789 [app] INFO: recv + +USOST: 0,58
     5.790 AT read OK    6 "\r\nOK\r\n"
     5.791 AT send       4 "AT\r\n"
0000005791 [app] INFO: recv OK
0000005791 [app] INFO: send command AT
     5.794 AT read OK    6 "\r\nOK\r\n"
     5.794 AT send      14 "AT+USORF=0,0\r0000005795 [app] INFO: recv OK
\n"
0000005796 [app] INFO: send command AT+USORF=0,0
     5.800 AT read  +   15 "\r\n+USORF: 0,0\r\n"
Socket 0: handle 0 has 0 bytes pending
     5.801 AT read OK    6 "\r\nOK\r\n"
0000005801 [app] INFO: recv + +USORF: 0,0
     6.212 AT read  +   18 "\r\n+UUSORD: 0,300\r\n"
Socket 0: handle 0 has 300 bytes pending
0000006213 [app] INFO: recv + +UUSORD: 0,300
     6.223 AT send      16 "AT+USORF=0,512\r\n"
0000006223 [app] INFO: send command AT+USORF=0,512
     6.259 AT read  +  333 "\r\n+USORF: 0,\"8.8.8.8\",53,300,\"\x00\x01\x81\x80\x00\x01\x00\v\x00\x00\x00\x00\x18430034001951343334363036\x03udp\bparticle\x02io\x00\x00\x01\x00\x01\xc0\f\x00\x05\x00\x01\x00\x00\x00;\x00F#eks-udp-device-service-green-static\tus-east-1\x15eks-production-gotham\xc0)\xc0F\x00\x01\x00\x01\x00\x00\x00\x12\x00\x04\x03\xe1q\xcd\xc0F\x00\x01\x00\x01\x00\x00\x00\x12\x00\x04\x03\xde\xfd<\xc0F\x00\x01\x00\x01\x00\x00\x00\x12\x00\x04\x03\xe4u\xf4\xc0F\x00\x01\x00\x01\x00\x00\x00\x12\x00\x046\xe24\x16\xc0F\x00\x01\x00\x01\x00\x00\x00\x12\x00\x046R\x8d\xb0\xc0F\x00\x01\x00\x01\x00\x00\x00\x12\x00\x04\x03\xd2\xc2\xba\xc0F\x00\x01\x00\x01\x00\x00\x00\x12\x00\x04\"\xc20Y\xc0F\x00\x01\x00\x01\x00\x00\x00\x12\x00\x04\x03\xe3\xa3\xb1\xc0F\x00\x01\x00\x01\x00\x00\x00\x12\x00\x04\x03UG\b\xc0F\x00\x01\x00\x01\x00\x00\x00\x12\x00\x046V\xc6\xcb\"\r\n"
0000006281 [app] INFO: recv + +USORF: 0,"8.8.8.8",53,300,3603udpparticle02io0000010001c000050000\x01\x00\x01\xc0\f\x00\x05\x00\x0
     6.282 AT read OK    4 "OK\r\n"
     6.283 AT send       4 "AT\r\n"
0000006283 [app] INFO: recv OK
0000006283 [app] INFO: send command AT
     6.286 AT read OK    6 "\r\nOK\r\n"
     6.286 AT send      14 "AT+USORF=0,0\r\n"
     6.292 AT read  +   15 "\r\n+USORF: 0,0\r\n"
Socket 0: handle 0 has 0 bytes pending
     6.293 AT read OK    6 "\r\nOK\r\n"
0000006293 [system] INFO: Resolved 430034001951343334363036.udp.particle.io to 3.225.113.205
     6.294 AT send       4 "AT\r\n"
0000006292 [app] INFO: recv + +USORF: 0,0
     6.297 AT read OK    6 "\r\nOK\r\n"
     6.297 AT send      15 "AT+USOCTL=0,0\r\n"
     6.304 AT read  +   19 "\r\n+USOCTL: 0,0,17\r\n"
0000006304 [app] INFO: recv + +USOCTL: 0,0,17
     6.305 AT read OK    6 "\r\nOK\r\n"
     6.306 AT send      15 "AT+USOCTL=1,0\r\n"
0000006307 [app] INFO: recv OK
0000006307 [app] INFO: send command AT+USOCTL=1,0
     6.314 AT read ERR  37 "\r\n+CME ERROR: operation not allowed\r\n"
     6.316 AT send      15 "AT+USOCTL=2,0\r\n"
0000006316 [app] INFO: recv + +CME ERROR: operation not allowed
0000006317 [app] INFO: send command AT+USOCTL=2,0
     6.323 AT read ERR  37 "\r\n+CME ERROR: operation not allowed\r\n"
     6.325 AT send      15 "AT+USOCTL=3,0\r\n"
     6.332 AT read ERR  37 "\r\n+CME ERROR: operation not allowed\r\n"
     6.334 AT send      15 "AT+USOCTL=4,0\r\n"
0000006334 [app] INFO: recv + +CME ERROR: operation not allow     6.332 AT read ERR  37 
0000006335 [app] INFO: send command AT+USOCTL=4,0
     6.341 AT read ERR  37 "\r\n+CME ERROR: operation not allowed\r\n"
     6.343 AT send      15 "AT+USOCTL=5,0\r\n"
0000006343 [app] INFO: send command AT+USOCTL=5,0
     6.350 AT read ERR  37 "\r\n+CME ERROR: operation not allowed\r\n"
     6.352 AT send      15 "AT+USOCTL=6,0\r\n"
     6.359 AT read ERR  37 "\r\n+CME ERROR: operation not allowed\r\n"
socketSocket(UDP)
     6.361 AT send      18 "AT+USOCR=17,5684\r\n"
0000006361 [app] INFO: recv + +CME ERROR: operation not allow     6.359 AT read ERR  37 
0000006362 [app] INFO: send command AT+USOCR=17,5684
     6.367 AT read  +   13 "\r\n+USOCR: 1\r\n"
     6.368 AT read OK    6 "\r\nOK\r\n"
Socket 1: handle 1 was created
0000006368 [system] TRACE: Connection attempt to 3.225.113.205:5684
0000006370 [system] INFO: Cloud socket connected
0000006370 [system] INFO: Starting handshake: presense_announce=0
0000006372 [comm.protocol.handshake] INFO: Establish secure connection
0000006390 [comm.dtls] INFO: (CMPL,RENEG,NO_SESS,ERR) restoreStatus=2
socketSendTo(1,3.225.113.205,5684,,111)
     6.394 AT send      37 "AT+USOST=1,\"3.225.113.205\",5684,111\r\n"
     6.404 AT read  >    3 "\r\n@"
     6.404 AT send     111 "\x16\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\x00\x00b\x01\x00\x00V\x00\x00\x00\x00\x00\x00\x00V\xfe\xfdl\xb2+\x8c0\xba\xe1\xfcf\x06\xd3\xd9\xa3\xa2r\x01a\x8bU\xa5\xc4K\xf7\xf9\x1d\xf8\x8d\x8c47F2\x00\x00\x00\x04\xc0\xae\x00\xff\x01\x00\x00(\x00\r\x00\n\x00\b\x04\x03\x04\x01\x03\x03\x03\x01\x00\n\x00\x04\x00\x02\x00\x17\x00\v\x00\x02\x01\x00\x00\x13\x00\x02\x01\x02\x00\x14\x00\x02\x01\x02"
     6.551 AT read  +   17 "\r\n+USOST: 1,111\r\n"
0000006551 [app] INFO: recv + +USOST: 1,111
     6.552 AT read OK    6 "\r\nOK\r\n"
     6.553 AT send       4 "AT\r\n"
0000006553 [app] INFO: recv OK
0000006553 [app] INFO: send command AT
     6.556 AT read OK    6 "\r\nOK\r\n"
     6.556 AT send      14 "AT+USORF=1,0\r\n"
0000006557 [app] INFO: recv OK
0000006557 [app] INFO: send command AT+USORF=1,0
     6.561 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
0000006562 [app] INFO: recv + +USORF: 1,0
     6.564 AT read OK    6 "\r\nOK\r\n"
0000006564 [app] INFO: recv OK
     6.816 AT read  +   17 "\r\n+UUSORD: 1,60\r\n"
Socket 1: handle 1 has 60 bytes pending
0000006817 [app] INFO: recv + +UUSORD: 1,60
     6.818 AT send      17 "AT+USORF=1,1024\r\n"
     6.832 AT read  +  100 "\r\n+USORF: 1,\"3.225.113.205\",5684,60,\"\x16\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\x00\x00/\x03\x00\x00#\x00\x00\x00\x00\x00\x00\x00#\xfe\xfd _w;\x870\x9d\xa6(z\x17g<\xe7\xcbB\x84)\xe1\xba\xbf\xbd>\xdd\xc2\x03,\x95\x8d\xba\x18\x9c\x8f\"\r\n"
     6.839 AT read OK    4 "OK\r\n"
     6.839 AT send       4 "AT\r\n"
0000006839 [app] INFO: recv + +USORF: 1,"3.225.113.205",5684,60,"16fefd000000000000000000/030000\x00\x00\x00\x00\x00\x00/\x03\x00
0000006840 [app] INFO: send command AT
     6.842 AT read OK    6 "\r\nOK\r\n"
     6.842 AT send      14 "AT+USORF=1,0\r\n"
0000006843 [app] INFO: recv OK
     6.848 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
     6.849 AT read OK    6 "\r\nOK\r\n"
socketSendTo(1,3.225.113.205,5684,,143)
     6.849 AT send      37 "AT+USOST=1,\"3.225.113.205\",5684,143\r\n"
0000006853 [app] INFO: send command AT+USORF=1,0     6.849 AT send      37 
     6.859 AT read  >    3 "\r\n@"
     6.859 AT send     143 "\x16\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\x01\x00\x82\x01\x00\x00v\x00\x01\x00\x00\x00\x00\x00v\xfe\xfdl\xb2+\x8c0\xba\xe1\xfcf\x06\xd3\xd9\xa3\xa2r\x01a\x8bU\xa5\xc4K\xf7\xf9\x1d\xf8\x8d\x8c47F2\x00 _w;\x870\x9d\xa6(z\x17g<\xe7\xcbB\x84)\xe1\xba\xbf\xbd>\xdd\xc2\x03,\x95\x8d\xba\x18\x9c\x8f\x00\x04\xc0\xae\x00\xff\x01\x00\x00(\x00\r\x00\n\x00\b\x04\x03\x04\x01\x03\x03\x03\x01\x00\n\x00\x04\x00\x02\x00\x17\x00\v\x00\x02\x01\x00\x00\x13\x00\x02\x01\x02\x00\x14\x00\x02\x01\x02"
     7.011 AT read  +   17 "\r\n+USOST: 1,143\r\n"
     7.012 AT read OK    6 "\r\nOK\r\n"
     7.012 AT send       4 "AT\r\n"
     7.015 AT read OK    6 "\r\nOK\r\n"
     7.015 AT send      14 "AT+USORF=1,0\r\n"
0000007016 [app] INFO: recv OK
     7.020 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
0000007021 [app] INFO: send command AT+USORF=1,0     7.020 AT read  +   15 
     7.023 AT read OK    6 "\r\nOK\r\n"
0000007023 [app] INFO: recv OK
     7.365 AT read  +   18 "\r\n+UUSORD: 1,319\r\n"
Socket 1: handle 1 has 319 bytes pending
0000007366 [app] INFO: recv + +UUSORD: 1,319
     7.375 AT send      17 "AT+USORF=1,1024\r\n"
     7.394 AT read  +  159 "\r\n+USORF: 1,\"3.225.113.205\",5684,118,\"\x16\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\x01\x00i\x02\x00\x00]\x00\x01\x00\x00\x00\x00\x00]\xfe\xfd_w;\x87\xd7\x97+i<\x8b'\xff\xc8/\xd6\xf6\x9a\x8ev\x19\xf9\x83\xec\xc8\xce0\x00\xbe\t\x14\xca\x15 ~\x900\xa8tM\x84fx>\x8fJ\xff\xb79\xe7\fB\xa7(rG\xb9\x01\xb5|\xe9\x97\x03~\xeb\xcc\xc0\xae\x00\x00\x15\xff\x01\x00\x01\x00\x00\v\x00\x02\x01\x00\x00\x13\x00\x01\x02\x00\x14\x00\x01\x02\"\r\n"
     7.405 AT read OK    4 "OK\r\n"
     7.405 AT read  +   18 "\r\n+UUSORF: 0000007406 [app] INFO: recv OK
1,226\r\n"
Socket 1: handle 1 has 226 bytes pending
0000007407 [app] INFO: recv + +UUSORF: 1,226
     7.416 AT send      17 "AT+USORF=1,1024\r\n"
0000007416 [app] INFO: send command AT+USORF=1,1024
     7.440 AT read  +  209 "\r\n+USORF: 1,\"3.225.113.205\",5684,168,\"\x16\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\x02\x00\x9b\f\x00\x00\x8f\x00\x02\x00\x00\x00\x00\x00\x8f\x03\x00\x17A\x045-\xd8\x85\x9f\x06Z\xe5\xf8\x98EKQ\xb0\xb9\xaa\x18\x80\xed\x8at\xed\xf8\xa0\x95\xd6\x8dz\xe8\xe6\x92\xde7\xa2\xe2sL\xe3]&\xb6\x1c\x87\xa0\f\xd3\nBE\x19G\xc1X\xbbP\xb27\xbc\xa6\xe9\xb8-?'\x04\x03\x00F0D\x02 \b\x10\x04\xaa\xd2\x05\xa66\xcf\xa0\x15\xb0Z\xdd<\x9b\xc2\xa2\xf6\f#\xe9\xfbkWjA\x90\xe5\xc4\x10\xf8\x02 .\xeb\x0f\x04\xdc\xdb\xe1\xd3\x99Xd+i@\xdf\x8c\x8f\x80\xb4+\x947\xde.\x03\x89\xa1J\xf2\"\x8c\x88\"\r\n"
     7.455 AT read OK    4 "OK\r\n"
0000007456 [app] INFO: recv OK
     9.091 AT read  +   17 "\r\n+UUSORF: 1,58\r\n"
Socket 1: handle 1 has 58 bytes pending
0000009093 [app] INFO: recv + +UUSORF: 1,58
     9.102 AT send      17 "AT+USORF=1,1024\r\n"
     9.113 AT read  +   73 "\r\n+USORF: 1,\"3.225.113.205\",5684,33,\"\x16\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\x03\x00\x14\r\x00\x00\b\x00\x03\x00\x00\x00\x00\x00\b\x01@\x00\x02\x04\x03\x00\x00\"\r\n"
     9.118 AT read OK    4 "OK\r\n"
     9.118 AT read  +   17 "\r\n+UUSORF: 1,25\r0000009119 [app] INFO: recv OK
\n"
Socket 1: handle 1 has 25 bytes pending
0000009120 [app] INFO: recv + +UUSORF: 1,25
     9.129 AT send      17 "AT+USORF=1,1024\r\n"
     9.139 AT read  +   65 "\r\n+USORF: 1,\"3.225.113.205\",5684,25,\"\x16\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\x04\x00\f\x0e\x00\x00\x00\x00\x04\x00\x00\x00\x00\x00\x00\"\r\n"
0000009143 [app] INFO: recv + +USORF: 1,"3.225.113.205",5684,25,"16fefd0000000000000004000e0\x00\x00\x00\x00\x00\x04\x00\f\x0e\x0
     9.144 AT read OK    4 "OK\r\n"
     9.145 AT send       4 "AT\r\n"
     9.148 AT read OK    6 "\r\nOK\r\n"
     9.148 AT send      14 "AT+USORF=1,0\r\n"
0000009148 [app] INFO: recv OK
0000009149 [app] INFO: send command AT+USORF=1,0
     9.153 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
     9.154 AT read OK    6 "\r\nOK\r\n"
0000009153 [app] INFO: recv + +USORF: 1,0
socketSendTo(1,3.225.113.205,5684,,377)
    11.578 AT send      37 "AT+USOST=1,\"3.225.113.205\",5684,377\r\n"
0000011582 [app] INFO: send command AT+USOST=1,"3.225.113.205",5684,377
    11.588 AT read  >    3 "\r\n@"
    11.588 AT send     377 "\x16\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\x02\x00j\v\x00\x00^\x00\x02\x00\x00\x00\x00\x00^\x00\x00[0Y0\x13\x06\a*\x86H\xce=\x02\x01\x06\b*\x86H\xce=\x03\x01\a\x03B\x00\x04\f4\xa1\x8c\xa9?\x8e\x1c\x8c(\x1a\x94\x1by\x8f\xf7I\xa02}\xab\x8a?\xc5\xd7\xe2\x83Bl\xaf\xc2w\xa5x\x04\xf3\xf1\xf0\x1d\xc6h\xad\xb7\xec\nL\xd2\xcc`J\t6L\xe4\xb9\x8b\xf6\xc0%<\xab\xaf\x15\x1d\x16\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\x03\x00N\x10\x00\x00B\x00\x03\x00\x00\x00\x00\x00BA\x04\x11\x85\xae%\x82\xc4z\xc5)\xba\x94\xd1\xda\xc2\r+\x8a>\xf8%\x99\aJ\xc9\x04\xd2\x10\xcb^a\xd27\x94\x90\xd8\x03\x04\xfb$\x12\xe0\x9b\x89$(\xa4\v\xde\xe4\x10\xb1\x87\xf8e-v\x04\x1e\x80\xe6\xab\xf3\xda\b\x16\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\x04\x00W\x0f\x00\x00K\x00\x04\x00\x00\x00\x00\x00K\x04\x03\x00G0E\x02!\x00\xa4\x83m\xfe{\x03\xeb\x9c\xab\xc8\x8c\xda\xaa\xfa^\xf64\xb3\xf0\x89\xbc7\xd5\xc3\xc1\x83\xeb\xcc\x13vh?\x02 \x19\xdf\xe4E\x94D\r\xd0\xbf\xd7\xb0L\xdf\x90%_\xc6\xbb\xfe\x99M\xe8\xf9\xfcnE\x84\xd2\n$5\x1a\x14\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\x05\x00\x01\x01\x16\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x00\x00(\x00\x01\x00\x00\x00\x00\x00\x00'\xcc\r4\xc0\xe5C\x9c\xdf\xff\xaf\xbb\x93H\x13\x18\xf8\xae\xed\x10\xbd\x18\xf7\xe4D\x8f0\x97%\xcc\xce1"
    11.778 AT read  +   17 "\r\n+USOST: 1,377\r\n"
0000011778 [app] INFO: recv + +USOST: 1,377
    11.779 AT read OK    6 "\r\nOK\r\n"
    11.780 AT send       4 "AT\r\n"
0000011780 [app] INFO: recv OK
0000011780 [app] INFO: send command AT
    11.783 AT read OK    6 "\r\nOK\r\n"
    11.783 AT send      14 "AT+USORF=1,0\r\n"
0000011784 [app] INFO: recv OK
    11.789 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
    11.790 AT read OK    6 "\r\nOK\r\n"
0000011790 [app] INFO: send command AT+USORF=1,0    11.789 AT read  +   15 
    12.566 AT read  +   18 "\r\n+UUSORD: 1,411\r\n"
Socket 1: handle 1 has 411 bytes pending
0000012567 [app] INFO: recv + +UUSORD: 1,411
    12.571 AT send      17 "AT+USORF=1,1024\r\n"
    12.591 AT read  +  159 "\r\n+USORF: 1,\"3.225.113.205\",5684,118,\"\x16\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\x05\x00i\x02\x00\x00]\x00\x01\x00\x00\x00\x00\x00]\xfe\xfd_w;\x87\xd7\x97+i<\x8b'\xff\xc8/\xd6\xf6\x9a\x8ev\x19\xf9\x83\xec\xc8\xce0\x00\xbe\t\x14\xca\x15 ~\x900\xa8tM\x84fx>\x8fJ\xff\xb79\xe7\fB\xa7(rG\xb9\x01\xb5|\xe9\x97\x03~\xeb\xcc\xc0\xae\x00\x00\x15\xff\x01\x00\x01\x00\x00\v\x00\x02\x01\x00\x00\x13\x00\x01\x02\x00\x14\x00\x01\x02\"\r\n"
0000012602 [app] INFO: recv + +USORF: 1,"3.225.113.205",5684,118,"16fefd000000000000000500i020x00\x00\x00\x00\x00\x05\x00i\x02\x0
    12.604 AT read OK    4 "OK\r\n"
    12.604 AT read  +   18 "\r\n+UUSORF: 1,293\r\n"
Socket 1: handle 1 has 293 bytes pending
    12.615 AT send      17 "AT+USORF=1,1024\r\n"
    12.639 AT read  +  209 "\r\n+USORF: 1,\"3.225.113.205\",5684,168,\"\x16\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\x06\x00\x9b\f\x00\x00\x8f\x00\x02\x00\x00\x00\x00\x00\x8f\x03\x00\x17A\x045-\xd8\x85\x9f\x06Z\xe5\xf8\x98EKQ\xb0\xb9\xaa\x18\x80\xed\x8at\xed\xf8\xa0\x95\xd6\x8dz\xe8\xe6\x92\xde7\xa2\xe2sL\xe3]&\xb6\x1c\x87\xa0\f\xd3\nBE\x19G\xc1X\xbbP\xb27\xbc\xa6\xe9\xb8-?'\x04\x03\x00F0D\x02 \b\x10\x04\xaa\xd2\x05\xa66\xcf\xa0\x15\xb0Z\xdd<\x9b\xc2\xa2\xf6\f#\xe9\xfbkWjA\x90\xe5\xc4\x10\xf8\x02 .\xeb\x0f\x04\xdc\xdb\xe1\xd3\x99Xd+i@\xdf\x8c\x8f\x80\xb4+\x947\xde.\x03\x89\xa1J\xf2\"\x8c\x88\"\r\n"
    12.656 AT read OK    4 "OK\r\n"
    12.656 AT read  +   18 "\r\n+UUSORF: 1,125\r\n"
Socket 1: handle 1 has 125 bytes pending
0000012658 [app] INFO: recv + +USORF: 1,"3.225.113.205",5684,168,"16fefd0000000000000006009b0\x00\x00\x00\x00\x00\x06\x00\x9b\f\x
    12.667 AT send      17 "AT+USORF=1,1024\r\n"
0000012667 [app] INFO: send command AT+USORF=1,1024
    12.678 AT read  +   73 "\r\n+USORF: 1,\"3.225.113.205\",5684,33,\"\x16\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\a\x00\x14\r\x00\x00\b\x00\x03\x00\x00\x00\x00\x00\b\x01@\x00\x02\x04\x03\x00\x00\"\r\n"
0000012683 [app] INFO: recv + +USORF: 1,"3.225.113.205",5684,33,"16fefd000000000000000014000\x00\x00\x00\x00\x00\a\x00\x14\r\x00\
    12.685 AT read OK    4 "OK\r\n"
    12.685 AT read  +   17 "\r\n+UUSORF: 1,92\r\n"
Socket 1: handle 1 has 92 bytes pending
0000012686 [app] INFO: recv OK
    12.696 AT send      17 "AT+USORF=1,1024\r\n"
    12.707 AT read  +   65 "\r\n+USORF: 1,\"3.225.113.205\",5684,25,\"\x16\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\b\x00\f\x0e\x00\x00\x00\x00\x04\x00\x00\x00\x00\x00\x00\"\r\n"
0000012711 [app] INFO: recv + +UUSORF: 1,92    12.707 AT read  +   65 
    12.712 AT read OK    4 "OK\r\n"
socketSendTo(1,3.225.113.205,5684,,377)
    12.713 AT send      37 "0000012714 [app] INFO: recv OK
AT+USOST=1,\"3.225.113.205\",5684,377\r\n"
    12.715 AT read  +   17 "\r\n+UUSORF: 1,67\r\n"
Socket 1: handle 1 has 67 bytes pending
0000012716 [app] INFO: send command AT+USOST=1,"3.225.113.205",5684,377
    12.721 AT read  >    3 "\r\n@"
    12.721 AT send     377 "\x16\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\x06\x00j\v\x00\x00^\x00\x02\x00\x00\x00\x00\x00^\x00\x00[0Y0\x13\x06\a*\x86H\xce=\x02\x01\x06\b*\x86H\xce=\x03\x01\a\x03B\x00\x04\f4\xa1\x8c\xa9?\x8e\x1c\x8c(\x1a\x94\x1by\x8f\xf7I\xa02}\xab\x8a?\xc5\xd7\xe2\x83Bl\xaf\xc2w\xa5x\x04\xf3\xf1\xf0\x1d\xc6h\xad\xb7\xec\nL\xd2\xcc`J\t6L\xe4\xb9\x8b\xf6\xc0%<\xab\xaf\x15\x1d\x16\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\a\x00N\x10\x00\x00B\x00\x03\x00\x00\x00\x00\x00BA\x04\x11\x85\xae%\x82\xc4z\xc5)\xba\x94\xd1\xda\xc2\r+\x8a>\xf8%\x99\aJ\xc9\x04\xd2\x10\xcb^a\xd27\x94\x90\xd8\x03\x04\xfb$\x12\xe0\x9b\x89$(\xa4\v\xde\xe4\x10\xb1\x87\xf8e-v\x04\x1e\x80\xe6\xab\xf3\xda\b\x16\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\b\x00W\x0f\x00\x00K\x00\x04\x00\x00\x00\x00\x00K\x04\x03\x00G0E\x02!\x00\xa4\x83m\xfe{\x03\xeb\x9c\xab\xc8\x8c\xda\xaa\xfa^\xf64\xb3\xf0\x89\xbc7\xd5\xc3\xc1\x83\xeb\xcc\x13vh?\x02 \x19\xdf\xe4E\x94D\r\xd0\xbf\xd7\xb0L\xdf\x90%_\xc6\xbb\xfe\x99M\xe8\xf9\xfcnE\x84\xd2\n$5\x1a\x14\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\t\x00\x01\x01\x16\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x01\x00(\x00\x01\x00\x00\x00\x00\x00\x01\x88\xd1\xc13\xe1+\xbdp\r]~\xd9!\xd745m4\xb8\\\xb6O4 \xc38\xee;'\\Q\\"
    12.913 AT read  +   17 "\r\n+USOST: 1,377\r\n"
0000012913 [app] INFO: recv + +USOST: 1,377
    12.914 AT read OK    6 "\r\nOK\r\n"
0000012915 [app] INFO: recv OK
    12.926 AT send      17 "AT+USORF=1,1024\r\n"
0000012926 [app] INFO: send command AT+USORF=1,1024
    12.936 AT read  +   54 "\r\n+USORF: 1,\"3.225.113.205\",5684,14,\"\x14\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\t\x00\x01\x01\"\r\n"
0000012939 [app] INFO: recv + +USORF: 1,"3.225.113.205",5684,14,"14fefd00000000000000000101"\x00\x00\x00\x00\x00\t\x00\x01\x01\"\
    12.941 AT read OK    4 "OK\r\n"
    12.943 AT read  +   17 "\r\n+UUSORF: 1,53\r\n"
0000012944 [app] INFO: recv + +UUSORF: 1,53
Socket 1: handle 1 has 53 bytes pending
    12.954 AT send      17 "AT+USORF=1,1024\r\n"
0000012954 [app] INFO: send command AT+USORF=1,1024
    12.967 AT read  +   93 "\r\n+USORF: 1,\"3.225.113.205\",5684,53,\"\x16\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x00\x00(\x00\x01\x00\x00\x00\x00\x00\x00\xfb\x13\xa2\xb3t\x00`\xcc\xf2k|\xbf\x01\xcdqR\xd4v8\xbef\xb5*&-\x0f\xbcI[\xcc\xa0\xd2\"\r\n"
    12.974 AT read OK    4 "OK\r\n"
    12.974 AT send       4 "AT\r\n"
    12.977 AT read OK    6 "\r\nOK\r\n"
    12.977 AT send      14 "AT+USORF=1,0\r\n"
0000012978 [app] INFO: recv + +USORF: 1,"3.225.113.205",5684,53,"16fefd000100000000000000(000100\x00\x00\x00\x00\x00\x00(\x00\x01
0000012978 [app] INFO: send command AT+USORF=1,0
    12.982 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
0000012983 [app] INFO: recv + +USORF: 1,0
    12.985 AT read OK    6 "\r\nOK\r\n"
0000012986 [app] INFO: recv OK
0000012987 [comm.protocol.handshake] INFO: Sending HELLO message
socketSendTo(1,3.225.113.205,5684,,58)
    12.987 AT send      36 "AT+USOST=1,\"3.225.113.205\",5684,58\r\n"
    12.996 AT read  >    3 "\r\n@"
    12.996 AT send      58 "\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x02\x00-\x00\x01\x00\x00\x00\x00\x00\x02\b\xbd\xff\x89\xc5\xeaom\"\xdcye\xc3Q\xdc;\xba\xe2\xd2(\xfc\xac\x05Rc0\xcb\x0e\xec\xb7\xb3\xbb\x00e0\x0f\xef"
    13.137 AT read  +   16 "\r\n+USOST: 1,58\r\n"
0000013137 [app] INFO: send command AT+USOST=1,"3.225.113.205",5684,5800000200-0001000000000002bdff\x00\x00\x00\x00\x00\x02\b\xbd\xff\x
    13.138 AT read OK    6 "\r\nOK\r\n"
    13.139 AT send       4 "AT\r\n"
0000013139 [app] INFO: recv OK
0000013139 [app] INFO: send command AT
    13.142 AT read OK    6 "\r\nOK\r\n"
    13.142 AT send      14 "AT+USORF=1,0\r\n"
    13.147 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
0000013148 [app] INFO: recv + +USORF: 1,0
    13.149 AT read OK    6 "\r\nOK\r\n"
0000013149 [app] INFO: recv OK
    13.220 AT read  +   17 "\r\n+UUSORD: 1,14\r\n"
Socket 1: handle 1 has 14 bytes pending
    13.226 AT send      17 "AT+USORF=1,1024\r\n"
    13.236 AT read  +   54 "\r\n+USORF: 1,\"3.225.113.205\",5684,14,\"\x14\xfe\xfd\x00\x00\x00\x00\x00\x00\x00\n\x00\x01\x01\"\r\n"
    13.241 AT read OK    4 "OK\r\n"
    13.241 AT send       4 "AT\r\n"
    13.241 AT read  + 0000013242 [app] INFO: recv + +USORF: 1,"3.225.113.205",    13.241 AT read OK    4 
0000013242 [app] INFO: send command AT
  17 "\r\n+UUSORF: 1,53\r\n"
Socket 1: handle 1 has 53 bytes pending
0000013243 [app] INFO: recv + +UUSORF: 1,53
    13.244 AT read OK    6 "\r\nOK\r\n"
    13.245 AT send      14 "AT+USORF=1,0\r\n"
0000013245 [app] INFO: recv OK
0000013246 [app] INFO: send command AT+USORF=1,0
    13.250 AT read  +   16 "\r\n+USORF: 1,53\r\n"
Socket 1: handle 1 has 53 bytes pending
0000013251 [app] INFO: recv + +USORF: 1,53
    13.252 AT read OK    6 "\r\nOK\r\n"
0000013252 [app] INFO: recv OK
    13.263 AT send      17 "AT+USORF=1,1024\r\n"
    13.276 AT read  +   93 "\r\n+USORF: 1,\"3.225.113.205\",5684,53,\"\x16\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x01\x00(\x00\x01\x00\x00\x00\x00\x00\x01\xe4\x1b\x899\xd5\xdb\x8e^y\xf8;\\\xae4>\f\x13*0\xe3\x82m\x96\x13o_?^b\x88\x9a\x8f\"\r\n"
0000013282 [app] INFO: recv + +USORF: 1,"3.225.113.205",e41b899d5db8e^yf8;ae4>13*0e382m9613o_;\\\xae4>\f\x13*0\xe3\x82m\x96\x13o_
    13.283 AT read OK    4 "OK\r\n"
    13.284 AT send       4 "AT\r\n"
    13.287 AT read OK    6 "\r\nOK\r\n"
    13.287 AT send      14 "AT+USORF=1,0\r\n"
    13.292 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
    13.293 AT read OK    6 "\r\nOK\r\n"
0000013293 [app] INFO: recv OK
    13.379 AT read  +   17 "\r\n+UUSORD: 1,33\r\n"
Socket 1: handle 1 has 33 bytes pending
    13.382 AT send      17 "AT+USORF=1,1024\r\n"
0000013382 [app] INFO: send command AT+USORF=1,1024
    13.393 AT read  +   73 "\r\n+USORF: 1,\"3.225.113.205\",5684,33,\"\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x02\x00\x14\x00\x01\x00\x00\x00\x00\x00\x02`\xbb\xb4\xb9\x01\xcei\xdb\xad\xa6\x8d\x1b\"\r\n"
0000013397 [app] INFO: recv + +USORF: 1,"3.225.113.205",5684,33,"17fefd0001000000000002001400x00\x00\x00\x00\x00\x02\x00\x14\x00\
    13.398 AT read OK    4 "OK\r\n"
    13.399 AT send       4 "AT\r\n"
0000013399 [app] INFO: recv OK
0000013399 [app] INFO: send command AT
    13.402 AT read OK    6 "\r\nOK\r\n"
    13.402 AT send      14 "AT+USORF=1,0\r\n"
    13.407 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
0000013408 [app] INFO: recv + +USORF: 1,0
    13.410 AT read OK    6 "\r\nOK\r\n"
0000013410 [comm.protocol.handshake] INFO: Handshake completed
0000013411 [app] INFO: recv OK
0000013412 [system] INFO: Send spark/device/last_reset event
socketSendTo(1,3.225.113.205,5684,,69)
    13.414 AT send      36 "AT+USOST=1,\"3.225.113.205\",5684,69\r\n"
0000013416 [app] INFO: send command AT+USOST=1,"3.225.113.205",5684,69
    13.422 AT read  >    3 "\r\n@"
    13.422 AT send      69 "\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x03\x008\x00\x01\x00\x00\x00\x00\x00\x03R \a\x9b\t\xc1_\x99j\x97\xa2\xa1`o\xce\xb6\xc4\xaf8\x1d\x7f\xe8k\xf1!Nl\x95\x96\x05Y\xf1\xaf\xb5^[Hw~\xa7\xfcG\xab\xfef\xe0z7"
    13.562 AT read  +   16 "\r\n+USOST: 1,69\r\n"
    13.563 AT read OK    6 "\r\nOK\r\n"
    13.563 AT send       4 "AT\r\n"
0000013563 [app] INFO: recv OK
0000013564 [app] INFO: send command AT
    13.566 AT read OK    6 "\r\nOK\r\n"
    13.566 AT send      14 "AT+USORF=0000013567 [app] INFO: recv OK
1,0\r\n"
0000013568 [app] INFO: send command AT+USORF=1,0
    13.573 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
0000013574 [app] INFO: recv + +USORF: 1,0
    13.576 AT read OK    6 "\r\nOK\r\n"
socketSendTo(1,3.225.113.205,5684,,73)
0000013577 [app] INFO: recv OK
    13.576 AT send      36 "AT+USOST=1,\"3.225.113.205\",5684,73\r\n"
    13.586 AT read  >    3 "\r\n@"
    13.586 AT send      73 "\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x000000013587 [app] INFO: send command AT+USOST=1,"3.225.113.205",5684,73    13.586 AT read  >    3 
\x04\x00<\x00\x01\x00\x00\x00\x00\x00\x04#\x1c\xba\xe6p\xe9\xe8\xbb\xd2\x83\xb1\xa7\x0e\xf8\xa0.\xf8\xa5\x92b\x16T,\xa9\x83\xab1\xd5\t\x12\xca\x92\xcb}\x0e\x9f\xbd(T\xf7\xe7\x8d\xef\xe3lC\x98\v{\x14l\xf5"
    13.727 AT read  +   16 "\r\n+USOST: 1,73\r\n"
    13.728 AT read OK    6 "\r\nOK\r\n"
    13.728 AT send       4 "AT\r\n"
0000013728 [app] INFO: send command 17fefd00010000000000.f8a592b16T,a983ab1d512ca92cb}092b\x16T,\xa9\x83\xab1\xd5\t\x12\xca\x92\xcb}\x0
0000013729 [app] INFO: send command AT
    13.731 AT read OK    6 "\r\nOK\r\n"
    13.731 AT send      14 "AT+USORF=1,0\r\n"
0000013732 [app] INFO: recv OK
    13.736 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
0000013737 [app] INFO: send command AT+USORF=1,0    13.736 AT read  +   15 
    13.738 AT read OK    6 "\r\nOK\r\n"
socketSendTo(1,3.225.113.205,5684,,73)
    13.738 AT send      36 "AT+USOST=1,\"3.225.113.205\",5684,73\r\n"
    13.748 AT read  >    3 "\r\n@"
    13.748 AT send      73 "\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x05\x00<\x00\x01\x00\x00\x00\x00\x00\x05\xc9\xec\x88\xdd\xdf\xbcts\aG \xfd\x81%\xf7\x1ev\xc6\xfc\xc9\xc3\xe0=\xee\xa4\xc3\x04\xe5|\xac\xa8<\x7fgc\x13\x84\xf2\xf2\xc9\xb0\rf\xa6f\xe4\b\x18\xe7\xd04N"
0000013754 [app] INFO: send command 17fefd000100000000000500<0001000000000005c9ec88dd\x00\x01\x00\x00\x00\x00\x00\x05\xc9\xec\x88\xdd\x
    13.890 AT read  +   16 "\r\n+USOST: 1,73\r\n"
0000013890 [app] INFO: recv + +USOST: 1,73
    13.891 AT read OK    6 "\r\nOK\r\n"
    13.892 AT send       4 "AT\r\n"
    13.892 AT read  +   17 "\r\n+UUSORD: 1,33\r\n"
Socket 1: handle 1 has 33 bytes pending
0000013893 [app] INFO: recv OK
0000013894 [app] INFO: send command AT
    13.895 AT read OK    6 "\r\nOK\r\n"
    13.895 AT send      14 "AT+USORF=1,0\r\n"
0000013896 [app] INFO: recv OK
    13.901 AT read  +   16 "\r\n+USORF: 1,33\r\n"
Socket 1: handle 1 has 33 bytes pending
0000013902 [app] INFO: send command AT+USORF=1,0    13.901 AT read  +   16 
    13.903 AT read OK    6 "\r\nOK\r\n"
0000013903 [system] INFO: Send subscriptions
socketSendTo(1,3.225.113.205,5684,,43)
    13.905 AT send      36 "AT+USOST=1,\"3.225.113.205\",5684,43\r\n"
0000013907 [app] INFO: send command AT+USOST=1,"3.225.113.205",5684,43
    13.913 AT read  >    3 "\r\n@"
    13.913 AT send      43 "\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x06\x00\x1e\x00\x01\x00\x00\x00\x00\x00\x06b\x06@\x12d\x10\xf7\xc8{\xd0\x05\x9e\xf2\x9e%\xf7Ma\xeb\xfb\x94\xf5"
    14.050 AT read  +   16 "\r\n+USOST: 1,43\r\n"
0000014050 [app] INFO: recv + +USOST: 1,43
    14.051 AT read OK    6 "\r\nOK\r\n"
socketSendTo(1,3.225.113.205,5684,,46)
    14.052 AT send    0000014053 [app] INFO: recv OK
  36 "AT+USOST=1,\"3.225.113.205\",5684,46\r\n"
0000014055 [app] INFO: send command AT+USOST=1,"3.225.113.205",5684,46
    14.061 AT read  >    3 "\r\n@"
    14.061 AT send      46 "\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\a\x00!\x00\x01\x00\x00\x00\x00\x00\a\xbe\xc0\x13$\xca'E\xd3\x03S\xcb.\xa5m\x84\x11\x8b\xf6\xd9\xb2+\xaa\xa4\xd5\xf9"
    14.198 AT read  +   16 "\r\n+USOST: 1,46\r\n"
    14.199 AT read OK    6 "\r\nOK\r\n"
0000014199 [comm.dtls] INFO: session cmd (CLS,DIS,MOV,LOD,SAV): 4
0000014200 [app] INFO: recv OK
0000014201 [comm.dtls] INFO: session cmd (CLS,DIS,MOV,LOD,SAV): 3
0000014201 [comm] INFO: Sending TIME request
socketSendTo(1,3.225.113.205,5684,,36)
    14.203 AT send      36 "AT+USOST=1,\"3.225.113.205\",5684,36\r\n"
    14.211 AT read  >    3 "\r\n@"
    14.211 AT send      36 "\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\b\x00\x17\x00\x01\x00\x00\x00\x00\x00\b\xc1\x05\x12\xf1Rtm\xe1\x01\x84\x1d\xa5O\xdb\r"
0000014215 [app] INFO: send command AT+USOST=1,"3.225.113.000000001700010000000000c10512f1Rtme100\x00\x00\x00\b\xc1\x05\x12\xf1Rtm\xe1\
    14.347 AT read  +   16 "\r\n+USOST: 1,36\r\n"
0000014347 [app] INFO: recv + +USOST: 1,36
    14.348 AT read OK    6 "\r\nOK\r\n"
0000014349 [app] INFO: recv OK
    14.360 AT send      17 "AT+USORF=1,1024\r\n"
0000014360 [app] INFO: send command AT+USORF=1,1024
    14.371 AT read  +   73 "\r\n+USORF: 1,\"3.225.113.205\",5684,33,\"\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x03\x00\x14\x00\x01\x00\x00\x00\x00\x00\x03\xf4\xf2\x83\x93\xf7!\x1d ,:T7\"\r\n"
0000014375 [app] INFO: recv + +USORF: 1,"3.225.113.205",5684,33,"17fefd0001000000000003001400x00\x00\x00\x00\x00\x03\x00\x14\x00\
    14.376 AT read OK    4 "OK\r\n"
    14.377 AT send       4 "AT\r\n"
    14.377 AT read  +   17 "\r\n+UUSORF: 1,99\r\n"
Socket 1: handle 1 has 99 bytes pending
    14.380 AT read OK    6 "\r\nOK\r\n"
    14.380 AT send      14 "AT+USORF=1,0\r\n"
0000014381 [app] INFO: recv OK
0000014381 [app] INFO: send command AT+USORF=1,0
    14.385 AT read  +   16 "\r\n+USORF: 1,99\r\n"
Socket 1: handle 1 has 99 bytes pending
    14.388 AT read OK    6 "\r\nOK\r\n"
0000014388 [comm.protocol] TRACE: Reply recieved: type=2, code=0
0000014389 [comm.protocol] INFO: message id 2 complete with code 0.00
0000014389 [comm.protocol] INFO: rcv'd message type=13
0000014389 [system] TRACE: Waiting until all handshake messages are processed by the protocol layer
0000014389 [app] INFO: recv OK
    14.401 AT send      17 "AT+USORF=1,1024\r\n"
0000014401 [app] INFO: send command AT+USORF=1,1024
    14.412 AT read  +   73 "\r\n+USORF: 1,\"3.225.113.205\",5684,33,\"\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x04\x00\x14\x00\x01\x00\x00\x00\x00\x00\x04\x19A\x1a\x8f\x9b\xe4\xe9h\xed\x96+\xbc\"\r\n"
    14.417 AT read OK    4 "OK\r\n"
0000014417 [comm.protocol] TRACE: Reply recieved: type=2, code=0
0000014418 [app] INFO: recv OK
0000014417 [comm.protocol] INFO: message id 3 complete with code 0.00
0000014419 [comm.protocol] INFO: rcv'd message type=13
    14.519 AT read  +   17 "\r\n+UUSORF: 1,66\r\n"
Socket 1: handle 1 has 66 bytes pending
    14.530 AT send      17 "AT+USORF=1,1024\r\n"
0000014530 [app] INFO: send command AT+USORF=1,1024
    14.541 AT read  +   73 "\r\n+USORF: 1,\"3.225.113.205\",5684,33,\"\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x05\x00\x14\x00\x01\x00\x00\x00\x00\x00\x05\xfb\xa0\xd9B\r\x88q=\xa7:|E\"\r\n"
    14.546 AT read OK    4 "OK\r\n"
0000014546 [comm.protocol] TRACE: Reply recieved: type=2, code=0
0000014547 [app] INFO: recv + +USORF: 1,"3.225.113.205",56    14.546 AT read OK    4 
0000014546 [comm.protocol] INFO: message id 4 complete with code 0.00
0000014548 [comm.protocol] INFO: rcv'd message type=13
    14.648 AT read  +   17 "\r\n+UUSORF: 1,66\r\n"
Socket 1: handle 1 has 66 bytes pending
0000014649 [app] INFO: recv + +UUSORF: 1,66
    14.659 AT send      17 "AT+USORF=1,1024\r\n"
    14.670 AT read  +   73 "\r\n+USORF: 1,\"3.225.113.205\",5684,33,\"\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x06\x00\x14\x00\x01\x00\x00\x00\x00\x00\x06\xc3G\x1e\xb5{\x95\x906\x15\xe2\a\xcb\"\r\n"
0000014674 [app] INFO: recv + +USORF: 1,"3.225.113.205",5684,33,"17fefd0001000000000006001400x00\x00\x00\x00\x00\x06\x00\x14\x00\
    14.675 AT read OK    4 "OK\r\n"
0000014676 [comm.protocol] TRACE: Reply recieved: type=2, code=0
0000014676 [comm.protocol] INFO: message id 5 complete with code 0.00
0000014677 [comm.protocol] INFO: rcv'd message type=13
0000014677 [app] INFO: recv OK
    14.777 AT read  +   17 "\r\n+UUSORF: 1,33\r\n"
Socket 1: handle 1 has 33 bytes pending
0000014778 [app] INFO: recv + +UUSORF: 1,33
    14.788 AT send      17 "AT+USORF=1,1024\r\n"
0000014788 [app] INFO: send command AT+USORF=1,1024
    14.799 AT read  +   73 "\r\n+USORF: 1,\"3.225.113.205\",5684,33,\"\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\a\x00\x14\x00\x01\x00\x00\x00\x00\x00\ar>S\x16l\xf0:\xaf{\xd5\xe6\x1d\"\r\n"
    14.804 AT read OK    4 "OK\r\n"
    14.804 AT send       4 "AT\r\n"
    14.804 AT read  +   17 "\r\n+UUSORF: 1,39\r\n"
Socket 1: handle 1 has 39 bytes pending
0000014806 [app] INFO: recv + +USORF: 1,"3.225.113.205",5684,33,"17fefd000100000000000014000\x00\x00\x00\x00\x00\a\x00\x14\x00\x0
    14.807 AT read OK    6 "\r\nOK\r\n"
    14.808 AT send      14 "AT+USORF=1,0\r\n"
0000014809 [app] INFO: recv OK
0000014809 [app] INFO: send command AT+USORF=1,0
    14.813 AT read  +   16 "\r\n+USORF: 1,39\r\n"
Socket 1: handle 1 has 39 bytes pending
0000014814 [app] INFO: recv + +USORF: 1,39
    14.815 AT read OK    6 "\r\nOK\r\n"
0000014815 [comm.protocol] TRACE: Reply recieved: type=2, code=0
0000014817 [comm.protocol] INFO: message id 6 complete with code 0.00
0000014817 [comm.protocol] INFO: rcv'd message type=13
    14.928 AT send      17 "AT+USORF=1,1024\r\n"
0000014928 [app] INFO: send command AT+USORF=1,1024
    14.940 AT read  +   79 "\r\n+USORF: 1,\"3.225.113.205\",5684,39,\"\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\b\x00\x1a\x00\x01\x00\x00\x00\x00\x00\b\xdc\x7fZ\xe9tW\xed\xc7\x94\xaf\xaa\x95\xfeE]N\xcbX\"\r\n"
    14.947 AT read OK    4 "OK\r\n"
    14.947 AT send       4 "AT\r\n"
    14.947 AT read  +   17 "\r\n+UUSORF: 1,76\r\n"
Socket 1: handle 1 has 76 bytes pending
0000014948 [app] INFO: recv OK
0000014949 [app] INFO: send command AT
    14.950 AT read OK    6 "\r\nOK\r\n"
    14.950 AT send      14 "AT+USORF=1,0\r\n0000014951 [app] INFO: recv OK
"
    14.956 AT read  +   16 "\r\n+USORF: 1,76\r\n"
Socket 1: handle 1 has 76 bytes pending
0000014957 [app] INFO: send command AT+USORF=1,0    14.956 AT read  +   16 
    14.959 AT read OK    6 "\r\nOK\r\n"
0000014959 [system] INFO: All handshake messages have been processed
0000014961 [comm.protocol] TRACE: Reply recieved: type=2, code=69
0000014961 [comm.protocol] INFO: message id 7 complete with code 2.05
0000014961 [comm.protocol] INFO: Received TIME response: 1601649551
0000014963 [comm.protocol] INFO: rcv'd message type=12
    15.076 AT send      17 "AT+USORF=1,1024\r\n"
    15.088 AT read  +   78 "\r\n+USORF: 1,\"3.225.113.205\",5684,38,\"\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\t\x00\x19\x00\x01\x00\x00\x00\x00\x00\t\f_n/\x03\xbfO\xfa\x9d,\xc3\xea\xfb\x85\x90\x87:\"\r\n"
    15.093 AT read OK    4 "OK\r\n"
0000015094 [app] INFO: recv + +USORF: 1,"3.225.113.205",5684,38,"17fefd000100000000000019000\x00\x00\x00\x00\x00\t\x00\x19\x00\x0
0000015111 [comm.protocol] INFO: Posting 'S' describe message
socketSendTo(1,3.225.113.205,5684,,679)
    15.115 AT send      37 "AT+USOST=1,\"3.225.113.205\",5684,679\r\n"
    15.117 AT read  +   17 "\r\n+UUSORF: 1,38\r\n"
Socket 1: handle 1 has 38 bytes pending
    15.123 AT read  >    3 "\r\n@"
    15.123 AT send     679 "\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x000000015124 [app] INFO: send command AT+USOST=1,"3.225.11    15.123 AT read  >    3 
\t\x02\x9a\x00\x01\x00\x00\x00\x00\x00\t\xf8Xj((\xb9\x17\xbfK\xc3\xa2\xc0\xcc\x9c\xf0\x81;\xee\x85\x1a\xcaz\xe6X\x9f$]\xe1T\xb5\xe28}\x98\x10\x91\xa2\xb6EzzlKoS\xffv\xe2\xed\x0f\\u\x03'\x9a\x97\xa8\x16\x89Q\xf7\xe0\x8c\xba\xf6H\x12A8CGq*H\a(qm\x82\xf0)\xc0\x0e\xda\xb9z\xd0\xe2Z\x90\x15\"\xfb\xc7\x1d^G\x05\xbd\xfd\xc9\xf2\x9f\xfaG\xfa-k\xbc\x12Vzr-\b\x9cI\xfe\xc7\xc86\xb9\x90\x0f\r~{\fi\xf2\xaf6\xd8\xba\xd4\xfb\xf5P\f\x9b\xfbw\xc7-,B1R2\xb2\xf5\xb1g\x88\xa5L\xb9\x14\xfc\x02\x9a2\xe8\xeb\xaf9\xf0\x9c`\xb0\xd9J\xf7B\xa9\xdaT\xd5\xf4\x14g\x80\x89\x91\rv\xf6\x01\x85h\xd4\xb7\x93\x1ec\xf0\xf3\x83\xfd\x8dGONR\x88\xd1\xd0\xf4/\xf8^\xd6\xb5\x80\xf8\xae\xa2\x06U\x12\x9e\xb4\x15\x13I\x18\xd1\x1dH\r\x1bT\x04\xbfgz&m\x85\v\xe1J\xe4\xd2\x98\xddFg\x82=\xa77\x17\xf8F\xea\xd3GwX|\xd0 \"I\xecM#\xc0\xeaf}\xe6*\xc3\xe7\xaf\x9c`:p\xe7\xd0\x9fPjQ$O\x13\xfa\x1a\xb7\xa2u\xc5\xa8\xd9q\xf9\xac[W3\x9c\x16\xce\x92\xfe\xd2!\xfc\v9E\xad\x8c\xc0\xc8]$@\xa2*\xd7R\x14O\"M\x13\xe5K\x84\x9d\x8eJ\x05k:\x91!\xa8q\xfa\x80\xf7\xa8\xff:Ms\xb5\x03\b\xd9{$\x06o\xda\xf5Y\xb2\xb7\x13nEeR2>,\xa4\xda6\xd5#\x8d\x97\xdb\xef\x800\xc4kD=\v\xc8-\xa4PVb?`r\x81\xaf8\x95a\r\xc4%\xc7\x06\xbb\x97DN\xeb\x8a3\xf7\xc7\xc5\x14\x94n|\tV7=\xb3\x84w}}y\xc1Zb\xdflw\xc4\xce\x1bT\xd5S\xea\x062\xef\x9f\x9d\xac\xa06\x7f\xe4\x9b\xe5\xeeu\xd8[\xef\xbb\a\xe4:\xb6\x90\x7f\xa7\xea;\xd8$\x03;I9t\xe8~\"\x15e\x7f`c\xa1/\xa5\xd4TM\xcd\x8a\xce\xdd\xdf\xc6mg \xa1\x93\xc4M\fB\x00\x03\xb3@\xacv[G\xfc\x87C[L}\xbf \xfc\xc1c\x9a\xb1\xab\xfbr\f\xd4\xf2ZS\xb7\x8e\xf0\xa5\xbfb\xef\x01\xf8$\x8ag\x8bL\x8aK\xe4~\xad^\xd6\x93\xe3\xdbT\x18\xc6`\v8qr8\xc2\xcd\xec\b\x1f\xd8\xecP\xd6\xa4\xdbB\xf5\x03t[G\xbf\x92\x9d?7\xe0)\x88Q1\\\x9dt\x91\x0eR\xa9\x14\x8c\xcb\x03#\x05D\x81vg\"\x15\xfc\x8f\xb2\x10\xeb\xa0\xc5\xa1\\0\x833\xf5a\x13\xd4\r\xbc\x10H\xd8\x8aX\xa2e\xda\xb0\xb6\x1f\xea\xbd}\xe8,\xd2J\xa9W1\xd9tN"
    15.357 AT read  +   17 "\r\n+USOST: 1,679\r\n"
0000015357 [app] INFO: send command 17fefd00010000000000029a00010000000000f8Xj((b917ba\x00\x01\x00\x00\x00\x00\x00\t\xf8Xj((\xb9\x17\xb
    15.358 AT read OK    6 "\r\nOK\r\n"
0000015359 [comm.dtls] INFO: session cmd (CLS,DIS,MOV,LOD,SAV): 4
0000015377 [comm.dtls] INFO: session cmd (CLS,DIS,MOV,LOD,SAV): 3
0000015377 [comm.protocol] INFO: rcv'd message type=1
0000015379 [system] INFO: Cloud connected
    15.390 AT send      17 "AT+USORF=1,1024\r\n"
    15.402 AT read  +   78 "\r\n+USORF: 1,\"3.225.113.205\",5684,38,\"\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\n\x00\x19\x00\x01\x00\x00\x00\x00\x00\n\xf0?\xa6/\xeb\xc2.\xda\x8czu\xd7\xfe\x0f\x9a\x03\x87\"\r\n"
    15.409 AT read OK    4 "OK\r\n"
    15.409 AT send       4 "AT\r\n"
    15.409 AT read  +   17 "\r\n+UUSORF: 1,38\r\n"
Socket 1: handle 1 has 38 bytes pending
0000015410 [app] INFO: recv + +USORF: 1,"3.225.113.205",5684,38,"17fefd000100000000000019000\x00\x00\x00\x00\x00\n\x00\x19\x00\x0
0000015411 [app] INFO: send command AT
    15.412 AT read OK    6 "\r\nOK\r\n"
    15.413 AT send      14 "AT+USORF=1,0\r\n"
0000015414 [app] INFO: send command AT+USORF=1,0
    15.419 AT read  +   16 "\r\n+USORF: 1,38\r\n"
Socket 1: handle 1 has 38 bytes pending
0000015420 [app] INFO: recv + +USORF: 1,38
    15.422 AT read OK    6 "\r\nOK\r\n"
0000015422 [comm.protocol] INFO: Posting 'A' describe message
socketSendTo(1,3.225.113.205,5684,,50)
    15.423 AT send      36 "AT+USOST=0000015423 [app] INFO: recv OK
1,\"3.225.113.205\",5684,50\r\n"
    15.431 AT read  >    3 "\r\n@"
    15.431 AT send      50 "\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\n\x00%\x00\x01\x00\x00\x00\x00\x00\n\x01\xb8\xec\xe6\xf4\xdb\t\x94\xb1k\xf7\x99\v\xb1\xb1\xdcp\xf6l~l\xff\x10\xc3\xb1}\xafS\x90"
0000015435 [app] INFO: send command 17fefd0001000000000000%0001000000000001b8ece6f4\x00\x01\x00\x00\x00\x00\x00\n\x01\xb8\xec\xe6\xf4\x
    15.568 AT read  +   16 "\r\n+USOST: 1,50\r\n"
0000015568 [app] INFO: recv + +USOST: 1,50
    15.569 AT read OK    6 "\r\nOK\r\n"
0000015570 [comm.dtls] INFO: session cmd (CLS,DIS,MOV,LOD,SAV): 4
0000015570 [comm.dtls] INFO: session cmd (CLS,DIS,MOV,LOD,SAV): 3
0000015571 [comm.protocol] INFO: rcv'd message type=1
0000015571 [app] INFO: recv OK
    15.682 AT send      17 "AT+USORF=1,1024\r\n"
0000015682 [app] INFO: send command AT+USORF=1,1024
    15.694 AT read  +   78 "\r\n+USORF: 1,\"3.225.113.205\",5684,38,\"\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\v\x00\x19\x00\x01\x00\x00\x00\x00\x00\v\x92\xef\x98\x9e\x00\x17\xa5\xfc\xfdL\x0f\x90\xf41c\x01\xdd\"\r\n"
    15.699 AT read OK    4 "OK\r\n"
    15.699 AT send       4 "AT\r\n"
0000015699 [app] INFO: recv + +USORF: 1,"3.225.113.205",5684,38,"17fefd000100000000000019000\x00\x00\x00\x00\x00\v\x00\x19\x00\x0
    15.702 AT read OK    6 "\r\nOK\r\n"
    15.702 AT send      14 "AT+USORF=1,0\r\n"
0000015703 [app] INFO: recv OK
0000015703 [app] INFO: send command AT+USORF=1,0
    15.707 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
0000015708 [app] INFO: recv + +USORF: 1,0
    15.709 AT read OK    6 "\r\nOK\r\n"

[ Modem::getSignalStrength ] = = = = = = = = = =
    15.711 AT send       4 "AT\r\n"
    15.716 AT read OK    6 "\r\nOK\r\n"
    15.716 AT send      13 "AT+COPS=3,2\r\n"
    15.721 AT read OK    6 "\r\nOK\r\n"
    15.721 AT send      10 "AT+COPS?\r\n"
0000015721 [app] INFO: recv OK
0000015722 [app] INFO: send command AT+COPS?
    15.727 AT read  +   25 "\r\n+COPS: 0,2,\"310410\",2\r\n"
    15.730 AT read OK    6 "\r\nOK\r\n"
    15.730 AT send       8 "AT+CSQ\r\n"
0000015730 [app] INFO: recv OK
0000015731 [app] INFO: send command AT+CSQ
    15.735 AT read  +   14 "\r\n+CSQ: 15,2\r\n"
0000015735 [app] INFO: recv + +CSQ: 15,2
    15.736 AT read OK    6 "\r\nOK\r\n"
    15.736 AT send       4 "AT\r\n"
    15.739 AT read OK    6 "\r\nOK\r\n"
    15.739 AT send      13 "AT+COPS=3,2\r\n"
0000015739 [app] INFO: recv OK
0000015740 [app] INFO: send command AT+COPS=3,2
    15.743 AT read OK    6 "\r\nOK\r\n"
    15.743 AT send      10 "AT+COPS?\r\n"
    15.749 AT read  +   25 "\r\n+COPS: 0,2,\"310410\",2\r\n"
0000015750 [app] INFO: recv + +COPS: 0,2,"310410",2
    15.752 AT read OK    6 "\r\nOK\r\n"
0000015752 [comm.protocol] INFO: Posting 'M' describe message
socketSendTo(1,3.225.113.205,5684,,222)
    15.754 AT send      37 "AT+USOST=1,\"3.225.113.205\",5684,222\r\n"
0000015756 [app] INFO: send command AT+USOST=1,"3.225.113.205",5684,222
    15.762 AT read  >    3 "\r\n@"
    15.762 AT send     222 "\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\v\x00\xd1\x00\x01\x00\x00\x00\x00\x00\v6\xdbD\xe1\x9c\x14u2\xd0\xa5\xa2\xc4+$G\"\xe4\xf9U>\b\x9e'B \xce\xed\xf2\xa0\x94\x10\x94\xd4\x05\"R\xb7}y\x1e\xaeK\xab\xfa\xf4\xb6\xe7\xc7mV{\x10~\xc5\xd3\v\rG\x06\x10q\x94\xfe\x98\xb7\x00\xed\xbd,1\x15N5\xa0\x00\xf3[U\xad\xe2\xdeA\x1eX1\x15\xcd?\xf7(\x9d\xb4E\x7f\x96$=\x96r\xbe\xf2\xe3g\xed\x14\x9b4\\\x9a\x84\x9e\x00\x9av\xacA\x11\\\x0f]f\x14\x8e\xa82\xf9\xb5x.\n\xe5\xdb\x9eG\x83\x7f\xa7F(s2\x0erh\xa0W6\xd0\xca\xa7\xf3\x80\xd1\xb4\xc0\x807\xb3\x1f\xf6\x7f\xb8\xfe\x13\x9c}r\xa0t\x98\x9d\x81.-\xa7\xfa\xd26\x85FR \x15\xceR\xf5\x1a\xcf\x9c\xeb\x12f\x96\xf6\xb9\xa7\x88\x9d\xbavC"
    15.926 AT read  +   17 "\r\n+USOST: 1,222\r\n"
0000015926 [app] INFO: recv + +USOST: 1,222
    15.927 AT read OK    6 "\r\nOK\r\n"
    15.928 AT send       4 "AT\r\n"
0000015928 [app] INFO: recv OK
0000015928 [app] INFO: send command AT
    15.931 AT read OK    6 "\r\nOK\r\n"
    15.931 AT send      14 "AT+USORF=1,0\r0000015932 [app] INFO: recv OK
\n"
    15.937 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
    15.940 AT read OK    6 "\r\nOK\r\n"
0000015940 [comm.protocol] INFO: rcv'd message type=1
0000015940 [app] INFO: send command AT+USORF=1,0    15.940 AT read OK    6 
    16.817 AT read  +   17 "\r\n+UUSORD: 1,76\r\n"
Socket 1: handle 1 has 76 bytes pending
0000016818 [app] INFO: recv + +UUSORD: 1,76
    16.828 AT send      17 "AT+USORF=1,1024\r\n"
    16.843 AT read  +  116 "\r\n+USORF: 1,\"3.225.113.205\",5684,76,\"\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\f\x00?\x00\x01\x00\x00\x00\x00\x00\f\x1f\xb4\xccO\xd8\x7fjx5\xac'\xf5\xc0h\xf9\x00rn\x19\x93\xf0\x85\xb0)\xc3\xe7\x9d\vM\xca\x15T\f\xab\x8a\xaf\n\xbcD\xe8\xdan\xb9\x81(\xd3\xd3\xec\fRh3\xed\xf1D\"\r\n"
    16.852 AT read OK    4 "OK\r\n"
    16.852 AT send       4 "AT\r\n"
0000016852 [app] INFO: recv + +USORF: 1,"3.225.113.205",5684,76,"17fefd0001000000000000?0001\x00\x00\x00\x00\x00\f\x00?\x00\x01\x
0000016853 [app] INFO: send command AT
    16.855 AT read OK    6 "\r\nOK\r\n"
    16.855 AT send      14 "AT+USORF=1,0\r\n"
0000016856 [app] INFO: recv OK
    16.860 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
    16.863 AT read OK    6 "\r\nOK\r\n"
socketSendTo(1,3.225.113.205,5684,,33)
    16.864 AT send      36 "AT+USOST=1,\"3.225.113.205\",5684,33\r\n"
0000016864 [app] INFO: send command AT+USORF=1,0    16.863 AT read OK    6 
    16.871 AT read  >    3 "\r\n@"
    16.871 AT send      33 "\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\f\x00\x14\x00\x01\x00\x00\x00\x00\x00\f \xb2I\xcc\x04\xaa \xd529\xf4&"
    17.005 AT read  +   16 "\r\n+USOST: 1,33\r\n"
    17.006 AT read OK    6 "\r\nOK\r\n"
    17.006 AT send       4 "AT\r\n"
0000017006 [app] INFO: recv OK
0000017007 [app] INFO: send command AT
    17.009 AT read OK    6 "\r\nOK\r\n"
    17.009 AT send      14 "AT+USORF=1,0\r\n"
    17.014 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
0000017015 [app] INFO: recv + +USORF: 1,0
    17.017 AT read OK    6 "\r\nOK\r\n"
0000017017 [comm.protocol] INFO: rcv'd message type=8
0000017017 [app] INFO: recv OK
    20.891 AT read  +   17 "\r\n+UUSORD: 1,38\r\n"
Socket 1: handle 1 has 38 bytes pending
    20.902 AT send      17 "AT+USORF=1,1024\r\n"
0000020902 [app] INFO: send command AT+USORF=1,1024
    20.914 AT read  +   78 "\r\n+USORF: 1,\"3.225.113.205\",5684,38,\"\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\r\x00\x19\x00\x01\x00\x00\x00\x00\x00\rZ\xc7\xcbQ\x81\x00d\x01\x00C\xcf\xd3\x1cH\x9aZI\"\r\n"
    20.921 AT read OK    4 "OK\r\n"
    20.921 AT send       4 "AT\r\n"
    20.924 AT read OK    6 "\r\nOK\r\n"
    20.924 AT send      14 "AT+USORF=1,0\r0000020925 [app] INFO: recv OK
\n"
0000020926 [app] INFO: send command AT+USORF=1,0
    20.930 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
0000020931 [app] INFO: recv + +USORF: 1,0
    20.932 AT read OK    6 "\r\nOK\r\n"
0000020932 [comm.protocol] INFO: Posting 'A' describe message
socketSendTo(1,3.225.113.205,5684,,50)
    20.934 AT send      36 "AT+USOST=1,\"3.225.113.205\",5684,50\r\n"
0000020936 [app] INFO: send command AT+USOST=1,"3.225.113.205",5684,50
    20.942 AT read  >    3 "\r\n@"
    20.942 AT send      50 "\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\r\x00%\x00\x01\x00\x00\x00\x00\x00\r\xe2\xc1\xcd\xfc\xba\xbdB\x82=\xb8\r\x15u\xd7\xe3\x96q\xb1/\xdf\x17\n4\v\xfa\x82\xa4\x9c5"
    21.080 AT read  +   16 "\r\n+USOST: 1,50\r\n"
    21.081 AT read OK    6 "\r\nOK\r\n"
    21.081 AT send       4 "AT\r\n"
0000021081 [app] INFO: recv OK
0000021082 [app] INFO: send command AT
    21.084 AT read OK    6 "\r\nOK\r\n"
    21.084 AT send      14 "AT+USORF=1,0\r\n"
    21.089 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
0000021090 [app] INFO: recv + +USORF: 1,0
    21.091 AT read OK    6 "\r\nOK\r\n"
0000021091 [comm.dtls] INFO: session cmd (CLS,DIS,MOV,LOD,SAV): 4
0000021091 [comm.dtls] INFO: session cmd (CLS,DIS,MOV,LOD,SAV): 3
0000021093 [comm.protocol] INFO: rcv'd message type=1
    33.403 AT read  +   17 "\r\n+UUSORD: 1,38\r\n"
Socket 1: handle 1 has 38 bytes pending
0000033404 [app] INFO: recv + +UUSORD: 1,38
    33.414 AT send      17 "AT+USORF=1,1024\r\n"
0000033414 [app] INFO: send command AT+USORF=1,1024
    35.409 AT read  +   78 "\r\n+USORF: 1,\"3.225.113.205\",5684,38,\"\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x0e\x00\x19\x00\x01\x00\x00\x00\x00\x00\x0e\xdc\xee\xc5\xcc\x81\xa1+Q\x84u1\xa8\x8a\xbf\x97\xa51\"\r\n"
    35.414 AT read OK    4 "OK\r\n"
    35.414 AT send       4 "AT\r\n"
0000035414 [app] INFO: send command AT
    35.417 AT read OK    6 "\r\nOK\r\n"
    35.417 AT send      14 "AT+USORF=1,0\r\n"
0000035418 [app] INFO: recv OK
    35.422 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
0000035423 [app] INFO: send command AT+USORF=1,0    35.422 AT read  +   15 
    35.425 AT read OK    6 "\r\nOK\r\n"
0000035425 [comm.protocol] INFO: Posting 'A' describe message
socketSendTo(1,3.225.113.205,5684,,50)
    35.427 AT send      36 "AT+USOST=1,\"3.225.113.205\",5684,50\r\n"
    35.435 AT read  >    3 "\r\n@"
    35.435 AT send      50 "\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x0e\x00%\x00\x01\x00\x00\x00\x00\x00\x0eF:\xd2\x84\xd1\x98C\x917RY\xc3|u\x11\x18.\x89\x8b\x13o\x9a\x1d\xf6H\xe1\xe1\x85\x95"
    35.572 AT read  +   16 "\r\n+USOST: 1,50\r\n"
    35.573 AT read OK    6 "\r\nOK\r\n"
    35.573 AT send       4 "AT\r\n"
0000035573 [app] INFO: recv OK
0000035574 [app] INFO: send command AT
    35.575 AT read  +   17 "\r\n+UUSORD: 1,38\r\n"
Socket 1: handle 1 has 38 bytes pending
0000035576 [app] INFO: recv + +UUSORD: 1,38
    35.577 AT read OK    6 "\r\nOK\r\n"
    35.577 AT send      14 "AT+USORF=1,0\r\n0000035578 [app] INFO: recv OK
"
0000035579 [app] INFO: send command AT+USORF=1,0
    35.584 AT read  +   16 "\r\n+USORF: 1,38\r\n"
Socket 1: handle 1 has 38 bytes pending
0000035585 [app] INFO: recv + +USORF: 1,38
    35.587 AT read OK    6 "\r\nOK\r\n"
0000035587 [comm.dtls] INFO: session cmd (CLS,DIS,MOV,LOD,SAV): 4
0000035587 [comm.dtls] INFO: session cmd (CLS,DIS,MOV,LOD,SAV): 3
0000035589 [comm.protocol] INFO: rcv'd message type=1
    35.700 AT send      17 "AT+USORF=1,1024\r\n"
    35.712 AT read  +   78 "\r\n+USORF: 1,\"3.225.113.205\",5684,38,\"\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x0f\x00\x19\x00\x01\x00\x00\x00\x00\x00\x0f\r\x8e\xf4#)>\x91\x87\xceW\xfa\xc3\xaf\xa3~\x19\xc1\"\r\n"
0000035716 [app] INFO: recv + +USORF: 1,"3.225.113.205",5684,38,"17fefd000100000000000f001900x00\x00\x00\x00\x00\x0f\x00\x19\x00\
    35.717 AT read OK    4 "OK\r\n"
    35.718 AT send       4 "AT\r\n"
0000035718 [app] INFO: recv OK
0000035718 [app] INFO: send command AT
    35.721 AT read OK    6 "\r\nOK\r\n"
    35.721 AT send      14 "AT+USORF=1,0\r\n"
0000035722 [app] INFO: recv OK
0000035722 [app] INFO: send command AT+USORF=1,0
    35.726 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
    35.729 AT read OK    6 "\r\nOK\r\n"
socketSendTo(1,3.225.113.205,5684,,50)
    35.729 AT send      36 "AT+USOST=1,\"3.225.113.205\",5684,50\r\n"
    35.738 AT read  >    3 "\r\n@"
    35.738 AT send      50 "\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x0f\x00%\x00\x01\x00\x00\x00\x00\x00\x0f\x97\xa7Ms&\t\xc1\xcc\xde\xdd\xc3m\x02sb\x93[D\xde`\xeb\x87\x16\xbe\xd58\xb2\xfd\xc3"
0000035742 [app] INFO: send command AT+USOST=1,"3.225.113.205",5684,500f00%000100000000000f97a7Ms&c10\x00\x00\x00\x0f\x97\xa7Ms&\t\xc1\
    35.875 AT read  +   16 "\r\n+USOST: 1,50\r\n"
0000035875 [app] INFO: recv + +USOST: 1,50
    35.876 AT read OK    6 "\r\nOK\r\n"
    35.877 AT send       4 "AT\r\n"
0000035877 [app] INFO: recv OK
0000035877 [app] INFO: send command AT
    35.880 AT read OK    6 "\r\nOK\r\n"
    35.880 AT send      14 "AT+USORF=1,0\r\n"
0000035881 [app] INFO: recv OK
    35.885 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
    35.888 AT read OK    6 "\r\nOK\r\n"
0000035888 [app] INFO: send command AT+USORF=1,0    35.888 AT read OK    6 
    58.965 AT read  +   17 "\r\n+UUSORD: 1,38\r\n"
Socket 1: handle 1 has 38 bytes pending
0000058966 [app] INFO: recv + +UUSORD: 1,38
    58.976 AT send      17 "AT+USORF=1,1024\r\n"
0000058976 [app] INFO: send command AT+USORF=1,1024
    61.497 AT read  +   78 "\r\n+USORF: 1,\"3.225.113.205\",5684,38,\"\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x10\x00\x19\x00\x01\x00\x00\x00\x00\x00\x10\x18\xed\x82\xadKGe\xeb\xda-\xfd\x81M\xce\x1b\x8ch\"\r\n"
0000061502 [app] INFO: recv + +USORF: 1,"3.225.113.205",5684,38,"17fefd0001000000000010001900x00\x00\x00\x00\x00\x10\x00\x19\x00\
    61.504 AT read OK    4 "OK\r\n"
    61.504 AT send       4 "AT\r\n"
    61.504 AT read  +   17 "0000061505 [app] INFO: recv OK
0000061505 [app] INFO: send command AT
\r\n+UUSORF: 1,38\r\n"
Socket 1: handle 1 has 38 bytes pending
0000061506 [app] INFO: recv + +UUSORF: 1,38
    61.507 AT read OK    6 "\r\nOK\r\n"
    61.508 AT send      14 "AT+USORF=1,0\r\n"
    61.514 AT read  +   16 "\r\n+USORF: 1,38\r\n"
Socket 1: handle 1 has 38 bytes pending
0000061515 [app] INFO: recv + +USORF: 1,38
    61.517 AT read OK    6 "\r\nOK\r\n"
0000061517 [comm.protocol] INFO: Posting 'A' describe message
0000061518 [app] INFO: recv OK
socketSendTo(1,3.225.113.205,5684,,50)
    61.519 AT send      36 "AT+USOST=1,\"3.225.113.205\",5684,50\r\n"
    61.527 AT read  >    3 "\r\n@"
    61.527 AT send      50 "\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x10\x00%\x00\x01\x00\x00\x00\x00\x00\x10\xdcK\xf5\xa2\x19IF\x1d\xb1\x8f\x7f\xea@\xfe5\xf4\xf26\xe9a3\x05\xae\xf1\xce\xb5\xf09\n"
    61.665 AT read  +   16 "\r\n+USOST: 1,50\r\n"
    61.666 AT read OK    6 "\r\nOK\r\n"
0000061666 [comm.dtls] INFO: session cmd (CLS,DIS,MOV,LOD,SAV): 4
0000061666 [comm.dtls] INFO: session cmd (CLS,DIS,MOV,LOD,SAV): 3
0000061668 [comm.protocol] INFO: rcv'd message type=1
    61.779 AT send      17 "AT+USORF=1,1024\r\n"
0000061779 [app] INFO: send command AT+USORF=1,1024
    61.791 AT read  +   78 "\r\n+USORF: 1,\"3.225.113.205\",5684,38,\"\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x11\x00\x19\x00\x01\x00\x00\x00\x00\x00\x11\x91*\x00\xff$\x0e\x97X\xb9\xfe\x12\x9e\\\xe3\xfe\xba\xf9\"\r\n"
    61.798 AT read OK    4 "OK\r\n"
    61.798 AT send       4 "AT\r\n"
0000061798 [app] INFO: recv + +USORF: 1,"3.225.113.205",5684,38,"17fefd0001000000000011001900x00\x00\x00\x00\x00\x11\x00\x19\x00\
0000061799 [app] INFO: send command AT
    61.801 AT read OK    6 "\r\nOK\r\n"
    61.801 AT send      14 "AT+USORF=1,0\r\n"
0000061802 [app] INFO: recv OK
    61.807 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
0000061808 [app] INFO: send command AT+USORF=1,0    61.807 AT read  +   15 
    61.810 AT read OK    6 "\r\nOK\r\n"
socketSendTo(1,3.225.113.205,5684,,50)
0000061811 [app] INFO: recv OK
    61.810 AT send      36 "AT+USOST=1,\"3.225.113.205\",5684,50\r\n"
0000061814 [app] INFO: send command AT+USOST=1,"3.225.113.205",5684,50
    61.820 AT read  >    3 "\r\n@"
    61.820 AT send      50 "\x17\xfe\xfd\x00\x01\x00\x00\x00\x00\x00\x11\x00%\x00\x01\x00\x00\x00\x00\x00\x11?)\xd3\x9c]\xd9\x82Y\xbd\x8aWMX\x8e\xe9\xce\x16g\xce\xb8.\xdc\xe2\xf3\xe4\xb1i\xa9b"
    61.958 AT read  +   16 "\r\n+USOST: 1,50\r\n"
0000061958 [app] INFO: recv + +USOST: 1,50
    61.959 AT read OK    6 "\r\nOK\r\n"
    61.960 AT send       4 "AT\r\n"
    61.963 AT read OK    6 "\r\nOK\r\n"
    61.963 AT send      14 "AT+USORF=1,0\r\n"
0000061964 [app] INFO: recv OK
    61.968 AT read  +   15 "\r\n+USORF: 1,0\r\n"
Socket 1: handle 1 has 0 bytes pending
0000061969 [app] INFO: send command AT+USORF=1,0    61.968 AT read  +   15 
    61.971 AT read OK    6 "\r\nOK\r\n"


*/