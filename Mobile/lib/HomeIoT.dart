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
  int isValveClosed = 0;

  String strHumi = '0';
  String strTemp = '0';
  String strGasValve = '0';

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
  TcpSocketConnection socket=TcpSocketConnection("10.10.141.13", 6000);

  /* 게이지 위젯 생성 */
  /*
  Widget _getRadialGauge() {
    return SfRadialGauge(
        title: GaugeTitle(
            text: 'Speedometer',
            textStyle:
            const TextStyle(fontSize: 20.0, fontWeight: FontWeight.bold)),
        axes: <RadialAxis>[
          RadialAxis(minimum: 0, maximum: 150, ranges: <GaugeRange>[
            GaugeRange(
                startValue: 0,
                endValue: 50,
                color: Colors.green,
                startWidth: 10,
                endWidth: 10),
            GaugeRange(
                startValue: 50,
                endValue: 100,
                color: Colors.orange,
                startWidth: 10,
                endWidth: 10),
            GaugeRange(
                startValue: 100,
                endValue: 150,
                color: Colors.red,
                startWidth: 10,
                endWidth: 10)
          ], pointers: <GaugePointer>[
            NeedlePointer(value: 90)
          ], annotations: <GaugeAnnotation>[
            GaugeAnnotation(
                widget: Container(
                    child: const Text('90.0',
                        style: TextStyle(
                            fontSize: 25, fontWeight: FontWeight.bold))),
                angle: 90,
                positionFactor: 0.5)
          ])
        ]);
  }
  */

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
    strGasValve = listSensorVal[2];
    print('parsedGasValve : ' + strGasValve);
    temp = double.parse(strTemp);
    humi = double.parse(strHumi);
    isValveClosed = int.parse(strGasValve);
    isValveClosed == 1 ? isSwitched = false : isSwitched = true;

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
              _getHumiLinearGauge()
            ],
          ),
          Row(
            children: [
              Text(
                'gas valve',
                style: TextStyle(fontSize: 30),
              ),
              Switch(value: isSwitched, onChanged: (value){setState(() {isSwitched = value; if(!isSwitched){sendMessage('APP:2');}});}),
            ],
          ),

          Text(
            'Recevied message : ' + message,
          ),
          Text('temp : ' + strTemp,
          ),
          Text('humi : ' + strHumi,
          ),
          ElevatedButton(onPressed: (){sendMessage('APP:1');}, child: Text('Send')),
        ],
      ),
    );
  }
}
