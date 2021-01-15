
#ifndef DIYBMSServer_H_
#define DIYBMSServer_H_

#include <Arduino.h>

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <EEPROM.h>

#include "defines.h"
#include "Rules.h"
#include "settings.h"
#include "ArduinoJson.h"
#include "PacketRequestGenerator.h"
#include "PacketReceiveProcessor.h"

#include "Modbus.h"

class DIYBMSServer
{
public:
    static void StartServer(AsyncWebServer *webserver,
                            diybms_eeprom_settings *mysettings,
                            sdcard_info (*sdcardcallback)(),
                            PacketRequestGenerator *prg,
                            PacketReceiveProcessor *pktreceiveproc,
                            ControllerState *controlState,
                            Rules *rules,
                            ModbusInfo (*ModBus)[MODBUS_NUM],
                            ModbusVal (*ModBusVal)[MODBUS_NUM]);

    static void generateUUID();
    static void clearModuleValues(uint8_t module);
    //static uint16_t ConfigHasChanged;

private:
    static AsyncWebServer *_myserver;
    static String UUIDString;

    //Pointers to other classes (not always a good idea in static classes)
    static sdcard_info (*_sdcardcallback)();
    static PacketRequestGenerator *_prg;
    static PacketReceiveProcessor *_receiveProc;
    static diybms_eeprom_settings *_mysettings;
    static Rules *_rules;
    static ControllerState *_controlState;

    static ModbusInfo (*_ModBus)[MODBUS_NUM];
    static ModbusVal (*_ModBusVal)[MODBUS_NUM];

    static void saveConfiguration()
    {
        Settings::WriteConfig("diybms", (char *)_mysettings, sizeof(diybms_eeprom_settings));
    }

    static void handleNotFound(AsyncWebServerRequest *request);
    static void monitor2(AsyncWebServerRequest *request);
    static void monitor3(AsyncWebServerRequest *request);
    //static void monitor(AsyncWebServerRequest *request);
    static void modules(AsyncWebServerRequest *request);
    static void integration(AsyncWebServerRequest *request);
    static void identifyModule(AsyncWebServerRequest *request);
    static void GetRules(AsyncWebServerRequest *request);
    static String TemplateProcessor(const String &var);
    static bool validateXSS(AsyncWebServerRequest *request);
    static void SendSuccess(AsyncWebServerRequest *request);
    static void SendFailure(AsyncWebServerRequest *request);
    static void settings(AsyncWebServerRequest *request);
    static void resetCounters(AsyncWebServerRequest *request);
    static void handleRestartController(AsyncWebServerRequest *request);
    static void storage(AsyncWebServerRequest *request);

    static void modbus(AsyncWebServerRequest *request);
    static void modbusVal(AsyncWebServerRequest *request);
    static void saveModbus(AsyncWebServerRequest *request);

    static void saveSetting(AsyncWebServerRequest *request);
    static void saveInfluxDBSetting(AsyncWebServerRequest *request);
    static void saveMQTTSetting(AsyncWebServerRequest *request);
    static void saveGlobalSetting(AsyncWebServerRequest *request);
    static void saveBankConfiguration(AsyncWebServerRequest *request);
    static void saveRuleConfiguration(AsyncWebServerRequest *request);
    static void saveNTP(AsyncWebServerRequest *request);
    static void saveStorage(AsyncWebServerRequest *request);

    static void saveDisplaySetting(AsyncWebServerRequest *request);

    static String uuidToString(uint8_t *uuidLocation);
    static void SetCacheAndETagGzip(AsyncWebServerResponse *response, String ETag);
    static void SetCacheAndETag(AsyncWebServerResponse *response, String ETag);
};

#endif
