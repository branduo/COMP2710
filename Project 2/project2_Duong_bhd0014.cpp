/*
 * Author: Brandon Duong
 * AU ID: bhd0014
 * Class: COMP2710
 * Filename: project2_Duong_bhd0014.cpp
 * Compile source code with g++.
 * I used Dr. Li's hints to write my code.
 */

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
using namespace std;

//Prototypes
bool at_least_two_alive (bool A_alive, bool B_alive, bool C_alive);
void Aaron_shoots1(bool& B_alive, bool& C_alive);
void Bob_shoots(bool& A_alive, bool& C_alive);
void Charlie_shoots(bool& A_alive, bool& B_alive);
void Aaron_shoots2(bool& B_alive, bool& C_alive);
void pressAnyKey(void);

void test_at_least_two_alive(void);
void test_Aaron_shoots1(void);
void test_Bob_shoots(void);
void test_Charlie_shoots(void);
void test_Aaron_shoots2(void);

//Variables
const int TOTAL_RUNS = 10000;
const int A_ACCURACY = 33;
const int B_ACCURACY = 49;
bool A_alive = true;
bool B_alive = true;
bool C_alive = true;
int A_win1 = 0;
int B_win = 0;
int C_win = 0;
int A_win2 = 0;

//Main Method
int main() {
    cout << "*** Welcome to Duong's Duel Simulator***\n";
    srand(time(0));

    test_at_least_two_alive();
    pressAnyKey();
    test_Aaron_shoots1();
    pressAnyKey();
    test_Bob_shoots();
    pressAnyKey();
    test_Charlie_shoots();
    pressAnyKey();
    test_Aaron_shoots2();
    pressAnyKey();

    //Strategy 1
    cout << "Ready to test strategy 1 (run 10000 times): \n";
    pressAnyKey();

    //Strategy 1's Duel loop
    for (int i = 0; i < TOTAL_RUNS; i++) {

        //Set all to alive for each duel
        A_alive = true;
        B_alive = true;
        C_alive = true;

        while (at_least_two_alive(A_alive, B_alive, C_alive)) {

            if (A_alive == true) {
                Aaron_shoots1(B_alive, C_alive);
            }

            if (B_alive == true) {
                Bob_shoots(A_alive, C_alive);
            }

            if (C_alive == true) {
                Charlie_shoots(A_alive, B_alive);
            }
        }

        //Increment for each win
        if (A_alive == true) {
            A_win1 ++;
        }
        if (B_alive == true) {
            B_win ++;
        }
        if (C_alive == true) {
            C_win ++;
        }
    }

    cout << "Aaron won " << A_win1 << "/10000 duels or " << static_cast<double>(A_win1) / TOTAL_RUNS * 100 << "%\n"

         << "Bob won " << B_win << "/10000 duels or " << static_cast<double>(B_win) / TOTAL_RUNS * 100 << "%\n"

         << "Charlie won " << C_win << "/10000 duels or " << static_cast<double>(C_win) / TOTAL_RUNS * 100 << "%\n"
         << endl;


    //Strategy 2
    cout << "Ready to test strategy 2 (run 10000 times): \n";
    pressAnyKey();

    //Reset Bob's and Charlie's wins
    B_win = 0;
    C_win = 0;

    //Strategy 2's Duel Loop
    for (int i = 0; i < TOTAL_RUNS; i++) {

        //Set all to alive for each duel
        A_alive = true;
        B_alive = true;
        C_alive = true;

        while (at_least_two_alive(A_alive, B_alive, C_alive)) {

            if (A_alive == true) {
                Aaron_shoots2(B_alive, C_alive);
            }
            if (B_alive == true) {
                Bob_shoots(A_alive, C_alive);
            }
            if (C_alive == true) {
                Charlie_shoots(A_alive, B_alive);
            }
        }

        //Increment for each win
        if (A_alive == true) {
            A_win2 ++;
        }
        if (B_alive == true) {
            B_win ++;
        }
        if (C_alive == true) {
            C_win ++;
        }
    }
    cout << "Aaron won " << A_win2 << "/10000 duels or " << static_cast<double>(A_win2) / TOTAL_RUNS * 100 << "%\n"

         << "Bob won " << B_win << "/10000 duels or " << static_cast<double>(B_win) / TOTAL_RUNS * 100 << "%\n"

         << "Charlie won " << C_win << "/10000 duels or " << static_cast<double>(C_win) / TOTAL_RUNS * 100 << "%\n"
         << endl;

    //Determine if Strategy 1 or 2 is better
    if (A_win1 > A_win2) {
        cout << "Strategy 1 is better than strategy 2.\n";
    }
    else {
        cout << "Strategy 2 is better than strategy 1.\n";
    }
    return 0;
}

//IMPLEMENTATION OF FUNCTIONS

/*
 * Function used to determine if the duel continues.
 * Continues if true, returns false otherwise.
 */
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {

    if (((A_alive == true) & (B_alive == true)) || ((A_alive == true) & (C_alive == true)) ||
        ((B_alive == true) & (C_alive == true))) {
        return true;
    }
    return false;
}


void test_at_least_two_alive(void) {
    cout << "Unit Testing 1: Function - at_least_two_alive()\n";
    bool aaron_a = true;
    bool bob_a = true;
    bool charlie_a = true;
    cout <<"\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(at_least_two_alive(aaron_a, bob_a, charlie_a));
    cout << "\tCase passed ...\n";

    aaron_a = false;
    bob_a = true;
    charlie_a = true;
    cout <<"\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(at_least_two_alive(aaron_a, bob_a, charlie_a));
    cout << "\tCase passed ...\n";

    aaron_a = true;
    bob_a = false;
    charlie_a = true;
    cout <<"\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(at_least_two_alive(aaron_a, bob_a, charlie_a));
    cout << "\tCase passed ...\n";

    aaron_a = true;
    bob_a = true;
    charlie_a = false;
    cout <<"\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(at_least_two_alive(aaron_a, bob_a, charlie_a));
    cout << "\tCase passed ...\n";

    aaron_a = false;
    bob_a = false;
    charlie_a = true;
    cout <<"\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(aaron_a, bob_a, charlie_a));
    cout << "\tCase passed ...\n";

    aaron_a = false;
    bob_a = true;
    charlie_a = false;
    cout <<"\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(aaron_a, bob_a, charlie_a));
    cout << "\tCase passed ...\n";

    aaron_a = true;
    bob_a = false;
    charlie_a = false;
    cout <<"\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(aaron_a, bob_a, charlie_a));
    cout << "\tCase passed ...\n";

    aaron_a = false;
    bob_a = false;
    charlie_a = false;
    cout <<"\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(aaron_a, bob_a, charlie_a));
    cout << "\tCase passed ...\n";
}

/*
 * Function to determine who Aaron shoots and if he hits them
 * for Strategy 1.
 * Shoots Charlie if he's alive, Bob otherwise.
 */

void Aaron_shoots1(bool& B_alive, bool& C_alive) {

        //Used to get a number from 0-99
        int shot = rand() % 100;

        //If shot = 33 or less, Aaron hit his shot
        if (shot <= A_ACCURACY) {
            if (C_alive == true) {
                C_alive = false;
            }
            else {
                B_alive = false;
            }
        }
}


void test_Aaron_shoots1(void) {
    cout << "Unit Testing 2: Function Aaron_shoots1(B_alive, C_alive)\n";
    //
    bool bob_a = true;
    bool charlie_a = true;
    cout << "\tCase 1: Bob alive, Charlie alive\n"
         << "\t\tAaron is shooting at Charlie\n";
    Aaron_shoots1(bob_a, charlie_a);

    bob_a = false;
    charlie_a = true;
    cout << "\tCase 2: Bob dead, Charlie alive\n"
         <<"\t\tAaron is shooting at Charlie\n";
    Aaron_shoots1(bob_a, charlie_a);

    bob_a = true;
    charlie_a = false;
    cout << "\tCase 3: Bob alive, Charlie dead\n"
         << "\t\tAaron is shooting at Bob\n";
    Aaron_shoots1(bob_a, charlie_a);
}

/*
 * Function to determine who Bob shoots and if he hits them
 * for Strategy 1.
 * Bob shoots at Charlie if he's alive, Aaron otherwise.
 */
void Bob_shoots(bool& A_alive, bool& C_alive) {

        //Used to get a number from 0-99
        int shot = rand() % 100;

        //If shot = 49 or less (since 0 counts), Bob hit his shot
        if (shot <= B_ACCURACY) {
            if (C_alive == true) {
                C_alive = false;
            }
            else {
                A_alive = false;
            }
        }
}

void test_Bob_shoots(void) {
    cout << "\nUnit Testing 3: Function Bob_shoots(A_alive, C_alive)\n";
    //
    bool aaron_a = true;
    bool charlie_a = true;
    cout << "\tCase 1: Aaron alive, Charlie alive\n"
         << "\t\tBob is shooting at Charlie\n";
    Bob_shoots(aaron_a, charlie_a);

    aaron_a = false;
    charlie_a = true;
    cout << "\tCase 2: Aaron dead, Charlie alive\n"
         <<"\t\tBob is shooting at Charlie\n";
    Bob_shoots(aaron_a, charlie_a);

    aaron_a = true;
    charlie_a = false;
    cout << "\tCase 3: Aaron alive, Charlie dead\n"
         <<"\t\tBob is shooting at Aaron\n";
    Bob_shoots(aaron_a, charlie_a);

}
/*
 * Function to determine who Charlie kills for Strategy 1.
 * Kills Bob if he's alive, Aaron otherwise.
 */

void Charlie_shoots(bool& A_alive, bool& B_alive) {

        if (B_alive == true) {
            B_alive = false;
        }
        else {
            A_alive = false;
        }
}

void test_Charlie_shoots(void) {
    cout << "Unit Testing 4: Function Charlie_shoots(A_alive, B_alive)\n";
    //
    bool aaron_a = true;
    bool bob_a = true;
    cout <<"\tCase 1: Aaron alive, Bob alive\n"
         <<"\t\tCharlie is shooting at Bob\n";
    Charlie_shoots(aaron_a, bob_a);

    aaron_a = false;
    bob_a = true;
    cout << "\tCase 2: Aaron dead, Bob alive\n"
         <<"\t\tCharlie is shooting at Bob\n";
    Charlie_shoots(aaron_a, bob_a);

    aaron_a = true;
    bob_a = false;
    cout << "\tCase 3: Aaron alive, Bob dead\n"
         << "\t\tCharlie is shooting at Aaron\n";
    Charlie_shoots(aaron_a, bob_a);
}

/*
 * Function to determine who Aaron shoots and if he hits them.
 * Generates a random number 0-2, where 1 = hit
 * everything else misses - representing 1/3 accuracy
 * Strategy 2: Aaron intentionally misses the first shot, then
 * he aims for Charlie if he's alive, Bob otherwise.
 */

void Aaron_shoots2(bool& B_alive, bool& C_alive) {

    int shot = rand() % 100;
    if (A_alive == true) {

        //If Charlie and Bob are alive (first shot), Aaron intentionally misses
        if ((C_alive == true) & (B_alive == true)) {
            //Nothing happens
        }

            //If not, then Aaron shoots with a 1/3 chance of hitting his target
        else {

            if (shot <= A_ACCURACY) {
                if (C_alive == true) {
                    C_alive = false;
                }
                else {
                    B_alive = false;
                }
            }
        }
    }
}



void test_Aaron_shoots2(void) {
    cout << "Unit Testing 5: Function Aaron_shoots2(B_alive, C_alive)\n";
    //
    bool bob_a = true;
    bool charlie_a = true;
    cout << "\tCase 1: Bob alive, Charlie alive\n"
         << "\t\tAaron intentionally misses his first shot\n"
         <<"\t\tBoth Bob and Charlie are alive\n";
    Aaron_shoots2(bob_a, charlie_a);

    bob_a = false;
    charlie_a = true;
    cout << "\tCase 2: Bob dead, Charlie alive\n"
         <<"\t\tAaron is shooting at Charlie\n";
    Aaron_shoots2(bob_a, charlie_a);

    bob_a = true;
    charlie_a = false;
    cout << "\tCase 3: Bob alive, Charlie dead\n"
         << "\t\tAaron is shooting at Bob\n";
    Aaron_shoots2(bob_a, charlie_a);
}

//Function used to continue
void pressAnyKey() {
    cout <<"Press any key to continue...\n";
    cin.ignore().get();
}