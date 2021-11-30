# Trabalho-1
Repositório contendo as especificações do Trabalho 1 da disciplina de LP1

## Compilacao
Na pasta root, digite:

```bash
make all
```

## Execucao

na pasta root apos a compilacao digite:

```bash
./forca [argumento1] [argumento2]
```
Onde [argumento1] representa o caminho do arquivo de palavras a ser selecionado e [argumento2] representa o caminho do arquivo de score a ser selecionado.

Exemplo:
```bash
./forca data/palavras_funcional.txt data/score_funcional.txt
```

### testes:
O repositorio contem varios arquivos na pasta data/ dois funcionais nomeados *_funcional.txt e  com problema nomeados *_erro_*.txt, para realizar testes no codigo basta realizar a etapa de execucao alterando os arquivos para os que tem problema.

## Funcionalidades/Limitacoes
o codigo nao inicia o jogo, apenas prepara tudo para iniciar

# Documento de Especificação

Leia o documento de especificação contido em [Especificação do Trabalho 1](https://docs.google.com/document/d/1X3VDW6EBE_ZRDHCoRNwqva17R1EZMpwDunRgDg9N4HU/edit?usp=sharing). Preencha o [author.md](author.md) com as informações relativas ao grupo/autor.

# Avaliação

## Código | Funcionalidades
1. Classe forca 10/10
- Como boa parte está implementada vou considerar 100%, mas veja a observação que fiz sobre o uso do construtor.

2. Interface textual 5/10
- Não mostra o jogo em sí.

3. Execução completa do jogo 5/15
- Não executa o jogo apenas os menus iniciais.

4. Validação dos arquivos de texto 5/5

5. Arquivos de teste de validação dos casos de erro 5/5

6. Arquivos de teste de validação dos níveis de dificuldade 1/5
- A ideia aqui era vc enviar diferentes arquivos palavras.txt para testar os modos de dificuldade, especialmente
o caso de game over onde o usuário acerta todas as palavras.

7. Observações gerais
- Escolher colocar no loop do jogo no construtor foi uma escolha bem ruim, nesses casos o mais comum é ter um construtor
depois um método "start ou run", por exemplo. Aí primeiro vc constroi o objeto e depois chama o método.

## Código | Boas práticas

1. Documentação do código e readme 6/10
- Não vou considerar 100% da documentação dos outros arquivos uma vez que vc não seguiu o padrão Doxygen ou algum padrão
profissional de documentação.

2. Organização e indentação 5/10
- Muitas partes do código estão com problemas de indentação, mas a organização ficou muito boa!

3. Compilação automatizada 5/5


