#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "grid.h"

using namespace std;

int main(int argc, char* argv[]) {

    Grid g;

    // Handle cmd line
    for (int i = 0; i < argc; ++i) {

		string arg = argv[i];
        if (arg == "-ability1") {
            // Set ability of P1
            string s = argv[i + 1];
            g.getPlayer(1).setAbility(s);
            ++i;

        } else if (arg == "-ability2") {
            // Set ability of P2
            string s = argv[i + 1];
            g.getPlayer(2).setAbility(s);
            ++i;

        } else if (arg == "-link1" || arg == "-link2") {
            // Handle placement file
            string fileName = argv[i + 1];
            ifstream f(fileName);
            string line;
            getline(f, line);
            istringstream iss(line);
            string s;

            // Handle placement file contents
            int i = 0;
            vector<int> strength;
            vector<bool> type;
            while (iss >> s) {
                type[i] = (s[0] == 'V') ? false : true;
                strength[i] = s[1] - '0';
                ++i;
            }

            // Update board according to placement file
            vector<char> charVector;
            if (arg == "-link1") {
                vector<char> charVector = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
            } else {
                vector<char> charVector = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
            }
            for (auto &element : charVector) {
                char t;
                int s;
                iss >> s >> t;
                // TODO: update cell at element to be type t and strength s
            }
            ++i;

        } else if (arg == "-graphics") {
            // TODO: enable graphical interface
        }
    };

    // Handling playing the game
    cin.exceptions(ios::failbit|ios::eofbit);
    string s;

    try {
        while (1) {
            getline(cin, s);
            istringstream iss{s};
            iss.exceptions(ios::failbit);
            string stream_type;
            iss >> stream_type;
            istream *in = nullptr;
            if (stream_type != "sequence") {
                istream *in = &cin;
            } else {
                string fname;
                iss >> fname;
                ifstream *in = new ifstream(fname.c_str());
            }
            in->exceptions(ios::failbit|ios::eofbit);

            string cmd;
            try {
                while (getline(*in, s)) {

                    g.nextTurn();
                    
                    istringstream iss{s};
                    iss >> cmd;

                    if (cmd == "move") {
                        char c;
                        char d;
                        iss >> c >> d;
                        g.move(c, d);

                    } else if (cmd == "abilities") {
                        g.printAbilities();

                    } else if (cmd == "ability") {
                        char a;

                        // TODO: Take in input for each ability

                        // TODO: Implement execute ability

                    } else if (cmd == "board") {
                        std::cout << g;

                    } else if (cmd == "quit") {
                        cout << "Game ended" << endl;
                        break;
                    }
                    g.nextTurn();
                }
            }
            catch (ios::failure) {}

            if (in != &cin) delete in;
        }
    }
    catch (ios::failure) {}
}
