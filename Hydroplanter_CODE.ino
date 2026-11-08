#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define WATER_SENSOR_PIN D0
#define SOIL_SENSOR_PIN  D2
#define PUMP_PIN         D6

#define OLED_SDA_PIN     D4
#define OLED_SCL_PIN     D5

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

const bool WATER_OK_WHEN_LOW = true;

const int SOIL_DRY_READING = 3000;
const int SOIL_WET_READING = 1300;

const int PUMP_START_PERCENT = 30;
const int PUMP_STOP_PERCENT  = 55;

const unsigned long MAX_PUMP_RUNTIME = 15000UL;

const unsigned long MIN_TIME_BETWEEN_WATERINGS =
  10UL * 60UL * 1000UL;

const unsigned long DISPLAY_INTERVAL = 1000UL;

#define PLANT_BITMAP_WIDTH 47
#define PLANT_BITMAP_HEIGHT 64
#define PLANT_BITMAP_BYTES_PER_ROW 6

const unsigned char epd_bitmap_spider_plant[] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,

  0xff, 0xff, 0xfe, 0xff, 0xff, 0xfe,
  0xff, 0xff, 0xfe, 0xff, 0xff, 0xfe,
  0xff, 0xff, 0xfd, 0x3f, 0xff, 0xfe,
  0xff, 0xff, 0xfd, 0x3f, 0xff, 0xfe,
  0xff, 0xff, 0xf3, 0x3f, 0xff, 0xfe,
  0xff, 0xff, 0xf3, 0x3f, 0xff, 0xfe,
  0xff, 0xff, 0xf3, 0xff, 0xff, 0xfe,
  0xfe, 0x10, 0x73, 0xdc, 0x10, 0x7e,

  0xff, 0xcf, 0xd3, 0xc3, 0xc7, 0xfe,
  0xff, 0xef, 0xc3, 0xc3, 0xc7, 0xfe,
  0xff, 0xf1, 0xf3, 0xdf, 0x3f, 0xfe,
  0xff, 0xfe, 0xfd, 0x3e, 0xff, 0xfe,
  0xff, 0xff, 0x3e, 0xfd, 0xff, 0xfe,
  0xff, 0xff, 0x3e, 0xfd, 0xff, 0xfe,
  0xff, 0x01, 0xde, 0xf3, 0x03, 0xfe,
  0xf8, 0xff, 0x1d, 0xf1, 0xfe, 0x3e,

  0xf8, 0xff, 0x1d, 0xe1, 0xfe, 0x3e,
  0xe7, 0xff, 0xcd, 0xcf, 0xff, 0xde,
  0x80, 0x0f, 0xf3, 0x3f, 0xfe, 0x02,
  0xff, 0xf1, 0xfc, 0xff, 0xc1, 0xfe,
  0xff, 0xf1, 0xfc, 0xff, 0xc1, 0xfe,
  0xff, 0xfe, 0xfc, 0xfe, 0x3f, 0xfe,
  0xff, 0xf0, 0x3e, 0xfc, 0x0f, 0xfe,
  0xff, 0xcf, 0xdf, 0xf1, 0xf3, 0xfe,

  0xff, 0xcf, 0xdf, 0xf3, 0xf3, 0xfe,
  0xff, 0x1f, 0xdf, 0x33, 0xfd, 0xfe,
  0xff, 0x00, 0xef, 0x2c, 0x01, 0xfe,
  0xfe, 0x7f, 0x8f, 0x23, 0xfc, 0x7e,
  0xfe, 0x7f, 0x8f, 0x23, 0xfc, 0x7e,
  0xff, 0xe0, 0x00, 0x00, 0x07, 0xfe,
  0xff, 0xef, 0xff, 0xff, 0xe7, 0xfe,
  0xff, 0xef, 0xff, 0xff, 0xe7, 0xfe,

  0xff, 0xef, 0xff, 0xff, 0xe7, 0xfe,
  0xff, 0xef, 0xff, 0xff, 0xe7, 0xfe,
  0xff, 0xe0, 0x00, 0x00, 0x1f, 0xfe,
  0xff, 0xe0, 0x00, 0x00, 0x1f, 0xfe,
  0xff, 0xfd, 0xff, 0xff, 0x3f, 0xfe,
  0xff, 0xfd, 0xff, 0xff, 0x3f, 0xfe,
  0xff, 0xfd, 0xff, 0xff, 0xff, 0xfe,
  0xff, 0xfd, 0xff, 0xff, 0xff, 0xfe,

  0xff, 0xfd, 0xff, 0xff, 0xff, 0xfe,
  0xff, 0xff, 0xff, 0xfe, 0xff, 0xfe,
  0xff, 0xff, 0xff, 0xfe, 0xff, 0xfe,
  0xff, 0xff, 0xff, 0xfe, 0xff, 0xfe,
  0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe,
  0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe,
  0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe,
  0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe,

  0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe,
  0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe,
  0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe,
  0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe,
  0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe,
  0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe
};

bool waterAvailable = false;
bool pumpRunning = false;

int soilRawValue = 0;
int moisturePercent = 0;

unsigned long pumpStartTime = 0;
unsigned long lastPumpStopTime = 0;
unsigned long lastDisplayUpdate = 0;

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(WATER_SENSOR_PIN, INPUT_PULLUP);

  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);

  Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("OLED not detected.");

    digitalWrite(PUMP_PIN, LOW);

    while (true) {
      delay(1000);
    }
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(52, 2);
  display.println("Dusty");

  display.setTextSize(1);
  display.setCursor(52, 25);
  display.println("Starting...");
  display.setCursor(52, 38);
  display.println("USB/Battery");

  display.display();

  delay(1500);

  lastPumpStopTime =
    millis() - MIN_TIME_BETWEEN_WATERINGS;
}

void loop() {
  unsigned long currentTime = millis();

  updateWaterLevel();
  readSoilMoisture();
  controlPump();

  if (currentTime - lastDisplayUpdate >= DISPLAY_INTERVAL) {
    lastDisplayUpdate = currentTime;
    updateDisplay();
  }

  delay(50);
}

void updateWaterLevel() {
  bool switchState = digitalRead(WATER_SENSOR_PIN);

  if (WATER_OK_WHEN_LOW) {
    waterAvailable = switchState == LOW;
  } else {
    waterAvailable = switchState == HIGH;
  }
}

void readSoilMoisture() {
  const int numberOfSamples = 10;
  long total = 0;

  for (int i = 0; i < numberOfSamples; i++) {
    total += analogRead(SOIL_SENSOR_PIN);
    delay(2);
  }

  soilRawValue = total / numberOfSamples;

  moisturePercent = map(
    soilRawValue,
    SOIL_DRY_READING,
    SOIL_WET_READING,
    0,
    100
  );

  moisturePercent = constrain(moisturePercent, 0, 100);
}

void controlPump() {
  unsigned long currentTime = millis();

  if (!waterAvailable) {
    stopPump();
    return;
  }

  if (pumpRunning &&
      currentTime - pumpStartTime >= MAX_PUMP_RUNTIME) {
    Serial.println("Pump stopped: maximum runtime.");
    stopPump();
    return;
  }

  if (pumpRunning &&
      moisturePercent >= PUMP_STOP_PERCENT) {
    Serial.println("Pump stopped: moisture target reached.");
    stopPump();
    return;
  }

  if (!pumpRunning &&
      moisturePercent <= PUMP_START_PERCENT &&
      currentTime - lastPumpStopTime >=
      MIN_TIME_BETWEEN_WATERINGS) {
    startPump();
  }
}

void startPump() {
  if (!waterAvailable) {
    return;
  }

  digitalWrite(PUMP_PIN, HIGH);

  pumpRunning = true;
  pumpStartTime = millis();

  Serial.println("Pump started.");
}

void stopPump() {
  digitalWrite(PUMP_PIN, LOW);

  if (pumpRunning) {
    lastPumpStopTime = millis();
  }

  pumpRunning = false;
}

void updateDisplay() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  drawMoisturePlant(moisturePercent);

  display.setTextSize(1);
  display.setCursor(52, 2);
  display.println("Dusty");

  display.setTextSize(2);
  display.setCursor(52, 14);
  display.print(moisturePercent);
  display.println("%");

  display.setTextSize(1);
  display.setCursor(52, 40);

  if (!waterAvailable) {
    display.println("WATER");
    display.println("EMPTY");
  } else if (pumpRunning) {
    display.println("PUMP ON");
  } else if (moisturePercent <= PUMP_START_PERCENT) {
    display.println("SOIL DRY");
  } else {
    display.println("SOIL OK");
  }

  display.display();

  Serial.print("Soil ADC: ");
  Serial.print(soilRawValue);

  Serial.print(" | Moisture: ");
  Serial.print(moisturePercent);
  Serial.print("% | Water: ");

  Serial.print(waterAvailable ? "AVAILABLE" : "EMPTY");

  Serial.print(" | Pump: ");
  Serial.println(pumpRunning ? "ON" : "OFF");
}

bool bitmapPlantPixel(int x, int y) {
  if (x < 0 ||
      x >= PLANT_BITMAP_WIDTH ||
      y < 0 ||
      y >= PLANT_BITMAP_HEIGHT) {
    return false;
  }

  int byteIndex =
    y * PLANT_BITMAP_BYTES_PER_ROW + (x / 8);

  uint8_t bitmapByte =
    pgm_read_byte(
      &epd_bitmap_spider_plant[byteIndex]
    );

  bool bitIsSet =
    bitmapByte & (0x80 >> (x % 8));

  return !bitIsSet;
}

bool bitmapPlantEdge(int x, int y) {
  if (!bitmapPlantPixel(x, y)) {
    return false;
  }

  if (!bitmapPlantPixel(x - 1, y)) {
    return true;
  }

  if (!bitmapPlantPixel(x + 1, y)) {
    return true;
  }

  if (!bitmapPlantPixel(x, y - 1)) {
    return true;
  }

  if (!bitmapPlantPixel(x, y + 1)) {
    return true;
  }

  return false;
}

void drawMoisturePlant(int moisture) {
  const int originX = 0;
  const int originY = 0;

  int fillY = map(
    moisture,
    0,
    100,
    originY + PLANT_BITMAP_HEIGHT,
    originY
  );

  fillY = constrain(
    fillY,
    originY,
    originY + PLANT_BITMAP_HEIGHT
  );

  for (int y = 0; y < PLANT_BITMAP_HEIGHT; y++) {
    for (int x = 0; x < PLANT_BITMAP_WIDTH; x++) {
      if (!bitmapPlantPixel(x, y)) {
        continue;
      }

      int screenX = originX + x;
      int screenY = originY + y;

      bool edgePixel = bitmapPlantEdge(x, y);

      if (edgePixel || screenY >= fillY) {
        display.drawPixel(
          screenX,
          screenY,
          SSD1306_WHITE
        );
      } else {
        display.drawPixel(
          screenX,
          screenY,
          SSD1306_BLACK
        );
      }
    }
  }
}