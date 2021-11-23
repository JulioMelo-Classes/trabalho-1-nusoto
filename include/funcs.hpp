#ifndef FUNCS_H
#define FUNCS_H

#include <iostream>
#include <vector>
#include <algorithm>

void menu();// menu inicial

void menu_opcao_1_iniciar_jogo();// menu caso o jogador inicie o jogo, mostra uma selecao de dificuldades

void menu_opcao_2_ver_scores();//monu para mostrar o score

std::vector<std::string> split(const std::string& str, const std::string& delim);// funcao para dar split em uma linha de palavras, usando o delim como delimitador

bool is_number(const std::string& s);// retorna se eh um numero ou nao

bool voltar_menu();// retorna true para voltar ao menu e false para encerrar o programa

#endif