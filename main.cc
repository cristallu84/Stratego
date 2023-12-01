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

                        vector<string> cards = g.printAbilities();
                        for (int i = 0; i < cards.size(); i += 2) {
                            cout << cards[i] << " - " << cards[i + 1] << endl;
                        }

                    } else if (cmd == "ability") {
                        int player = g.getTurn();
                        int ID; 
                        iss >> ID; // will be 1-5 
                        Card c = g.getPlayer(player).getCard(ID);

                        if (c.type == CardType::Firewall && c.used == false){ //going to get r and c
                        int row; 
                        int col;
                        iss >> row >> col; 
                        Cell& cell = g.findCoord(row, col);
                        std::unique_ptr<Firewall> f = std::make_unique<Firewall>(cell, player);
                        f->execute();
                        c.used = true;

                        }else if (c.type == CardType::Download && c.used == false){
                        char link;
                        iss >> link;
                        Link& l = g.findCell(link).getLink();
                        std::unique_ptr<Download> d = std::make_unique<Download>(l, player, g.getPlayer(1), g.getPlayer(2));
                        d->execute();
                        c.used = true;

                        }else if (c.type == CardType::Linkboost && c.used == false){
                        char link;
                        iss >> link;
                        Link& l = g.findCell(link).getLink();
                        std::unique_ptr<Linkboost> L = std::make_unique<Linkboost>(l);
                        L->execute();
                        c.used = true;

                        }else if (c.type == CardType::Polarize && c.used == false){
                        char link;
                        iss >> link;
                        Link& l = g.findCell(link).getLink();
                        std::unique_ptr<Polarize> p = std::make_unique<Polarize>(l);
                        p->execute();
                        c.used = true;

                        }else if (c.type == CardType::Scan && c.used == false){
                        char link;
                        iss >> link;
                        Link& l = g.findCell(link).getLink();
                        std::unique_ptr<Scan> s = std::make_unique<Scan>(l, g.getPlayer(1), g.getPlayer(2));
                        s->execute();
                        c.used = true;

                        }else{
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
