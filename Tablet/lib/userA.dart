import 'package:flutter/material.dart';

class userA extends StatelessWidget {
  const userA({Key? key}) : super(key: key);

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
