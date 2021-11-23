#include "Forca.hpp"

using namespace std;

Forca::Forca( std::string palavras, std::string scores ){
    this->m_arquivo_palavras = palavras; // carrega o que foi lido nos argumentos da chamada do programa para duas posicoes
    this->m_arquivo_scores = scores;
    int opcao;

    cout << ">>> Lendo arquivos de palavras [" + this->m_arquivo_palavras + "] e scores [" + this->m_arquivo_scores + "], por favor aguarde.." << std::endl 
         << "--------------------------------------------------------------------" << std::endl;
    std::pair<bool, std::string> teste_arquivos = eh_valido(); // testa se tanto o arquivo de palavras quanto o de score eh valido

    if (!teste_arquivos.first){ // se o retorno da funcao eh_valido() tiver no seu primeiro parametro false, significa que nao eh valido
        cout << ">>> Problema ao abrir arquivo, motivo: " << teste_arquivos.second << std::endl; // informa qual o problema ao validar os arquivos, o problema eh retornado pela funcao na segunda posicao do pair
        return;
    }
    cout << ">>> Arquivos OK!" << std::endl << "--------------------------------------------------------------------" << std::endl;
    carrega_arquivos(); // carrega o conteudo dos arquivos para o programa

    for(;;)// loop do jogo
    {
        menu(); // informa o menu inicial para o usuario e espera a escolha da opcao 1 = jogar, 2 = ver score
        cin >> opcao;
        if (opcao == 2){// mostra o score
            menu_opcao_2_ver_scores();
            display_pontuacao();
            if (!voltar_menu())// espera o usuario decidir se quer voltar ao menu ou encerrar
                return;
            continue;
        }
        else
            menu_opcao_1_iniciar_jogo(); // mostra o menu de inicializacao do jogo
        cin >> opcao; // recebe a opcao de dificuldade do usuario 1=facil, 2=medio, 3=dificil
        if (opcao == 2)
            set_dificuldade(MEDIO);
        else if(opcao == 3)
            set_dificuldade(DIFICIL);
        else
            set_dificuldade(FACIL);
        
    }
}

std::pair<bool, std::string> Forca::eh_valido(){
    string razao = ""; // inicializa a string que sera retornada com o valor vazio pois se nenhum erro for encontrado ela que sera retornada
    std::string line, subline, delimiter = ", ";// define string para armazenar as linhas e o delimitador para o arquivos de score
    std::vector<string> tem;// cria um vetor de string para dar split depois e separar a palavra do score
    size_t pos = 0;

    std::ifstream file(this->m_arquivo_palavras); // abre o arquivo de palavras informado pelo usuario
    if (!file.is_open() || file.fail()) { // se o arquivo nao estiver aberto ou encontrar algum erro ao abrir modifica a string de razao para informar o erro e retorna como false
        razao.assign("O arquivo não existe no caminho especificado em \"" + this->m_arquivo_palavras + "\".");
        return {false, razao};
    }

    while (!file.eof()){// itera por todo o arquivo de palavras ate chegar no fim
        std::getline(file, line);// pega toda a linha de uma vez
        if (line.size() <= 1)// se a linha estiver vazia ou com apenas o \n pula ela
            continue;
        tem = split(line, " ");// da split armazenando a palavra e a frequencia em duas strings
        if (tem.size() > 2){// se o split tiver gerado mais que duas strings por linha significa que o arquivo eh invalido
            razao.assign("O arquivo contem mais de dois itens por linha em: " + line);// modifica a string razao para informar o erro e retorna false
            return {false, razao};
        }
        pos = line.find(" ");// procura o primeiro espaco e do inicio da linha ate ali considera que eh a primeira palavra
        subline.assign(line.substr(0,pos));
        if (subline.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-") != std::string::npos){// se a palavra possuir algum caractere que nao seja de a-zA-Z+'-' informa que a palavra eh invalida na string de razao e retorna false
            razao.assign("A palavra contem caracteres invalidos em: " + line);
            return {false, razao};
        }
        if (subline.size() <= 4){// se a palavra tiver menos que 5 letras informa o erro e retorna false
            razao.assign("A palavra contem 4 ou menos letras em: " + line);
            return {false, razao};
        }
        if (subline.size() == 1){// se a palavra tiver sem sua frequencia correspondente
            razao.assign("Palavra sem frequencia correspondente");
            return {false, razao};
        }
        line.erase(0, pos);//apaga a palavra da linha para comecar a ler a frequencia
        pos = line.find_first_not_of(" ");
        
        line.erase(0, pos);
        pos = line.find_last_not_of(" ");// serve para caso o arquivo tenha varios espacos entre a palavra e a frequencia
        
        subline = line.substr(0,pos);
        if (!is_number(subline)){//se a funcao is_number retornar true significa que seu parametro eh um inteiro positivo, entao o ! serve para pegar qualquer caso que nao seja esse
            razao.assign("frequencia nao eh um numero inteiro positivo em: " + line);
            return {false, razao};
        }
    }
    file.close();// fecha o arquivo
    std::ifstream file2(this->m_arquivo_scores);// abre o arquivo de score

    while (!file2.eof()){// itera ate chegar no eof do arquivo
        Score atual_s;// inicia stual_s para armazenar o score atual lido na linha
        std::getline(file2, line);// pega toda a linha de uma vez
        if (line.size() <= 1)// linhas vazias ou com \n sao puladas
            continue;
        auto n = std::count(line.begin(), line.end(), ';');// conta quantas vezes ';' apareceu na linha, sendo mais que 3 invalido
        if (n > 3){
            razao.assign("Mais que 3 \";\" no arquivo de score em: " + line);
            return {false, razao};
        }
        pos = line.find(";");// procura o primeiro ';' e guarda a posicao
        subline = line.substr(0,pos);// move tudo o que esta no inicio da linha ate o primeir0 ';' para subline
        if (subline.compare("Médio") == 0)// chega se for facil, medio ou dificil e seta ele conforme
            atual_s.set_dificuldade(Dificuldade::MEDIO);
        else if(subline.compare("Difícil") == 0)
            atual_s.set_dificuldade(Dificuldade::DIFICIL);
        else
            atual_s.set_dificuldade(Dificuldade::FACIL);
        
        line.erase(0, pos+2);//apaga a dificuldade da linha

        pos = line.find(";");//procura o proximo ';' na linha que delimita o nome
        subline = line.substr(0,pos);//move ele para subline
        atual_s.set_nome(subline);// guarda em atual_s

        line.erase(0, pos+2);//apaga o nome da linha

        subline.clear();
        while ((pos = line.find(delimiter)) != std::string::npos) {//enquanto tiver palavras que o jogador acertou continua executando
        subline = line.substr(0, pos);//guarda a posicao que encontrou a ','
        atual_s.add_acertos(subline);//adiciona a atual_s
        line.erase(0, pos + delimiter.length());// e apaga da linha
        }
        pos = line.find(";");
        subline = line.substr(0, pos);
        atual_s.add_acertos(subline);// faz para a ultima palavra ja que ela nao psossui ',' depois
        line.erase(0, pos + 2);

        atual_s.set_pontuacao(std::stoi(line));// o que sobrou foi a pontuacao

        if (atual_s.get_dificuldade() == FACIL || atual_s.get_dificuldade() == MEDIO || atual_s.get_dificuldade() == DIFICIL)// checa se dificuldade eh valido entre FACIL MEDIO e DIFICIL
            ;
        else{
            razao.assign("Dificuldade invalida no arquivo de score em: " + line);
            return {false, razao};
        }
            
        if (atual_s.get_nome().empty()){// se o nome estiver vazio informa no campo de razao e retorna false
            razao.assign("Nome invalido no arquivo de score em: " + line);
            return {false, razao};
        }
        if (atual_s.get_pontuacao() == -1){// pontuacao nao alterara informa no campo de razao e retorna false
            razao.assign("Pontuacao invalida no arquivo de score em: " + line);
            return {false, razao};
        }
    }
    
    return {true, razao};
}

void Forca::carrega_arquivos(){
    std::ifstream file(this->m_arquivo_palavras);//abre o arquivo de palavras
    
    std::string line, subline, delimiter = ", ";// delimitador para quando chegar em score separar os acertos
    std::vector<Palavra> vetor_palavras;
    Palavra atual_p;// cria a palavr atual
    size_t pos = 0, pos_2 = 0;

    while (!file.eof()) {//enquanto nao chegar no fim do arquivo
        std::getline(file, line);
        if (line.size() <= 1)// linhas vzias ou com \n sao puladas
            continue;
        pos = line.find(" ");// procura o primeiro espaco vazio
        atual_p.set_palavra(line.substr(0,pos));// considera do inicio da linha ate pos como sendo a palavra e guarda em atual_p
        line.erase(0, pos);
        pos_2 = line.find_first_not_of(" ");//procura a frequencia
        line.erase(0, pos_2);
        atual_p.set_id(std::stoi(line));//converte de string para int e guarda em atual_s a frequencia
        vetor_palavras.push_back(atual_p);// da um push_back em atual_p no vetor de palavras
    }
    this->m_palavras = vetor_palavras;
    file.close();//fecha o arquivo

    std::ifstream file2(this->m_arquivo_scores);// abre o arquivo score
    std::vector<Score> vetor_score;

    while (!file2.eof()) {//itera ate o fim do arquivo
        Score atual_s;
        std::getline(file2, line);
        if (line.size() <= 1)//linhas vazias sao puladas
            continue;
        pos = line.find(";");//procura o primeiro ';' e considera que eh a dificudade
        subline = line.substr(0,pos);
        if (subline.compare("Médio") == 0)// seta a dificuldade de acordo
            atual_s.set_dificuldade(Dificuldade::MEDIO);
        else if(subline.compare("Difícil") == 0)
            atual_s.set_dificuldade(Dificuldade::DIFICIL);
        else
            atual_s.set_dificuldade(Dificuldade::FACIL);
        
        line.erase(0, pos+2);// apaga a dificuldade da linha

        pos = line.find(";");//procura o proximo ';' que corresponde ao nome
        subline = line.substr(0,pos);
        atual_s.set_nome(subline);//guarda em atual_s

        line.erase(0, pos+2);//apaga o nome da linha

        subline.clear();
        while ((pos = line.find(delimiter)) != std::string::npos) {// enquanto tiver palavras que o jogador acertou
        subline = line.substr(0, pos);
        atual_s.add_acertos(subline);// adiciona a atual_s os acertos
        line.erase(0, pos + delimiter.length());// apaga da linha o acerto
        }
        pos = line.find(";");
        subline = line.substr(0, pos);
        atual_s.add_acertos(subline);// faz para o ultimo
        line.erase(0, pos + 2);

        atual_s.set_pontuacao(std::stoi(line));
        vetor_score.push_back(atual_s);// da um push_back em atual_s no vetor de scores
    }

    this->score_carregado = vetor_score;// coloca o vetor carregado no campo certo em de Forca
    file2.close();// fecha o arquivo
}

void Forca::set_dificuldade(Dificuldade d){
    this->d = d;
}

std::string Forca::proxima_palavra(){
    string palavra;
    int tam = this->m_palavras.size(), media = 0;
    for (int i = 0; i < tam; i++){
        media += this->m_palavras[i].get_id();
    }
    media /= tam;
    if (this->d == FACIL){
        for (int i = 0; i < tam; i++){
            if ((this->m_palavras[i].get_id() >= media) && (find(this->sorteadas.begin(), this->sorteadas.end(), this->m_palavras[i].get_id()) != this->sorteadas.end())){
                this->sorteadas.push_back(this->m_palavras[i].get_id());
                return this->m_palavras[i].get_palavra();
            }
        }
    }
    if (this->d == MEDIO){
        for (int i = 0; i < tam; i++){
            if ((this->m_palavras[i].get_id() <= media) && (find(this->sorteadas.begin(), this->sorteadas.end(), this->m_palavras[i].get_id()) != this->sorteadas.end())){
                this->sorteadas.push_back(this->m_palavras[i].get_id());
                return this->m_palavras[i].get_palavra();
            }
        }
    }
    if (this->d == DIFICIL){
        for (int i = 0; i < tam; i++){
            if ((this->m_palavras[i].get_id() <= media) && (find(this->sorteadas.begin(), this->sorteadas.end(), this->m_palavras[i].get_id()) != this->sorteadas.end())){
                this->sorteadas.push_back(this->m_palavras[i].get_id());
                return this->m_palavras[i].get_palavra();
            }
        }
    }







    return palavra;
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
        if (elem.get_dificuldade() == 1)
            cout << "Dificuldade: Médio, ";
        else if(elem.get_dificuldade() == 2)
            cout << "Dificuldade: Difícil, ";
        else
            cout << "Dificuldade: Fácil, ";
        cout << "Nome: " + elem.get_nome() + ", ";
        cout << "Acertos: ";
        for (long unsigned int i = 0; i < ac.size(); i++){
            cout << ac[i] + ", ";
        }
        cout << "Pontuacao: " << elem.get_pontuacao() << endl;
    }
}

void Forca::add_sorteadas(int id){
    this->sorteadas.push_back(id);
}

void Forca::limpar_sorteadas(){
    this->sorteadas.clear();
}