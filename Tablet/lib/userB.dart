import 'package:flutter/material.dart';
import 'package:tcp_socket_connection/tcp_socket_connection.dart';

import 'dart:io';
import 'dart:convert';
import 'dart:async';

final int NUM_BUTTON = 9;

class userB extends StatefulWidget {
  const userB({Key? key}) : super(key: key);

  @override
  State<userB> createState() => _userBState();
}

class _userBState extends State<userB> {


  var buttonState_array = List<bool>.filled(NUM_BUTTON, true);

  int btnCount = 0;
  int btnState = 0;
  List items = ['열쇠', '핸드폰', '우산', '약', '지갑', '없음', '없음', '없음', '없음'];

  //Socket socket;

  TcpSocketConnection socketConnection=TcpSocketConnection("10.10.141.43", 5000);
  //final channel = IOWebSocketChannel.connect('ws://echo.websocket.org');
  String message = "";

  @override
  void initState() {
    super.initState();
    startConnection();
  }

  //receiving and sending back a custom message
  void messageReceived(String msg){
    setState(() {
      message=msg;
    });
  }


  //starting the connection and listening to the socket asynchronously
  void startConnection() async{
    socketConnection.enableConsolePrint(true);    //use this to see in the console what's happening
   // if(await socketConnection.canConnect(5000, attempts: 3)){   //check if it's possible to connect to the endpoint
      await socketConnection.connect(5000, messageReceived, attempts: 3);
    //}
  }

  void startconn() async {
    Socket socket = await Socket.connect('10.10.141.43', 5005);
    print('connected');




    // send hello
    socket.add(utf8.encode('1'));

    // listen to the received data event stream
    socket.listen((List<int> event) {
      print(utf8.decode(event));
    });

    // wait 5 seconds
    await Future.delayed(Duration(seconds: 5));

    // .. and close the socket
    socket.close();
  }

  /*
  bool chkButton(){
    //bool allDisabled = false;
    for(int i = 0; i < NUM_BUTTON; i++){
      if(buttonState_array[i])
        return false;
    }
    return true;
  }
  */

  /* 버튼 누르면 비활성화 */
  void setBtnDisable(int btnIdx){
    //int index = btnIdx - 1;
    btnCount++;
    if(btnCount == 9)
      //btnState = 1;
      //socketConnection.sendMessage('1');
      //socketConnection.sendMessageEOM('1','0');
      startconn();
    setState((){
      if(buttonState_array[btnIdx]) {
        buttonState_array[btnIdx] = false;
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Color.fromRGBO(171, 216, 245, 1.0),
      body: Row(
        children: [
          Expanded(child: Container(
              margin: EdgeInsets.fromLTRB(10, 10, 10, 10),
              child: GridView.count(
                crossAxisCount: 3,
                crossAxisSpacing: 10,
                mainAxisSpacing: 10,
                children: [
                  SizedBox(
                    child: ElevatedButton(onPressed: buttonState_array[0] ? () => setBtnDisable(0) : null,
                      child: Text(items[0], style: TextStyle(fontSize: 75),),
                    style: ElevatedButton.styleFrom(
                        primary: Colors.orangeAccent,
                        shape: RoundedRectangleBorder(
                            borderRadius: BorderRadius.circular(30)
                        )
                    ),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: buttonState_array[1] ? () => setBtnDisable(1) : null,
                      child: Text(items[1], style: TextStyle(fontSize: 75),),
                      style: ElevatedButton.styleFrom(
                          primary: Colors.orangeAccent,
                          shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(30)
                          )
                      ),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: buttonState_array[2] ? () => setBtnDisable(2) : null,
                      child: Text(items[2], style: TextStyle(fontSize: 75),),
                      style: ElevatedButton.styleFrom(
                          primary: Colors.orangeAccent,
                          shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(30)
                          )
                      ),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: buttonState_array[3] ? () => setBtnDisable(3) : null,
                      child: Text(items[3], style: TextStyle(fontSize: 75),),
                      style: ElevatedButton.styleFrom(
                          primary: Colors.orangeAccent,
                          shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(30)
                          )
                      ),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: buttonState_array[4] ? () => setBtnDisable(4) : null,
                      child: Text(items[4], style: TextStyle(fontSize: 75),),
                      style: ElevatedButton.styleFrom(
                          primary: Colors.orangeAccent,
                          shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(30)
                          )
                      ),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: buttonState_array[5] ? () => setBtnDisable(5) : null,
                      child: Text(items[5], style: TextStyle(fontSize: 75),),
                      style: ElevatedButton.styleFrom(
                          primary: Colors.orangeAccent,
                          shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(30)
                          )
                      ),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: buttonState_array[6] ? () => setBtnDisable(6) : null,
                      child: Text(items[6], style: TextStyle(fontSize: 75),),
                      style: ElevatedButton.styleFrom(
                          primary: Colors.orangeAccent,
                          shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(30)
                          )
                      ),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: buttonState_array[7] ? () => setBtnDisable(7) : null,
                      child: Text(items[7], style: TextStyle(fontSize: 75),),
                      style: ElevatedButton.styleFrom(
                          primary: Colors.orangeAccent,
                          shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(30)
                          )
                      ),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: buttonState_array[8] ? () => setBtnDisable(8) : null,
                      child: Text(items[8], style: TextStyle(fontSize: 75),),
                      style: ElevatedButton.styleFrom(
                          primary: Colors.orangeAccent,
                          shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(30)
                          )
                      ),),
                  ),
                ],
              )
          ),
            flex: 7,),
          Expanded(child: Container(
            child: Text('You have received ' + message),
            color: Colors.yellow,
          ),

            flex: 3,)
        ],
      ),
    );
  }
}
