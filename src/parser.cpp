// =============================================================
//  parser.cpp - Implementação do Analisador Sintático
//  (descida recursiva: uma função por regra da gramática)
// =============================================================
#include "parser.h"

#include <iostream>

using namespace std;

Parser::Parser(const vector<Token>& listaTokens)
    : tokens(listaTokens), posicao(0)
{
}

// -------------------------------------------------------------
//  Auxiliares
// -------------------------------------------------------------

// Ainda existem tokens a ler?
bool Parser::temToken() const
{
    return posicao < tokens.size();
}

// O token atual é do tipo informado?
bool Parser::atualEh(TipoToken tipo) const
{
    return temToken() && tokens[posicao].tipo == tipo;
}

// Linha do token atual (ou do último, se a entrada acabou).
int Parser::linhaAtual() const
{
    if (temToken())
        return tokens[posicao].linha;
    return tokens.empty() ? 1 : tokens.back().linha;
}

// Mensagem padrão de erro sintático.
void Parser::erro(const string& esperado)
{
    cout << endl;
    cout << "ERRO SINTATICO! (linha " << linhaAtual() << ")" << endl;
    cout << "Esperado: " << esperado << endl;
    cout << "Encontrado: "
         << (temToken() ? "'" + tokens[posicao].valor + "'" : "FIM DA ENTRADA")
         << endl;
}

// Se o token atual for o esperado, avança; senão, reporta erro.
bool Parser::consumir(TipoToken esperado)
{
    if (atualEh(esperado))
    {
        posicao++;
        return true;
    }

    erro(nomeToken(esperado));
    return false;
}

// -------------------------------------------------------------
//  programa -> INICIO declaracao* comando+ FIM
// -------------------------------------------------------------
bool Parser::programa()
{
    if (!consumir(INICIO))
        return false;

    // Zero ou mais declarações
    while (atualEh(TIPO_NUMERO) || atualEh(TIPO_DIRECAO))
    {
        if (!declaracao())
            return false;
    }

    // Um ou mais comandos
    size_t inicioComandos = posicao;

    while (atualEh(ANDAR) || atualEh(VIRAR) || atualEh(IDENTIFICADOR))
    {
        if (!comando())
            return false;
    }

    if (posicao == inicioComandos)
    {
        erro("pelo menos um comando (andar, virar ou atribuicao)");
        return false;
    }

    if (!consumir(FIM))
        return false;

    // Nada pode vir depois de 'fim'
    if (temToken())
    {
        erro("nada depois de 'fim'");
        return false;
    }

    return true;
}

// -------------------------------------------------------------
//  declaracao -> (TIPO_NUMERO | TIPO_DIRECAO) IDENTIFICADOR ;
// -------------------------------------------------------------
bool Parser::declaracao()
{
    int linha = linhaAtual();
    string tipo = tokens[posicao].valor;   // "numero" ou "direcao"
    posicao++;

    if (!atualEh(IDENTIFICADOR))
    {
        erro("IDENTIFICADOR");
        return false;
    }
    string nome = tokens[posicao].valor;
    posicao++;

    if (!consumir(PONTO_VIRGULA))
        return false;

    instrucoes.push_back({"DECLARAR", tipo, nome, linha});
    return true;
}

// -------------------------------------------------------------
//  comando -> atribuicao | andar | virar
// -------------------------------------------------------------
bool Parser::comando()
{
    if (atualEh(IDENTIFICADOR)) return atribuicao();
    if (atualEh(ANDAR))         return andar();
    if (atualEh(VIRAR))         return virar();

    erro("ANDAR, VIRAR ou IDENTIFICADOR");
    return false;
}

// -------------------------------------------------------------
//  atribuicao -> IDENTIFICADOR = (NUMERO | DIREITA | ESQUERDA) ;
// -------------------------------------------------------------
bool Parser::atribuicao()
{
    int linha = linhaAtual();
    string nome = tokens[posicao].valor;
    posicao++;

    if (!consumir(IGUAL))
        return false;

    if (!(atualEh(NUMERO) || atualEh(DIREITA) || atualEh(ESQUERDA)))
    {
        erro("NUMERO, DIREITA ou ESQUERDA");
        return false;
    }
    string valor = tokens[posicao].valor;
    posicao++;

    if (!consumir(PONTO_VIRGULA))
        return false;

    instrucoes.push_back({"ATRIBUIR", nome, valor, linha});
    return true;
}

// -------------------------------------------------------------
//  andar -> ANDAR (NUMERO | IDENTIFICADOR) ;
// -------------------------------------------------------------
bool Parser::andar()
{
    int linha = linhaAtual();
    posicao++;   // consome 'andar'

    if (!(atualEh(NUMERO) || atualEh(IDENTIFICADOR)))
    {
        erro("NUMERO ou IDENTIFICADOR");
        return false;
    }
    string argumento = tokens[posicao].valor;
    posicao++;

    if (!consumir(PONTO_VIRGULA))
        return false;

    instrucoes.push_back({"ANDAR", argumento, "", linha});
    return true;
}

// -------------------------------------------------------------
//  virar -> VIRAR (DIREITA | ESQUERDA | IDENTIFICADOR) ;
// -------------------------------------------------------------
bool Parser::virar()
{
    int linha = linhaAtual();
    posicao++;   // consome 'virar'

    if (!(atualEh(DIREITA) || atualEh(ESQUERDA) || atualEh(IDENTIFICADOR)))
    {
        erro("DIREITA, ESQUERDA ou IDENTIFICADOR");
        return false;
    }
    string argumento = tokens[posicao].valor;
    posicao++;

    if (!consumir(PONTO_VIRGULA))
        return false;

    instrucoes.push_back({"VIRAR", argumento, "", linha});
    return true;
}

const vector<Instrucao>& Parser::getInstrucoes() const
{
    return instrucoes;
}
