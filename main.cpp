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

    while(op != "SAIR"){
        if(dia % 7 == 0){semana();}
        menu();

        if(acoesPorDia <= 0 || pularDia == 1){
            dia++;
            acoesPorDia = 3;   
            pularDia = 0;
        }
    }

    return 0;

}
