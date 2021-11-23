#include "funcs.hpp"

using namespace std;

void menu(){//menu inicial do jogo
    cout << endl <<  "Bem vindo ao Jogo Forca! Por favor escolha uma das opções" << endl;
    cout << "1 - Iniciar Jogo" << endl;
    cout << "2 - Ver scores anteriores" << endl;
    cout << "Sua escolha: ";
}

void menu_opcao_1_iniciar_jogo(){//caso o jogador escolha iniciar o jogo pergunda a dificuldade
    cout << endl << "Vamos iniciar o jogo! Por favor escolha o nível de dificuldade" << endl;
    cout << "1 - Fácil" << endl;
    cout << "2 - Médio" << endl;
    cout << "3 - Difícil" << endl;
    cout << "Sua escolha: ";
}

void menu_opcao_2_ver_scores(){//menu para mostrar score
    cout << endl << "exibindo todos os scores armazenados ate o momento: " << endl;
}

bool voltar_menu(){//menu para perguntar se quer voltar ao menu inicial ou terminar o programa
    char a;
    cout << "deseja encerrar o programa? \"s\" para sim, qualquer outra tecla para nao.";
    cin >> a;
    if (a != 's')
        return true;
    return false;
}

vector<string> split(const string& str, const string& delim)//pegado da net
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

bool is_number(const std::string& s)//pegado da net
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}