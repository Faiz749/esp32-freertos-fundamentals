TimerHandle_t systemTimer;
TaskHandle_t statusTaskHandle;

void systemTimerCallBack(TimerHandle_t xtimer);
void statusTask(void *paraneter);
void monitorTask(void *parameter);

void setup(){
  Serial.begin(115200);
  systemTimer = xTimerCreate("System Timer",pdMS_TO_TICKS(2000),pdTRUE,NULL,systemTimerCallBack);
  if(systemTimer == NULL){
    Serial.println("System Timer Creation Failed.....");
    return;
  }
  xTimerStart(systemTimer,0);
  xTaskCreatePinnedToCore(statusTask,"Status Task",2048,NULL,1,&statusTaskHandle,1);
  xTaskCreatePinnedToCore(monitorTask,"Monitor Task",2048,NULL,1,NULL,1);
}

void loop(){
}

void systemTimerCallBack(TimerHandle_t xtimer){
  Serial.println("System Check");
}

void statusTask(void *paraneter){
  while(true){
    ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
    Serial.println("Status Check Received");
  }
}

void monitorTask(void *parameter){
  while(true){
    vTaskDelay(pdMS_TO_TICKS(5000));
    Serial.println("Monitor Triggered");
    xTaskNotifyGive(statusTaskHandle);
  }
}


