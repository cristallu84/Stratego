#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>
#include <vector>
#include <ctime>
#include <chrono>
#include "game.h"
#include "window.h"
#include "graphicsdisplay.h"

using namespace std;

// Produces a vector of random placements
vector<string> randomPlacements() {
    vector<string> d = {"V1", "V2", "V3", "V4", "D1", "D2", "D3", "D4"};
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(begin(d), end(d), default_random_engine(seed));
    return d;
}

int main(int argc, char* argv[]) {
    
    Grid g;
    vector<string> p1_links;
    vector<string> p2_links;
    bool ability1 = false;
    bool ability2 = false;
    bool graphics = false;

    // Handle cmd line
    for (int i = 0; i < argc; ++i) {

		string arg = argv[i];
        if (arg == "-ability1") {
            // Set ability of P1
            string s = argv[i + 1];

            ++i;
                
            try {
                g.getPlayer(1).setAbility(s);
            } catch (const incorrect_init& e) {
                std::cout << e.what() << "player 1 abilities." << endl;
            }

        } else if (arg == "-ability2") {
            // Set ability of P2
            string s = argv[i + 1];
             ++i;

            try {
                g.getPlayer(2).setAbility(s);
            } catch (const incorrect_init& e) {
                cout << e.what() << "player 2 abilities." << endl;
            }    
                
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
            
            
            vector<string> file_links;

            while (iss >> s) {
                // cout << s << endl;
                file_links.emplace_back(s);
            }

            ++i;

            bool correct = true;
      
            try {

                g.initAbilities(file_links);

            } catch (const incorrect_init& e) {
                correct = false;
                string temp = (arg == "-link1") ? "player 1's" : "player 2's";
                cout << e.what() << temp << " link assignments." << endl;
            }  

            if (correct) {
                current_links = file_links;
            }

        } else if (arg == "-graphics") {
            graphics = true;
        }
    };
    
    // Randomizing depending on empty links
    if (p1_links.empty()) p1_links = randomPlacements();
    if (p2_links.empty()) p2_links = randomPlacements();

    // Default abilities
    if (!ability1) {
        string s = "LFDSP";
        g.getPlayer(1).setAbility(s);
    }
    if (!ability2) {
        string s = "LFDSP";
        g.getPlayer(2).setAbility(s);
    }
    
        Xwindow window;
        g.init(8, p1_links, p2_links, graphics, window);


    // Handling playing the game
    cin.exceptions(ios::failbit|ios::eofbit);
    string s;

    try {
        while (1) {
            istream *in = nullptr;
            in = &cin; 

            string cmd;
            try {

                cout << g << endl;

                while (getline(*in, s)) {
                    int player = g.getTurn();
                    istringstream iss{s};
                    iss >> cmd;
                    if (cmd == "sequence"){
                        string fname;
                        iss >> fname;
                        in = new ifstream(fname.c_str());
                        continue; 
                    } else if (cmd == "move") {
                        char c;
                        string d;
                        iss >> c >> d;

                        g.move(c,d);

                        // try {
                        //     g.move(c, d);
                        // } catch (const not_link& e) {
                        //     cerr << "Error: " << e.what() << endl;
                        //     g.nextTurn();
                        // } catch (const not_your_link& e) {
                        //     cerr << "Error: " << e.what() << endl;
                        //     g.nextTurn();
                        // } catch (const not_on_board& e) {
                        //     cerr << "Error: " << e.what() << endl;
                        //     g.nextTurn();
                        // } catch (const out_bounds& e) {
                        //     cerr << "Error: " << e.what() << endl;
                        //     g.nextTurn();
                        // } catch (...) {
                        //     cerr << "Error: " << "Be better bro B)" << endl;
                        //     g.nextTurn();
                        // }

                        g.nextTurn();
                        cout << g << endl;

                    } else if (cmd == "abilities") {

                        vector<string> cards = g.printAbilities();
                        for (std::vector<std::string>::size_type i = 0; i < cards.size(); i += 2) {
                            cout << cards[i] << " - " << cards[i + 1] << endl;
                        }

                    } else if (cmd == "ability") {
                        int ID; 
                        iss >> ID;

                        //checks that ID inputed is valid
                        if (!(ID >= 0 && ID <= 5)){
                            throw invalid_input();
                        }
                     
                        Card &c = g.getPlayer(player).getCard(ID);
                        if (c.type == CardType::Firewall && c.used == false){ //going to get r and c
                            int row; 
                            int col;
                            iss >> row >> col; 
                            Cell& cell = g.findCoord(row, col);
                            std::unique_ptr<Firewall> f = std::make_unique<Firewall>(cell, player);
                            f->execute();
                            c.used = true;

                        } else if (c.type == CardType::Download && c.used == false){
                            char cellname;
                            iss >> cellname;

                            Cell& cell = g.findCell(cellname);

                            //player is trying to use download on their own link:
                            if ((cellname <= 'h' && player == 1 && cellname >= 'a') || 
                                (cellname >= 'A' && player == 2 && cellname >= 'H')) {
                                throw wrong_player();
                            }  

                            std::unique_ptr<Download> d = std::make_unique<Download>(cell, player, g.getPlayer(1), g.getPlayer(2));
                            d->execute();
                            c.used = true;

                        } else if (c.type == CardType::Linkboost && c.used == false){
                            char link;
                            iss >> link;
                            
                            //player is trying to use linkboost on their opponent's link 
                            if ((link >= 'a' && link <= 'h' && player == 2) || (link >= 'A' && link <= 'H' && player == 1)){
                                cout << player << endl;
                                throw wrong_player();
                            }
                            
                            Link& l = g.findCell(link).getLink();
                            std::unique_ptr<Linkboost> L = std::make_unique<Linkboost>(l);
                            L->execute();
                            c.used = true;

                        } else if (c.type == CardType::Polarize && c.used == false){
                            char link;
                            iss >> link;
                            Link& l = g.findCell(link).getLink();
                            std::unique_ptr<Polarize> p = std::make_unique<Polarize>(l, g.getPlayer(1), g.getPlayer(2));
                            p->execute();
                            c.used = true;

                         }else if (c.type == CardType::Scan && c.used == false){
                            char link;
                            iss >> link;
                            Link& l = g.findCell(link).getLink();
                            std::unique_ptr<Scan> s = std::make_unique<Scan>(l, g.getPlayer(1), g.getPlayer(2));
                            s->execute();
                            c.used = true;

                        }else if (c.type == CardType::Diagonal && c.used == false){
                            char link;
                            iss >> link;
                            
                            //player is trying to use linkboost on their opponent's link 
                            if ((link <= 'h' && player == 2) || (link >= 'A' && player == 1)){
                                throw wrong_player();
                            }
                            
                            Link& l = g.findCell(link).getLink();
                            std::unique_ptr<Diagonal> Di = std::make_unique<Diagonal>(l);
                            Di->execute();
                            c.used = true;
                        }else if (c.type == CardType::PlayerSwap && c.used == false){
                            std::unique_ptr<PlayerSwap> Ps = std::make_unique<PlayerSwap>(g.getPlayer(1), g.getPlayer(2));
                            Ps->execute();
                            c.used = true;
                        }else if (c.type == CardType::MoveSPort && c.used == false){
                            int portRow;
                            int portCol;
                            int newRow;
                            int newCol;
                            iss >> portRow >> portCol >> newRow >> newCol;
                            Cell& port = g.findCoord(portRow, portCol);
                            Cell& location = g.findCoord(newRow, newCol);

                            std::unique_ptr<MoveSPort> Ps = std::make_unique<MoveSPort>(port, location);
                            Ps->execute();
                            c.used = true;
                        } else {
                            throw cant_use_card();
                        }

                        if (c.used == true) {
                            if (player == 1) {
                                g.getPlayer(1).decrMyAbil();
                                g.getPlayer(2).decrOppAbil();
                                g.getPlayer(1).notifyObservers();
                                g.getPlayer(2).notifyObservers();
                            }
                            if (player == 2) {
                                g.getPlayer(2).decrMyAbil();
                                g.getPlayer(1).decrOppAbil();
                                g.getPlayer(1).notifyObservers();
                                g.getPlayer(2).notifyObservers();
                            }
                        }

                    } else if (cmd == "board") {
                        cout << g << endl;

                    } else if (cmd == "quit") {
                        cout << "Game ended" << endl;
                        break;
                    }

                    if (g.getPlayer(player).gameState() == "Won") {
                        cout << "Player " << player << "wins!" << endl;
                        break;
                    } if (g.getPlayer(player).gameState() == "Lost") {
                        g.nextTurn();
                        int player = g.getTurn();
                        cout << "Player " << player << "wins!" << endl;
                        break;
                    } else {
                        continue;
                    }
                }
            } catch (ios::failure) {
            } catch (std::exception& e) {
                cout << "ERROR: " << e.what() << endl;
            } catch (...) {
                cout << "Error occured" << endl;
            }

            if (in != &cin) delete in;
        }
    }
    catch (ios::failure) {}
}
