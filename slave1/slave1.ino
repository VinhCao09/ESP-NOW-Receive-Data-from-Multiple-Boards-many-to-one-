#include <esp_now.h>
#include <WiFi.h>

// Địa chỉ MAC của ESP32 Master (CẦN ĐÚNG ĐỊA CHỈ)
uint8_t masterAddress[] = {0x24, 0x0A, 0xC4, 0x45, 0x88, 0xBC};

// Cấu trúc dữ liệu gửi đi
typedef struct {
    int id;          // ID thiết bị
    int dataType;    // Loại dữ liệu: 1 = Nhiệt độ & Độ ẩm
    float value1;    // Nhiệt độ
    float value2;    // Độ ẩm
    float value3;    // Không dùng
} DataPacket;

DataPacket dataToSend;

// Callback khi gửi xong
void onSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "✅ Gửi thành công" : "❌ Gửi thất bại");
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("❌ ESP-NOW khởi động thất bại!");
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
    dataToSend.id = 1;       // ID của bo này (Bo 1)
    dataToSend.dataType = 1; // Loại dữ liệu: 1 = Nhiệt độ & Độ ẩm
    dataToSend.value1 = random(20, 35);  // Giả lập Nhiệt độ (°C)
    dataToSend.value2 = random(40, 90);  // Giả lập Độ ẩm (%)
    dataToSend.value3 = 0;   // Không dùng

    esp_err_t result = esp_now_send(masterAddress, (uint8_t *)&dataToSend, sizeof(dataToSend));
    if (result == ESP_OK) {
        Serial.println("✅ Gửi dữ liệu thành công");
    } else {
        Serial.printf("❌ Lỗi khi gửi dữ liệu, mã lỗi: %d\n", result);
    }

    delay(5000);
}
