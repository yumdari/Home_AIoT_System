//import 'dart:html';
import 'dart:typed_data';

import 'package:flutter/material.dart';
import 'package:flutter_hooks/flutter_hooks.dart';
import 'package:flutter_mjpeg/flutter_mjpeg.dart'; // Fullter widget shows mjpeg stream from URL
import 'Time.dart'; // Make present time
import 'package:screenshot/screenshot.dart'; // Capture screen
import 'package:image_gallery_saver/image_gallery_saver.dart'; // Save captured image

import 'package:permission_handler/permission_handler.dart'; // Handling permission

class CameraViewer extends HookWidget {
  String btnName = 'Pause';
  ScreenshotController screenshotController = ScreenshotController();

  @override
  Widget build(BuildContext context) {
    final isRunning = useState(true);
    //controller: screenshotController,

    return Scaffold(
      body: Column(
        children: <Widget>[
          SizedBox(
            height: 25,
          ),

          /* Show present time */
          Time(),

          /* Mjpeg widget is captured */
          Screenshot(
            controller: screenshotController,
            child: Container(
              child: Center(
                child: Mjpeg(
                  isLive: isRunning.value,
                  error: (context, error, stack) {
                    print(error);
                    print(stack);
                    return Text(error.toString(),
                        style: TextStyle(color: Colors.red));
                  },
                  stream: 'http://10.10.141.171:8001/?action=stream',
                ),
              ),
            ),
          ),

          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              ElevatedButton(
                onPressed: () {
                  isRunning.value = !isRunning.value;
                  if (isRunning.value)
                    btnName = 'Pause';
                  else
                    btnName = 'Play';
                },
                child: Text(btnName),
              ),
              SizedBox(width: 30),
              ElevatedButton(
                  onPressed: () async {
                    final image = await screenshotController.capture();
                    if (image == null) return;
                    await saveImage(image);
                  },
                  child: Text('Screenshot'))
            ],
          ),
        ],
      ),
    );
  }

  Future<String> saveImage(Uint8List bytes) async {
    print('saveImage method');
    await [Permission.storage].request();
    final time = DateTime.now()
        .toIso8601String()
        .replaceAll('.', '-')
        .replaceAll(':', '-');
    final name = 'screenshot_$time';
    final result = await ImageGallerySaver.saveImage(bytes, name: name);
    return result['filepath'];
  }
}
