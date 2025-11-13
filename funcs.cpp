#include "jog.h"

void limpar_buffer(){
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void input(){
    cin >> op;
    limpar_buffer();
}

void criarEmpresa(string nome){
    Empresa nova;
    nova.nome = nome;

    Empresas.push_back(nova);

}

void DetalharEmpresa(Empresa emp){
    LIMPAR
    cout << "Detalhes de " << emp.nome << endl;
    cout << "Valor da empresa: R$ " << emp.valor << endl;
    cout << "\nQuantidade de funcionários: " << emp.funcionarios.size() << endl;
    cout << "\nAmbiente NV " << emp.melhorias["Ambiente"]<< endl; 
    cout << "Infraestrutura NV " << emp.melhorias["Infraestrutura"]<< endl; 
    cout << "Marketing NV " << emp.melhorias["Marketing"] << "\n\n"; 

    input();

}

void menu(){

    LIMPAR
    
    cout << "~ " << NomeDoEmpresario << " | " << "Dia " << dia << endl;
    cout << "R$ " << dinheiro << endl;
    
    cout << "\n| Gerenciar EMPRESAS |" << endl;
    
    for(int i = 0;i < Empresas.size();i++){
        cout << i+1 << "- " << Empresas[i].nome << endl;
    }

    cout << "\n" << Empresas.size() + 1 << "- Contratar Funcionários" << endl;
    input();

    string opGerenciarEmpresas = to_string(Empresas.size());

    if(op > "0" && op <= opGerenciarEmpresas){
        LIMPAR

        int empNum = stoi(op) - 1;

        cout << "~ Empresa: " << Empresas[empNum].nome << endl;

        cout << "\n1- Detalhes" << endl; 
        cout << "2- Deletar Empresa" << endl; // Opção não feita ainda
        input();

        if(op == "1") DetalharEmpresa(Empresas[empNum]);
        else if (op == to_string(Empresas.size() + 1));

    } else if(op == to_string(Empresas.size() + 1)){
        SistemaContratacao();
    }

    dia++;
}

void SistemaContratacao(){
    srand(time(NULL));

    LIMPAR

    for(int i = 0; i < 3;i++){

        double salario = 0;

        Funcionario novo;
        novo.nome = ListaNomes[(rand() % ListaNomes.size()) + 1];
        novo.id = i;

        for(auto& func : novo.atributos){
            func.second = (rand() % 5) + 1;
            novo.overall += func.second;
            salario += func.second;
        }        

        novo.salario = ((salario*salario) * 50) + 1200;

        Contratacoes.push_back(novo);

    }

    cout << "----------Menu-De-Contratação------------\n\n";
    for(auto i : Contratacoes){

        printf("%s > %d <\n",i.nome.c_str(),i.overall);

        for(auto& func : i.atributos){
            cout << func.first << ": " << func.second << " | ";
        }

        cout << "\nSalário: R$ " << i.salario << "\n" << endl;

    }

    input();
}