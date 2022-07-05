import 'package:flutter/material.dart';

import 'package:geolocator/geolocator.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

import 'package:flutter_svg/flutter_svg.dart';

const apikey = '78875fa7b0b0cad43ec365684ab3eb1b';

class Weather extends StatefulWidget {
  const Weather({Key? key}) : super(key: key);

  @override
  State<Weather> createState() => _WeatherState();
}

class _WeatherState extends State<Weather> {

  double latitude2 = 0;
  double longitude2 = 0;

  String cityName = "";
  //String strWeatherId = "";
  int strWeatherId = 0;
  String iconPath = "svg/sunny.svg"; // 초깃값
  double temp = 0.0;
  int tempInt = 0; // int형으로 변환하기 위한 변수


  /* 페이지 열리면서 바로 실행 */
  @override
  void initState(){
    super.initState();
    getLocation();
  }

  /* 날씨 아이콘 선택 */
  String getWeatherIcon(int str_id){
    //int id = int.parse(str_id);
    int id = str_id;
    if(id < 300) {
      return 'svg/sunny.svg'; //climacon-sun
    } else if(id < 600) {
      return 'svg/rainny.svg'; //climacon-cloud_rain
    } else if(id == 800) {
      return 'svg/sunny.svg'; //climacon-sun
    } else if(id <= 804) {
      return 'svg/cloudy.svg'; //climacon-cloud_sun
    }
    return 'svg/sunny.svg';
  }

  /* 위치 조회 */
  void getLocation() async{
    // LocationPermission permission;
    //permission = await Geolocator.requestPermission();
    try {
      Position position = await Geolocator.getCurrentPosition(
          desiredAccuracy: LocationAccuracy.high);
      latitude2 = position.latitude;
      longitude2 = position.longitude;
    }catch(e) {
      print('Error : Internet connection problem');
    }
    fetchData();
  }

  /* JSON 데이터 수신 및 파싱 */
  void fetchData() async {
    /* API 주소 */
    String urlStr = 'https://api.openweathermap.org/data/2.5/weather?lat=$latitude2&lon=$longitude2'
        '&exclude=current&appid=$apikey&units=metric';
    http.Response response = await http.get(
        Uri.parse(urlStr));

    if (response.statusCode == 200) { /* Connected successfully */
      print(response.body); // 수신받은 JSON 콘솔 출력
      String jsonData = response.body;

      temp = jsonDecode(jsonData)['main']['temp'];
      tempInt = temp.round();
      cityName = jsonDecode(jsonData)['weather'][0]['main'];
      strWeatherId = jsonDecode(jsonData)['weather'][0]['id'];
      iconPath = getWeatherIcon(strWeatherId);
      print(iconPath);
      setState(() { });
    }
    else{
      print(response.statusCode);
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: Row(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            SvgPicture.asset('$iconPath',
              width: 96,
              height: 96,
            ),
            SizedBox(
              width: 50.0,
            ),
            Text(
              '$tempInt'+'℃',
              style: TextStyle(
                  fontSize: 50.0
              ),
            )
          ],

        ),
      ),
    );
  }
}