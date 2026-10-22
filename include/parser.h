// =============================================================
//  parser.h - Analisador Sintático
// -------------------------------------------------------------
//  Segunda fase: verifica se a sequência de tokens segue a
//  gramática da linguagem (descida recursiva) e gera a lista
//  de instruções.
//
//  Gramática:
//    programa    -> INICIO declaracao* comando+ FIM
//    declaracao  -> (TIPO_NUMERO | TIPO_DIRECAO) IDENTIFICADOR ;
//    comando     -> atribuicao | andar | virar
//    atribuicao  -> IDENTIFICADOR = (NUMERO | direcao) ;
//    andar       -> ANDAR (NUMERO | IDENTIFICADOR) ;
//    virar       -> VIRAR (direcao | IDENTIFICADOR) ;
//    direcao     -> DIREITA | ESQUERDA
// =============================================================
#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "instrucao.h"

#include <cstddef>
#include <string>
#include <vector>

class Parser
{
private:
    std::vector<Token> tokens;
    std::size_t posicao;                 // índice do token atual
    std::vector<Instrucao> instrucoes;   // saída do parser

    // Funções auxiliares
    bool temToken() const;
    bool atualEh(TipoToken tipo) const;
    int linhaAtual() const;
    void erro(const std::string& esperado);
    bool consumir(TipoToken esperado);

    // Uma função para cada regra da gramática
    bool declaracao();
    bool comando();
    bool atribuicao();
    bool andar();
    bool virar();

public:
    explicit Parser(const std::vector<Token>& listaTokens);

    // Regra inicial. Devolve true se o programa é sintaticamente válido.
    bool programa();

    const std::vector<Instrucao>& getInstrucoes() const;
};

#endif
