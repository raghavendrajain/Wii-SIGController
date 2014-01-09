#include <iostream>
#include <string>
 
using namespace std;
 
int alert();
 
int main () {
    cout << "Hey!\nAlert! Alert:\n";
    cout << "I'm a C++ program! YAY!\n\n";
    alert();
    cout << "To quit the program, press [ENTER]\n";
    cin.get();
    return 0;
}
 
int alert() {
    string message;
    message = "This is an initialized array with a maximum capacity of 255 characters. Have a nice day!\n\n";
    cout << message << endl;
    return 0;
}