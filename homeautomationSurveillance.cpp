#include <WiFi.h>
#include "esp_camera.h"
#include <WebServer.h>

// WiFi Credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);

bool motionDetected = false;

// Function Prototypes
void initCamera();
void connectToWiFi();
bool detectMotion();
void storeImage();
void startStreaming();

void setup()
{
    Serial.begin(115200);

    initCamera();

    connectToWiFi();

    startStreaming();
}

void loop()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        connectToWiFi();
    }

    server.handleClient();

    motionDetected = detectMotion();

    if (motionDetected)
    {
        Serial.println("Motion Detected!");

        storeImage();

        // Optional:
        // sendNotification();
        // uploadToCloud();
    }

    delay(100);
}

void initCamera()
{
    // ESP32-CAM camera configuration
    Serial.println("Initializing Camera...");
    
    // Camera pin configuration goes here
    
    Serial.println("Camera Ready");
}

void connectToWiFi()
{
    Serial.print("Connecting to WiFi");

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi Connected");
    Serial.println(WiFi.localIP());
}

void startStreaming()
{
    server.on("/", []()
    {
        server.send(200, "text/plain",
                    "IoT Surveillance Camera Running");
    });

    server.begin();

    Serial.println("Web Server Started");
}

bool detectMotion()
{
    // Motion detection logic
    // Compare current frame with previous frame

    return false;
}

void storeImage()
{
    camera_fb_t *fb = esp_camera_fb_get();

    if (!fb)
    {
        Serial.println("Image Capture Failed");
        return;
    }

    Serial.println("Image Captured");

    // Save image to SD card or upload to cloud

    esp_camera_fb_return(fb);
}
