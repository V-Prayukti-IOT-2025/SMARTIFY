#include <SimpleDHT.h>


const char msg_soil_dry[] PROGMEM = "Soil is dry! LED ON (Alert)";
const char msg_soil_wet[] PROGMEM = "Soil is moist. LED OFF";


#define DHT_PIN D4            
#define DHT_TYPE 11           
#define SOIL_SENSOR_PIN D6    
#define LED_PIN D5            


SimpleDHT11 dht11;


ICACHE_FLASH_ATTR float getTemperature() {
    byte temperature = 0;
    dht11.read(DHT_PIN, &temperature, NULL, NULL);
    return (float)temperature;
}


ICACHE_FLASH_ATTR float getHumidity() {
    byte humidity = 0;
    dht11.read(DHT_PIN, NULL, &humidity, NULL);
    return (float)humidity;
}

void setup() {
    Serial.begin(115200);

    
    pinMode(SOIL_SENSOR_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW); 

    Serial.println(F("Smart Irrigation System Initialized..."));
}

void loop() {
    
    int soilStatus = digitalRead(SOIL_SENSOR_PIN);
    float temperature = getTemperature();
    float humidity = getHumidity();

    
    Serial.printf("Soil: %s | Temp: %.1f°C | Humidity: %.1f%%\n", 
                  (soilStatus == HIGH) ? "Dry" : "Wet", 
                  temperature, humidity);

  
    if (soilStatus == HIGH) {  
        Serial.println(FPSTR(msg_soil_dry)); 
        digitalWrite(LED_PIN, HIGH);
    } else {
        Serial.println(FPSTR(msg_soil_wet));
        digitalWrite(LED_PIN, LOW);
    }

    delay(5000); 
}
