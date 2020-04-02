#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <fstream>

using namespace std;

void initializeGraph(int &picks, int &ribs, vector<int> &start, vector<int> &end);

void BFS(int startPick, int &picks, int &ribs, vector<int> &start, vector<int> &end);

void DFS(int startPick, int &picks, int &ribs, vector<int> &start, vector<int> &end);

void sortRibs(int &picks, int &ribs, vector<int> &start, vector<int> &end);

int main() {
    vector<int> startVector = {};
    vector<int> endVector = {};
    vector<int> vectorOfPower = {};
    int n = 0, m = 0;
    initializeGraph(n, m, startVector, endVector);
    sortRibs(n, m, startVector, endVector);
    BFS(3, n, m, startVector, endVector);
    DFS(2, n, m, startVector, endVector);

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
    vector<bool> isBFS(picks);
    vector<int> BFSNumbers(picks);
    int BFSNumber = 0;

    for (auto &&i : isBFS) {
        i = false;
    }

    queue<int> myQueue;

    myQueue.push(startPick);
    isBFS[startPick - 1] = true;
    BFSNumbers[startPick - 1] = ++BFSNumber;

    while (!myQueue.empty()) {

        for (int i = 0; i < ribs; i++) {

            if (start[i] == myQueue.front()) {
                if (isBFS[end[i] - 1] == false) {
                    myQueue.push(end[i]);
                    isBFS[end[i] - 1] = true;
                    BFSNumbers[end[i] - 1] = ++BFSNumber;
                }
            }
            if (end[i] == myQueue.front()) {
                if (isBFS[start[i] - 1] == false) {
                    myQueue.push(start[i]);
                    isBFS[start[i] - 1] = true;
                    BFSNumbers[start[i] - 1] = ++BFSNumber;
                }
            }

        }
        myQueue.pop();

    }
}

void DFS(int startPick, int &picks, int &ribs, vector<int> &start, vector<int> &end) {
    vector<bool> isDFS(picks);
    vector<int> DFSNumbers(picks);
    int DFSNumber = 0;
    for (auto &&i : isDFS) {
        i = false;
    }

    stack<int> myStack;
    myStack.push(startPick);
    isDFS[startPick - 1] = true;
    DFSNumbers[startPick - 1] = ++DFSNumber;
    while (!myStack.empty()) {
        for (int i = 0; i < ribs; i++) {
            if (start[i] == myStack.top()) {
                if (isDFS[end[i] - 1] == false) {
                    myStack.push(end[i]);
                    DFSNumbers[end[i] - 1] = ++DFSNumber;
                    isDFS[end[i] - 1] = true;
                }
            }

            if (end[i] == myStack.top()) {
                if (isDFS[start[i] - 1] == false) {
                    myStack.push(start[i]);
                    DFSNumbers[start[i] - 1] = ++DFSNumber;
                    isDFS[start[i] - 1] = true;
                }
            }

        }
        myStack.pop();
    }
}

void sortRibs(int &picks, int &ribs, vector<int> &start, vector<int> &end) {

    int endTmp;
    int startTmp;

    for (int i = 0; i < ribs - 1; i++) {
        for (int j = 0; j < ribs - 1; j++) {
            if ((start[j] + end[j]) > (start[j + 1] + end[j + 1])) {
                startTmp = start[j];
                start[j] = start[j + 1];
                start[j + 1] = startTmp;
                endTmp = end[j];
                end[j] = end[j + 1];
                end[j + 1] = endTmp;
            }
        }
    }
}