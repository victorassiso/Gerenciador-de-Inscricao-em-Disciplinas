#include "menu.h"

void Menu::printTelaDeLogin()
{
    cout << "+----------------------------------------+\n"
         << "|                  Login                 |\n"
         << "+----+-----------------------------------+\n"
         << "| ID | Situação do Aluno                 |\n"
         << "+----+-----------------------------------+\n"
         << "| 1  | 1º Período EEL                    |\n"
         << "| 2  | 2º Período EEL                    |\n"
         << "| 3  | 3º Período EEL                    |\n"
         << "| 4  | 4º Período EEL                    |\n"
         << "| 5  | 4º Período (com ressalvas) EEL    |\n"
         << "| 6  | 1º Período COS                    |\n"
         << "| 7  | 2º Período COS                    |\n"
         << "| 8  | 3º Período COS                    |\n"
         << "| 9  | 4º Período COS                    |\n"
         << "| 10 | 4º Período (com ressalvas) COS    |\n"
         << "+----+-----------------------------------+\n"
         << "| 0  | Sair                              |\n"
         << "+----+-----------------------------------+\n"
         << endl;
}

void Menu::printMenuPrincipal()
{
    cout << "+----------------------------------------+\n"
         << "|             Menu Principal             |\n"
         << "+--------+-------------------------------+\n"
         << "| Indice |            Função             |\n"
         << "+--------+-------------------------------+\n"
         << "|    1   | Imprimir Grade do Curso       |\n"
         << "|    2   | Imprimir Turmas Disponíveis   |\n"
         << "|    3   | Imprimir Inscrições em Turmas |\n"
         << "|    4   | Inscrever-se em Turmas        |\n"
         << "|    5   | Cancelar Inscrições em Turmas |\n"
         << "|    6   | Trocar de Aluno               |\n"
         << "|    7   | Sair                          |\n"
         << "+--------+-------------------------------+\n"
         << endl;
}
template <typename T>
void Menu::getInputVerboso(T& opcao, int tamMax)
{
    cout << "Opção: ";
    cin >> setw(2) >> opcao;

    //Valida Input
    while (!cin.good())
    {
        //Reporta erro
        cout << "ERRO: Entrada inválida! Tente novamente..." << endl;

        //Clear stream
        cin.clear();
        cin.ignore(1000, '\n');

        //Tenta de novo
        cout << "Opção: ";
        cin >> setw(tamMax) >> opcao;
    }

    //Clear stream
    cin.clear();
    cin.ignore(1000, '\n');
}

template <typename T>
void Menu::getInput(T& opcao, int tamMax)
{
    cin >> setw(2) >> opcao;

    //Valida Input
    while (!cin.good())
    {
        //Reporta erro
        cout << "ERRO: Entrada inválida! Tente novamente..." << endl;

        //Clear stream
        cin.clear();
        cin.ignore(1000, '\n');

        //Tenta de novo
        cin >> setw(tamMax) >> opcao;
    }

    //Clear stream
    cin.clear();
    cin.ignore(1000, '\n');
}

int Menu::getOpcaoLogin()
{
    cout << "Escolha um aluno:" << endl;
    int opcao = -1;
    getInputVerboso(opcao, 2);

    //Valida opção
    while(opcao < 0 || opcao > 10)
    {
        cout << "ERRO: ID inexistente! Tente novamente..." << endl;
        getInputVerboso(opcao, 2);
    };

    return opcao;
}

int Menu::getOpcaoMenu()
{
    int opcao = -1;
    getInputVerboso(opcao, 1);

    //Valida opção
    while(opcao < 1 || opcao > 7)
    {
        cout << "ERRO: Índice inexistente! Tente novamente..." << endl;
        getInputVerboso(opcao, 1);
    };

    return opcao;
}

void Menu::pressioneEnterParaContinuar()
{
    
    cout << "Pressione ENTER para continuar...";
    cin >> setw(0);

    //Limpa stream
    cin.clear();
    cin.ignore(1000, '\n');
    
    cout << endl;
}

bool Menu::confirma()
{
    char x = 'x';

    cout << "[S/N]: ";
    getInput(x, 1);

    //Valida Input
    while (x != 's' && x != 'S' && x != 'n' && x != 'N')
    {
        cout << "ERRO: Entrada inválida! Tenta novamente..." << endl;
        cout << "[S/N]: ";
        getInput(x, 1);
    }

    //Define retorno (Sim -> True, Não -> False)
    if (x == 's' || x == 'S')
        return true;
    
    return false;
}

//Define tipos aceitos para a função template
template void Menu::getInputVerboso<int>(int&, int);
template void Menu::getInputVerboso<char>(char&, int);
template void Menu::getInput<int>(int&, int);
template void Menu::getInput<char>(char&, int);