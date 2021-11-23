#ifndef PALAVRA_H
#define PALAVRA_H

#include <iostream>

class Palavra {
    private:
        std::string palavra;//a palavra em si
        int id; // a frequencia da palavra
    public:
        Palavra();

        Palavra(std::string s, int d);

        std::string get_palavra();//retorna a palavra

        void set_palavra(std::string palavra);//da set na palavra

        int get_id();//retorna a frequencia

        void set_id(int id);// da set na frequencia
};

#endif