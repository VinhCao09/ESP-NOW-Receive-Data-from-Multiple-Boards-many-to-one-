#include <esp_now.h>
#include <WiFi.h>

// Cấu trúc dữ liệu nhận về
typedef struct {
    int id;
    int dataType;
    float value1;
    float value2;
    float value3;
} DataPacket;

DataPacket receivedData;

// Biến toàn cục để lưu dữ liệu từ các slave
float temperature = 0.0, humidity = 0.0;
float nitrogen = 0.0, phosphorus = 0.0, potassium = 0.0;
bool tempHumUpdated = false, npkUpdated = false;  // Cờ kiểm tra dữ liệu mới

// Hàm callback khi nhận dữ liệu từ ESP-NOW
void onReceive(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
    memcpy(&receivedData, incomingData, sizeof(receivedData));

    Serial.printf("📩 Nhận từ Slave ID %d\n", receivedData.id);
    
    if (receivedData.dataType == 1) {  // Nhiệt độ & Độ ẩm
        temperature = receivedData.value1;
        humidity = receivedData.value2;
        tempHumUpdated = true;  // Đánh dấu dữ liệu mới

    } 
    else if (receivedData.dataType == 2) {  // Dữ liệu NPK
        nitrogen = receivedData.value1;
        phosphorus = receivedData.value2;
        potassium = receivedData.value3;
        npkUpdated = true;  // Đánh dấu dữ liệu mới
    }

    Serial.println("-------------------------");
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("❌ ESP-NOW khởi động thất bại!");
        return;
    }

    esp_now_register_recv_cb(onReceive);
}

void loop() {
    if (tempHumUpdated) {
        Serial.println("🔥 [Dữ liệu mới] Cập nhật nhiệt độ & độ ẩm!");
        tempHumUpdated = false;  // Reset cờ sau khi xử lý
    }

    if (npkUpdated) {
        Serial.println("🔥 [Dữ liệu mới] Cập nhật NPK!");
        npkUpdated = false;  // Reset cờ sau khi xử lý
    }
        Serial.printf("🌱 NPK - Nitrogen: %.2f\n", nitrogen);
        Serial.printf("🌱 NPK - Phosphorus: %.2f\n", phosphorus);
        Serial.printf("🌱 NPK - Potassium: %.2f\n", potassium);
        Serial.printf("🌡️ Nhiệt độ: %.2f°C\n", temperature);
        Serial.printf("💧 Độ ẩm: %.2f%%\n", humidity);
        
    delay(2000);  // Kiểm tra dữ liệu mỗi 2 giây
}
