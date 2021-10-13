//#include "aluno.h"
#include "postgres.h"
#include "aluno.h"
#include <iomanip>
#include <pqxx/pqxx>



int main ()
{
    /*
    Aluno alunoEEL1("1");
    Aluno alunoEEL2("2");
    Aluno alunoEEL3("3");
    Aluno alunoEEL4("4");
    Aluno alunoEEL5("5");
    Aluno alunoCOS6("6");
    Aluno alunoCOS7("7");
    Aluno alunoCOS8("8");
    Aluno alunoCOS9("9");
    Aluno alunoCOS10("10");
    */

    int opcao = 0;
    int login = 0;
    string confirmacao = "x";
    string IDs;

    //Abre Looping principal
    while (opcao != 7 )
    {   
        //Login
        if (login == 0)
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
                 << endl;

            while (login < 1 || login > 10)
            {
                cout << "Aluno: ";
                cin >> login;
                cout << endl;
            }
        }

        Aluno aluno(to_string(login));

        //Menu Principal
        opcao = 0;
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
             << "+--------+-------------------------------+\n\n"
             << "Opção: ";
        cin >> opcao;

        switch (opcao)
        {
            case 7: //Sair
                break;
            case 6: //Trocar de Aluno
                login = 0;
                break;
            case 1:
                aluno.printGrade();
                cout << "Aperte 'ENTER' para continuar..";
                cin.ignore();
                cin.get();
                break;
            case 2:
                aluno.printTurmasDisponiveis();
                cout << "Aperte 'ENTER' para continuar...";
                cin.ignore();
                cin.get();
                break;
            case 3:
                aluno.printInscricoes();
                cout << "Aperte 'ENTER' para continuar...";
                cin.ignore();
                cin.get();
                break;
            case 4:
                while (confirmacao != "s" && confirmacao != "S" && confirmacao != "n" && confirmacao != "N")
                {
                    cout << "Obs.: Deseja, antes, imprimir a tabela de turmas disponíveis? [S/N]:";
                    cin >> confirmacao;
                    cin.ignore();
                }
                if (confirmacao == "s" || confirmacao == "S")
                {
                    aluno.printTurmasDisponiveis();
                    confirmacao = 'x';
                }
                cout << "Entre os IDs das turmas as quais deseja inscrever-se separados por espaço:" << endl;
                cout << "IDs: ";
                getline(cin, IDs);
                aluno.fazerInscricoes(IDs);
                break;
            case 5:
                while (confirmacao != "s" && confirmacao != "S" && confirmacao != "n" && confirmacao != "N")
                {
                    cout << "Obs.: Deseja, antes, imprimir suas inscrições? [S/N]:";
                    cin >> confirmacao;
                    cin.ignore();
                }
                if (confirmacao == "s" || confirmacao == "S")
                {
                    aluno.printInscricoes();
                    confirmacao = 'x';
                }
                cout << "Entre os IDs das turmas as quais deseja cancelar sua inscrição separados por espaço:" << endl;
                cout << "IDs: ";
                getline(cin, IDs);
                aluno.cancelarInscricoes(IDs);
                break;
        }
        
    }

    return 0;
}

/*TO DO
Primários:
    -Separar requisições ao banco
    -nao permitir se inscrever em turmas nao disponíveis (Por pŕe-requisitos e por vagas)
Secundários:
    -Printar Pré-requisitos
    -Trocar Vagas por Inscrições/Vagas 1/1 (transmormar em dinâmico)
    -Mensagem de confirmação (cancelarInscrições)
    -Inscrever outros alunos em turmas, mais exemplos prontos
    -overload operator << para usar em print turmas
    -Tratar erros
        (buscas nao encontradas)
Revisar:
    -Query printGrade() (muito grande)

Turmas Disponiveis:
    9:
        COE241
        COS242
        COS471
        FIM240
        FIN241
        IQG111
        MAC248
*/