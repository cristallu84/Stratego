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

#endif