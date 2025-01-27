/*
 * Author: Brandon Duong
 * AU ID: bhd0014
 * Class: COMP2710
 * Filename: project4_Duong_bhd0014.cpp
 *
 * FOR PRODUCTION VERSION:
 * Compile source code with g++ -std=c++11.
 *
 * FOR DEBUGGING VERSION:
 * Compile source code with g++ -std=c++11 -DUNIT_TESTING.
 *
 * I used Dr. Li's hints and StackOverflow on implementing linked lists
 * to write my code.
 */

#include <iostream>
#include <string>

using namespace std;

//node structure for the game using question, answer, and point value
struct TriviaNode {
    string question;
    string answer;
    int points;
    TriviaNode* next;
};

//creates pointer to trivia node
typedef TriviaNode* ptrNode;
ptrNode list = NULL;

//prototype functions
void addNode (ptrNode & list, string question, string answer, int points);
void addQuestion ();
void initialQuestionList();
int askQuestion (ptrNode & qlist, int numQ);
void unitTest();

#define triviaQuiz
//#define UNIT_TESTING

int main() {

    //initialize point count
    int totalPoints = 0;
#ifdef triviaQuiz

    //normal trivia
    cout << "*** Welcome to Duong's trivia quiz game ***\n";

    addQuestion();

    //loop to iterate through the linked list, while there is a next.
    for (ptrNode temp = list; temp != NULL; temp = temp->next) {
        string userAnswer;
        cout << "Question: " << temp->question << "\n";
        cout << "Answer: ";
        //sets user input as userAnswer string to compare to actual answer.
        getline(cin, userAnswer);

        if (userAnswer == temp->answer) {
            cout << "Your answer is correct! You receive " << temp->points << " points.";
            totalPoints += temp->points;
            cout << "\nYour total points: " << totalPoints << "\n\n";
        } else {
            cout << "Your answer is wrong. The correct answer is " << temp->answer << "\n";
            cout << "Your total points: " << totalPoints << "\n\n";
        }

    }

    cout << "\n\n*** Thank you for playing the trivia quiz game. Goodbye! ***\n";
#endif

    //debugging version
#ifdef UNIT_TESTING
    unitTest();
    return 0;
#endif
}


//FUNCTION DEFINITIONS

/*
 * Function to add a node to the linked list
 * @param ptrNode and list for where to add
 * @param setQuestion for the input question part of the node
 * @param setAnswer for the input answer part of the node
 * @param setPoints for the input point value of the node
 */
void addNode (ptrNode & list, string setQuestion, string setAnswer, int setPoints) {
    ptrNode node = new TriviaNode;
    node -> question = setQuestion;
    node -> answer = setAnswer;
    node -> points = setPoints;

    //adds node to the list if empty and sets next to null
    //first node in will be the last node in the list
    if (list == NULL) {
        list = node;
        list -> next = NULL;
    }
    //adds node to the front of the list by making next point to the rest of the list.
    else {
        node -> next = list;
        list = node;
    }
}

/*
 * Function for user to add their own questions
 */

void addQuestion() {
    string question;
    string answer;
    //continue option
    string con;
    string playerAnswer;
    int points;

    //sets user input to question, answer, and point value variables for the new node
    cout << "Enter a question: ";
    getline(cin, question);

    cout << "Enter an answer: ";
    getline(cin, answer);

    cout << "Enter award points: ";
    cin >> points;

    //adds the node to the list by calling addNode function
    addNode(list, question, answer, points);

    cout << "Continue? (Y/N): ";
    cin >> con;
    cin.ignore();
    cout << "\n";

    //if user selects y, it prompts them for another trivia node.
    if(con == "Y" || con == "y") {
        addQuestion();
    }
}

/*
 * Hard-codes the 3 initial trivia questions
 */
void initialQuestionList() {
    //the new trivia nodes for each question
    TriviaNode node1;
    TriviaNode node2;
    TriviaNode node3;

    //given question 1
    string question1 = "How long was the shortest war on record? (Hint: how many minutes)";
    string answer1 = "38";
    int points1 = 100;

    //given question 2
    string question2 = "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
    string answer2 = "Bank of Italy";
    int points2 = 50;

    //given question 3
    string question3 = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)";
    string answer3 = "Wii Sports";
    int points3 = 20;

    //add the nodes to the list, first node in is the last one in the list
    addNode(list, question3, answer3, points3);
    addNode(list, question2, answer2, points2);
    addNode(list, question1, answer1, points1);

}

/*
 * Function for the unit testing function; generates warnings
 */
int askQuestion (ptrNode & qlist, int numQ) {
    int success = 1;

    if (numQ == 0) {
        cout << "Warning - the number of trivia asked must equal to or be larger than 1.\n";
        return success;
    }
    else {
        string userGuess;
        int totalPoints =0;
        int length = 0;

        ptrNode temp = qlist;

        while (temp != NULL) {
            length++;
            temp = temp -> next;
        }

        if (numQ > length) {
            cout << "Warning - only " << length << " trivia questions in the list.\n";
            return success;
        }

        temp = qlist;

        for (int i =0; i < numQ; i++) {
            cout << "Question: " << temp -> question << "\n";
            cout << "Answer: ";

            getline (cin, userGuess);

            if (userGuess == temp -> answer) {
                totalPoints += temp -> points;
                success = 0;

                cout << "Your answer is correct! You receive " << temp -> points << " points.\n";
                cout << "Your total points: " << totalPoints << "\n\n";
            }
            else {
                cout << "Your answer is wrong. The correct answer is " << temp -> answer << "\n";
                cout << "Your total points: " << totalPoints << "\n\n";
                success = 1;
            }
            temp = temp -> next;
        }
        return success;
    }


}

/*
 * Function for the debugging version of the program
 */
void unitTest() {
    initialQuestionList();

    cout << "*** This is a debugging version ***\n";
    cout << "Unit Test Case 1: Ask no questions. The program should give a warning message.\n";
    askQuestion(list, 0);
    cout << "Case 1 Passed\n";

    cout << "\nUnit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer.\n";
    if (askQuestion(list, 1) == 1) {
        cout << "Case 2.1 passed\n";
    }
    else {
        cout << "Case 2.1 failed\n";
    }


    cout << "\nUnit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer.\n";
    if (askQuestion(list, 1)==0) {
        cout << "Case 2.2 passed\n";
    }
    else {
        cout << "Case 2.2 failed\n";
    }

    cout << "\nUnit Testing Case 3: Ask all questions of the last trivia in the linked list.\n";
    if (askQuestion(list, 3)==0) {
        cout << "Case 3 passed\n";
    }
    else {
        cout << "Case 3 failed\n";
    }

    cout << "\nUnit Testing Case 4: Ask five questions in the linked list.\n";
    askQuestion(list, 5);
    cout <<"Case 4 passed\n";

    cout << "\n*** End of the Debugging Version ***\n";
}