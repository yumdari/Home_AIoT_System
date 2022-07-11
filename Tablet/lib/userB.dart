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
                    child: ElevatedButton(onPressed: (){
                      if(buttonState_array[0])

                    }, child: Text("item1"),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: (){

                    }, child: Text("item2"),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: (){

                    }, child: Text("item3"),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: (){

                    }, child: Text("item4"),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: (){

                    }, child: Text("item5"),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: (){

                    }, child: Text("item6"),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: (){

                    }, child: Text("item7"),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: (){

                    }, child: Text("item8"),),
                  ),
                  SizedBox(
                    child: ElevatedButton(onPressed: (){

                    }, child: Text("item9"),),
                  ),
                ],
              )
          ),
            flex: 7,),
          Expanded(child: Container(
            color: Colors.yellow,
          ),
            flex: 3,)
        ],
      ),
    );
  }
}
