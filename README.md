# Reminder_Door

## 22 IoT SW 공모전 3팀

|이름|역할|
|---|--------|
|염훈|팀장, LiDAR, OpenCV|
|윤건우|부팀장, MCU, Tab & Mobile APP|
|민동재|MCU, Server & DB|
|손혜수|LiDAR, OpenCV|

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
22.07.11(윤건우) 상세페이지 그리드뷰 구현   
22.07.12(윤건우) 버튼 비활성화   
22.07.13(윤건우) 메인페이지, 상세페이지 ElevatedButton 모서리 radius 변경, 소켓 라이브러리 변경 (기존걸로 다시 변경 필요)   
22.07.18(손혜수) opencv 2D 선 검출     
22.07.19(손혜수) opencv image contour morphology 적용     
22.07.19(손혜수) opencv video contour 구현   
22.07.20(손혜수) opencv video floodfill로 색 채우기 구현   
22.07.20(손혜수) opencv video morphology 대신 Trackbar로 기능 구현   

## 기술 스택

| <center>분류</center> |<center>기술 스택</center>|
| :-------------------- | :----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| *Languages & Code Rules*|<img src="https://img.shields.io/badge/C-A8B9CC?style=flat-square&logo=C&logoColor=white"/> <img src="https://img.shields.io/badge/C++-00599C?style=flat-square&logo=C%2B%2B&logoColor=white"/> <img src="https://img.shields.io/badge/Python-3776AB?style=flat-square&logo=Python&logoColor=white"/> <img src="https://img.shields.io/badge/Java-007396?style=flat-square&logo=Java&logoColor=white"/> |
| *MCU & MPU*| <img src="https://img.shields.io/badge/ESP32-E7352C?style=flat-square&logo=Espressif&logoColor=white"/> <img src="https://img.shields.io/badge/Raspberry Pi-A22846?style=flat-square&logo=Raspberry Pi&logoColor=white"/> <img src="https://img.shields.io/badge/Jetson Nano-76B900?style=flat-square&logo=NVIDIA&logoColor=white"/> |
| *Server & DB*|<img src="https://img.shields.io/badge/Apache-D22128?style=flat-square&logo=Apache&logoColor=white"/> <img src="https://img.shields.io/badge/PHP-777BB4?style=flat-square&logo=PHP&logoColor=white"/> <img src="https://img.shields.io/badge/MySQL-4479A1?style=flat-square&logo=MySQL&logoColor=white"/>|
| *VersionControl & CI/CD*| <img src="https://img.shields.io/badge/Git-F05032?style=flat-square&logo=Git&logoColor=white"/> <img src="https://img.shields.io/badge/GitHub-181717?style=flat-square&logo=GitHub&logoColor=white"/>|
| *OS*|<img src="https://img.shields.io/badge/Windows 10-0078D6?style=flat-square&logo=Windows&logoColor=white"/> <img src="https://img.shields.io/badge/Ubuntu 20.04-E95420?style=flat-square&logo=Ubuntu&logoColor=white"/>|
| *Platform & Library*|<img src="https://img.shields.io/badge/ROS Melodic-22314E?style=flat-square&logo=ROS&logoColor=white"/> <img src="https://img.shields.io/badge/OpenCV-5C3EE8?style=flat-square&logo=OpenCV&logoColor=white"/>|
| *Collaboration Tools*|<img src="https://img.shields.io/badge/Google Docs-4285F4?style=flat-square&logo=Google&logoColor=white"/>  <img src="https://img.shields.io/badge/Notion-000000?style=flat-square&logo=Notion&logoColor=white"/>|
