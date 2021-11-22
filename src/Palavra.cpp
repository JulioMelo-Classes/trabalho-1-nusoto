#include "Palavra.hpp"

using namespace std;

Palavra::Palavra(){
    this->id = 0;
    this->palavra = "";
}

Palavra::Palavra(string s, int d){
    this->id = d;
    this->palavra = s;
}

std::string Palavra::get_palavra(){
    return this->palavra;
}

void Palavra::set_palavra(std::string palavra){
    this->palavra = palavra;
}

int Palavra::get_id(){
    return this->id;
}

void Palavra::set_id(int id){
    this->id = id;
}