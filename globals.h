// Global declarations
//
// s60sc 2022

#pragma once
// to compile with -Wall -Werror=all -Wextra
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
//#pragma GCC diagnostic ignored "-Wunused-variable"
//#pragma GCC diagnostic ignored "-Wunused-but-set-variable"


/******************** User modifiable defines *******************/

#define MCU_TX_PIN 21 // must be UART0 TX pin if controller ESP, eg pin 21 for ESP32-C3
#define MCU_RX_PIN 20 // must be UART0 RX pin if controller ESP, eg pin 20 for ESP32-C3

// sniffer
#define USE_SNIFFER false // false to be tuya device, true when sniffing and need to connect ESP to external wifi eg a removed WBR3 Tuya wifi module 
#define WIFI_TX_PIN 4 // only when USE_SNIFFER is true
#define WIFI_RX_PIN 3 // only when USE_SNIFFER is true
#define USE_UART0 true // true if using ESP as tuya device, else false if used as external wifi module


#define ALLOW_SPACES false // set set true to allow whitespace in configs.txt key values

//#define USE_LOG_COLORS  // uncomment to colorise log messages (eg if using idf.py, but not arduino)

#define IS_ESP32_C3 // uncomment if ESP32-C3 is being used


/** Do not change anything below here unless you know what you are doing **/

/********************* fixed defines leave as is *******************/ 
 
#define APP_NAME "ESP-TuyaDevice" // max 15 chars
#define APP_VER "1.0"

#define MAX_CLIENTS 3 // allowing too many concurrent web clients can cause errors
#define DATA_DIR "/data"
#define HTML_EXT ".htm"
#define TEXT_EXT ".txt"
#define JS_EXT ".js"
#define CSS_EXT ".css"
#define ICO_EXT ".ico"
#define SVG_EXT ".svg"
#if USE_SNIFFER
#define INDEX_PAGE_PATH DATA_DIR "/TSN" HTML_EXT
#else
#define INDEX_PAGE_PATH DATA_DIR "/Thermo" HTML_EXT
#endif
#define CONFIG_FILE_PATH DATA_DIR "/configs" TEXT_EXT
#define LOG_FILE_PATH DATA_DIR "/log" TEXT_EXT
#define OTA_FILE_PATH DATA_DIR "/OTA" HTML_EXT
#define FILE_NAME_LEN 64
#define ONEMEG (1024 * 1024)
#define MAX_PWD_LEN 64
#define JSON_BUFF_LEN (1024 * 2) 
#define MAX_CONFIGS 60 // > number of entries in configs.txt
#define GITHUB_URL "https://raw.githubusercontent.com/s60sc/ESP32-Tuya_Device/main"

#define UART_RTS UART_PIN_NO_CHANGE
#define UART_CTS UART_PIN_NO_CHANGE
#define TUYA_BAUD_RATE 9600 
#define BUFF_LEN UART_FIFO_LEN * 2 // bigger than biggest tuya message

#define FILLSTAR "****************************************************************"
#define DELIM '~'
#define STORAGE SPIFFS // use of SPIFFS or SD_MMC
#define RAMSIZE (1024 * 8) 
#define CHUNKSIZE (1024 * 4)
#define FLUSH_DELAY 0 // for debugging crashes
//#define INCLUDE_FTP 
//#define INCLUDE_SMTP
//#define INCLUDE_SD
//#define DEV_ONLY // leave commented out
#define STATIC_IP_OCTAL "162" // dev only
#define IS_IO_EXTENDER false // must be false unless IO_Extender
#define EXTPIN 100
// which optional web assets to download
#define USE_JQUERY false


/******************** Libraries *******************/

#include "Arduino.h"
#include <driver/i2s.h>
#include "esp_http_server.h"
#include <ESPmDNS.h> 
#include "lwip/sockets.h"
#include <vector>
#include "ping/ping_sock.h"
#include <Preferences.h>
#include <regex>
#include <SD_MMC.h>
#include <SPIFFS.h>
#include <sstream>
#include <Update.h>
#include <WebServer.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>

/******************** Function declarations *******************/

// global mandatory app specific functions, in appSpecific.cpp 
void appDataFiles();
void buildAppJsonString(bool filter);
void heartBeat();
void OTAprereq();
void processMCUcmd();
bool updateAppStatus(const char* variable, const char* value);
esp_err_t webAppSpecificHandler(httpd_req_t *req, const char* variable, const char* value);
void wsAppSpecificHandler(const char* wsMsg);

// global app specific functions, in sniffer.cpp
void prepUarts();
void processTuyaMsg(const char* wsMsg) ;

// global general utility functions in utils.cpp / utilsSD.cpp / peripherals.cpp 
void buildJsonString(uint8_t filter);
bool checkDataFiles();
bool checkFreeSpace();
void checkMemory();
void dateFormat(char* inBuff, size_t inBuffLen, bool isFolder);
void deleteFolderOrFile(const char* deleteThis);
void devSetup();
void doRestart(String restartStr);
void emailAlert(const char* _subject, const char* _message);
const char* encode64(const char* inp);
const uint8_t* encode64chunk(const uint8_t* inp, int rem);
bool externalPeripheral(byte pinNum, uint32_t outputData = 0);
void flush_log(bool andClose = false);
void formatElapsedTime(char* timeStr, uint32_t timeVal);
void formatHex(const char* inData, size_t inLen);
bool ftpFileOrFolder(const char* fileFolder);
bool getLocalNTP();
void getOldestDir(char* oldestDir);
void goToSleep(int wakeupPin, bool deepSleep);
void initStatus(int cfgGroup, int delayVal);
void listBuff(const uint8_t* b, size_t len); 
bool listDir(const char* fname, char* jsonBuff, size_t jsonBuffLen, const char* extension);
bool loadConfig();
void logPrint(const char *fmtStr, ...);
void logSetup();
bool parseJson(int rxSize);
void prepPeripherals();
void prepSMTP();
void prepUart();
void remote_log_init();
void removeChar(char *s, char c);
void reset_log();
void setPeripheralResponse(const byte pinNum, const uint32_t responseData);
void showProgress();
float smooth(float latestVal, float smoothedVal, float alpha);
void startFTPtask();
void startOTAtask();
void startSecTimer(bool startTimer);
bool startStorage();
void startWebServer();
bool startWifi();
void syncToBrowser(const char *val);
bool updateConfigVect(const char* variable, const char* value);
void updateStatus(const char* variable, const char* _value);
void urlDecode(char* inVal);
uint32_t usePeripheral(const byte pinNum, const uint32_t receivedData);
void wgetFile(const char* githubURL, const char* filePath, bool restart = false);
void wsAsyncSend(const char* wsData);

/******************** Global utility declarations *******************/

extern String AP_SSID;
extern char AP_Pass[];
extern char AP_ip[];
extern char AP_sn[];
extern char AP_gw[];

extern char hostName[]; //Host name for ddns
extern char ST_SSID[]; //Router ssid
extern char ST_Pass[]; //Router passd

extern char ST_ip[]; //Leave blank for dhcp
extern char ST_sn[];
extern char ST_gw[];
extern char ST_ns1[];
extern char ST_ns2[];

extern char Auth_Name[]; 
extern char Auth_Pass[];

extern int responseTimeoutSecs; // time to wait for FTP or SMTP response
extern bool allowAP; // set to true to allow AP to startup if cannot reconnect to STA (router)
extern int wifiTimeoutSecs; // how often to check wifi status
extern uint8_t percentLoaded;
extern int refreshVal;
extern bool configLoaded;

extern char timezone[];
extern char* jsonBuff; 
extern bool dbgVerbose;
extern bool logMode;
extern bool timeSynchronized;
extern bool monitorOpen; 
extern const char* defaultPage_html;
extern const char* otaPage_html;

// SD storage
extern int sdMinCardFreeSpace; // Minimum amount of card free Megabytes before freeSpaceMode action is enabled
extern int sdFreeSpaceMode; // 0 - No Check, 1 - Delete oldest dir, 2 - Upload to ftp and then delete folder on SD 
extern bool sdFormatIfMountFailed ; // Auto format the sd card if mount failed. Set to false to not auto format.

// peripheral stored values
extern bool useIOextender; // true to use IO Extender, otherwise false


/******************** Global app declarations *******************/



/************************** structures ********************************/

struct tuyaStruct {
  uint8_t tuyaCmd;
  uint8_t tuyaDP;
  int32_t tuyaInt;
  uint8_t tuyaData[200]; // bigger than max message size from tuya MCU
};
extern tuyaStruct mcuTuya;

/*********************** Log formatting ************************/

#ifdef USE_LOG_COLORS
#define LOG_COLOR_ERR  "\033[0;31m" // red
#define LOG_COLOR_WRN  "\033[0;33m" // yellow
#define LOG_COLOR_DBG  "\033[0;36m" // cyan
#define LOG_NO_COLOR   "\033[0m"
#else
#define LOG_COLOR_ERR
#define LOG_COLOR_WRN
#define LOG_COLOR_DBG
#define LOG_NO_COLOR
#endif 

#define INF_FORMAT(format) "[%s %s] " format "\n", esp_log_system_timestamp(), __FUNCTION__
#define LOG_INF(format, ...) logPrint(INF_FORMAT(format), ##__VA_ARGS__)
#define WRN_FORMAT(format) LOG_COLOR_WRN "[%s WARN %s] " format LOG_NO_COLOR "\n", esp_log_system_timestamp(), __FUNCTION__
#define LOG_WRN(format, ...) logPrint(WRN_FORMAT(format), ##__VA_ARGS__)
#define ERR_FORMAT(format) LOG_COLOR_ERR "[%s ERROR @ %s:%u] " format LOG_NO_COLOR "\n", esp_log_system_timestamp(), pathToFileName(__FILE__), __LINE__
#define LOG_ERR(format, ...) logPrint(ERR_FORMAT(format), ##__VA_ARGS__)
#define DBG_FORMAT(format) LOG_COLOR_DBG "[%s DEBUG @ %s:%u] " format LOG_NO_COLOR "\n", esp_log_system_timestamp(), pathToFileName(__FILE__), __LINE__
#define LOG_DBG(format, ...) if (dbgVerbose) logPrint(DBG_FORMAT(format), ##__VA_ARGS__)
#define LOG_PRT(buff, bufflen) log_print_buf((const uint8_t*)buff, bufflen)
