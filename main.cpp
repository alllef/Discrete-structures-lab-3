#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <fstream>
#include <iomanip>
#include<Windows.h>

using namespace std;

void initializeGraph(int &picks, int &ribs, vector<int> &start, vector<int> &end);

void BFS(int startPick, int &picks, int &ribs, vector<int> &start, vector<int> &end);

void DFS(int startPick, int &picks, int &ribs, vector<int> &start, vector<int> &end);

void sortRibs(int &picks, int &ribs, vector<int> &start, vector<int> &end);

void printProtocol(int pick, int number, const string &content);

void makeMenu(int &picks, int &ribs, vector<int> &start, vector<int> &end);

int main() {
    SetConsoleOutputCP(CP_UTF8);
    vector<int> startVector = {};
    vector<int> endVector = {};
    vector<int> vectorOfPower = {};
    int n = 0, m = 0;
    initializeGraph(n, m, startVector, endVector);
    sortRibs(n, m, startVector, endVector);
    makeMenu(n, m, startVector, endVector);

    return 0;
}

void initializeGraph(int &picks, int &ribs, vector<int> &start, vector<int> &end) {
    int startNumber, endNumber;

    ifstream inFile;
    inFile.open("myGraph.txt");

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
    string whatInQueue;
    queue<int> myQueue;

    myQueue.push(startPick);
    isBFS[startPick - 1] = true;
    BFSNumbers[startPick - 1] = ++BFSNumber;
    whatInQueue += to_string(startPick);
    printProtocol(startPick, BFSNumber, whatInQueue);
    while (!myQueue.empty()) {

        for (int i = 0; i < ribs; i++) {

            if (start[i] == myQueue.front()) {
                if (isBFS[end[i] - 1] == false) {
                    myQueue.push(end[i]);
                    whatInQueue += to_string(end[i]);
                    isBFS[end[i] - 1] = true;
                    BFSNumbers[end[i] - 1] = ++BFSNumber;
                    printProtocol(end[i], BFSNumber, whatInQueue);
                }
            }
            if (end[i] == myQueue.front()) {
                if (isBFS[start[i] - 1] == false) {
                    myQueue.push(start[i]);
                    whatInQueue += to_string(start[i]);
                    isBFS[start[i] - 1] = true;
                    BFSNumbers[start[i] - 1] = ++BFSNumber;
                    printProtocol(start[i], BFSNumber, whatInQueue);
                }
            }

        }
        whatInQueue.erase(0, 1);

        printProtocol(NULL, NULL, whatInQueue);
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
    string whatInStack;
    stack<int> myStack;

    myStack.push(startPick);
    isDFS[startPick - 1] = true;
    DFSNumbers[startPick - 1] = ++DFSNumber;
    whatInStack += to_string(startPick);
    printProtocol(startPick, DFSNumber, whatInStack);
    while (!myStack.empty()) {
        for (int i = 0; i < ribs; i++) {
            if (start[i] == myStack.top()) {
                if (isDFS[end[i] - 1] == false) {
                    myStack.push(end[i]);
                    whatInStack += to_string(end[i]);
                    DFSNumbers[end[i] - 1] = ++DFSNumber;
                    isDFS[end[i] - 1] = true;
                    printProtocol(end[i], DFSNumber, whatInStack);
                }
            }

            if (end[i] == myStack.top()) {
                if (isDFS[start[i] - 1] == false) {
                    myStack.push(start[i]);
                    whatInStack += to_string(start[i]);
                    DFSNumbers[start[i] - 1] = ++DFSNumber;
                    isDFS[start[i] - 1] = true;
                    printProtocol(start[i], DFSNumber, whatInStack);
                }
            }

        }
        whatInStack.erase(whatInStack.length() - 1);
        printProtocol(NULL, NULL, whatInStack);
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

void printProtocol(int pick, int number, const string &content) {
    cout << setw(10) << pick;
    cout << setw(10) << number;
    cout << setw(10) << content;
    cout << endl;
}

void makeMenu(int &picks, int &ribs, vector<int> &start, vector<int> &end) {

    int startPick;
    bool BFSorDFS;

    cout << "Введіть 0 якщо хочете BFS пошук та введіть 1 якщо хочете DFS-пошук:";
    cin >> BFSorDFS;
    cout << endl;

    cout << "Введіть вершину з якої хочете почати обхід в діапазоні від 1 до " << picks<<":";
    cin >> startPick;
    cout << endl;

    if (!BFSorDFS) {
        cout << setw(20) << "Вершина" << setw(16) << "BFS-номер" << setw(23) << "вміст черги\n";
        BFS(startPick, picks, ribs, start, end);
    }

    if (BFSorDFS) {
        cout << setw(20) << "Вершина" << setw(16) << "DFS-номер" << setw(23) << "вміст стеку\n";
        DFS(startPick, picks, ribs, start, end);
    }

}