import 'package:flutter/material.dart';
import 'package:tcp_socket_connection/tcp_socket_connection.dart';
import 'package:syncfusion_flutter_gauges/gauges.dart';

class HomeIoT extends StatefulWidget {
  //final TcpSocketConnection socket;
  //final String data;
  const HomeIoT({Key? key}) : super(key: key);


  @override
  State<HomeIoT> createState() => _HomeIoTState();
}

class _HomeIoTState extends State<HomeIoT> {

  String message="00:00";

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
  TcpSocketConnection socket=TcpSocketConnection("10.10.141.217", 5000);

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
            LinearShapePointer(value: temp, color: Colors.blueAccent,)
          ],
          barPointers: [LinearBarPointer(value: temp, color: Colors.red,thickness: 15.0)],
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
            LinearShapePointer(value: humi, color: Colors.blueAccent,)
          ],
          barPointers: [LinearBarPointer(value: humi, color: Colors.blueAccent,thickness: 15.0)],
          axisTrackStyle: LinearAxisTrackStyle(
            //color: Colors.red,
              edgeStyle: LinearEdgeStyle.bothFlat,
              thickness: 15.0,
              borderColor: Colors.grey)),
      // margin: EdgeInsets.all(10),

    );
  }

  /* LED 게이지 위젯 생성 */
  Widget _getLEDRadialGauge() {
    return SfRadialGauge(
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
                    child:  Text(strLed,
                        style: TextStyle(
                            fontSize: 25, fontWeight: FontWeight.bold))),
                angle: 90,
                positionFactor: 0.5)
          ])
        ]);
  }


  /* 페이지 열리면서 바로 실행 */
  @override
  void initState(){
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
  void messageReceived(String msg){

    setState(() {
      parseMsg(msg);
    });
  }

  //starting the connection and listening to the socket asynchronously
  void connectServer() async{
    socket.enableConsolePrint(true);    //use this to see in the console what's happening
    if(await socket.canConnect(5000, attempts: 1)){   //check if it's possible to connect to the endpoint
      await socket.connect(5000, messageReceived, attempts: 1);
    }
    sendMessage('APP:1');
  }

  void sendMessage(String msg){
    socket.sendMessage(msg);
  }

  void parseMsg(String msg){
    var listSensorVal = msg.split('/');

    strTemp = listSensorVal[0];
    print('parsedTemp : ' + strTemp);
    strHumi = listSensorVal[1];
    print('parsedHumi : ' + strHumi);
    //strGasValve = listSensorVal[2];
    //print('parsedGasValve : ' + strGasValve);
    strLed = listSensorVal[2];
    print('LedValue : ' + strLed);
    temp = double.parse(strTemp);
    humi = double.parse(strHumi);
    led = double.parse(strLed);
    isValveClosed = int.parse(strGasValve);
    //isValveClosed == 1 ? isSwitched = false : isSwitched = true;
  }

  @override
  Widget build(BuildContext context) {
    print('HomeIoT build()');
    return Scaffold(
      body: Column(
        children: [
          Column(
            children: [
              Text(
                'Temperature',
                style: TextStyle(fontSize: 30),
              ),
              _getTempLinearGauge(),
              Text(
                  'Humidity',
                style: TextStyle(fontSize: 30),
              ),
              _getHumiLinearGauge(),

              //_getLEDRadialGauge()
            ],
          ),
          Container(
            width: 250,
            height: 250,
            child: SfRadialGauge(
                enableLoadingAnimation: true, animationDuration: 1000,
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
                            child:  Text(strLed,
                                style: TextStyle(
                                    fontSize: 25, fontWeight: FontWeight.bold))),
                        angle: 90,
                        positionFactor: 0.5)
                  ])
                ]),
          ),
          Row(
                mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Text(
                'gas valve',
                style: TextStyle(fontSize: 30),
              ),
              Switch(value: isSwitched, onChanged: (value){setState(() {
                isSwitched = value;
                if(!isSwitched){
                  sendMessage('APP:1');
                }
                else
                  sendMessage('APP:0');
              });
              }),
            ],
          ),

          Text(
            'Recevied message : ' + message + '/' + strTemp + '/' + strHumi + '/' + strLed,
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
