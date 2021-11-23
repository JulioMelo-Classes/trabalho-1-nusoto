#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <vector>
#include "datatype.hpp"
#include "Palavra.hpp"

class Score {
    private:
        Dificuldade dif;//armazena a dificuldade de uma linha do score

        std::string nome;// armazena o nome do jogador

        std::vector<std::string> acertos;// vetor de strings para armazenar as palavras que foram acertadas pelo jogador naquele score

        int pontuacao = -1;//inicia a pontuacao com -1 para saber se ela foi alterada ou nao;
    public:
        Score();

        Dificuldade get_dificuldade();// retorna a dificuldade

        void set_dificuldade(Dificuldade dif);// seta a dificuldade

        std::string get_nome();// retorna o nome

        void set_nome(std::string nome);// seta o nome

        std::vector<std::string> get_acertos();//retorna o vetor de strings acertos

        void set_acertos(std::vector<std::string> acertos);// seta um vetor de strings como sendo acertos

        void add_acertos(std::string acerto);// adiciona a string acerto no vetor de acertos com push_back()

        int get_pontuacao();//retorna a pontuacao

        void set_pontuacao(int p);// da set na pontuacao
};

#endif