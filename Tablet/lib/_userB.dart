import 'package:flutter/material.dart';
import 'package:tcp_socket_connection/tcp_socket_connection.dart';

class userB extends StatefulWidget {
  const userB({Key? key}) : super(key: key);

  @override
  State<userB> createState() => _userBState();
}

class _userBState extends State<userB> {

  var buttonState_array = List<int>.filled(9, 0);

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

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          crossAxisAlignment: CrossAxisAlignment.center,
        children: [
          SizedBox(
            child: RaisedButton(
              onPressed: (){
                Navigator.pop(context);
              },
              child: Text('Go back'),
            ),
          ),
          SizedBox(
            child: RaisedButton(
              onPressed: (){
                socketConnection.sendMessage('hello world');
              },
              child: Text('send'),
            ),
          ),
          SizedBox(
            child: Text(
              'You have received ' + message,
            ),
          )
        ],
      ),
    );
  }
}
