
#include "BinaryTree.h"
#include "Commander.h"

int main() {

    cout << "============================================================================" << endl;
    cout << "Hello, you are using a program for working with binary trees" << endl;
    cout << "============================================================================" << endl;

    while (true) {

        cout << "Choose what you would like and enter the number corresponding to the action:" << endl;
        cout << "============================================================================" << endl;
        cout << "1 - Definition of a binary tree" << endl;
        cout << "2 - Create a new binary tree" << endl;
        cout << "3 - Load an existing binary tree" << endl;
        cout << "4 - Exit" << endl;
        cout << "============================================================================" << endl << endl;
        cout << "I command: ";

        string command;
        cin >> command;

        cout << endl;

        if (!execute(command)) {
            break;
        }

    }
}
