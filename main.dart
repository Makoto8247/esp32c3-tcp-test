import 'dart:io';

import 'package:flutter/material.dart';

void main() {
  runApp(MainApp());
}

class MainApp extends StatelessWidget {
  MainApp({super.key});

  TcpClient tcpClient = TcpClient();

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        body: Center(
          child: Container(
            child: Column(
              mainAxisSize: MainAxisSize.min,
              children: [
                OutlinedButton(
                  onPressed: () => tcpClient.on_button(),
                  child: Text("ON",
                      style: TextStyle(
                        color: Colors.green,
                      )),
                ),
                OutlinedButton(
                  onPressed: () => tcpClient.off_button(),
                  child: Text("OFF",
                      style: TextStyle(
                        color: Colors.red,
                      )),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}

class TcpClient with ChangeNotifier {
  String host = "192.168.1.10";
  int port = 1337;

  void on_button() {
    Socket.connect(host, port).then((socket) {
      socket.write("TurnOn");
      socket.close();
    });
  }

  void off_button() {
    Socket.connect(host, port).then((socket) {
      socket.write("TurnOff");
      socket.close();
    });
  }
}
