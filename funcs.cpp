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

void prasos(){

    for(auto& prs : contarDias){
        if(prs.second != -1){
            prs.second--;
        }

        if(prs.second == 0){
            if(prs.first == "Pagar Funcionarios"){
                double total = 0;

                for(int i = 0; i < Empresas.size(); i++){
                    for(auto& func : Empresas[i].funcionarios){
                        total += func.salario;
                    }
                }

                if(total > dinheiro){
                    fimDeJogo(2);
                } else {
                    noticia("Como esperado hoje você pagou seus funcionários!");
                    dinheiro -= total;
                }

            }
        } else if(prs.second == 1){
            noticia("Amanhã é o ÚLTIMO DIA para pagar todos os seus funcionários!");
        }
    }
}

void semana(){
    Contratacoes.clear();
    SortearContratacoes();
    noticia("Novos candidatos apareceram!");
}

void mes(){

    double pagarFuncionario = 0;

    for(int i = 0; i < Empresas.size(); i++){
        for(auto& func : Empresas[i].funcionarios){
            pagarFuncionario += func.salario;
        }
    }

    if(pagarFuncionario > dinheiro){
        noticia("Você tem 7 dias para pagar todos os seus funcionários, total de R$" + to_string(pagarFuncionario) + " !");
        contarDias["Pagar Funcionarios"] = 7;
    } else {
        noticia("Você pagou seus funcionários!");
        dinheiro -= pagarFuncionario;
    }
}

void DetalharEmpresa(Empresa& emp){
    LIMPAR
    cout << "Detalhes de " << emp.nome << endl;
    cout << "Valor da empresa: R$ " << emp.valor << endl;
    cout << "\nQuantidade de funcionários: " << emp.funcionarios.size() << endl;
    cout << "\nAmbiente NV " << emp.melhorias["Ambiente"]<< endl; 
    cout << "Infraestrutura NV " << emp.melhorias["Infraestrutura"]<< endl; 
    cout << "Marketing NV " << emp.melhorias["Marketing"] << "\n\n"; 

    cout << "Aperte ENTER para voltar..." << endl;
    getchar();

}

void EmpresasFuncionarios(Empresa& emp){
    LIMPAR

    cout << "Funcionários de " << emp.nome << "\n" << endl;

    if(emp.funcionarios.size() <= 0){
        cout << "Empresa sem funcionários...\n" << endl;
        cout << "Aperte ENTER para voltar..." << endl;
        getchar();
        return;
    }

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
                func.custoMelhoria = (func.salario * 0.25) + (50 * func.overall);
                func.salario += 50;
                noticia(func.nome + " foi melhorado!");
            } else {
                LIMPAR
                cout << "- Dinheiro INSUFICIENTE! -\n" << endl;
                cout << "Digite algo para voltar..." << endl;
                input();
            }
        }
    }

}

void EmpresasVender(Empresa& emp){
    LIMPAR
    cout << "Voce tem certeza que deseja vender " + emp.nome + "?" << endl;
    cout << "(Será deletado junto todos os funcionários)" << endl;
    cout << "Valor que sera ganho: R$" << emp.valor << "\n" << endl;
    cout << "Digite <S> e ENTER para confirmar a venda: ";
    input();

    if(op == "s" || op == "S"){

        bool encontrado = false;
        int cont = 0;
    
        for(auto& emps : Empresas){
            if(emps == emp){
                encontrado = true;
                break;
            }
            cont++;
        }

        LIMPAR

        if(encontrado){
            EmpresasFinalizadas[emp.nome] = emp.valor;
            Empresas.erase(Empresas.begin() + cont);
        } else {
            cout << "Algum erro ao tentar vender a empresa " + emp.nome << "\n" << endl;
            cout << "Aperte ENTER para voltar" << endl;
            getchar();
            return;
        }

        cout << emp.nome << " foi vendido por R$" << emp.valor << "\n" << endl;
        cout << "Aperte ENTER para voltar" << endl;
        getchar();

    }
}


void noticia(string mensagem){
    noticiaMensagem = mensagem;
    noticiaAtivada = true;
    cout << "* " << mensagem << " *" << "\n" << endl;
}

void fimDeJogo(int tipoDeFim){
    LIMPAR

    cout << "SEU FIM...\n" << endl;
    if(tipoDeFim == 1) cout << "Você esta sem empresas para administrar..." << endl;
    else if(tipoDeFim == 2) cout << "Você não tem dinheiro suficiente para pagar todos os seu funcionários..." << endl;

    double patrimonioTotal = dinheiro;
    double empresasValorTotal = 0;

    for(auto& emps : EmpresasFinalizadas){
        patrimonioTotal += emps.second;
        empresasValorTotal += emps.second;
    }

    if(patrimonioTotal <= 5000){
        cout << "Infelizmente você FALIU por completo na sua carreira!" << endl;
        cout << "Com esse patrimonio no nome " << NomeDoEmpresario << " foi descoberto que administrar o financeiro NÃO ERA seu forte.\n" << endl;
    } else if(patrimonioTotal <= 10000){
        cout << "Pelo visto não foram muitas conquistas no nome de " << NomeDoEmpresario << endl;
        cout << "Mas pelo menos dar pra alugar uma kitnet por um tempinho...\n"<< endl;
    } else if(patrimonioTotal <= 50000){
        cout << NomeDoEmpresario << " conseguiu algo pra se sustentar por um período de tempo (Menos de 1 ano com certeza)" << endl;
        cout << "É bom dizer que foi uma boa tentativa de construir um futuro...\n" << endl;
    }

    cout << "~ Conquistas:" << endl;
    cout << "Dinheiro: R$" << dinheiro << "\n" << endl;

    for(auto& emps : EmpresasFinalizadas){
        cout << "- " << emps.first << " R$" << emps.second << endl;
    }

    cout << "Valor total de empresas: R$" << empresasValorTotal << endl;

    cout << "\nPatrimônio total: R$" << patrimonioTotal << endl;
    exit(1);
}

void Trabalhos(){
    LIMPAR 

    cout << "~ Trabalhos: \n" << endl;
    
    cout << "1- Negociar";

    if(negociacaoFeita) cout << " (Em progresso)" << endl;
    else cout << endl;

    cout << "2- Avançar pesquisa" << endl;

    input();

    if(op == "1"){
        negociacaoFeita = true;
        LIMPAR
        cout << "Digite o valor que deseja negociar em reais:";
        input();
        double valorNegociacao = stod(op);
        float porcentagemSucesso = (rand() + 100) / 100;

        cout << "Valor da negociação: R$" << valorNegociacao << endl;
        cout << "Porcentagem de sucesso: " << porcentagemSucesso << "%\n" << endl;

        // Aqui tem que fazer as opções para se a negociacão for feita ou não
        cout << "Aperte ENTER para voltar..." << endl;
        getchar();

    }
}

void menu(){

    if(Empresas.size() <= 0) fimDeJogo(1);
    
    ganhoDiario(Empresas);

    if(noticiaAtivada){
        LIMPAR
        noticia(noticiaMensagem);
        noticiaAtivada = false;
    } else {
        LIMPAR
    }

    cout << "~ " << NomeDoEmpresario << " | " << "Dia " << dia << " | " << "R$ " << dinheiro << endl;
    cout << "Ações restantes: " << acoesPorDia << endl;
    
    cout << "\n| Gerenciar EMPRESAS |" << endl;
    
    for(int i = 0;i < Empresas.size();i++){
        cout << i+1 << "- " << Empresas[i].nome << endl;
    }

    cout << "\n" << Empresas.size() + 1 << "- Contratar Funcionários" << endl;
    cout << Empresas.size() + 2 << "- Trabalhos" << endl;

    cout << "\nDigite uma opção não listada para pular um dia..." << endl;
    input();

    string opGerenciarEmpresas = to_string(Empresas.size());

    if(op > "0" && op <= opGerenciarEmpresas){
        LIMPAR

        int empNum = stoi(op) - 1;

        cout << "~ Empresa: " << Empresas[empNum].nome << endl;

        cout << "\n1- Detalhes" << endl; 
        cout << "2- Funcionários..." << endl;
        cout << "3- Vender Empresa\n" << endl; // Opção não feita ainda
        input();

        if(op == "1") DetalharEmpresa(Empresas[empNum]);
        else if(op == "2") EmpresasFuncionarios(Empresas[empNum]);
        else if(op == "3") EmpresasVender(Empresas[empNum]);

    } else if(op == to_string(Empresas.size() + 1)){ SistemaContratacao();
    } else if(op == to_string(Empresas.size() + 2)){ Trabalhos();

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
        
        novo.contratavel = true;
        novo.salario = ((salario*salario) * 45) + 1200;
        novo.custoMelhoria = (novo.salario * 0.25) + (5 * novo.overall);

        Contratacoes.push_back(novo);

    }

}

void SistemaContratacao(){
    LIMPAR

    int funcNum = 0;

    cout << "----------Menu-De-Contratação------------\n\n";

    int cont = 1;
    int contNaoContrataveis = 0;

    for(int i = 0; i < Contratacoes.size();i++){

        if(contNaoContrataveis < 3){
        
            if(Contratacoes[i].contratavel){
                printf("%d- %s > %d <\n",i+1, Contratacoes[i].nome.c_str(), Contratacoes[i].overall);

                for(auto& func : Contratacoes[i].atributos){
                    cout << func.first << ": " << func.second << " | ";
                }

                cout << "\nSalário: R$ " << Contratacoes[i].salario << "\n" << endl;

            } else {
                cout << i+1 << "- =- CANDIDATO INDISPONÍVEL -=\n" << endl;
                contNaoContrataveis++;
            }

        }
    }

    if(contNaoContrataveis == 3){
        LIMPAR
        cout << "----------Menu-De-Contratação------------\n\n";
        cout << "=- Aguarde a próxima semana para mais novos candidatos... \n(A cada sete dias)\n" << endl;

        cout << "Aperte ENTER para voltar..." << endl;
        getchar();
        return;
    }

    cout << "Digite o número do funcionário que deseja contratar!\n (Qualquer outra entrada para voltar)" << endl;
    input();

    LIMPAR

    if(op >= "1" && op <= "3"){

        funcNum = stoi(op) - 1;

        if(dinheiro < Contratacoes[funcNum].salario){
            LIMPAR
            cout << "> Dinheiro Insuficiente! <\n" << endl;
            cout << "Aperte ENTER para voltar..." << endl;
            getchar();
            return;
        }

        if(!Contratacoes[funcNum].contratavel){
            LIMPAR
            cout << "> Funcionário indisponível! <\n" << endl;
            cout << "Aperte ENTER para voltar..." << endl;
            getchar();
            return;
        }

        cout << "Qual a empresa que você deseja contratar o " << Contratacoes[funcNum].nome << "?" <<endl;

        for(int i = 0; i < Empresas.size(); i++){
            cout << i+1 << "- " << Empresas[i].nome << endl;
        }

        cout << endl;
        input();

        if(op >= "1" && op <= to_string(Empresas.size()) && Contratacoes[funcNum].contratavel){
            Empresas[stoi(op) - 1].funcionarios.push_back(Contratacoes[funcNum]);
            Empresas[stoi(op) - 1].funcionarios.back().contratavel = false;
            Contratacoes[funcNum].contratavel = false;
            dinheiro -= Contratacoes[funcNum].salario;
            noticia(Contratacoes[funcNum].nome + " foi contratado em " + Empresas[stoi(op) - 1].nome + "!");
            acoesPorDia--;
        }
    }
}

void ganhoDiario(vector<Empresa>& Empresas){
    double ganho = 0;

    int MotivacaoTotal = 0;

    for(int i = 0; i < Empresas.size(); i++){
        Empresa emp = Empresas[i];

        MotivacaoTotal = 0;

        for(int j = 0; j < emp.funcionarios.size() ;j++){
            MotivacaoTotal += emp.funcionarios[j].atributos["Motivacao"];
        }

        ganho += MotivacaoTotal;

    }

    ganho *= 50;

    dinheiro += ganho;
}