import 'package:flutter/material.dart';

class userA extends StatelessWidget {
  const userA({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Row(
        children: [
          Expanded(child: Container(
            child: Row(
              children: [
                Expanded(child: Container(
                  child: Column(

                    children: [
                      Expanded(child: SizedBox(
                        width: 100,
                        height: 100,
                        child: ElevatedButton(onPressed: (){
                        }, child: Text("USER1"), ),
                        //color: Colors.black54,
                      ),
                      flex: 1,),
                      Expanded(child: Container(
                        color: Colors.amber,
                      ),
                        flex: 1,),
                      Expanded(child: Container(
                        color: Colors.blue,
                      ),
                        flex: 1,)
                    ],
                  ),
                  color: Colors.teal,
                ),
                flex: 1,),
                Expanded(child: Container(
                  child: Column(
                    children: [
                      Expanded(child: Container(
                        color: Colors.purpleAccent,
                      ),
                        flex: 1,),
                      Expanded(child: Container(
                        color: Colors.green,
                      ),
                        flex: 1,),
                      Expanded(child: Container(
                        color: Colors.white,
                      ),
                        flex: 1,)
                    ],
                  ),
                  color: Colors.brown,
                ),
                  flex: 1,),
                Expanded(child: Container(
                  child: Column(
                    children: [
                      Expanded(child: Container(
                        color: Colors.brown,
                      ),
                        flex: 1,),
                      Expanded(child: Container(
                        color: Colors.white12,
                      ),
                        flex: 1,),
                      Expanded(child: Container(
                        color: Colors.tealAccent,
                      ),
                        flex: 1,)
                    ],
                  ),
                  color: Colors.deepOrange,
                ),
                  flex: 1,)

              ],
            ),
            color: Colors.red,
          ),
          flex: 7,),
          Expanded(child: Container(
            color: Colors.yellow,
          ),
          flex: 3,)
        ],
      )
    );
  }
}
