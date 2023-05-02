#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

int main() {
    // Read the questions from the file
    ifstream file("question_bank.txt");
    if (!file.is_open()) {
        cerr << "Failed to open the file" << std::endl;
        return 1;
    }
    vector<std::string> questions;
    string question;
    while (std::getline(file, question)) {
        if (!question.empty()) {
            questions.push_back(question);
        }
    }
    file.close();

    // Shuffle the questions using a random engine
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(questions.begin(), questions.end(), default_random_engine(seed));

    // Choose the number of random questions for each paper
    cout << "How many questions do you need in each question paper?" << std::endl;
    int num_questions;
    cin >> num_questions;

    // Choose the number of question papers to generate
    cout << "How many question papers do you want to generate?" << std::endl;
    int num_papers;
    cin >> num_papers;

    // Generate and save each question paper
    for (int i = 1; i <= num_papers; i++) {
        // Shuffle the questions again for each paper
        shuffle(questions.begin(), questions.end(), default_random_engine(seed));

        // Create the filename for the current paper
        string filename = "generated_question_" + to_string(i) + ".txt";

        // Open the file for writing
        ofstream outfile(filename);
        if (!outfile.is_open()) {
            cerr << "Failed to open the file: " << filename << endl;
            return 1;
        }

        // Choose the questions for the current paper and write them to the file
        cout << "Question paper " << i << ":" << endl;
        for (int j = 0; j < num_questions; j++) {
            int index = i * j % questions.size();
            string curr_question = "Question " + std::to_string(j + 1) + ": " + questions[index] + "\n";
            outfile << curr_question;
            cout << curr_question;
        }

        // Close the file
        outfile.close();

        // Print a message indicating that the current paper has been generated and saved
        cout << "The generated questions have been saved in " << filename << endl;
    }

    return 0;
}
