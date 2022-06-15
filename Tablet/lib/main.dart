import 'package:flutter/material.dart';
import 'package:tablet_app/weather.dart';

/* Clock */
import 'package:timer_builder/timer_builder.dart';
import 'package:date_format/date_format.dart';


//import 'package:weather_app';



void main() => runApp(MyApp());

class MyApp extends StatelessWidget {


  @override
  Widget build(BuildContext context) {

    return MaterialApp(
      home: Home(),
    );
  }
}

class Home extends StatelessWidget {

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: Text('Reminder Door'),
        ),
        backgroundColor: Colors.grey,
        body: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            SizedBox(
              height: 200,
              //color: Colors.green,
              //padding: const EdgeInsets.all(6.0),
              child: TimerBuilder.periodic(
                const Duration(seconds: 1),
                builder: (context) {
                  return Text(
                    formatDate(DateTime.now(), [mm, "월  ", dd, "일  ", HH, " : ", nn]),
                    style: const TextStyle(
                      fontSize: 120,
                      fontWeight: FontWeight.w500,
                    ),
                  );
                },
              ),
            ),
            Container(
              child: Weather(),
              height: 100,
              color: Colors.red,
            ),
            Container(
              height: 350,
              color: Colors.blue,
            ),
          ],
        ));
  }
}



