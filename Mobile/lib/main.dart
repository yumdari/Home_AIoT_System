import 'package:flutter/material.dart';
import 'CameraViewer.dart';
import 'HomeIoT.dart';
import 'package:mobile/setting.dart';
import 'DataPage.dart';

import 'package:tcp_socket_connection/tcp_socket_connection.dart';

import 'package:flutter_mjpeg/flutter_mjpeg.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        // This is the theme of your application.
        //
        // Try running your application with "flutter run". You'll see the
        // application has a blue toolbar. Then, without quitting the app, try
        // changing the primarySwatch below to Colors.green and then invoke
        // "hot reload" (press "r" in the console where you ran "flutter run",
        // or simply save your changes to "hot reload" in a Flutter IDE).
        // Notice that the counter didn't reset back to zero; the application
        // is not restarted.
        primarySwatch: Colors.blue,
      ),
      home: const MyHomePage(title: 'Home AIoT'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({Key? key, required this.title}) : super(key: key);

  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  int _currentIndex = 0; // 현재 인덱스

  /* 네비게이션 아이템 선택 시 실행*/
  _onTap(int index) {
    setState(() {
      _currentIndex = index;
    });
  }

  Widget getPage(int index) {
    switch (index) {
      case 0:
        return CameraViewer();
        break;
      case 1:
        return HomeIoT();
        break;
      default:
        return DataPage();
        break;
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      //body: _pages[_currentIndex],
      body: getPage(_currentIndex),
      bottomNavigationBar: BottomNavigationBar(
        backgroundColor: Colors.blue,
        selectedItemColor: Colors.white,
        unselectedItemColor: Colors.white70,
        //iconSize: 40, // font size
        //selectedFontSize: 25, // selected font size
        //unselectedFontSize: 10, // unselected font size
        showUnselectedLabels: false,
        // unselected item label hidden
        currentIndex: _currentIndex,
        //onTap: (index) => setState(() => _currentIndex = index),
        onTap: _onTap,
        items: [
          BottomNavigationBarItem(
            icon: Icon(Icons.camera_alt_rounded),
            label: 'Camera',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.home),
            label: 'HomeIoT',
          ),
          /*
          BottomNavigationBarItem(
            icon: Icon(Icons.add_alert),
            label: 'Test',
          ),
           */
        ],
      ),
    );
  }
}
