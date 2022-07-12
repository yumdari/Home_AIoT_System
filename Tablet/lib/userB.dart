import 'package:flutter/material.dart';
import 'package:tcp_socket_connection/tcp_socket_connection.dart';

final int NUM_BUTTON = 9;

class userB extends StatefulWidget {
  const userB({Key? key}) : super(key: key);

  @override
  State<userB> createState() => _userBState();
}

class _userBState extends State<userB> {


  var buttonState_array = List<bool>.filled(NUM_BUTTON, true);

  int temp = 0;
  int btnCount = 0;
  int btnState = 0;


  TcpSocketConnection socketConnection=TcpSocketConnection("10.10.141.43", 5055);
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
    //socketConnection.sendMessage("MessageIsReceived :D ");
  }


  //starting the connection and listening to the socket asynchronously
  void startConnection() async{
    socketConnection.enableConsolePrint(true);    //use this to see in the console what's happening
   // if(await socketConnection.canConnect(5000, attempts: 3)){   //check if it's possible to connect to the endpoint
      await socketConnection.connect(5000, messageReceived, attempts: 3);
    //}
  }

  bool chkButton(){
    //bool allDisabled = false;
    for(int i = 0; i < NUM_BUTTON; i++){
      if(buttonState_array[i])
        return false;
    }
    return true;
  }

  /* 버튼 누르면 비활성화 */
  void setBtnDisable(int btnIdx){
    //int index = btnIdx - 1;
    btnCount++;
    if(btnCount == 9)
      btnState = 1;
    setState((){
      if(buttonState_array[btnIdx]) {
        buttonState_array[btnIdx] = false;
      }
    });


  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
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
                      child: Text("item1"),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: buttonState_array[1] ? () => setBtnDisable(1) : null,
                      child: Text("item2"),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: buttonState_array[2] ? () => setBtnDisable(2) : null,
                      child: Text("item3"),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: buttonState_array[3] ? () => setBtnDisable(3) : null,
                      child: Text("item4"),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: buttonState_array[4] ? () => setBtnDisable(4) : null,
                      child: Text("item5"),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: buttonState_array[5] ? () => setBtnDisable(5) : null,
                      child: Text("item6"),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: buttonState_array[6] ? () => setBtnDisable(6) : null,
                      child: Text("item7"),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: buttonState_array[7] ? () => setBtnDisable(7) : null,
                      child: Text("item8"),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: buttonState_array[8] ? () => setBtnDisable(8) : null,
                      child: Text("item9"),),
                  ),
                ],
              )
          ),
            flex: 7,),
          Expanded(child: Container(
            child: Text('$btnState'),
            color: Colors.yellow,
          ),
            flex: 3,)
        ],
      ),
    );
  }
}
