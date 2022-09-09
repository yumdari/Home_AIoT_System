import 'package:flutter/material.dart';
import 'package:tcp_socket_connection/tcp_socket_connection.dart';
import 'package:syncfusion_flutter_gauges/gauges.dart';

class HomeIoT extends StatefulWidget {
  const HomeIoT({Key? key}) : super(key: key);

  @override
  State<HomeIoT> createState() => _HomeIoTState();
}

class _HomeIoTState extends State<HomeIoT> {
  String message = "00:00";

  double temp = 0;
  double humi = 0;
  double led = 0;
  int isValveClosed = 0;

  
  String strHumi = '0';
  String strTemp = '0';
  String strGasValve = '0';
  String strLed = '0';

  bool isSwitched = false;

  /*
  Widget _getGauge(bool whichGauge) {
    if (whichGauge) {
      return _getTempLinearGauge();
    } else {
      return _getHumiLinearGauge();
    }
  }
   */

  /* TCP/IP 소켓 객체 생성 */
  // 라즈베리파이 서버
  //TcpSocketConnection socket = TcpSocketConnection("10.10.141.217", 5000);
  // 내 서버
  //TcpSocketConnection socket = TcpSocketConnection("10.10.141.13", 6000);
  // 집 서버
  TcpSocketConnection socket = TcpSocketConnection("192.168.22.32", 5000);

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
    connectServer();
  }

  /* 페이지 종료되면 disconnect */
  @override
  void dispose() {
    // TODO: implement dispose
    super.dispose();
    print('dispose()');
    socket.disconnect();
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
    var listSensorVal = msg.split('/');
    strTemp = listSensorVal[0];
    print('parsedTemp : ' + strTemp);
    strHumi = listSensorVal[1];
    print('parsedHumi : ' + strHumi);
    strLed = listSensorVal[2];
    print('LedValue : ' + strLed);

    temp = double.parse(strTemp);
    humi = double.parse(strHumi);
    led = double.parse(strLed);
    //isValveClosed = int.parse(strGasValve);
    //isValveClosed == 1 ? isSwitched = false : isSwitched = true;
  }

  void sendLedValue(double value) {
    print('gauge value : ' + value.toString());
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

  void handlePointerValueChangedA(double value) {
    setState(() {
      //print('value : ' + value.toString());
      final int _value = value.toInt();
      shapePointerValueA = value;

      //sendMessage('LED:'+intPointerValue.toString()+'127:127');
      _annotationValueA = '$_value';
    });
  }

  void handlePointerValueChangedB(double value) {
    setState(() {
      //print('value : ' + value.toString());
      final int _value = value.toInt();
      shapePointerValueB = value;

      //sendMessage('LED:'+intPointerValue.toString()+'127:127');
      _annotationValueB = '$_value';
    });
  }

  void handlePointerValueChangedC(double value) {
    setState(() {
      //print('value : ' + value.toString());
      final int _value = value.toInt();
      shapePointerValueC = value;

      //sendMessage('LED:'+intPointerValue.toString()+'127:127');
      _annotationValueC = '$_value';
    });
  }

  void handlePointerValueChangedEndA(double value) {
    intPointerValueA = (value * 255 / 100).toInt();
    //print('LED:'+intPointerValue.toString()+':127:127');
    sendMessage('LED:' +
        intPointerValueA.toString() +
        ':' +
        intPointerValueB.toString() +
        ':' +
        intPointerValueC.toString());
  }

  void handlePointerValueChangedEndB(double value) {
    intPointerValueB = (value * 255 / 100).toInt();
    //print('LED:'+intPointerValue.toString()+':127:127');
    sendMessage('LED:' +
        intPointerValueA.toString() +
        ':' +
        intPointerValueB.toString() +
        ':' +
        intPointerValueC.toString());
  }

  void handlePointerValueChangedEndC(double value) {
    intPointerValueC = (value * 255 / 100).toInt();
    //print('LED:'+intPointerValue.toString()+':127:127');
    sendMessage('LED:' +
        intPointerValueA.toString() +
        ':' +
        intPointerValueB.toString() +
        ':' +
        intPointerValueC.toString());
  }

  @override
  Widget build(BuildContext context) {
    print('HomeIoT build()');
    return Scaffold(
      body: Column(
        children: [
          Column(
            children: [
              SizedBox(
                // 여백
                height: 20,
              ),
              Text(
                'Temperature',
                style: TextStyle(fontSize: 30),
              ),
              _getTempLinearGauge(), // 온도 게이지 출력
              SizedBox(
                // 여백
                height: 25,
              ),
              Text(
                'Humidity',
                style: TextStyle(fontSize: 30),
              ),
              _getHumiLinearGauge(), // 습도 게이지 출력
            ],
          ),

          /* 여백 */
          SizedBox(
            height: 25,
          ),
          /* LED 조절 게이지 */
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: [
              Container(
                width: 250,
                height: 250,
                child: SfRadialGauge(
                  axes: <RadialAxis>[
                    RadialAxis(pointers: <GaugePointer>[
                      RangePointer(
                        value: shapePointerValueA,
                        //onValueChangeStart: handlePointerValueChanged,
                        onValueChangeEnd: handlePointerValueChangedEndA,
                        onValueChanged: handlePointerValueChangedA,
                        enableDragging: true,
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

          /* LED 게이지 출력 */
          /*
          Container(
            width: 250,
            height: 250,
            child: SfRadialGauge(
                enableLoadingAnimation: true,
                animationDuration: 1000,
                title: GaugeTitle(
                    text: 'LED Value',
                    textStyle:
                        //const TextStyle(fontSize: 30.0, fontWeight: FontWeight.bold)),
                        const TextStyle(fontSize: 30.0)),
                axes: <RadialAxis>[
                  RadialAxis(minimum: 0, maximum: 255, ranges: <GaugeRange>[
                    GaugeRange(
                        startValue: 0,
                        endValue: 100,
                        color: Colors.green,
                        startWidth: 10,
                        endWidth: 10),
                    GaugeRange(
                        startValue: 100,
                        endValue: 200,
                        color: Colors.orange,
                        startWidth: 10,
                        endWidth: 10),
                    GaugeRange(
                        startValue: 200,
                        endValue: 255,
                        color: Colors.red,
                        startWidth: 10,
                        endWidth: 10)
                  ], pointers: <GaugePointer>[
                    NeedlePointer(value: led)
                  ], annotations: <GaugeAnnotation>[
                    GaugeAnnotation(
                        widget: Container(
                            child: Text(strLed,
                                style: TextStyle(
                                    fontSize: 25,
                                    fontWeight: FontWeight.bold))),
                        angle: 90,
                        positionFactor: 0.5)
                  ])
                ]),
          ),

           */

          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Text(
                'gas valve',
                style: TextStyle(fontSize: 30),
              ),
              Switch(
                  value: isSwitched,
                  onChanged: (value) {
                    setState(() {
                      isSwitched = value;
                      if (!isSwitched) {
                        sendMessage('GAS:0');
                      } else
                        sendMessage('GAS:1');
                    });
                  }),
            ],
          ),
          Text(
            'Recevied message : ' + strTemp + '/' + strHumi + '/' + strLed,
          ),
          /*
          Text('temp : ' + strTemp,
          ),
          Text('humi : ' + strHumi,
          ),
          Text('LED : ' + strLed,
          ),
           */
          //ElevatedButton(onPressed: (){sendMessage('APP:1');}, child: Text('Send')),
        ],
      ),
    );
  }
}
