#include "esp_camera.h"
#include <SD_MMC.h>

// Pin assignments for SD card module
#define SD_CS 13

// Camera model
#define CAMERA_MODEL_AI_THINKER

// Camera pins
#define CAM_PIN_PWDN 32
#define CAM_PIN_RESET -1
#define CAM_PIN_XCLK 0
#define CAM_PIN_SIOD 26
#define CAM_PIN_SIOC 27
#define CAM_PIN_D7 35
#define CAM_PIN_D6 34
#define CAM_PIN_D5 39
#define CAM_PIN_D4 36
#define CAM_PIN_D3 21
#define CAM_PIN_D2 19
#define CAM_PIN_D1 18
#define CAM_PIN_D0 5
#define CAM_PIN_VSYNC 25
#define CAM_PIN_HREF 23
#define CAM_PIN_PCLK 22

// Interval between taking pictures (in milliseconds)
#define INTERVAL 1000

// Initialize SD card
void initSDCard() {
  // Start SD_MMC communication
  if (!SD_MMC.begin("/sdcard", true)) {
    Serial.println("SD card mount failed");
    return;
  }

  Serial.println("SD card mounted");
}

void setup() {
  Serial.begin(115200);

  // Initialize SD card
  initSDCard();

  // Initialize camera
  camera_config_t config;
  config.ledc_timer = LEDC_TIMER_0;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.pin_pwdn = CAM_PIN_PWDN;
  config.pin_reset = CAM_PIN_RESET;
  config.pin_xclk = CAM_PIN_XCLK;
  config.pin_sscb_sda = CAM_PIN_SIOD;
  config.pin_sscb_scl = CAM_PIN_SIOC;
  config.pin_d7 = CAM_PIN_D7;
  config.pin_d6 = CAM_PIN_D6;
  config.pin_d5 = CAM_PIN_D5;
  config.pin_d4 = CAM_PIN_D4;
  config.pin_d3 = CAM_PIN_D3;
  config.pin_d2 = CAM_PIN_D2;
  config.pin_d1 = CAM_PIN_D1;
  config.pin_d0 = CAM_PIN_D0;
  config.pin_vsync = CAM_PIN_VSYNC;
  config.pin_href = CAM_PIN_HREF;
  config.pin_pclk = CAM_PIN_PCLK;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_SVGA;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  Serial.println("Camera initialized");
}

void loop() {
  // Take a picture
  camera_fb_t* fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    return;
  }else{
    Serial.println("photo taken succesfully!");
  }

  // // Create filename with timestamp
  // String filename = "/sdcard/image_" + String(millis()) + ".jpg";

  // // Save picture to SD card
  // File file = SD_MMC.open(filename, FILE_WRITE);
  // if (!file) {
  //   Serial.println("Failed to create file");
  //   return;
  // }
  // file.write(fb->buf, fb->len);
  // file.close();

  // Serial.println("Picture saved to " + filename);

  // Free camera framebuffer
  esp_camera_fb_return(fb);

  // Wait for the interval to elapse
  delay(1000);
  }
