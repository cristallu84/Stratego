#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

class already_exists : public std::exception {
public:
    const char* what() const noexcept override {
        return "The firewall is already present at the specified position.";
    }
};

class out_bounds : public std::exception {
public:
    const char* what() const noexcept override {
        return "The cell selected is outside of the grid.";
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


#endif