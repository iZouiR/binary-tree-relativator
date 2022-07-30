
#ifndef BINARYTREERELATIVATOR_COMMANDER_H
#define BINARYTREERELATIVATOR_COMMANDER_H

#include "FileAccessor.h"
#include <iostream>
#include <string>

using namespace std;

bool execute(const string &command);

void commandFirst();

void commandSecond();

void commandThird();

void processTree(BinaryTree &binaryTree);

bool execute(const string &command) {
    bool operation = false;
    try {
        switch (stoi(command)) {
            case 1: {
                commandFirst();
                operation = true;
                break;
            }
            case 2: {
                commandSecond();
                operation = true;
                break;
            }
            case 3: {
                commandThird();
                operation = true;
                break;
            }
            case 4: {
                cout << "Exit the program..." << endl;
                break;
            }
            default: {
                cout << "What a pity, what a pity, but we don't have such an operation :(" << endl << endl << endl;
                operation = true;
            }
        }
    } catch (exception &) {
        cout << "It was asked to enter a number, and you..." << endl << endl << endl;
        operation = true;
    }
    return operation;
}

void commandFirst() {
    cout << "=============================================================================================" << endl;
    cout << "A binary tree is a hierarchical data structure in which each node has a value" << endl;
    cout << "(it is also the key in this case) and references to the left and right descendant." << endl;
    cout << "The node located at the topmost level (which is not someone's descendant) is called the root." << endl;
    cout << "Nodes that have no descendants (both of whose descendants are NULL) are called leaves." << endl;
    cout << "=============================================================================================" << endl;
    cout << "A binary search tree is a binary tree with additional properties:" << endl;
    cout << "the value of the left child is less than or equals to the value of the parent, " << endl;
    cout << "and the value of the right child is greater than the value of the parent for each node of the tree." << endl;
    cout << "That is, the data in the binary search tree is stored in sorted form." << endl;
    cout << "Each time a new node is inserted or an existing node is deleted, the sorted order of the tree is preserved." << endl;
    cout << "When searching for an element, the desired value is compared with the root." << endl;
    cout << "If the desired is greater than the root, then the search continues in the right descendant of the root," << endl;
    cout << "if less, then in the left, if equal to, then value is found and the search stops." << endl;
    cout << "The definition is taken from habr.com" << endl;
    cout << "=============================================================================================" << endl << endl << endl;
}

void commandSecond() {
    BinaryTree binaryTree;
    cout << "You have created an empty binary tree!" << endl << endl << endl;
    processTree(binaryTree);
}

void commandThird() {
    BinaryTree binaryTree;

    while (true) {
        cout << "Enter the full path to the file containing the binary tree" << endl;
        string pathToBinaryTree;

        try {
            cin >> pathToBinaryTree;
            binaryTree = FileAccessor::loadBinaryTree(pathToBinaryTree);
            break;
        } catch (exception &) {
            cout << "The program could not open this file" << endl << endl << endl;
            return;
        }
    }
    cout << "Binary tree was loaded successfully!" << endl << endl << endl;
    processTree(binaryTree);
}

void processTree(BinaryTree &binaryTree) {
    while (true) {
        cout << "======================================================================" << endl;
        cout << "What would you like to do with a binary tree?" << endl;
        cout << "======================================================================" << endl;
        cout << "1 - Add an element" << endl;
        cout << "2 - Read an element" << endl;
        cout << "3 - Delete an element" << endl;
        cout << "4 - Balance the tree" << endl;
        cout << "5 - Output to the console in the form of a tree" << endl;
        cout << "6 - Output to the console in the form of a table" << endl;
        cout << "7 - Save and exit" << endl;
        cout << "8 - Exit without saving" << endl;
        cout << "======================================================================" << endl << endl;
        cout << "I command: ";

        string input;
        cin >> input;
        try {
            switch (stoi(input)) {
                case 1: {
                    cout << "Enter the number to add" << endl;
                    string value;
                    try {
                        cin >> value;
                        int id = binaryTree.add(stoi(value));
                        cout << "Successfully! The <" << value << "> element has been assigned an id =" << id << endl << endl;
                    } catch (exception &) {
                        cout << "Alas, but you did something wrong" << endl << endl << endl;
                    }
                    break;
                }
                case 2: {
                    cout << "Enter the id of the element you want to read" << endl;
                    string id;
                    try {
                        cin >> id;
                        int value = binaryTree.read(stoi(id)).value;
                        cout << "id = " << id << " matches an element with value = " << value << endl << endl << endl;
                    } catch (exception &) {
                        cout << "I don't think you entered the id correctly" << endl << endl << endl;
                    }
                    break;
                }
                case 3: {
                    cout << "Enter the id of the element you want to delete" << endl;
                    string id;
                    try {
                        cin >> id;
                        binaryTree.remove(stoi(id));
                        cout << "Element with id = " << id << " was removed" << endl << endl << endl;
                    } catch (exception &) {
                        cout << "I don't think you entered the id correctly" << endl << endl << endl;
                    }
                    break;
                }
                case 4: {
                    if (binaryTree.empty()) {
                        cout << "There's nothing to balance" << endl << endl << endl;
                        break;
                    }
                    binaryTree.balance();
                    cout << "The binary tree has been successfully balanced" << endl << endl << endl;
                    break;
                }
                case 5: {
                    binaryTree.treeOutput();
                    break;
                }
                case 6: {
                    binaryTree.relativeOutput();
                    break;
                }
                case 7: {
                    while (true) {
                        cout << "Enter the full path to the file where you want to save the binary tree" << endl;
                        string pathToBinaryTree;
                        try {
                            cin >> pathToBinaryTree;
                            FileAccessor::saveBinaryTree(binaryTree, pathToBinaryTree);
                            cout << "The binary tree was successfully saved at " << pathToBinaryTree << endl
                                 << endl << endl;
                            return;
                        } catch (exception&) {
                            cout << "The program could not save the binary tree at the specified path" << endl << endl << endl;
                            break;
                        }
                    }
                    break;
                }
                case 8: {
                    cout << "Work with the binary tree has been discontinued" << endl << endl << endl;
                    return;
                }
                default: {
                    cout << "The program does not know how to do this yet :(" << endl << endl << endl;
                }
            }
        } catch (exception &) {
            cout << "It was asked to enter a number, and you..." << endl << endl << endl;
        }
    }
}

#endif //BINARYTREERELATIVATOR_COMMANDER_H
