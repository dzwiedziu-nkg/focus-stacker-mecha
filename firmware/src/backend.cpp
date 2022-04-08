#include "backend.h"
#include "motor_camera.h"

#ifdef ESP32
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>

#define MAX_TIME 60000

const char* PARAM_MESSAGE = "message";
const char* CONTENT_TYPE = "application/json";

const char* JSON_PROGRAM = "program";
const char* JSON_CHANGE_SETTINGS = "change_settings";
const char* JSON_MOTOR_TIME = "motor_time";
const char* JSON_MOTOR_PAUSE = "motor_pause";
const char* JSON_FOCUS_TIME = "focus_time";
const char* JSON_EXPOSURE_TIME = "exposure_time";
const char* JSON_EXPOSURE_PAUSE = "exposure_pause";
const char* JSON_MESSAGE = "message";

AsyncWebServer server(80);

void send_response_with_status(AsyncWebServerRequest *request, int code, const String &message = "") {
    DynamicJsonDocument json(1024);
    json[JSON_PROGRAM] = program;
    json[JSON_MOTOR_TIME] = motor_time;
    json[JSON_MOTOR_PAUSE] = motor_pause;
    json[JSON_FOCUS_TIME] = focus_time;
    json[JSON_EXPOSURE_TIME] = exposure_time;
    json[JSON_EXPOSURE_PAUSE] = exposure_pause;
    json[JSON_MESSAGE] = message;
    
    String buff;
    serializeJson(json, buff);

    request->send(200, CONTENT_TYPE, buff);
}

void api_get_status(AsyncWebServerRequest *request) {
    send_response_with_status(request, 200);
}

/*
 * JSON format (as typescript notation):
 * {
 *   "program": number,          // set program, from 0 to 5
 *   "change_settings": number,  // 1 - set_settings from followed values:
 *   "motor_time"?: number,      // motor_time and etc. (not used when change_settings is 0)
 *   "motor_pause"?: number,
 *   "focus_time"?: number,
 *   "exposure_time"?: number,
 *   "exposure_pause"?: number
 * }
 */
void api_set_program(AsyncWebServerRequest *request, JsonVariant &json) {
    const JsonObject& jsonObj = json.as<JsonObject>();

    int p = jsonObj[JSON_PROGRAM];
    if (p < PROGRAM_IDLE || p > PROGRAM_TEST ) {
        send_response_with_status(request, 400, "Invalid program");
        return;
    }

    if (jsonObj[JSON_CHANGE_SETTINGS]) {
        const char *for_validation[] = {JSON_MOTOR_TIME, JSON_MOTOR_PAUSE, JSON_FOCUS_TIME, JSON_EXPOSURE_TIME, JSON_EXPOSURE_PAUSE};

        for (int i = 0; i < 5; i++) {
            const char *key = for_validation[i];
            
            if (!jsonObj.containsKey(key)) {
                send_response_with_status(request, 400, String("Required value: ") + key);
                return;
            }

            int v = jsonObj[key];
            if (v < 0 || v > MAX_TIME) {
                send_response_with_status(request, 400, String("Value ") + key + " must be between 0 and " + MAX_TIME);
                return;
            }
        }

        set_settings(
            jsonObj[JSON_MOTOR_TIME],
            jsonObj[JSON_MOTOR_PAUSE],
            jsonObj[JSON_FOCUS_TIME],
            jsonObj[JSON_EXPOSURE_TIME],
            jsonObj[JSON_EXPOSURE_PAUSE]
        );
    }

    if (program != p) {
        switch_program(p);
    }

    api_get_status(request);
}

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void init_server() {
    server.on("/api/status", HTTP_GET, api_get_status);
    //server.on("/api/program", HTTP_POST, api_set_program);
    server.addHandler(new AsyncCallbackJsonWebHandler("/api/program", api_set_program));

    SPIFFS.begin();
    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
    server.onNotFound(notFound);

    server.begin();
}
