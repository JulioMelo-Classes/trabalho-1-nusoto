#include "Forca.hpp"

using namespace std;

Forca::Forca( std::string palavras, std::string scores ){
    this->m_arquivo_palavras = palavras;
    this->m_arquivo_scores = scores;

    cout << ">>> Lendo arquivos de palavras [" + this->m_arquivo_palavras + "] e scores [" + this->m_arquivo_scores + "], por favor aguarde.." << std::endl 
         << "--------------------------------------------------------------------" << std::endl;
    std::pair<bool, std::string> teste_arquivos = eh_valido();

    if (!teste_arquivos.first){
        cout << ">>> Problema ao abrir arquivo, motivo: " << teste_arquivos.second << std::endl;
        return;
    }
    cout << ">>> Arquivos OK!" << std::endl << "--------------------------------------------------------------------" << std::endl;
    carrega_arquivos();

    menu();

}

std::pair<bool, std::string> Forca::eh_valido(){
    string razao = "";

    std::ifstream file(this->m_arquivo_palavras);
    if (!file.is_open() || file.fail()) {
        razao.assign("O arquivo não existe no caminho especificado em \"" + this->m_arquivo_palavras + "\".");
        return {false, razao};
    }

    return {true, razao};
}

void Forca::carrega_arquivos(){
    std::ifstream file(this->m_arquivo_palavras);
    
    std::string line, subline;
    std::vector<Palavra> vetor_palavras;
    Palavra atual_p;
    size_t pos = 0, pos_2 = 0;

    while (!file.eof()) {
        std::getline(file, line);
        if (line.size() == 0)
            continue;
        pos = line.find(" ");
        atual_p.set_palavra(line.substr(0,pos));
        line.erase(0, pos+1);
        atual_p.set_id(std::stoi(line));
        vetor_palavras.push_back(atual_p);
    }
    this->m_palavras = vetor_palavras;
    file.close();

    std::ifstream file2(this->m_arquivo_scores);
    std::vector<Score> vetor_score;
    Score atual_s;

    while (!file2.eof()) {
        std::getline(file2, line);
        if (line.size() == 0)
            continue;
        
        pos = line.find(";");
        subline = line.substr(0,pos);
        if (subline.compare("Médio") == 0)
            atual_s.set_dificuldade(Dificuldade::MEDIO);
        else if(subline.compare("Difícil") == 0)
            atual_s.set_dificuldade(Dificuldade::DIFICIL);
        else
            atual_s.set_dificuldade(Dificuldade::FACIL);
        
        line.erase(0, pos+2);

        pos = line.find(";");
        subline = line.substr(0,pos);
        atual_s.set_nome(subline);

        line.erase(0, pos+2);
        while ((pos = line.find(";")) != 0){
            pos_2 = line.find(",");
            subline = line.substr(0,pos_2);
            atual_s.add_acertos(subline);
            line.erase(0, pos_2+2);
        }
        if (line.front() == ';')
            line.erase(0);
        atual_s.set_pontuacao(std::stoi(line));
        vetor_score.push_back(atual_s);
    }

    this->score_carregado = vetor_score;
    file2.close();
}

void Forca::set_dificuldade(Dificuldade d){
    this->d = d;
}

std::string Forca::proxima_palavra(){
    return "";
}

std::string Forca::get_palavra_atual(){
    return this->m_palavra_atual.get_palavra();
}

bool Forca::palpite(std::string palpite){
    if (this->m_palavra_atual.get_palavra().find(palpite) != std::string::npos)
        return true;
    this->m_tentativas_restantes -= 1;
    return false;
}

bool Forca::game_over(){
    if (this->m_tentativas_restantes == 0)
        return true;
    return false;
}

void Forca::set_tentativas_restantes(int tentativas){
    this->m_tentativas_restantes = tentativas;
}

int Forca::get_tentativas_restantes(){
    return this->m_tentativas_restantes;
}

void Forca::set_score(std::vector<Score> score){
    this->score_carregado = score;
}

std::vector<Score> Forca::get_score(){
    return this->score_carregado;
}

void Forca::display_pontuacao(){
    std::vector<Score> sc = this->get_score();
    std::vector<std::string> ac;
    for(auto & elem : sc){
        std::vector<std::string> ac = elem.get_acertos();
        cout << elem.get_dificuldade() << elem.get_nome();
        for (long unsigned int i = 0; i < ac.size(); i++){
            cout << ac[i] + ", ";
        }
        cout << elem.get_pontuacao() << endl;
    }
}