import 'package:flutter/material.dart';
import 'package:tcp_socket_connection/tcp_socket_connection.dart';
import 'package:syncfusion_flutter_gauges/gauges.dart';
import 'notification.dart';

class HomeIoT extends StatefulWidget {
  const HomeIoT({Key? key}) : super(key: key);

  @override
  State<HomeIoT> createState() => _HomeIoTState();
}

class _HomeIoTState extends State<HomeIoT> {

  late final NotificationService service;

  double temp = 0; // 온도 값
  double humi = 0; // 습도 값
  double led = 0; // LED 값

  String strFunc = '';
  String strAlert = '0';
  String strHumi = '0';
  String strTemp = '0';

  bool isGasSwitched = false;

  /* TCP/IP 소켓 객체 생성 */
  // 라즈베리파이 서버
  TcpSocketConnection socket = TcpSocketConnection("10.10.141.217", 5000);
  // 내 서버
  //TcpSocketConnection socket = TcpSocketConnection("10.10.141.13", 6000);
  // 집 서버
  //TcpSocketConnection socket = TcpSocketConnection("192.168.22.32", 5000);

  /* 온도 게이지 위젯 생성 */
  Widget _getTempLinearGauge() {
    return Container(
      child: SfLinearGauge(
          minimum: 0.0,
          maximum: 100.0,
          orientation: LinearGaugeOrientation.horizontal,
          majorTickStyle: LinearTickStyle(length: 20),
          axisLabelStyle: TextStyle(fontSize: 12.0, color: Colors.black),
          markerPointers: [
            LinearShapePointer(
              value: temp,
              color: Colors.redAccent,
            )
          ],
          barPointers: [
            LinearBarPointer(value: temp, color: Colors.red, thickness: 15.0)
          ],
          axisTrackStyle: LinearAxisTrackStyle(
              //color: Colors.red,
              edgeStyle: LinearEdgeStyle.bothFlat,
              thickness: 15.0,
              borderColor: Colors.grey)),
      // margin: EdgeInsets.all(10),
    );
  }

  /* 습도 게이지 위젯 생성 */
  Widget _getHumiLinearGauge() {
    return Container(
      child: SfLinearGauge(
          minimum: 0.0,
          maximum: 100.0,
          orientation: LinearGaugeOrientation.horizontal,
          majorTickStyle: LinearTickStyle(length: 20),
          axisLabelStyle: TextStyle(fontSize: 12.0, color: Colors.black),
          markerPointers: [
            LinearShapePointer(
              value: humi,
              color: Colors.blueAccent,
            )
          ],
          barPointers: [
            LinearBarPointer(
                value: humi, color: Colors.blueAccent, thickness: 15.0)
          ],
          axisTrackStyle: LinearAxisTrackStyle(
              //color: Colors.red,
              edgeStyle: LinearEdgeStyle.bothFlat,
              thickness: 15.0,
              borderColor: Colors.grey)),
      // margin: EdgeInsets.all(10),
    );
  }

  /* 페이지 열리면서 바로 실행 */
  @override
  void initState() {
    super.initState();
    connectServer(); // 소켓 서버 연결
    service = NotificationService(); // push 서비스 객체 생성
    service.init(); // push 서비스 초기화
  }

  /* 페이지 종료되면 disconnect */
  @override
  void dispose() {
    // TODO: implement dispose
    super.dispose();
    print('dispose()');
    socket.disconnect(); // 소켓 연결 해제
  }

  /* push 알림 출력 */
  void showNotification(String mode) async {
    String strTitle;
    //mode.compareTo('ddd');
    if(mode[0] == '0') {
      strTitle = '외부인 감지';
    }
    else if (mode[0] == '1') {
      strTitle = '택배상자 감지';
    }
    else if (mode[0] == '2') {
      strTitle = '지문인식 오류';
    }
    else{
      strTitle = 'No Title';
    }
    await service.showNotification(id: 0, title: strTitle, body: '카메라를 확인하세요');
  }

  //receiving and sending back a custom message
  void messageReceived(String msg) {
    setState(() {
      parseMsg(msg);
    });
  }

  //starting the connection and listening to the socket asynchronously
  void connectServer() async {
    socket.enableConsolePrint(
        true); //use this to see in the console what's happening
    if (await socket.canConnect(5000, attempts: 1)) {
      //check if it's possible to connect to the endpoint
      await socket.connect(5000, messageReceived, attempts: 1);
    }
    //sendMessage('APP:1');
  }

  void sendMessage(String msg) {
    socket.sendMessage(msg);
  }

  /* 메시지 파싱 */
  void parseMsg(String msg) {
    /* 접두어 SENSOR */
    if(msg.startsWith('S'))
      {
        var listSensorVal = msg.split('/');
        strFunc = listSensorVal[0];
        print('parsedFunc : ' + strFunc);
        strTemp = listSensorVal[1];
        print('parsedTemp : ' + strTemp);
        strHumi = listSensorVal[2];
        print('parsedHumi : ' + strHumi);
        temp = double.parse(strTemp);
        humi = double.parse(strHumi);

      }
    /* 접두어 ALERT */
    else if(msg.startsWith('A'))
      {
        print('Alert!!');
        var listSensorVal = msg.split('/');
        strAlert = listSensorVal[1];
        showNotification(strAlert);
      }
  }

  String _annotationValueA = '60';
  String _annotationValueB = '60';
  String _annotationValueC = '60';

  double shapePointerValueA = 50;
  double shapePointerValueB = 50;
  double shapePointerValueC = 50;

  int intPointerValueA = 0;
  int intPointerValueB = 0;
  int intPointerValueC = 0;

  /* 게이지 Room A 값 변경 콜백 함수 */
  void handlePointerValueChangedA(double value) {
    setState(() {
      final int _value = value.toInt();
      shapePointerValueA = value;
      _annotationValueA = '$_value';
    });
  }

  /* 게이지 Room B 값 변경 콜백 함수 */
  void handlePointerValueChangedB(double value) {
    setState(() {
      final int _value = value.toInt();
      shapePointerValueB = value;
      _annotationValueB = '$_value';
    });
  }

  /* 게이지 Room C 값 변경 콜백 함수 */
  void handlePointerValueChangedC(double value) {
    setState(() {
      final int _value = value.toInt();
      shapePointerValueC = value;
      _annotationValueC = '$_value';
    });
  }

  /* 게이지 Room A 드래깅 완료 콜백 함수 */
  void handlePointerValueChangedEndA(double value) {
    intPointerValueA = (value * 255 / 100).toInt();
    sendMessage('LED:$intPointerValueA:$intPointerValueB:$intPointerValueC');
  }

  /* 게이지 Room B 드래깅 완료 콜백 함수 */
  void handlePointerValueChangedEndB(double value) {
    intPointerValueB = (value * 255 / 100).toInt();
    sendMessage('LED:$intPointerValueA:$intPointerValueB:$intPointerValueC');
  }

  /* 게이지 Room C 드래깅 완료 콜백 함수 */
  void handlePointerValueChangedEndC(double value) {
    intPointerValueC = (value * 255 / 100).toInt();
    sendMessage('LED:$intPointerValueA:$intPointerValueB:$intPointerValueC');
  }

  @override
  Widget build(BuildContext context) {
    print('HomeIoT build()');
    return Scaffold(
      body: Column(
        children: [
          Column(
            children: [
              const SizedBox(
                // 여백
                height: 20,
              ),
              const Text(
                'Temperature',
                style: TextStyle(fontSize: 30),
              ),
              _getTempLinearGauge(), // 온도 게이지 출력
              const SizedBox(
                // 여백
                height: 25,
              ),
              const Text(
                'Humidity',
                style: TextStyle(fontSize: 30),
              ),
              _getHumiLinearGauge(), // 습도 게이지 출력
            ],
          ),

          /* 여백 */
          const SizedBox(
            height: 25,
          ),

          /* LED 조절 게이지 */
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: [
              /* 게이지 Room A */
              Container(
                width: 250,
                height: 250,
                child: SfRadialGauge(
                  axes: <RadialAxis>[
                    RadialAxis(pointers: <GaugePointer>[
                      RangePointer(
                        value: shapePointerValueA,
                        //onValueChangeStart: handlePointerValueChanged,
                        onValueChangeEnd: handlePointerValueChangedEndA, // 드래깅 끝나면 함수 call
                        onValueChanged: handlePointerValueChangedA, // 게이지 값 변경마다 함수 call
                        enableDragging: true, // 드래깅 값 조정 가능
                      ),
                      MarkerPointer(
                        value: shapePointerValueA,
                        markerWidth: 20,
                        markerHeight: 20,
                        markerType: MarkerType.circle,
                        color: const Color(0xFF00A8B5)
                      )
                    ], annotations: <GaugeAnnotation>[
                      GaugeAnnotation(
                          widget: Column(
                            mainAxisAlignment: MainAxisAlignment.center,
                            children: <Widget>[
                              Text(
                                '$_annotationValueA' + ' %',
                                style: TextStyle(
                                    fontSize: 25,
                                    fontFamily: 'Times',
                                    fontWeight: FontWeight.bold,
                                    color: const Color(0xFF00A8B5)),
                              ),
                              Text(
                                'Room A',
                                style: TextStyle(
                                    fontSize: 25,
                                    fontFamily: 'Times',
                                    fontWeight: FontWeight.bold,
                                    color: const Color(0xFF00A8B5)),
                              )
                            ],
                          ),
                          positionFactor: 0.13,
                          angle: 0)
                    ])
                  ],
                ),
              ),

              /* 게이지 Room B */
              Container(
                width: 250,
                height: 250,
                child: SfRadialGauge(
                  axes: <RadialAxis>[
                    RadialAxis(pointers: <GaugePointer>[
                      RangePointer(
                        value: shapePointerValueB,
                        //onValueChangeStart: handlePointerValueChanged,
                        onValueChangeEnd: handlePointerValueChangedEndB,
                        onValueChanged: handlePointerValueChangedB,
                        enableDragging: true,
                      ),
                      MarkerPointer(
                          value: shapePointerValueB,
                          markerWidth: 20,
                          markerHeight: 20,
                          markerType: MarkerType.circle,
                          color: const Color(0xFF00A8B5)
                      )
                    ], annotations: <GaugeAnnotation>[
                      GaugeAnnotation(
                          widget: Column(
                            mainAxisAlignment: MainAxisAlignment.center,
                            children: <Widget>[
                              Text(
                                '$_annotationValueB' + ' %',
                                style: TextStyle(
                                    fontSize: 25,
                                    fontFamily: 'Times',
                                    fontWeight: FontWeight.bold,
                                    color: const Color(0xFF00A8B5)),
                              ),
                              Text(
                                'Room B',
                                style: TextStyle(
                                    fontSize: 25,
                                    fontFamily: 'Times',
                                    fontWeight: FontWeight.bold,
                                    color: const Color(0xFF00A8B5)),
                              )
                            ],
                          ),
                          positionFactor: 0.13,
                          angle: 0)
                    ])
                  ],
                ),
              ),

              /* 게이지 Room C */
              Container(
                width: 250,
                height: 250,
                child: SfRadialGauge(
                  axes: <RadialAxis>[
                    RadialAxis(pointers: <GaugePointer>[
                      RangePointer(
                        value: shapePointerValueC,
                        //onValueChangeStart: handlePointerValueChanged,
                        onValueChangeEnd: handlePointerValueChangedEndC,
                        onValueChanged: handlePointerValueChangedC,
                        enableDragging: true,
                      ),
                      MarkerPointer(
                          value: shapePointerValueC,
                          markerWidth: 20,
                          markerHeight: 20,
                          markerType: MarkerType.circle,
                          color: const Color(0xFF00A8B5)
                      )
                    ], annotations: <GaugeAnnotation>[
                      GaugeAnnotation(
                          widget: Column(
                            mainAxisAlignment: MainAxisAlignment.center,
                            children: <Widget>[
                              Text(
                                '$_annotationValueC' + ' %',
                                style: TextStyle(
                                    fontSize: 25,
                                    fontFamily: 'Times',
                                    fontWeight: FontWeight.bold,
                                    color: const Color(0xFF00A8B5)),
                              ),
                              Text(
                                'Room C',
                                style: TextStyle(
                                    fontSize: 25,
                                    fontFamily: 'Times',
                                    fontWeight: FontWeight.bold,
                                    color: const Color(0xFF00A8B5)),
                              )
                            ],
                          ),
                          positionFactor: 0.13,
                          angle: 0)
                    ])
                  ],
                ),
              ),
            ],
          ),

          /* 가스 밸브 스위치 위젯 */
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Text(
                'gas valve',
                style: TextStyle(fontSize: 30),
              ),
              Switch(
                  value: isGasSwitched,
                  onChanged: (value) {
                    setState(() {
                      isGasSwitched = value;
                      if (!isGasSwitched) {
                        sendMessage('GAS:0');
                      } else
                        sendMessage('GAS:1');
                    });
                  }),
            ],
          ),/*
          Text(
            'Recevied message : ' +strFunc +'/'+ strTemp + '/' + strHumi,
          ),*/
        ],
      ),
    );
  }
}
