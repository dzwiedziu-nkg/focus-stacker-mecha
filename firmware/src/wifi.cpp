#include "wifi.h"
#include "debug.h"
#include "default_settings.h"

#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

void init_wifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(DEFAULT_SSID, DEFAULT_PASSWORD);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        PRINTLN_LOG("WiFi Failed!");
        return;
    }

    PRINT_LOG("IP Address: ");
    PRINTLN_LOG(WiFi.localIP());

    WiFi.setAutoReconnect(true);
    // WiFi.persistent(true);
}
