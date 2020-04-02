#include <iostream>
#include<vector>
#include<queue>
#include<string>
#include<fstream>

using namespace std;

void initializeGraph(int &picks, int &ribs, vector<int> &start, vector<int> &end);

void BFS(int startPick, int &picks, int &ribs, vector<int> &start, vector<int> &end);

int main() {
    vector<int> startVector = {};
    vector<int> endVector = {};
    vector<int> vectorOfPower = {};
    int n = 0, m = 0;
    initializeGraph(n, m, startVector, endVector);
    BFS(1, n, m, startVector, endVector);
    return 0;
}

void initializeGraph(int &picks, int &ribs, vector<int> &start, vector<int> &end) {
    int startNumber, endNumber;

    ifstream inFile;
    inFile.open(R"(C:\Users\alekz29\Documents\myGraph.txt)");

    if (!inFile.is_open()) cout << "It is not open" << endl;
    inFile >> picks >> ribs;

    for (int i = 0; i < ribs; i++) {
        inFile >> startNumber >> endNumber;
        start.push_back(startNumber);
        end.push_back(endNumber);
    }
    inFile.close();
}

void BFS(int startPick, int &picks, int &ribs, vector<int> &start, vector<int> &end) {

    int BFSNumber = 0;
    vector<bool> isBFS(picks);
    vector<int> BFSNumbers(picks);

    for (int i = 0; i < isBFS.size(); i++) {
        isBFS[i] = false;
    }

    queue<int> myQueue;

    myQueue.push(startPick);
    isBFS[startPick - 1] = true;
    BFSNumbers[startPick - 1] = 0;
    BFSNumber++;
    while (!myQueue.empty()) {

        for (int i = 0; i < ribs; i++) {

            if (start[i] == myQueue.front()) {
                if (isBFS[end[i] - 1] == false) {
                    myQueue.push(end[i]);
                    isBFS[end[i] - 1] = true;
                    BFSNumbers[end[i] - 1] = BFSNumbers[start[i]-1]+1;
                }
            }
            if (end[i] == myQueue.front()) {
                if (isBFS[start[i] - 1] == false) {
                    myQueue.push(start[i]);
                    isBFS[start[i] - 1] = true;
                    BFSNumbers[start[i] - 1] = BFSNumbers[end[i]-1]+1;
                }
            }

        }
        myQueue.pop();

    }
}