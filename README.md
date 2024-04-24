# **Samurai Combat 2D**

![Samurai Combat 2D](img_source/icon.png)

---
## ***Video Demo :***   
https://www.youtube.com/watch?v=v81oVOWdSM0
---
## ***Table of Contents***
- [**Samurai Combat 2D**](#samurai-combat-2d)
    - [**Video Demo**](#video-demo)
    - [***Table of contents***](#table-of-contents)
    - [**Mô tả game**](#mô-tả-game)
    - [**Cách tải game**](#cách-tải-game)
        - [Yêu cầu](#yêu-cầu)
        - [Cài đặt](#cài-đặt)
    - [**Hướng dẫn chơi**](#hướng-dẫn-chơi)
    - [**Kỹ thuật lập trình**](#kỹ-thuật-lập-trình)
    - [**Ứng dụng**](#ứng-dụng)
    - [**Về đồ họa**](#về-đồ-họa)
    - [**Lời kết**](#lời-kết)
    - [**Nguồn tham khảo**]

## Mô tả game

- Samurai Combat 2D là một trò chơi hành động phiêu lưu 2D nơi bạn sẽ nhập vai thành một samurai chiến đấu chống lại kẻ thù.

## Cách tải game

### Yêu cầu

- Hệ điều hành Windows, macOS hoặc Linux.
- Cài đặt ngôn ngữ lập trình C++ và thư viện SDL2

### Cài đặt

1. Tải xuống theo: `https://github.com/Nezuko1909/SDL_Game_prj/archive/refs/heads/master.zip`
2. Giải nén và chạy trò chơi: chạy scb2d.exe

## Hướng dẫn chơi

Khi vào game, bấm nút start để bắt đầu chơi game. 
Sau đó bấm vào level bạn muốn chơi. Hiện tại có 3 level với độ khó tăng dần theo level

- Bấm ESC để tạm dừng game
- Sử dụng các phím a, d, space để di chuyển nhân vật của bạn.
- Sử dụng phím j, k, l, u để tấn công và tiêu diệt kẻ thù.
- Sử dụng phím h để hồi máu.
- Tránh các đòn tấn công của kẻ thù.

## Kỹ thuật lập trình
### ***Phát triển trên nền tảng:***
- IDE Visual Studio Code
- Ngôn ngữ lập trình C++
- Thư viện SDL2
- Extension của SDL2:
    - SDL_Image: Hỗ trợ xử lý hình ảnh
    - SDL_Mixer: Hỗ trợ xử lý âm thanh
    - SDL_Ttf: Hỗ trợ xử lý fonts chữ

### ***Các kỹ thuật lập trình:***
- Gồm tất cả các kỹ thuật cơ bản:
    - Vòng lặp, cấu trúc rẽ nhánh,...
    - Con trỏ, vector, string, 
    - Class: Tạo, hủy, member function.
    - Đọc viết file: fstream
    - Tách file quản lý code.
    - Kỹ thuật duyệt mảng, sinh số ngẫu nhiên.
    - Thay đổi đường dẫn file theo level và đối tượng
    - Các kỹ thuật, syntax của SDL.
    - Kỹ thuật giải phóng bộ nhớ.
    - Kỹ thuật xử lý thời gian

## Ứng dụng
- Mỗi chức năng của game (Map, Main Player, Threats, Text,...) được xác định bằng 1 đối tượng (class) riêng biệt.
- Xây dựng Tile Map
- Xử lý tương tác map
- Kiểm tra - xử lý va chạm giữa các đối tượng.
- Sử dụng Vector để lưu trữ Threats - kẻ địch.
- Sử dụng các vòng lặp để liên tục xử lý các sự kiện và hiển thị hình ảnh trong game.
- Xử lý FPS - Frame Per Second điều chỉnh tốc độ game

## Về đồ họa
- Các texture trong game được lấy từ:
    - Map [resourcepack](https://resourcepack.net/)
    - Nhân vật và Kẻ địch [crafpix](https://craftpix.net/)
    - Hiệu ứng [NSO](http://ninjaschool.vn/) [crafpix](https://craftpix.net/)
- Bản đồ được xây dựng bằng [Tiled](https://www.mapeditor.org/)

## Lời kết
- Khung ban đầu của code được tham khảo từ [phattrienphanmem123az](https://www.youtube.com/@PhatTrienPhanMem123AZ)
- Cách dùng hàm của SDL được tham khảo từ [lazyfoo](https://lazyfoo.net/tutorials/SDL/)
- Toàn bộ source code sau đều được tôi tự lên ý tưởng lập trình dựa theo khung có sẵn trước đó.

## Nguồn tham khảo
1. https://lazyfoo.net/tutorials/SDL
2. Youtube: Phát Triển Phần Mềm 123A-Z

