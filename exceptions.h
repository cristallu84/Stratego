#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

class game_quit : public std::exception {  
public:
    const char* what() const noexcept override {
        return "Game exited"; 
    }
};


class cell_occupied : public std::exception {  
public:
    const char* what() const noexcept override {
        return "Chosen cell is already occupied"; 
    }
};

class out_bounds : public std::exception { 
public:
    const char* what() const noexcept override {
        return "STAY ON THE GRID >:(";
    }
};

class not_link : public std::exception {
public:
    const char* what() const noexcept override {
        return "The link selected does not exist.";
    }
};

class not_on_board : public std::exception {
public:
    const char* what() const noexcept override {
        return "The link selected is not on the board.";
    }
};

class not_your_link : public std::exception {
public:
    const char* what() const noexcept override {
        return "The link selected is the other player's.";
    }
};

class not_diagonal_link : public std::exception {
public:
    const char* what() const noexcept override {
        return "This link does not have a diagonal ability";
    }
};

class invalid_input: public std::exception {
public:
    const char* what() const noexcept override {
        return "Input is invalid, try again";
    }
};

class wrong_player: public std::exception{
public:
    const char* what() const noexcept override {
        return "Only your opponent can do that";
    }
};
class cant_use_card: public std::exception{
public:
    const char* what() const noexcept override {
        return "Ability card does not exist or has already been used";
    }
};

class incorrect_init: public std::exception {
    public:
        const char* what() const noexcept override {
            return "Game initialized incorrectly, default settings will be applied for ";
        }
};

#endif