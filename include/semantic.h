// =============================================================
//  semantic.h - Analisador Semântico
// -------------------------------------------------------------
//  Terceira fase: verifica o significado do programa.
//    - variável declarada duas vezes
//    - variável usada sem ser declarada
//    - tipo incompatível (ex.: numero recebendo direita)
//    - variável usada sem valor atribuído
// =============================================================
#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "instrucao.h"
#include "symtable.h"

#include <string>
#include <vector>

class Semantic
{
private:
    std::vector<Instrucao> instrucoes;
    SymTable tabela;

    void erro(int linha, const std::string& mensagem) const;

    // Uma verificação para cada tipo de instrução
    bool declarar(const Instrucao& instrucao);
    bool atribuir(const Instrucao& instrucao);
    bool andar(const Instrucao& instrucao);
    bool virar(const Instrucao& instrucao);

    // Garante que a variável existe, tem o tipo esperado e possui valor.
    bool verificarUso(const Instrucao& instrucao,
                      const std::string& tipoEsperado,
                      const std::string& comando);

public:
    explicit Semantic(const std::vector<Instrucao>& lista);

    // Devolve true se o programa é semanticamente válido.
    bool analisar();

    void mostrarTabela() const;
};

#endif
