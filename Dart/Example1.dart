// https://dartpad.dev/?id
// Created 2024-Jan-12 Friday
// https://www.linkedin.com/learning/flutter-essential-training-build-for-multiple-platforms
void main() {
  for (int i = 0; i < 5; i++) {
    print('hello ${i + 1}');
  }
  
  // 1. Numbers
  int a = 7;
  print(a.isEven);
  
  double b = 5.6;
  print(b);
  
  // 2. Strings
  int count = 5;
  String msg = "I have $count apples";
  print(msg);
  
  // 3. Booleans
  bool isLocationEnabled = false;
  print(isLocationEnabled);
  
  // 4. Lists
  List<String?> bookTitles = ["A1" , "A2", "A3", null];
  print(bookTitles);
  print(bookTitles.length);
  
  // 5. Maps
  Map<int, String?>? employeeList = { 001: "A1", 002: "A2"};
  employeeList.addAll({ 003: null });
  print(employeeList);
  
  // dynamic & var
  dynamic price = 5.5;
  print(price.runtimeType);
  price = "Price!";
  print(price.runtimeType);
  
  var varVariable = 6;
  print(varVariable.runtimeType);
  // varVariable = "varVariable!"; // Can not be changed type again.
  
  printCost(price: 4.0, itemName: "apple");
  
}

void printCost({required double price, String? itemName}) {
  print("The cost of $itemName is $price");
}

int area(length, breadth) => length * breadth;

/*
Here is the output:

hello 1
hello 2
hello 3
hello 4
hello 5
false
5.6
I have 5 apples
false
[A1, A2, A3, null]
4
{1: A1, 2: A2, 3: null}
double
String
int
The cost of apple is 4
*/
