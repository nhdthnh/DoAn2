# DoAn2
Chương 4: Kết quả đánh giá
4.1. Kết quả mô hình thi công
![image](https://github.com/nhdthnh/DoAn2/assets/114224704/baf9e51c-892a-4153-9f03-6a2afe90db49)
Hình 4. 1. Thiết kế PCB
 ![image](https://github.com/nhdthnh/DoAn2/assets/114224704/580823f0-3bc8-4d87-8947-570eaacb97fd)
Hình 4. 2. Phần cứng hệ thống
4.2. Hoạt động của hệ thống
Để có thể kết nối wifi mới, vào cài đặt và chọn kết nối vào wifi có tên là “AutoConnectAP”
 ![image](https://github.com/nhdthnh/DoAn2/assets/114224704/db25bc7f-8496-491c-9da7-64ca6816c24a)

Hình 4. 3. Kết nối tới wifi hệ thống
Sau khi chọn, vào trình duyệt nhập địa chỉ 192.168.4.1 để hiển thị giao diện lựa chọn wifi để kết nối. Sau đó chọn Configure Wifi và thực hiện chọn 1 wifi để kết nối. Nhập đúng mật khẩu và đợi khi màn hình hiển thị lại. Sau khi kết nối thành công wifi “AutoConnectAP” cũng sẽ không còn và tự động thoát ra khỏi trang web chọn wifi.
 ![image](https://github.com/nhdthnh/DoAn2/assets/114224704/bdd3cb49-e30b-4f62-baed-94a12c96fb05)

Hình 4. 4. Thực hiện nhập mật khẩu

Để có thể chọn 1 wifi khác có thể nhấn nút Reset trên phần cứng  , và thực hiện nhập mật khẩu wifi như các bước trên.
Nút SW trên phần cứng   dùng để chuyển màn hình hiển thị thời gian và hiển thị giá trị các cảm biến. 
2 nút RELAY1 và RELAY2   dùng để kích hoạt các thiết bị bơm và quạt. Các nút nhấn bật tắt các thiết bị cũng sẽ được đồng bộ với 2 nút nhấn   trong app Blynk và ngược lại. 
 ![image](https://github.com/nhdthnh/DoAn2/assets/114224704/f350b074-0986-4904-9643-55153fd71f7d)

Hình 4. 5. LCD hiển thị khi chưa kết nối
Hệ thông sử dụng thư viện RTC (Read Time Clock) để sử dụng internet cập nhập giờ trực tiếp theo múi giờ hiển thị lên LCD ở tác vụ thứ nhất được thực hiện ở core 1. 
 ![image](https://github.com/nhdthnh/DoAn2/assets/114224704/3ca0821e-5a47-4aca-bba5-357a6aed798f)

Hình 4. 6. LCD hiển thị ngày và giờ
Các giá trị của cảm biến được cập nhập và hiển thị lên LCD ở tác vụ 2 thực hiện ở core 2.
 ![image](https://github.com/nhdthnh/DoAn2/assets/114224704/1cdb9132-3282-43f8-b1b5-0a8ca400829e)

Hình 4. 7. LCD hiển thị giá trị các cảm biến
Khi hệ thống phát hiện khí gas, hệ thống sẽ gửi thông báo về điện thoại qua Blynk
 ![image](https://github.com/nhdthnh/DoAn2/assets/114224704/fa0a3038-181c-4645-ac3b-de31101a50ac)

Hình 4. 8. Cảnh báo khi có khí gas rò rỉ
Khi hệ thống phát hiện có hỏa hoạn, hệ thống cũng sẽ gửi thông báo về điện thoại đồng thời kích hoạt máy bơm chữa cháy và máy bơm chỉ có thể tắt thủ công hoặc tắt từ xa qua Blynk để đảm bảo có thể dập tắt hỏa hoạn triệt để.
![image](https://github.com/nhdthnh/DoAn2/assets/114224704/e9bf2b69-d7fa-4aab-9a37-3c80d1d06069)


Hình 4. 9. Cảnh báo khi có hỏa hoạn
Máy bơm chữa cháy và quạt thông gió cũng có thể điều khiển thủ công qua điện thoại hoặc nút nhấn trên hệ thống. Khi sử dụng nút nhấn thì hệ thống cũng sẽ tự đồng bộ trạng thái giá trị của thiết bị với ứng dụng điện thoại. 
 ![image](https://github.com/nhdthnh/DoAn2/assets/114224704/dc9bc0b9-7347-4757-b0d9-b90620f88799)

Hình 4. 10. Điều khiển máy bơm chữa cháy
 ![image](https://github.com/nhdthnh/DoAn2/assets/114224704/23148eb3-5499-4039-909b-de89af94acda)


