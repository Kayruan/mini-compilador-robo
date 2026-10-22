// =============================================================
//  lexer.h - Analisador Léxico
// -------------------------------------------------------------
//  Primeira fase do compilador: transforma o texto do programa
//  em uma lista de tokens (palavras com significado).
// =============================================================
#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

// Todos os tipos de token que a linguagem do robô reconhece.
enum TipoToken
{
    // Delimitadores do programa
    INICIO,         // inicio
    FIM,            // fim

    // Comandos do robô
    ANDAR,          // andar
    VIRAR,          // virar

    // Valores de direção
    DIREITA,        // direita
    ESQUERDA,       // esquerda

    // Literal numérico
    NUMERO,         // 10, 25, ...

    // Tipos usados em declarações
    TIPO_NUMERO,    // numero
    TIPO_DIRECAO,   // direcao

    // Nomes de variáveis
    IDENTIFICADOR,  // passos, lado, ...

    // Símbolos
    IGUAL,          // =
    PONTO_VIRGULA,  // ;

    INVALIDO
};

// Um token: seu tipo, o texto original e a linha onde apareceu.
struct Token
{
    TipoToken tipo;
    std::string valor;
    int linha;
};

// Percorre o código-fonte e devolve a lista de tokens.
// Em caso de erro léxico, imprime a mensagem e devolve lista vazia.
std::vector<Token> analisarLexico(const std::string& codigo);

// Devolve o nome legível de um tipo de token (para exibição).
std::string nomeToken(TipoToken tipo);

#endif
