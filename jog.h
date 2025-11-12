#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

#define LIMPAR system("cls");

class Funcionario{
    public:
        int id;
        /* Aqui vai ter um
        dicionario com os
        atributos
        Inteligência
        Pesquisa e Desenvolvimento
        Motivação
        */
        double salario;
};

class Empresa{
    public:
        string nome;
        double valor = 0 ;
        vector<Funcionario> funcionarios;

        map<string, int> melhorias = {
            {"Ambiente", 1},
            {"Infraestrutura", 1},
            {"Marketing", 1}
        };
};

string NomeDoEmpresario;
double dinheiro;
int dia;

string op;

vector<Empresa> Empresas;

void menu();
void criarEmpresa(string nome);