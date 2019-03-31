/*
David Roberts - 10095527
CPSC 457 - Assignment 4
Q2 - Deadlock Detection
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <algorithm>

using namespace std;

int maxSize = 1000000;
int ** graph = new int*[maxSize];

bool checkNode(int size, int side) {
    int outgoing = 0;
    if (side == 0){
        outgoing = 1;
    }

    bool deleted = false;
    for(int leftcheck = 0; leftcheck < size; leftcheck++){
        int isOut = 0;
        if (graph[leftcheck][1] != -1) {
            for(int checkones = 0; checkones < size; checkones++){
                if ((graph[leftcheck][side] == graph[checkones][side]) && (graph[checkones][1] == outgoing)){
                    isOut++;
                }
            }
            if (isOut == 0) {
                for(int del = 0; del < size; del++){
                    if (graph[leftcheck][side] == graph[del][side]){
                        graph[del][1] = -1;
                    }
                }
            deleted = true;
            break;
            }
        }
    }
    return deleted;
}


int main(){
    for (int i = 0; i < maxSize; i++){
        graph[i] = new int[3];
        graph[i][1] = -1;
    }

    string edge;
    while (1) {
        int lines = 0;
        //cout << "set graph to 0" << endl;
        bool takingInput = true;
        while (takingInput){
            getline(cin, edge);
            if (cin.eof()) {
               // cout << "eof detected"<<endl;
                takingInput = false;
            }
            //cout << edge << endl;
            stringstream ss(edge);
            if ((edge.find('#') != string::npos) || (!takingInput)){
                //cout << "made it to algorithm" << endl;
                bool procStatus = true;
                bool resStatus = true;
                while (procStatus || resStatus){
                    procStatus = checkNode(lines, 0);
		    resStatus = checkNode(lines, 2);
                }
                //for (int i = 0; i < lines; i++) {
                //    cout << graph[i][0] << " " << graph[i][1] << " " << graph[i][2] << endl;
                //}
                int deadlockMax[lines];
                int nextValue = 0;
                for (int i = 0; i < lines; i++){
                    //cout << graph[i][0] << " " << graph[i][1] << " " << graph[i][2] << endl;
                    bool duplicate = false;
                    if ((graph[i][1] == 1) || (graph[i][1] == 0)) {
                        for (int j = nextValue; j >= 0; j--) {
                            if (deadlockMax[j] == graph[i][0]) {
                                duplicate = true;
                            }
                        }
                        if (!duplicate) {
                            deadlockMax[nextValue] = graph[i][0];
                            nextValue++;
                            //cout << "not duplicate: " << nextValue-1 << endl;
                        }
                    }
                }
                lines = 0;

                cout << "Deadlocked processes: ";
                if (nextValue != 0) {
                    int deadlockActual[nextValue];
                    for (int j = 0; j < nextValue; j++) {
                        deadlockActual[j] = deadlockMax[j];
                    }
                    int n = sizeof(deadlockActual)/sizeof(deadlockActual[0]);
                    sort(deadlockActual, deadlockActual+n);
                    for (int k = 0; k < nextValue; k++){
                        cout << deadlockActual[k] << " ";
                    }
                }
                else {
                    cout << "none";
                }
                cout << endl;
            }
            else {
                string left;
                string middle;
                string right;
                ss >> left >> middle >> right;

                int proc = stoi(left);
                int res = stoi(right);
                int dir;
                if (middle == "<-") {
                    dir = 0;
                }
                else {
                    dir = 1;
                }
                graph[lines][0] = proc;
                graph[lines][1] = dir;
                graph[lines][2] = res;

                lines++;
            }
        }
        break;
    }
    return 0;
}

