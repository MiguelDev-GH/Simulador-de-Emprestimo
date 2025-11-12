#include "jog.h"

void criarEmpresa(string nome){
    Empresa nova;
    nova.nome = nome;

    Empresas.push_back(nova);

}

void DetalharEmpresa(Empresa emp){
    LIMPAR
    cout << "Detalhes de " << emp.nome << endl;
    cout << "Valor da empresa: R$ " << emp.valor << endl;
    cout << "Quantidade de funcionários: " << emp.funcionarios.size() << endl;
    cout << "Ambiente NV " << emp.melhorias["Ambiente"]<< endl; 
    cout << "Infraestrutura NV " << emp.melhorias["Infraestrutura"]<< endl; 
    cout << "Marketing NV " << emp.melhorias["Marketing"]<< endl; 

    system("PAUSE");
}

void menu(){

    LIMPAR
    
    cout << "~ " << NomeDoEmpresario << " | " << "R$ " << dinheiro << endl;
    cout << "Dia " << dia << endl;
    
    cout << "| Gerenciar EMPRESAS |" << endl;

    for(int i = 0;i < Empresas.size();i++){
        cout << i+1 << "- " << Empresas[i].nome << endl;
    }

    cout << "2- " << endl;

    cin >> op;

    string opGerenciarEmpresas = to_string(Empresas.size());

    if(op > "0" && op <= opGerenciarEmpresas){
        LIMPAR

        int empNum = stoi(op) - 1;

        cout << "~ Empresa: " << Empresas[empNum].nome << endl;

        cout << "\n1- Detalhes" << endl; 
        cout << "2- Deletar Empresa" << endl; // Opção não feita ainda
        cin >> op;

        if(op == "1") DetalharEmpresa(Empresas[empNum]);

    }

    dia++;
}