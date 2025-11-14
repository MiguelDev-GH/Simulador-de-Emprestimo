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
    Contratacoes.clear();
    SortearContratacoes();
}

void DetalharEmpresa(Empresa& emp){
    LIMPAR
    cout << "Detalhes de " << emp.nome << endl;
    cout << "Valor da empresa: R$ " << emp.valor << endl;
    cout << "\nQuantidade de funcionários: " << emp.funcionarios.size() << endl;
    cout << "\nAmbiente NV " << emp.melhorias["Ambiente"]<< endl; 
    cout << "Infraestrutura NV " << emp.melhorias["Infraestrutura"]<< endl; 
    cout << "Marketing NV " << emp.melhorias["Marketing"] << "\n\n"; 

    input();

}

void EmpresasFuncionarios(Empresa& emp){
    LIMPAR

    cout << "Funcionários de " << emp.nome << "\n" << endl;

    for(int i = 0; i < (int)emp.funcionarios.size(); i++){
        cout << i+1 << "- " << emp.funcionarios[i].nome << " | ";
        cout << "DP " << emp.funcionarios[i].atributos["Desenvolvimento e Pesquisa"];
        cout << " - INT " << emp.funcionarios[i].atributos["Inteligencia"];
        cout << " - MOT " << emp.funcionarios[i].atributos["Motivacao"] << endl;
    }

    cout << "\nEscreva um número assiciado ao funcionário para acessar tais funções..." << endl;
    input();

    if(op >= "1" && op <= to_string(emp.funcionarios.size())){
        LIMPAR

        Funcionario& func = emp.funcionarios[stoi(op) - 1];

        cout << func.nome << " | Rate > " << func.overall << " <\n" << endl;

        int cont = 1;

        for(auto& i : func.atributos){
            cout << cont << "- " << i.first << " NV " << i.second << endl;
            cont++;
        }

        cout << "\nPreço de melhoria: R$ " << func.custoMelhoria << endl;
        cout << "Digite o número do atributo se quiser melhorá-lo..." << endl;
        input();


        int op2 = 0;
        try {
            op2 = stoi(op);
        } catch(...) {
            return;
        }

        if(op2 >= 1 && op2 <= 3){
            if(dinheiro >= func.custoMelhoria){
                switch (op2){
                    case 1:
                        func.atributos["Desenvolvimento e Pesquisa"] += 1;
                        break;
                    case 2:
                        func.atributos["Inteligencia"] += 1;
                        break;
                    case 3:
                        func.atributos["Motivacao"] += 1;
                        break;
                    }

                dinheiro -= func.custoMelhoria;
                acoesPorDia--;
                func.overall += 1;
                func.custoMelhoria = (func.salario * 0.45) + (50 * func.overall);
            } else {
                LIMPAR
                cout << "- Dinheiro INSUFICIENTE! -\n" << endl;
                cout << "Digite algo para voltar..." << endl;
                input();
            }
        }
    }

}

void menu(){

    LIMPAR
    
    ganhoDiario(Empresas);
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
        cout << "2- Funcionários..." << endl;
        cout << "3- Deletar Empresa" << endl; // Opção não feita ainda
        input();

        if(op == "1") DetalharEmpresa(Empresas[empNum]);
        else if(op == "2") EmpresasFuncionarios(Empresas[empNum]);

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

        for(auto& func : novo.atributos){
            func.second = (rand() % 5) + 1;
            novo.overall += func.second;
            salario += func.second;
        }        
        
        novo.salario = ((salario*salario) * 45) + 1200;
        novo.custoMelhoria = (novo.salario * 0.45) + (5 * novo.overall);

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

        int funcNum = stoi(op) - 1;

        for(int i = 0; i < Empresas.size(); i++){
            cout << i+1 << "- " << Empresas[i].nome << endl;
        }

        cout << endl;
        input();

        if(op >= "1" && op <= to_string(Empresas.size())){
            Empresas[stoi(op) - 1].funcionarios.push_back(Contratacoes[funcNum]);
            acoesPorDia--;
        }
    }
}

void ganhoDiario(vector<Empresa>& Empresas){
    double ganho;

    int MotivacaoTotal = 0;

    for(int i = 0; i < Empresas.size(); i++){
        Empresa emp = Empresas[i];

        MotivacaoTotal = 0;

        for(int j = 0; j < emp.funcionarios.size() ;j++){
            cout << emp.funcionarios[j].atributos["Motivacao"] << endl;
            MotivacaoTotal += emp.funcionarios[j].atributos["Motivacao"];
        }

        cout << MotivacaoTotal << endl;

    }

}