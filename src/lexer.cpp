// =============================================================
//  lexer.cpp - Implementação do Analisador Léxico
// =============================================================
#include "lexer.h"

#include <cctype>
#include <iostream>
#include <unordered_map>

using namespace std;

// Palavras reservadas da linguagem e seus tokens.
static const unordered_map<string, TipoToken> palavrasReservadas = {
    {"inicio",   INICIO},
    {"fim",      FIM},
    {"andar",    ANDAR},
    {"virar",    VIRAR},
    {"direita",  DIREITA},
    {"esquerda", ESQUERDA},
    {"numero",   TIPO_NUMERO},
    {"direcao",  TIPO_DIRECAO},
};

// Wrappers para usar as funções de <cctype> com segurança em char.
static bool ehLetra(char c)  { return isalpha(static_cast<unsigned char>(c)) || c == '_'; }
static bool ehDigito(char c) { return isdigit(static_cast<unsigned char>(c)); }
static bool ehEspaco(char c) { return isspace(static_cast<unsigned char>(c)); }

vector<Token> analisarLexico(const string& codigo)
{
    vector<Token> tokens;
    size_t i = 0;
    int linha = 1;

    while (i < codigo.size())
    {
        char c = codigo[i];

        // 1) Espaços em branco são ignorados (contando as linhas)
        if (ehEspaco(c))
        {
            if (c == '\n')
                linha++;
            i++;
        }

        // 2) Comentário de linha: // até o fim da linha
        else if (c == '/' && i + 1 < codigo.size() && codigo[i + 1] == '/')
        {
            while (i < codigo.size() && codigo[i] != '\n')
                i++;
        }

        // 3) Palavra: reservada ou identificador
        //    (começa com letra/_ e pode conter letras, dígitos e _)
        else if (ehLetra(c))
        {
            string palavra;
            while (i < codigo.size() && (ehLetra(codigo[i]) || ehDigito(codigo[i])))
                palavra += codigo[i++];

            auto it = palavrasReservadas.find(palavra);
            TipoToken tipo = (it != palavrasReservadas.end()) ? it->second : IDENTIFICADOR;
            tokens.push_back({tipo, palavra, linha});
        }

        // 4) Número inteiro
        else if (ehDigito(c))
        {
            string numero;
            while (i < codigo.size() && ehDigito(codigo[i]))
                numero += codigo[i++];

            tokens.push_back({NUMERO, numero, linha});
        }

        // 5) Símbolos
        else if (c == '=')
        {
            tokens.push_back({IGUAL, "=", linha});
            i++;
        }
        else if (c == ';')
        {
            tokens.push_back({PONTO_VIRGULA, ";", linha});
            i++;
        }

        // 6) Qualquer outra coisa é erro léxico
        else
        {
            cout << "ERRO LEXICO! (linha " << linha << ")" << endl;
            cout << "Simbolo nao reconhecido: '" << c << "'" << endl;
            return {};
        }
    }

    return tokens;
}

string nomeToken(TipoToken tipo)
{
    switch (tipo)
    {
        case INICIO:        return "INICIO";
        case FIM:           return "FIM";
        case ANDAR:         return "ANDAR";
        case VIRAR:         return "VIRAR";
        case DIREITA:       return "DIREITA";
        case ESQUERDA:      return "ESQUERDA";
        case NUMERO:        return "NUMERO";
        case TIPO_NUMERO:   return "TIPO_NUMERO";
        case TIPO_DIRECAO:  return "TIPO_DIRECAO";
        case IDENTIFICADOR: return "IDENTIFICADOR";
        case IGUAL:         return "IGUAL";
        case PONTO_VIRGULA: return "PONTO_VIRGULA";
        default:            return "INVALIDO";
    }
}
