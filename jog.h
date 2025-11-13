#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <chrono>

using namespace std;

#define CACETINHO system("chcp 65001");

#define LIMPAR system("cls");

vector<string> ListaNomes = {"Luiz","Luis", "Marcos", "Luan", "Roberto", "Bernado", "Lucas", "Rogilson", "Romário", "Bob", "João", "Manuel"};

class Funcionario{
    public:
        string nome;
        int id;
        map<string, int> atributos = {
            {"Inteligencia", 1},
            {"Desenvolvimento e Pesquisa", 1},
            {"Motivacao", 1}
        };
        double salario;
        int overall = 0;
    


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
vector<Funcionario> Contratacoes;

void menu();
void criarEmpresa(string nome);
void ContratarFuncionario();
void SortearContratacoes();
void SistemaContratacao();
void limpar_buffer();