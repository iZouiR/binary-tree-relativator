
#ifndef BINARYTREERELATIVATOR_FILEACCESSOR_H
#define BINARYTREERELATIVATOR_FILEACCESSOR_H

#include <fstream>
#include <sstream>

class FileAccessor {

public:
    static BinaryTree loadBinaryTree(const string &pathToBinaryTree) {
        BinaryTree binaryTree;

        ifstream inputStream;
        inputStream.open(pathToBinaryTree);
        if (inputStream.is_open()) {
            multimap<int, int> byId;
            string str;
            while (getline(inputStream, str)) {
                stringstream stream(str);
                string item;
                vector<string> items;
                while (getline(stream, item, ' ')) {
                    items.push_back(item);
                }
                byId.insert(make_pair(stoi(items.at(0)), stoi(items.at(1))));
            }
            for (auto p : byId) {
                binaryTree.add(p.second);
            }
            inputStream.close();

            return binaryTree;
        }
        throw exception();
    }

    static void saveBinaryTree(BinaryTree &binaryTree, const string &pathToBinaryTree) {
        ofstream outputStream;
        outputStream.open(pathToBinaryTree);

        if (outputStream.is_open() & !binaryTree.empty()) {
            multimap<int, int> values = binaryTree.getNodes();
            auto it = values.begin();
            while (it != values.end()) {
                outputStream << it->second << " " << it->first << endl;
                it++;
            }

            outputStream.close();
            return;
        }
        throw exception();
    }
};

#endif //BINARYTREERELATIVATOR_FILEACCESSOR_H
