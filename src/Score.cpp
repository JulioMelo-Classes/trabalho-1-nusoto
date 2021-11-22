#include "Score.hpp"

Score(){
    return;
}

Dificuldade Score::get_dificuldade(){
    return this->dif;
}

void Score::set_dificuldade(Dificuldade dif){
    this->dif = dif;
}

std::string Score::get_nome(){
    return this->nome;
}

void Score::set_nome(std::string nome){
    this->nome = nome;
}

std::vector<std::string> Score::get_acertos(){
    return this->acertos;
}

void Score::set_acertos(std::vector<std::string> acertos){
    this->acertos = acertos;
}

void add_acertos(std::string acerto){
    this->acertos.push_back(acerto);
}

int Score::get_pontuacao(){
    return this->pontuacao;
}

void Score::set_pontuacao(int p){
    this->pontuacao = p;
}
