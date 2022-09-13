import 'package:flutter/material.dart';
import 'package:timer_builder/timer_builder.dart';
import 'package:intl/intl.dart';

class Time extends StatelessWidget {
  const Time({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    DateTime now = DateTime.now();
    String formattedDate = DateFormat('kk:mm:ss EEE d MMM').format(now);
    return TimerBuilder.periodic(Duration(seconds: 1), builder: (context){
      return Text("${DateFormat('yyyy년 MM월 dd일 kk:mm:ss').format(DateTime.now())}", style: new TextStyle(fontWeight: FontWeight.bold, fontSize: 30.0),);
    });
    //Text(formattedDate,textAlign: TextAlign.center,style: new TextStyle(fontWeight: FontWeight.bold,fontSize: 25.0),),
  }
}
