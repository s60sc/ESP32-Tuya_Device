// Global TuyaDevice declarations
//
// s60sc 2022

#pragma once
#include "globals.h"
#if !CONFIG_IDF_TARGET_ESP32C3
#error "Must select ESP32C3 module"
#endif

/******************** User modifiable defines *******************/

#define MCU_TX_PIN 21 // must be UART0 TX pin if controller is ESP, eg pin 21 for ESP32-C3
#define MCU_RX_PIN 20 // must be UART0 RX pin if controller is ESP, eg pin 20 for ESP32-C3

// sniffer
#define USE_SNIFFER true // false to be tuya device, true when sniffing and need to connect ESP to external wifi eg a removed WBR3 Tuya wifi module 
#define WIFI_TX_PIN 4 // only when USE_SNIFFER is true
#define WIFI_RX_PIN 3 // only when USE_SNIFFER is true
#define USE_UART0 false // true if using ESP as tuya device, else false if used as external wifi module

#define ALLOW_SPACES false // set true to allow whitespace in configs.txt key values
#define USE_IP6 false

// web server ports
#define HTTP_PORT 80 // app control
#define HTTPS_PORT 443 // secure app control

/*********************** Fixed defines leave as is ***********************/ 
/** Do not change anything below here unless you know what you are doing **/

#define STATIC_IP_OCTAL "163" // dev only
#define DEBUG_MEM false // leave as false
#define FLUSH_DELAY 0 // for debugging crashes
#define DBG_ON false // esp debug output
#define DOT_MAX 50
#define HOSTNAME_GRP 0

#define APP_NAME "ESP-TuyaDevice" // max 15 chars
#define APP_VER "1.8"

#define HTTP_CLIENTS 2 // http, ws
#define MAX_STREAMS 0
#if USE_SNIFFER
#define INDEX_PAGE_PATH DATA_DIR "/TSN" HTML_EXT
#else
#define INDEX_PAGE_PATH DATA_DIR "/Thermo" HTML_EXT
#endif
#define FILE_NAME_LEN 64
#define IN_FILE_NAME_LEN 128
#define JSON_BUFF_LEN (1024 * 2) 
#define MAX_CONFIGS 70 // > number of entries in configs.txt
#define GITHUB_PATH "/s60sc/ESP32-Tuya_Device/main"

#define STORAGE LittleFS // One of LittleFS or SD_MMC
#define RAMSIZE (1024 * 8) 
#define CHUNKSIZE (1024 * 4)
#define MIN_RAM 8 // min object size stored in ram instead of PSRAM default is 4096
#define MAX_RAM 4096 // max object size stored in ram instead of PSRAM default is 4096
#define TLS_HEAP (64 * 1024) // min free heap for TLS session
#define WARN_HEAP (32 * 1024) // low free heap warning
#define WARN_ALLOC (16 * 1024) // low free max allocatable free heap block
#define MAX_ALERT 1024

#define INCLUDE_FTP_HFS false // ftp.cpp (file upload)
#define INCLUDE_SMTP false    // smtp.cpp (email)
#define INCLUDE_MQTT false    // mqtt.cpp
#define INCLUDE_TGRAM false   // telegram.cpp
#define INCLUDE_CERTS false   // certificates.cpp (https and server certificate checking)
#define INCLUDE_WEBDAV true  // webDav.cpp (WebDAV protocol)

// to determine if newer data files need to be loaded
#define CFG_VER 3

#ifdef CONFIG_IDF_TARGET_ESP32S3 
#define SERVER_STACK_SIZE (1024 * 8)
#define DS18B20_STACK_SIZE (1024 * 2)
#define STICK_STACK_SIZE (1024 * 4)
#else
#define SERVER_STACK_SIZE (1024 * 4)
#define DS18B20_STACK_SIZE (1024)
#define STICK_STACK_SIZE (1024 * 2)
#endif
#define BATT_STACK_SIZE (1024 * 2)
#define EMAIL_STACK_SIZE (1024 * 6)
#define FS_STACK_SIZE (1024 * 4)
#define LOG_STACK_SIZE (1024 * 3)
#define MIC_STACK_SIZE (1024 * 4)
#define MQTT_STACK_SIZE (1024 * 4)
#define PING_STACK_SIZE (1024 * 5)
#define SERVO_STACK_SIZE (1024)
#define SUSTAIN_STACK_SIZE (1024 * 4)
#define TGRAM_STACK_SIZE (1024 * 6)
#define TELEM_STACK_SIZE (1024 * 4)
#define UART_STACK_SIZE (1024 * 2)

// task priorities
#define HTTP_PRI 5
#define TGRAM_PRI 1
#define EMAIL_PRI 1
#define FTP_PRI 1
#define LOG_PRI 1
#define UART_PRI 1
#define BATT_PRI 1

#define UART_RTS UART_PIN_NO_CHANGE
#define UART_CTS UART_PIN_NO_CHANGE
#define TUYA_BAUD_RATE 9600 
#define BUFF_LEN (UART_FIFO_LEN * 2) // bigger than biggest tuya message


/******************** Function declarations *******************/                                        

// global app specific functions
void heartBeat();
void prepUarts();
void processMCUcmd();
void processTuyaMsg(const char* wsMsg) ;


/******************** Global app declarations *******************/

extern const char* appConfig;
extern bool uartReady;

/************************** structures ********************************/

struct tuyaStruct {
  uint8_t tuyaCmd;
  uint8_t tuyaDP;
  int32_t tuyaInt;
  uint8_t tuyaData[200]; // bigger than max message size from tuya MCU
};
extern tuyaStruct mcuTuya;
