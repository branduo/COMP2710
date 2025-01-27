/*
 * Author: Brandon Duong
 * AU ID: bhd0014
 * Class: COMP2710
 * Filename: project3_Duong_bhd0014.cpp
 * Compile source code with g++.
 * I used Dr. Li's hints to write my code. I also googled how to use ifstream
 * and ofstream as well as how to use c_str().
 */

#include <fstream>
#include <iostream>

using namespace std;

const int MAX_SIZE = 100;

//function to check if file is valid
bool checkFile(string file) {
    ifstream stream;
    // check if file exists
    stream.open(file.c_str());

    if(stream.fail()) {
        cout << "No file found.";
        return false;
    }

    stream.close();
    return true;
}

//function to count the number of items in an array
int readFile(int inputArray[], ifstream& inStream){
    int index = 0;

    inStream >> inputArray[index];
    while (!inStream.eof()) {
        inStream >> inputArray[index];
        index++;
    }
    return index;
}

void writeFile(int outArray[], int outArraySize) {
    ofstream outStream;
    string outFile;

    cout << "Enter the output file name: ";
    cin >> outFile;

    outStream.open(outFile.c_str());
    for(int i = 0; i < outArraySize; i++) {
        outStream << outArray[i] << "\n";
    }
    outStream.close();

    cout << "*** Please check the new file - " << outFile << " ***\n";
}

int sort(int inputArray1[], int inputArray1_size, int inputArray2[],
         int inputArray2_size, int outputArray[]) {
    bool done = false;
    int j = 0; //Used to track array1 spot
    int k = 0; //Used to track array2 spot
    int outputSize = 0; //Increment every time something is added

    while (!done) {

        if (j < inputArray1_size && k < inputArray2_size) {

            //If Array 1's value is smaller
            if (inputArray1[j] < inputArray2[k]) {
                outputArray[outputSize] = inputArray1[j];
                j++;
            }

            //If Array 2's value is smaller
            else if (inputArray1[j] > inputArray2[k]) {
                outputArray[outputSize] = inputArray2[k];
                k++;
            }

            //If both values from each array are equal
            else {
                outputArray[outputSize] = inputArray1[j];
                j++;
                outputArray[outputSize+1] = inputArray2[k];
                outputSize++;
                k++;
            }
        }

        //Only input array 1 if it has values left
        else if (j < inputArray1_size) {
            outputArray[outputSize] = inputArray1[j];
            j++;
        }

        //Only input array 2 if it has values left
        else if (k < inputArray2_size) {
            outputArray[outputSize] = inputArray2[k];
            k++;
        }

        //All items sorted
        else {
            done = true;
            return outputSize;
        }
        outputSize++;
    }
    return 0;
}

int main() {
    string fileName;

    cout << "*** Welcome to Duong's sorting program ***\n";

    //file 1
    ifstream inStream;
    int Array1[MAX_SIZE];
    int Array1Size;

    cout << "Enter the first input file name: ";
    cin >> fileName;
    checkFile(fileName);

    inStream.open(fileName.c_str());
    //count the number of items in the array
    Array1Size = readFile(Array1, inStream);
    inStream.close();

    cout << "The list of " << Array1Size << " numbers in file " << fileName << " is:\n";
    for (int i = 0; i < Array1Size; i++) {
        cout << Array1[i] << "\n";
    }
    cout <<endl;

    int Array2[MAX_SIZE];
    int Array2Size;

    cout << "Enter the second input file name: ";
    cin >> fileName;
    checkFile(fileName);

    inStream.open(fileName.c_str());
    //count the number of items in the array
    Array2Size = readFile(Array2, inStream);
    inStream.close();

    cout << "The list of " << Array2Size << " numbers in file " << fileName << " is:\n";
    for (int i = 0; i < Array2Size; i++) {
        cout << Array2[i] << "\n";
    }
    cout <<endl;

    int outArray[MAX_SIZE];
    int outArraySize;

    outArraySize = sort(Array1, Array1Size, Array2, Array2Size, outArray);

    cout << "The sorted list of " << outArraySize << " numbers is: ";
    for (int i = 0; i < outArraySize; i++) {
        cout << outArray[i] << " ";
    }
    cout << endl;

    //Write file
    writeFile(outArray, outArraySize);

    cout << "*** Goodbye. ***" << endl;

    return 0;
}



