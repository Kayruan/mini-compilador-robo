// =============================================================
//  instrucao.h - Representação intermediária
// -------------------------------------------------------------
//  O parser gera uma lista de instruções simples que depois é
//  verificada pelo analisador semântico.
//
//  operacao     argumento1          argumento2
//  ---------    -----------------   ----------------
//  DECLARAR     tipo (numero/...)   nome da variável
//  ATRIBUIR     nome da variável    valor atribuído
//  ANDAR        número ou variável  (vazio)
//  VIRAR        direção ou variável (vazio)
// =============================================================
#ifndef INSTRUCAO_H
#define INSTRUCAO_H

#include <string>

struct Instrucao
{
    std::string operacao;
    std::string argumento1;
    std::string argumento2;
    int linha;   // linha do código-fonte (para mensagens de erro)
};

#endif
