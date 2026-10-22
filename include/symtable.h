// =============================================================
//  symtable.h - Tabela de Símbolos
// -------------------------------------------------------------
//  Guarda as variáveis declaradas: nome, tipo e valor atual.
//  Mantém a ordem de declaração para exibir a tabela.
// =============================================================
#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <string>
#include <unordered_map>
#include <vector>

struct Symbol
{
    std::string nome;
    std::string tipo;    // "numero" ou "direcao"
    std::string valor;   // "-" enquanto não houver atribuição
};

class SymTable
{
private:
    std::unordered_map<std::string, Symbol> tabela;   // busca rápida
    std::vector<std::string> ordem;                   // ordem de declaração

public:
    // Insere um símbolo. Devolve false se o nome já existe.
    bool Insert(const std::string& nome, const Symbol& simbolo);

    // Procura um símbolo. Devolve nullptr se não existe.
    Symbol* Find(const std::string& nome);

    // Imprime a tabela formatada.
    void Show() const;
};

#endif
