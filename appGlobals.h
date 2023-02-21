// Global TuyaDevice declarations
//
// s60sc 2022

#pragma once
#include "globals.h"

/******************** User modifiable defines *******************/

#define MCU_TX_PIN 21 // must be UART0 TX pin if controller ESP, eg pin 21 for ESP32-C3
#define MCU_RX_PIN 20 // must be UART0 RX pin if controller ESP, eg pin 20 for ESP32-C3

// sniffer
#define USE_SNIFFER false // false to be tuya device, true when sniffing and need to connect ESP to external wifi eg a removed WBR3 Tuya wifi module 
#define WIFI_TX_PIN 4 // only when USE_SNIFFER is true
#define WIFI_RX_PIN 3 // only when USE_SNIFFER is true
#define USE_UART0 true // true if using ESP as tuya device, else false if used as external wifi module


/********************* fixed defines leave as is *******************/ 
/** Do not change anything below here unless you know what you are doing **/

//#define DEV_ONLY // leave commented out
#define STATIC_IP_OCTAL "162" // dev only
#define CHECK_MEM false // set to false
#define FLUSH_DELAY 0 // for debugging crashes

#define APP_NAME "ESP-TuyaDevice" // max 15 chars
#define APP_VER "1.2.1"

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
#define MAX_CONFIGS 70 // > number of entries in configs.txt
#define GITHUB_URL "https://raw.githubusercontent.com/s60sc/ESP32-Tuya_Device/main"

#define UART_RTS UART_PIN_NO_CHANGE
#define UART_CTS UART_PIN_NO_CHANGE
#define TUYA_BAUD_RATE 9600 
#define BUFF_LEN UART_FIFO_LEN * 2 // bigger than biggest tuya message

#define FILLSTAR "****************************************************************"
#define DELIM '~'
#define STORAGE LittleFS // one of: LittleFS SD_MMC 
#define RAMSIZE (1024 * 8) 
#define CHUNKSIZE (1024 * 4)
//#define INCLUDE_FTP 
//#define INCLUDE_SMTP
//#define INCLUDE_SD
#define IS_IO_EXTENDER false // must be false unless IO_Extender
#define EXTPIN 100


/******************** Libraries *******************/


/******************** Function declarations *******************/                                        

// global app specific functions
void heartBeat();
void prepUarts();
void processMCUcmd();
void processTuyaMsg(const char* wsMsg) ;


/******************** Global app declarations *******************/


/************************** structures ********************************/

struct tuyaStruct {
  uint8_t tuyaCmd;
  uint8_t tuyaDP;
  int32_t tuyaInt;
  uint8_t tuyaData[200]; // bigger than max message size from tuya MCU
};
extern tuyaStruct mcuTuya;
