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

void semana(){
    SortearContratacoes();
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
    
    cout << "~ " << NomeDoEmpresario << " | " << "Dia " << dia << " | " << "R$ " << dinheiro << endl;
    cout << "Ações restantes: " << acoesPorDia << endl;
    
    cout << "\n| Gerenciar EMPRESAS |" << endl;
    
    for(int i = 0;i < Empresas.size();i++){
        cout << i+1 << "- " << Empresas[i].nome << endl;
    }

    cout << "\n" << Empresas.size() + 1 << "- Contratar Funcionários" << endl;
    cout << "\nDigite uma opção não listada para pular um dia..." << endl;
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
    } else {
        pularDia = 1;
    }
}

void SortearContratacoes(){
    srand(time(NULL));
    Contratacoes.clear();

    LIMPAR

    for(int i = 0; i < 3;i++){

        double salario = 0;

        Funcionario novo;
        novo.nome = ListaNomes[(rand() % ListaNomes.size())];
        novo.id = i;

        for(auto& func : novo.atributos){
            func.second = (rand() % 5) + 1;
            novo.overall += func.second;
            salario += func.second;
        }        
        
        novo.custoMelhoria = salario * 0.45;
        novo.salario = ((salario*salario) * 45) + 1200;

        Contratacoes.push_back(novo);

    }

}

void SistemaContratacao(){
    LIMPAR

    cout << "----------Menu-De-Contratação------------\n\n";
    for(int i = 0; i < Contratacoes.size();i++){
        
        printf("%d- %s > %d <\n",i+1, Contratacoes[i].nome.c_str(), Contratacoes[i].overall);

        for(auto& func : Contratacoes[i].atributos){
            cout << func.first << ": " << func.second << " | ";
        }

        cout << "\nSalário: R$ " << Contratacoes[i].salario << "\n" << endl;
    }

    cout << "Digite o número do funcionário que deseja contratar!\n (Qualquer outra entrada para voltar)" << endl;

    input();

    LIMPAR

    if(op >= "1" && op <= "3"){
        cout << "Qual a empresa que você deseja contratar o " << Contratacoes[stoi(op) - 1].nome << "?" <<endl;

        for(int i = 0; i < Empresas.size(); i++){
            cout << i+1 << "- " << Empresas[i].nome << endl;
        }

        cout << endl;
        input();

        if(op >= "0" && op <= to_string(Empresas.size())){
            Empresas[stoi(op) - 1].funcionarios.push_back(Contratacoes[stoi(op) - 1]);
            acoesPorDia--;
        }

    }
}