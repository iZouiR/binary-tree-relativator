
#ifndef BINARYTREERELATIVATOR_BINARYTREE_H
#define BINARYTREERELATIVATOR_BINARYTREE_H

#include <vector>
#include <map>
#include <iostream>
#include <iomanip>

using namespace std;

class BinaryTree {

    // Nested class for binary tree node representation
    class Node {
    public:
        int id;
        Node *parent;
        Node *first;
        Node *second;
        int value;
        bool isLeft;

        explicit Node(int value, int id) {
            this->id = id;
            this->parent = nullptr;
            this->first = nullptr;
            this->second = nullptr;
            this->value = value;
            this->isLeft = false;
        }
    };

    Node *head;
    int globalID = 0;

    // Slices only nodes belonging to the given level
    vector<Node> getLevel(int level) {
        vector<Node> nodes;
        nodes.push_back(*head);

        int currentLevel = 1;
        if (level == 1) {
            return nodes;
        }
        int counter = 0;
        while (currentLevel != level) {

            for (Node node: nodes) {
                if (node.first != nullptr) {
                    nodes.push_back(*node.first);
                }
                if (node.second != nullptr) {
                    nodes.push_back(*node.second);
                }
                counter++;
            }
            for (; counter != 0; counter--) {
                nodes.erase(nodes.begin(), nodes.begin() + 1);
            }
            currentLevel++;
        }
        return nodes;
    }

    // Splits the given map into halfs
    static vector<multimap<int, int>> getHalfs(multimap<int, int> values) {
        size_t size = values.size();
        auto middleIt = values.begin();
        for (int i = 0; i != size / 2; i++) {
            middleIt++;
        }
        multimap<int, int> half1;
        for (auto it = values.begin(); it != middleIt; it++) {
            half1.insert(make_pair(it->first, it->second));
        }
        multimap<int, int> half2;
        for (auto it = values.end(); it != middleIt; it--) {
            if (it == values.end()) {
                it--;
            }
            if (it == middleIt) {
                break;
            }
            half2.insert(make_pair(it->first, it->second));
        }
        vector<multimap<int, int>> result;
        if (!half1.empty()) {
            result.push_back(half1);
        }
        if (!half2.empty()) {
            result.push_back(half2);
        }
        return result;
    }

public:

    BinaryTree() {
        head = nullptr;
    }

    bool empty() {
        return head == nullptr;
    }

    int add(int value) {
        Node *target = new Node(value, globalID++);
        if (head == nullptr) {
            head = target;
            return target->id;
        }
        Node *node = head;
        while (true) {
            if (target->value > node->value) {
                if (node->second == nullptr) {
                    target->parent = node;
                    node->second = target;
                    return target->id;
                } else {
                    node = node->second;
                }
            } else {
                if (node->first == nullptr) {
                    target->isLeft = true;
                    target->parent = node;
                    node->first = target;
                    return target->id;
                } else {
                    node = node->first;
                }
            }
        }
    }

    Node read(int id) {
        if (head == nullptr) {
            throw exception();
        }
        if (id < 0 || id >= globalID) {
            throw exception();
        }
        int currentLevel = 1;
        vector<Node> nodes = getLevel(currentLevel);
        while (!nodes.empty()) {
            for (Node node: nodes) {
                if (node.id == id) {
                    return node;
                }
            }
            nodes = getLevel(++currentLevel);
        }
        throw exception();
    }

    void remove(int id) {
        if (head->id == id) {
            head = nullptr;
            return;
        }
        Node removeNode = read(id);
        Node *node = head;
        while (true) {
            if (removeNode.value > node->value) {
                if (node->second->id == id) {
                    node->second = nullptr;
                    return;
                } else {
                    node = node->second;
                }
            } else {
                if (node->first->id == id) {
                    node->first = nullptr;
                    return;
                } else {
                    node = node->first;
                }
            }
        }
    }

    // Balances the binary tree, so that perfomance of reading-writing operations increases
    void balance() {
        multimap<int, int> values = getNodes();
        head = nullptr;
        globalID = 0;

        size_t size = values.size();
        auto middleIt = values.begin();
        for (int i = 0; i != size / 2; i++) {
            middleIt++;
        }
        add(middleIt->first);

        vector<multimap<int, int>> halfs = getHalfs(values);
        while (!halfs.empty()) {
            vector<multimap<int, int>> tmpHalfs;
            for (auto half : halfs) {
                size = half.size();
                middleIt = half.begin();
                for (int i = 0; i != size / 2; i++) {
                    middleIt++;
                }
                add(middleIt->first);
                vector<multimap<int, int>> localHalfs = getHalfs(half);
                for (const auto& localHalf : localHalfs) {
                    tmpHalfs.push_back(localHalf);
                }
            }
            halfs = tmpHalfs;
        }
    }

    multimap<int, int> getNodes() {
        multimap<int, int> byValues;
        int currentLevel = 1;
        vector<Node> nodes = getLevel(currentLevel);
        while (!nodes.empty()) {
            for (Node node: nodes) {
                byValues.insert(make_pair(node.value, node.id));
            }
            nodes = getLevel(++currentLevel);
        }
        return byValues;
    }

    // Outputs the binary tree to the console as something like tree
    void treeOutput() {
        cout << endl << endl << endl;
        if (head == nullptr) {
            cout << "EMPTY" << endl << endl << endl;
            return;
        }
        int currentLevel = 1;
        cout << "=====================================================" << endl;
        cout << "LEVEL 1:" << setw(15) << "<" << head->id << "|ROOT|" << head->value << ">" << endl;
        vector<Node> nodes = getLevel(currentLevel);
        while (!getLevel(currentLevel + 1).empty()) {
            cout << "LEVEL " << currentLevel + 1 << ":" << setw(10);
            for (Node node: nodes) {
                cout << "<";
                if (node.first != nullptr) {
                    cout << node.first->id << "|" << node.id << "|" << node.first->value;
                } else {
                    cout << "empty";
                }
                cout << ">=-=<";
                if (node.second != nullptr) {
                    cout << node.second->id << "|" << node.id << "|" << node.second->value;
                } else {
                    cout << "empty";
                }
                cout << "> ";
            }
            cout << endl;
            nodes = getLevel(++currentLevel);
        }
        cout << "=====================================================" << endl << endl << endl;
    }

    // Outputs the binary tree to the console as a table of nodes
    void relativeOutput() {
        cout << endl << endl << endl;
        if (head == nullptr) {
            cout << "EMPTY" << endl << endl << endl;
            return;
        }
        int currentLevel = 1;
        vector<Node> nodes = getLevel(currentLevel);
        cout << "==============================================================" << endl;
        cout << setw(15) << "NODE_ID" << setw(15) << "PARENT_ID" << setw(15) << "VALUE" << setw(15) << "ORIENTATION"
             << endl;
        cout << setw(15) << nodes.at(0).id << setw(15) << "ROOT" << setw(15) << nodes.at(0).value << setw(15) << "ROOT"
             << endl;
        nodes = getLevel(++currentLevel);
        while (!nodes.empty()) {
            for (Node node: nodes) {
                cout << setw(15) << node.id << setw(15) << node.parent->id << setw(15) << node.value << setw(15);
                if (node.isLeft) {
                    cout << "LEFT";
                } else {
                    cout << "RIGHT";
                }
                cout << endl;
            }
            nodes = getLevel(++currentLevel);
        }
        cout << "==============================================================" << endl << endl << endl;
    }
};

#endif //BINARYTREERELATIVATOR_BINARYTREE_H
