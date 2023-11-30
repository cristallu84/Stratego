#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>
#include <vector>
#include <ctime>
#include "game.h"
#include "exceptions.h"

using namespace std;

// Produces a vector of random placements
vector<string> randomPlacements() {
    vector<string> d = {"V1", "V2", "V3", "V4", "D1", "D2", "D3", "D4"};
    unsigned random = unsigned(time(0));
    shuffle(begin(d), end(d), default_random_engine(random));
    return d;
}

int main(int argc, char* argv[]) {

    Grid g;
    vector<string> p1_links;
    vector<string> p2_links;

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
            // Clear the vectors before pushing back data into
            if (arg == "-link1") {
                p1_links.clear();
            } else {
                p2_links.clear();
            }

            // Handle placement file
            string fileName = argv[i + 1];
            ifstream f(fileName);
            string line;
            getline(f, line);
            istringstream iss(line);
            string s;

            // Determines which links to push back data into
            vector<string>& current_links = (arg == "-link1") ? p1_links : p2_links;

            while (iss >> s){
                current_links.emplace_back(s);
            }
            ++i;

        } else if (arg == "-graphics") {
            // TODO: enable graphical interface
        }
    };
    
    // Randomizing depending on empty links
    if (p1_links.empty()) p1_links = randomPlacements();
    if (p1_links.empty()) p2_links = randomPlacements();

    g.init(8, p1_links, p2_links);

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
                        string d;
                        iss >> c >> d;
                        g.move(c, d);

                    } else if (cmd == "abilities") {
                        //check whose turn it is 
                        g.printAbilities();

                    } else if (cmd == "ability") {
                        int ID; 
                        iss >> ID; // will be 1-5 

                        if (ID == 1) { // Firewall
                            int r;
                            int c;
                            iss >> r >> c;

                            try {
                                g.firewall(r,c);
                            } catch (const already_exists& e) {
                                cout << "Error occured: " << e.what() << endl;
                                g.nextTurn();
                            } catch (const out_bounds& e) {
                                cout << "Error occured: " << e.what() << endl;
                                g.nextTurn();
                            } catch (...) {
                                cout << "Unknown error occured." << endl;
                                g.nextTurn();
                            }

                        } else if (ID == 2) { // Linkboost
                            char c;
                            iss >> c;
                            try {
                                g.linkBoost(c);
                            } catch (const not_link& e) {
                                cout << "Error occured: " << e.what() << endl;
                                g.nextTurn();
                            } catch (const not_on_board& e) {
                                cout << "Error occured: " << e.what() << endl;
                                g.nextTurn();
                            } catch (const not_your_link& e) {
                                cout << "Error occured: " << e.what() << endl;
                                g.nextTurn();
                            } catch (...) {
                                cout << "Unknown error occured." << endl;
                                g.nextTurn();
                            }
                            
                            
                        } else if (ID == 3) { // Download
                            char c;
                            iss >> c;
                            try {
                                g.download(c);
                            } catch (const not_link& e) {
                                cout << "Error occured: " << e.what() << endl;
                                g.nextTurn();
                            } catch (...) {
                                cout << "Unknown error occured." << endl;
                                g.nextTurn();
                            }
                            
                        } else if (ID == 4) { // Polarize
                            char c;
                            iss >> c;
                            try {
                                g.polarize(c);
                            } catch (const not_link& e) {
                                cout << "Error occured: " << e.what() << endl;
                                g.nextTurn();
                            } catch (...) {
                                cout << "Unknown error occured." << endl;
                                g.nextTurn();
                            }

                        } else if (ID == 5) { // Scan
                            char c;
                            iss >> c;
                            try {
                                g.scan(c);
                            } catch (const not_link& e) {
                                cout << "Error occured: " << e.what() << endl;
                                g.nextTurn();
                            } catch (const not_on_board& e) {
                                cout << "Error occured: " << e.what() << endl;
                                g.nextTurn();
                            } catch (...) {
                                cout << "Unknown error occured." << endl;
                                g.nextTurn();
                            }

                        } else {
                            cout << "Please enter a valid ability." << endl;
                        }

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
