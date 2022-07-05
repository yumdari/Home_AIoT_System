import 'package:flutter/material.dart';

class userB extends StatefulWidget {
  const userB({Key? key}) : super(key: key);

  @override
  State<userB> createState() => _userBState();
}

class _userBState extends State<userB> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: RaisedButton(
          onPressed: (){
            Navigator.pop(context);
          },
          child: Text('Go back'),
        ),
      ),
    );
  }
}
