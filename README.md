# Mini Compilador do Robô

Compilador didático para uma linguagem simples de comandos de um robô.
Executa as três fases de análise: **léxica → sintática → semântica**.

## Estrutura

```
Projeto Robo/
├── include/           # Cabeçalhos (.h)
│   ├── lexer.h        # Tokens e analisador léxico
│   ├── instrucao.h    # Instrução intermediária gerada pelo parser
│   ├── parser.h       # Analisador sintático (com a gramática)
│   ├── symtable.h     # Tabela de símbolos
│   └── semantic.h     # Analisador semântico
├── src/               # Implementações (.cpp)
│   ├── aula6.cpp      # main: encadeia as três fases
│   ├── lexer.cpp
│   ├── parser.cpp
│   ├── symtable.cpp
│   └── semantic.cpp
├── exemplos/          # Programas de teste (válido e com erros)
├── build.bat          # Compila com g++
└── CMakeLists.txt     # Compila com CMake
```

## Como compilar

Opção 1 — g++ direto (Windows):

```
build.bat
```

Opção 2 — CMake:

```
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

## Como executar

```
build\aula6.exe exemplos\valido.txt     # lê de um arquivo
build\aula6.exe                         # digita no teclado, termina com 'fim'
```

## A linguagem

```
inicio
    numero passos;        // declarações (opcionais) vêm primeiro
    direcao lado;

    passos = 10;          // atribuição
    lado = direita;
    andar passos;         // andar <numero | variavel numero>
    virar lado;           // virar <direita | esquerda | variavel direcao>
fim
```

Gramática:

```
programa    -> INICIO declaracao* comando+ FIM
declaracao  -> (numero | direcao) IDENTIFICADOR ;
comando     -> atribuicao | andar | virar
atribuicao  -> IDENTIFICADOR = (NUMERO | direita | esquerda) ;
andar       -> andar (NUMERO | IDENTIFICADOR) ;
virar       -> virar (direita | esquerda | IDENTIFICADOR) ;
```

Comentários de linha com `//` são aceitos.

## Erros detectados

| Fase       | Exemplos                                                      |
|------------|---------------------------------------------------------------|
| Léxica     | símbolo desconhecido (`@`, `#`, ...)                          |
| Sintática  | falta de `;`, falta de `inicio`/`fim`, nenhum comando         |
| Semântica  | variável não declarada, declarada duas vezes, tipo errado, usada sem valor |

Todas as mensagens informam a linha do erro.
