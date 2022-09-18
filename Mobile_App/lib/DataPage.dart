import 'package:flutter/material.dart';
import 'package:flutter_local_notifications/flutter_local_notifications.dart';
import 'notification.dart';

class DataPage extends StatefulWidget {
  const DataPage({Key? key}) : super(key: key);

  @override
  State<DataPage> createState() => _DataPageState();
}

class _DataPageState extends State<DataPage> {
  late final NotificationService service;
  /* 페이지 열리면서 바로 실행 */
  @override
  void initState() {
    super.initState();
    service = NotificationService();
    service.init();
    print('Entered DataPage');
    //var initSettingsAndroid = AndroidInitializationSettings('@mipmap/ic_launcher');
    //var initSettingsIos = IOSInitializationSettings();
    //var initializationSettings = InitializationSettings(android : initSettingsAndroid, iOS: initSettingsIos);
  }

  @override
  Widget build(BuildContext context) {
    return Container(
        child: ElevatedButton(onPressed: () async {
          await service.showNotification(id: 0, title: 'Notification Title', body: 'Somebody');
        }, child: Text('button'),),
    );
  }
}
