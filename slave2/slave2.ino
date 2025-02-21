#include <esp_now.h>
#include <WiFi.h>

// Địa chỉ MAC của ESP32 Master
uint8_t masterAddress[] = {0x24, 0x0A, 0xC4, 0x45, 0x88, 0xBC};

// Cấu trúc dữ liệu gửi đi
typedef struct {
    int id;          // ID thiết bị
    int dataType;    // Loại dữ liệu: 2 = Chỉ số NPK
    float value1;    // N - Nitrogen
    float value2;    // P - Phosphorus
    float value3;    // K - Potassium
} DataPacket;

DataPacket dataToSend;

void onSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Gửi thành công" : "Gửi thất bại");
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW khởi động thất bại!");
        return;
    }

    esp_now_register_send_cb(onSent);

    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, masterAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    Serial.println("🔍 Đang kiểm tra danh sách Peer...");
esp_now_peer_info_t peer;
if (esp_now_get_peer(masterAddress, &peer) == ESP_OK) {
    Serial.println("✅ Master đã có trong danh sách Peer!");
} else {
    Serial.println("❌ Master KHÔNG có trong danh sách Peer. Đang thêm lại...");
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("❌ Lỗi khi thêm Master vào danh sách Peer!");
    } else {
        Serial.println("✅ Master đã được thêm vào danh sách Peer.");
    }
}

}

void loop() {
    dataToSend.id = 2;       // ID của bo này
    dataToSend.dataType = 2; // Loại dữ liệu: 2 = NPK
    dataToSend.value1 = random(10, 50); // Giả lập Nitrogen
    dataToSend.value2 = random(5, 30);  // Giả lập Phosphorus
    dataToSend.value3 = random(5, 20);  // Giả lập Potassium

    esp_err_t result = esp_now_send(masterAddress, (uint8_t *)&dataToSend, sizeof(dataToSend));
if (result == ESP_OK) {
    Serial.println("✅ Gửi dữ liệu thành công");
} else {
    Serial.printf("❌ Lỗi khi gửi dữ liệu, mã lỗi: %d\n", result);
}


    delay(5000);
}
