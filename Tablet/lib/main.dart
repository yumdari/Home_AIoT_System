import 'package:flutter/material.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget{
  @override
  Widget build(BuildContext context){
    return MaterialApp(
      home: Home(),
    );
  }
}

class Home extends StatelessWidget{
  @override
  Widget build(BuildContext context){
    return Scaffold(
      appBar: AppBar(
        title: Text('Reminder Door'),
      ),
      backgroundColor: Colors.grey,
      body: Column(
        children: [
          Container(
            height: 200,
            color: Colors.green,
          ),
          Container(
            height: 100,
            color: Colors.red,
          ),
          Container(
            height: 350,
            color: Colors.blue,
          ),
        ],
      )
    );
  }
}