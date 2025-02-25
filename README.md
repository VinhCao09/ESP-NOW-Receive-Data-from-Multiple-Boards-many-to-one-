# ESP-NOW: Receive Data from Multiple Boards many to one

## Mô hình ESP-NOW: 1 Master - Nhiều Slave
### Master: Nhận dữ liệu từ nhiều Slave.
### Slave: Gửi dữ liệu đến Master khi có sự kiện hoặc theo chu kỳ.

## Lưu ý: Xin lưu ý rằng ESP NOW khi dùng chung với thư viện Wifi để kết nối tới Router và giao tiếp với Server sẽ sinh ra lỗi không thể nhận được dữ liệu. Tôi đã nhận dữ liệu và gửi lên Server PHP bằng cách config lại file Sender. Tham khảo link sau: https://randomnerdtutorials.com/esp32-esp-now-wi-fi-web-server/

### 📌 Ưu điểm của ESP-NOW:
✅ Không cần kết nối Wi-Fi.

✅ Truyền dữ liệu nhanh (<10ms), (tốt hơn so với WiFi hoặc MQTT).

✅ Tiêu thụ ít năng lượng.

✅ Kết nối tối đa 20 thiết bị trong mạng.

✅ Bảo mật cao → Hỗ trợ mã hóa AES 128-bit.


### 📌 Nhược điểm: 

❌ Khoảng cách giới hạn (~100m ngoài trời, ~30m trong nhà).

❌ Dữ liệu tối đa mỗi lần gửi là 250 byte.

![images](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2020/01/ESP_NOW_one_slave_multiple_masters.png?w=649&quality=100&strip=all&ssl=1)

Để gửi tin nhắn qua ESP-NOW, bạn cần biết địa chỉ MAC của bo mạch nhận. Mỗi bo mạch có một địa chỉ MAC duy nhất!

Sau khi nạp code check_MACAddress, nhấn nút RST / EN và địa chỉ MAC sẽ được hiển thị trên Serial Monitor.

![images](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2020/04/ESP32-MAC-Address-Serial-Monitor.png?w=601&quality=100&strip=all&ssl=1)

## 🔹 Mở rộng

✅ Có thể thêm nhiều loại dữ liệu bằng cách mở rộng dataType.

✅ Dùng ESP-NOW hai chiều để Master phản hồi lại cho Slave.

✅ Nếu có nhiều Slave, dùng thêm cấu trúc lưu dữ liệu theo ID.
