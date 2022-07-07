import 'package:flutter/material.dart';
import 'package:tablet_app/userA.dart';
import 'package:tablet_app/userB.dart';
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
        backgroundColor: Colors.white70,
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
              //color: Colors.red,
            ),
            Container(
              child: Row(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: [
                  SizedBox(
                    height: 200,
                    width: 200,
                    child: ElevatedButton(onPressed: (){
                      Navigator.push(
                        context,
                        MaterialPageRoute(builder: (context) => userA()),
                      );
                    }, child: Text("USER1"), style: ElevatedButton.styleFrom(
                      primary: Colors.orange
                    ),)
                  ),
                  SizedBox(
                      height: 200,
                      width: 200,
                      child: ElevatedButton(onPressed: (){
                        Navigator.push(context,
                          MaterialPageRoute(builder: (context)=>userB()),
                        );
                      }, child: Text("USER2"), style: ElevatedButton.styleFrom(
                        primary: Colors.teal
                      ),)
                  ),
                  SizedBox(
                      height: 200,
                      width: 200,
                      child: ElevatedButton(onPressed: (){}, child: Text("USER3"), style: ElevatedButton.styleFrom(
                        primary: Colors.brown
                      ),)
                  ),
                  SizedBox(
                      height: 200,
                      width: 200,
                      child: ElevatedButton(onPressed: (){}, child: Text("USER4"),style: ElevatedButton.styleFrom(
                        primary: Colors.purpleAccent
                      ),)
                  ),
                ],
              ),
              height: 350,
            ),
          ],
        ));
  }
}



