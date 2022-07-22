import 'package:flutter/material.dart';

class userA extends StatelessWidget {
  const userA({Key? key}) : super(key: key);



  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Row(
        children: [
          Expanded(child: Container(
            margin: EdgeInsets.fromLTRB(10, 10, 10, 10),
            child: GridView.count(
              crossAxisCount: 3,
              crossAxisSpacing: 10,
              mainAxisSpacing: 10,
              children: [
                SizedBox(
                  child: ElevatedButton(onPressed: (){

                  }, child: Text("item1"),),
                ),
                SizedBox(
                  child: ElevatedButton(onPressed: (){

                  }, child: Text("item2"),),
                ),
                SizedBox(
                  child: ElevatedButton(onPressed: (){

                  }, child: Text("item3"),),
                ),
                SizedBox(
                  child: ElevatedButton(onPressed: (){

                  }, child: Text("item4"),),
                ),
                SizedBox(
                  child: ElevatedButton(onPressed: (){

                  }, child: Text("item5"),),
                ),
                SizedBox(
                  child: ElevatedButton(onPressed: (){

                  }, child: Text("item6"),),
                ),
                SizedBox(
                  child: ElevatedButton(onPressed: (){

                  }, child: Text("item7"),),
                ),
                SizedBox(
                  child: ElevatedButton(onPressed: (){

                  }, child: Text("item8"),),
                ),
                SizedBox(
                  child: ElevatedButton(onPressed: (){

                  }, child: Text("item9"),),
                ),
              ],
                )
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
