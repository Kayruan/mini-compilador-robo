// =============================================================
//  symtable.cpp - Implementação da Tabela de Símbolos
// =============================================================
#include "symtable.h"

#include <iomanip>
#include <iostream>

using namespace std;

bool SymTable::Insert(const string& nome, const Symbol& simbolo)
{
    // insert() não sobrescreve: .second é false se o nome já existia
    bool inserido = tabela.insert({nome, simbolo}).second;

    if (inserido)
        ordem.push_back(nome);

    return inserido;
}

Symbol* SymTable::Find(const string& nome)
{
    auto encontrado = tabela.find(nome);

    if (encontrado == tabela.end())
        return nullptr;

    return &encontrado->second;
}

void SymTable::Show() const
{
    const string separador(45, '-');

    cout << endl;
    cout << "TABELA DE SIMBOLOS" << endl;
    cout << separador << endl;
    cout << left << setw(15) << "NOME" << setw(15) << "TIPO" << setw(15) << "VALOR" << endl;
    cout << separador << endl;

    // Exibe na ordem em que as variáveis foram declaradas
    for (const string& nome : ordem)
    {
        const Symbol& s = tabela.at(nome);
        cout << left << setw(15) << s.nome << setw(15) << s.tipo << setw(15) << s.valor << endl;
    }

    cout << separador << endl;
}
