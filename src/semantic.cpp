// =============================================================
//  semantic.cpp - Implementação do Analisador Semântico
// =============================================================
#include "semantic.h"

#include <cctype>
#include <iostream>

using namespace std;

// Verifica se o texto é um número inteiro (só dígitos).
static bool ehNumero(const string& valor)
{
    if (valor.empty())
        return false;

    for (char c : valor)
    {
        if (!isdigit(static_cast<unsigned char>(c)))
            return false;
    }
    return true;
}

static bool ehDirecao(const string& valor)
{
    return valor == "direita" || valor == "esquerda";
}

Semantic::Semantic(const vector<Instrucao>& lista)
    : instrucoes(lista)
{
}

void Semantic::erro(int linha, const string& mensagem) const
{
    cout << endl;
    cout << "ERRO SEMANTICO! (linha " << linha << ")" << endl;
    cout << mensagem << endl;
}

// Percorre as instruções na ordem e valida cada uma.
bool Semantic::analisar()
{
    for (const Instrucao& instrucao : instrucoes)
    {
        bool ok = true;

        if (instrucao.operacao == "DECLARAR")      ok = declarar(instrucao);
        else if (instrucao.operacao == "ATRIBUIR") ok = atribuir(instrucao);
        else if (instrucao.operacao == "ANDAR")    ok = andar(instrucao);
        else if (instrucao.operacao == "VIRAR")    ok = virar(instrucao);

        if (!ok)
            return false;
    }
    return true;
}

// DECLARAR tipo nome -> não pode haver duas variáveis com o mesmo nome.
bool Semantic::declarar(const Instrucao& instrucao)
{
    const string& tipo = instrucao.argumento1;
    const string& nome = instrucao.argumento2;

    if (!tabela.Insert(nome, {nome, tipo, "-"}))
    {
        erro(instrucao.linha, "Identificador '" + nome + "' ja declarado.");
        return false;
    }
    return true;
}

// ATRIBUIR nome valor -> variável declarada e valor do tipo correto.
bool Semantic::atribuir(const Instrucao& instrucao)
{
    const string& nome = instrucao.argumento1;
    const string& valor = instrucao.argumento2;

    Symbol* simbolo = tabela.Find(nome);
    if (simbolo == nullptr)
    {
        erro(instrucao.linha, "Identificador '" + nome + "' nao declarado.");
        return false;
    }

    if (simbolo->tipo == "numero" && !ehNumero(valor))
    {
        erro(instrucao.linha, "A variavel '" + nome + "' espera numero, recebeu '" + valor + "'.");
        return false;
    }

    if (simbolo->tipo == "direcao" && !ehDirecao(valor))
    {
        erro(instrucao.linha, "A variavel '" + nome + "' espera direcao, recebeu '" + valor + "'.");
        return false;
    }

    simbolo->valor = valor;
    return true;
}

// ANDAR arg -> literal numérico ou variável numero com valor.
bool Semantic::andar(const Instrucao& instrucao)
{
    if (ehNumero(instrucao.argumento1))
        return true;

    return verificarUso(instrucao, "numero", "andar");
}

// VIRAR arg -> direita/esquerda ou variável direcao com valor.
bool Semantic::virar(const Instrucao& instrucao)
{
    if (ehDirecao(instrucao.argumento1))
        return true;

    return verificarUso(instrucao, "direcao", "virar");
}

bool Semantic::verificarUso(const Instrucao& instrucao,
                            const string& tipoEsperado,
                            const string& comando)
{
    const string& nome = instrucao.argumento1;
    Symbol* simbolo = tabela.Find(nome);

    if (simbolo == nullptr)
    {
        erro(instrucao.linha, "Identificador '" + nome + "' nao declarado.");
        return false;
    }

    if (simbolo->tipo != tipoEsperado)
    {
        erro(instrucao.linha, "'" + comando + "' espera " + tipoEsperado +
                              ", mas '" + nome + "' e do tipo " + simbolo->tipo + ".");
        return false;
    }

    if (simbolo->valor == "-")
    {
        erro(instrucao.linha, "Identificador '" + nome + "' usado sem valor atribuido.");
        return false;
    }

    return true;
}

void Semantic::mostrarTabela() const
{
    tabela.Show();
}
