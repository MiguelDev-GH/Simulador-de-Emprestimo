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
        menu();
    }

    return 0;

}
