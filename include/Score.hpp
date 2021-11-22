#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <vector>
#include "Forca.hpp"
#include "Palavra.hpp"

class Score {
    private:
        Dificuldade dif;

        std::string nome;

        std::vector<std::string> acertos;

        int pontuacao;
    public:
        Score();

        Dificuldade get_dificuldade();

        void set_dificuldade(Dificuldade dif);

        std::string get_nome();

        void set_nome(std::string nome);

        std::vector<std::string> get_acertos();

        void set_acertos(std::vector<std::string> acertos);

        void add_acertos(std::string acerto);

        int get_pontuacao();

        void set_pontuacao(int p);
};

#endif