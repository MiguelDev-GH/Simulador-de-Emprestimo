#include "funcs.cpp"

int main(){

    CACETINHO
    LIMPAR

    cout << "Bem vindo! Digite o seu nome: ";
    getline(cin, NomeDoEmpresario);

    LIMPAR

    cout << NomeDoEmpresario << "! vamos criar sua primeira empresa! " << endl;
    cout << "Digite o nome da empresa: ";

    getline(cin, op);
    criarEmpresa(op);

    SortearContratacoes();

    while(op != "SAIR"){
        if(op == "DINHEIRO") dinheiro+=1000;
        
        menu();

        if(acoesPorDia <= 0 || pularDia == 1){
            dia++;
            acoesPorDia = 3;   
            pularDia = 0;
            
            prasos();

            if(dia % 7 == 0){
                semana();
            } else if(dia % 30 == 0){
                mes();
            }
        }
    }

    return 0;

}