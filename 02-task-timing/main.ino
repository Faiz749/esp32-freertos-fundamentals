#define BLUELED_PIN  4
#define REDLED_PIN  5
#define GREENLED_PIN 2

void ledtask1(void *parameter);
void ledtask2(void *parameter);
void ledtask3(void *parameter);

void setup() {
  Serial.begin(115200);

  pinMode(BLUELED_PIN, OUTPUT);
  pinMode(REDLED_PIN, OUTPUT);
  pinMode(GREENLED_PIN, OUTPUT);

  digitalWrite(BLUELED_PIN, LOW);
  digitalWrite(REDLED_PIN, LOW);
  digitalWrite(GREENLED_PIN, LOW);

  xTaskCreatePinnedToCore( ledtask1, "LED TASK 1", 1000,  NULL, 1, NULL,1);

  xTaskCreatePinnedToCore( ledtask2, "LED TASK 2", 1000, NULL, 1,NULL,1 );

  xTaskCreatePinnedToCore(  ledtask3, "LED TASK 3", 1000, NULL, 1, NULL, 1);
}

void loop() {
}

void ledtask1(void *parameter) {
  while (true) {
    digitalWrite(BLUELED_PIN, LOW);
    Serial.println("BLUE LED: OFF");
    vTaskDelay(pdMS_TO_TICKS(500));

    digitalWrite(BLUELED_PIN, HIGH);
    Serial.println("BLUE LED: ON");
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void ledtask2(void *parameter) {
  while (true) {
    digitalWrite(REDLED_PIN, LOW);
    Serial.println("RED LED: OFF");
    vTaskDelay(pdMS_TO_TICKS(1000));

    digitalWrite(REDLED_PIN, HIGH);
    Serial.println("RED LED: ON");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void ledtask3(void *parameter) {
  while (true) {
    digitalWrite(GREENLED_PIN, LOW);
    Serial.println("GREEN LED: OFF");
    vTaskDelay(pdMS_TO_TICKS(2000));

    digitalWrite(GREENLED_PIN, HIGH);
    Serial.println("GREEN LED: ON");
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}