# Home AIoT System

## 기능

<img src="https://user-images.githubusercontent.com/91246353/190538243-c0b08c4c-17d0-461a-9e10-ac68305dc8f5.png" width="500" height="400"/>

## 22 IoT SW 공모전 3팀

|이름|역할|담당|
|---|---|--------|
|염  훈|팀  장|Git, H/W, OpenCV|
|윤건우|부팀장|MCU, APP|
|민동재|팀  원|MCU, Server, DB|
|손혜수|팀  원|OpenCV, Streaming Server|

##  개발 일지
22.06.13(염훈) Ubuntu 20.04 ROS Noetic에서 cyglidar 미지원 -> Ubuntu 18.04 ROS Melodic   
22.06.13(윤건우) geolocator 패키지 -> 현재 위치 좌표 출력, http 패키지 -> json 로딩   
22.06.14(윤건우) API 획득 및 저장   
22.06.14(민동재) SQL SELECT QUERY문 작성 -> MariaDB Motorvalue 최신값 출력   
22.06.15(윤건우) 메인클래스와 날씨 클래스 파일 분할, 날씨 레이아웃   
22.06.16(윤건우) 홈화면 날씨 위젯 출력, 공공데이터 api용 좌표 변환 dart파일 추가, 현재위치 json 데이터 이슈   
22.06.17(윤건우) 현재위치 이슈 해결 및 주석 추가, 도시이름->현재날씨 출력 변경   
22.06.17(민동재) RaspberryPi -> Esp32 소켓 통신   
22.06.27(윤건우) unable to load asset 에러, 변수 초기값 NULL   
22.06.28(윤건우) svg library 에러, svg 파일 교체   
22.06.29(윤건우) 메인 페이지 버튼 구현   
22.06.30(윤건우) 버튼 클릭 시 페이지 전환   
22.07.04(민동재) 서보모터 제어를 위한 insert문 추가   
22.07.04(민동재) 수신값을 활용하여 서보모터 제어   
22.07.07(윤건우) 소켓 기능 구현   
22.07.07(염훈) Image Proccessing용 Camera를 cyglidar -> PLEOMAX로 변경   
22.07.11(윤건우) 상세페이지 그리드뷰 구현   
22.07.12(윤건우) 버튼 비활성화   
22.07.13(윤건우) 메인페이지, 상세페이지 ElevatedButton 모서리 radius 변경, 소켓 라이브러리 변경 (기존걸로 다시 변경 필요)  
22.07.14(민동재) 멀티 쓰레드를 활용한 리눅스 서버 구축    
22.07.18(손혜수) opencv 2D 선 검출     
22.07.19(손혜수) opencv image contour morphology 적용     
22.07.19(손혜수) opencv video contour 구현   
22.07.19(염훈) OpenCV Motion Detection 및 Image Capture 구현   
22.07.20(손혜수) opencv video floodfill로 색 채우기 구현   
22.07.20(손혜수) opencv video morphology 대신 Trackbar로 기능 구현   
22.07.20(염훈) OpenCV Face Recognition 구현   
22.07.21(윤건우) mjpeg stream from url 출력, 하단네비게이션 메뉴 바 생성, 페이지 3개 생성   
22.07.22(염훈) OpenCV Object & Motion & Face Detection 구현   
22.07.25(염훈) OpenCV on Jetson Nano   
22.07.26(염훈) devide code(main, functions, header)   
22.07.29(윤건우) HomeIoT페이지 소켓 통신, parsing, 온습도 gauge 출력   
22.08.12(손혜수) streaming server 구축   
22.09.05(윤건우) HomeIoT 페이지 LED gauge 출력   
22.09.06(윤건우) 각 방 LED 조절 게이지 추가   
22.09.07(윤건우) 가스밸브 조절 전송 메시지 변경 'APP:x' -> 'GAS:x'  
22.09.09(윤건우) 푸쉬 알림 메시지 구현, 소켓 메시지 : ALERT, 온습도 센싱 메시지 : SENSOR/34/77   
22.09.13(윤건우) 푸쉬 기능 구현 완료, ALERT/0 : 외부인 인식, ALERT/1 : 상자 인식, ALERT/2 : 지문인식 에러   
22.09.13(윤건우) CameraViewer 페이지에 yyyy년MM월dd일 hh:mm:ss 형식으로 날짜 및 시간 출력   
22.09.13(윤건우) 스트리밍 영상 위젯 스크린샷 및 이미지 파일 저장   
22.09.13(염훈) Python Face Recognition Streaming   
22.09.14(염훈) Python Socket Programming   
22.09.14(손혜수) box object detection   
22.09.14(염훈) Image Processing Code Integration(Object, Face, Socket, Streaming)   
22.09.15(염훈) send socket message optimization   
22.09.15(민동재) ESP32(도어락), Arduino Pro Mini(Sensor&Actuator), Linux Server(RaspberryPi) 최종 구현   
22.09.15(윤건우) LED 조절 게이지 포인터 생성   
22.09.18(염훈) Directory 정리   

## 기술 스택

| <center>분류</center> |<center>기술 스택</center>|
| :-------------------- | :----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| *Languages & Code Rules*|<img src="https://img.shields.io/badge/C-A8B9CC?style=flat-square&logo=C&logoColor=white"/> <img src="https://img.shields.io/badge/C++-00599C?style=flat-square&logo=C%2B%2B&logoColor=white"/> <img src="https://img.shields.io/badge/Dart-0175C2?style=flat-square&logo=Dart&logoColor=white"/> <img src="https://img.shields.io/badge/Python-3776AB?style=flat-square&logo=Python&logoColor=white"/>|
| *Devices*| <img src="https://img.shields.io/badge/Arduino Pro Mini-00979D?style=flat-square&logo=Arduino&logoColor=white"/> <img src="https://img.shields.io/badge/ESP32-E7352C?style=flat-square&logo=Espressif&logoColor=white"/> <img src="https://img.shields.io/badge/Raspberry Pi 4-A22846?style=flat-square&logo=Raspberry Pi&logoColor=white"/> <img src="https://img.shields.io/badge/Jetson Nano-76B900?style=flat-square&logo=NVIDIA&logoColor=white"/> |
| *Server & DB*|<img src="https://img.shields.io/badge/Apache-D22128?style=flat-square&logo=Apache&logoColor=white"/> <img src="https://img.shields.io/badge/PHP-777BB4?style=flat-square&logo=PHP&logoColor=white"/> <img src="https://img.shields.io/badge/MariaDB-003545?style=flat-square&logo=MariaDB&logoColor=white"/> <img src="https://img.shields.io/badge/Flask-000000?style=flat-square&logo=Flask&logoColor=white"/>|
| *VersionControl & Collaboration Tools*| <img src="https://img.shields.io/badge/Git-F05032?style=flat-square&logo=Git&logoColor=white"/> <img src="https://img.shields.io/badge/GitHub-181717?style=flat-square&logo=GitHub&logoColor=white"/> <img src="https://img.shields.io/badge/Google Docs-4285F4?style=flat-square&logo=Google&logoColor=white"/>  <img src="https://img.shields.io/badge/Notion-000000?style=flat-square&logo=Notion&logoColor=white"/>|
| *OS*|<img src="https://img.shields.io/badge/Windows 10-0078D6?style=flat-square&logo=Windows&logoColor=white"/> <img src="https://img.shields.io/badge/Ubuntu 18.04-E95420?style=flat-square&logo=Ubuntu&logoColor=white"/>|
| *Platform*| <img src="https://img.shields.io/badge/OpenCV-5C3EE8?style=flat-square&logo=OpenCV&logoColor=white"/> <img src="https://img.shields.io/badge/Flutter-02569B?style=flat-square&logo=Flutter&logoColor=white"/>|
