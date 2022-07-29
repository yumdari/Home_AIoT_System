import 'package:flutter/material.dart';
import 'package:flutter_hooks/flutter_hooks.dart';
import 'package:flutter_mjpeg/flutter_mjpeg.dart'; // Fullter widget shows mjpeg stream from URL

class CameraViewer extends HookWidget {
  @override
  Widget build(BuildContext context) {
    final isRunning = useState(true);
    return  Scaffold(
      body: Column(
        children: <Widget>[
          Expanded(
            child: Center(
              child: Mjpeg(
                isLive: isRunning.value,
                error: (context, error, stack) {
                  print(error);
                  print(stack);
                  return Text(error.toString(), style: TextStyle(color: Colors.red));
                },
                stream: 'http://10.10.141.184:8001/?action=stream',
              ),
            ),
          ),
          Row(
            children: <Widget>[
              RaisedButton(
                onPressed: () {
                  isRunning.value = !isRunning.value;
                },
                child: Text('Toggle'),
              )
            ],
          ),
        ],
      ),
    );
  }
}
