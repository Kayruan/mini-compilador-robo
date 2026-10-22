// =============================================================
//  aula6.cpp - Programa principal do Mini Compilador do Robô
// -------------------------------------------------------------
//  Executa as três fases em sequência:
//    1. Análise léxica     (lexer.cpp)    texto   -> tokens
//    2. Análise sintática  (parser.cpp)   tokens  -> instruções
//    3. Análise semântica  (semantic.cpp) instruções -> tabela de símbolos
//
//  Uso:
//    aula6                 lê o programa do teclado (termine com 'fim')
//    aula6 arquivo.txt     lê o programa de um arquivo
// =============================================================
#include "lexer.h"
#include "parser.h"
#include "semantic.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Lê o programa inteiro de um arquivo.
static bool lerArquivo(const string& caminho, string& codigo)
{
    ifstream arquivo(caminho);
    if (!arquivo)
        return false;

    stringstream buffer;
    buffer << arquivo.rdbuf();
    codigo = buffer.str();
    return true;
}

// Lê linhas do teclado até encontrar a palavra 'fim'.
static string lerTeclado()
{
    cout << "Digite o programa (termine com fim):" << endl << endl;

    string codigo, linha;
    const regex fimDoPrograma(R"(\bfim\b)");

    while (getline(cin, linha))
    {
        codigo += linha + '\n';
        if (regex_search(linha, fimDoPrograma))
            break;
    }
    return codigo;
}

int main(int argc, char* argv[])
{
    cout << "==============================" << endl;
    cout << "      MINI COMPILADOR" << endl;
    cout << "==============================" << endl << endl;

    // ---------- Entrada ----------
    string codigo;

    if (argc > 1)
    {
        if (!lerArquivo(argv[1], codigo))
        {
            cout << "Nao foi possivel abrir o arquivo: " << argv[1] << endl;
            return 1;
        }
        cout << "Arquivo: " << argv[1] << endl << endl;
        cout << codigo << endl;
    }
    else
    {
        codigo = lerTeclado();
    }

    // Remove o BOM UTF-8 que alguns editores (ex.: Bloco de Notas) colocam no início
    if (codigo.rfind("\xEF\xBB\xBF", 0) == 0)
        codigo.erase(0, 3);

    if (codigo.find_first_not_of(" \t\r\n\v\f") == string::npos)
    {
        cout << "ERRO SINTATICO! Programa vazio." << endl;
        return 1;
    }

    // ---------- 1. Análise léxica ----------
    vector<Token> tokens = analisarLexico(codigo);
    if (tokens.empty())
        return 1;

    cout << endl << "ANALISE LEXICA: OK" << endl << endl;
    cout << "TOKENS:" << endl;
    cout << "------------------------" << endl;
    for (const Token& token : tokens)
        cout << nomeToken(token.tipo) << " -> " << token.valor << endl;

    // ---------- 2. Análise sintática ----------
    Parser parser(tokens);
    if (!parser.programa())
        return 1;

    cout << endl << "ANALISE SINTATICA: OK" << endl;

    // ---------- 3. Análise semântica ----------
    Semantic semantic(parser.getInstrucoes());
    if (!semantic.analisar())
        return 1;

    cout << endl << "ANALISE SEMANTICA: OK" << endl;
    semantic.mostrarTabela();

    cout << endl << "PROGRAMA ACEITO!" << endl;
    return 0;
}
