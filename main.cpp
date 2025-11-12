#include "funcs.cpp"

int main(){

    cout << "Bem vindo! Digite o seu nome: ";
    cin >> NomeDoEmpresario;

    LIMPAR

    cout << NomeDoEmpresario << "! vamos criar sua primeira empresa! " << endl;
    cout << "Digite o nome da empresa: ";

    cin >> op;
    criarEmpresa(op);

    while(op != "SAIR"){
        menu();
    }

    return 0;

}