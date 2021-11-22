#ifndef PALAVRA_H
#define PALAVRA_H

#include <iostream>

class Palavra {
    private:
        std::string palavra;
        int id;
    public:
        Palavra();

        Palavra(std::string s, int d);

        std::string get_palavra();

        void set_palavra(std::string palavra);

        int get_id();

        void set_id(int id);
};

#endif