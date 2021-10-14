//#include "aluno.h"
#include "postgres.h"
#include "gerenciamento.h"
#include <iomanip>
#include <pqxx/pqxx>

void pressioneEnterParaContinuar()
{
    cout << "Pressione ENTER para continuar...";
    cin.ignore();
    cin.get();
    cout << endl;
}

int main ()
{

    int opcao = 0;
    int login = 0;
    string login_str = "victor";
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
                /*
                cout << "--antes do try--" << endl;
                cout << "login_str: " << login_str << endl;
                cout << "login: " << login << endl;
                //getline(cin, login_str);
                */
                cout << "Aluno: ";
                cout << login << endl;
                //char a[8];
                //cin.getline(a, 8);
                if (!cin.good()){
                    cout << "Bad" << endl;
                    cin.clear();
                    cin.ignore();
                }
                cin.ignore(3, '\n');


                /*
                cin.eof();
                try
                {
                    cout << "--depois do try--" << endl;
                    cout << "login_str: " << login_str << endl;
                    cout << "login: " << login << endl;
                    login = stoi(login_str);
                    login_str = "assis";
                    cout << "login_str: " << login_str << endl;
                    cout << "login: " << login << endl;

                }
                catch (exception const &e)
                {
                    cout << "Erro: Entrada inválida! A entrada deve conter um número inteiro entre 1 e 10, mas contém caracteres alfabéticos." << endl;
                }
                */
            }
        }
        
        static Gerenciamento aluno(to_string(login));
        if (aluno.getId() == "-1")
        {
            return 1;
        }

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
                aluno.~Gerenciamento();
                break;
            case 6: //Trocar de Aluno
                aluno.~Gerenciamento();
                login = 0;
                break;
            case 1:
                aluno.printGrade();
                pressioneEnterParaContinuar();
                break;
            case 2:
                aluno.printTurmasDisponiveis();
                pressioneEnterParaContinuar();
                break;
            case 3:
                aluno.printInscricoes();
                pressioneEnterParaContinuar();
                break;
            case 4:
                while (confirmacao != "s" && confirmacao != "S" && confirmacao != "n" && confirmacao != "N")
                {
                    cout << "Obs.: Deseja, antes, imprimir a tabela de turmas disponíveis? [S/N]:";
                    cin.ignore();
                    cin >> confirmacao;
                }
                if (confirmacao == "s" || confirmacao == "S")
                {
                    aluno.printTurmasDisponiveis();
                    confirmacao = 'x';
                }
                cout << "Entre os IDs das turmas as quais deseja inscrever-se separados por espaço:" << endl;
                cout << "IDs: ";
                cin.ignore();
                getline(cin, IDs);
                aluno.fazerInscricoes(IDs);
                break;
            case 5:
                while (confirmacao != "s" && confirmacao != "S" && confirmacao != "n" && confirmacao != "N")
                {
                    cout << "Obs.: Deseja, antes, imprimir suas inscrições? [S/N]:";
                    cin.ignore();
                    cin >> confirmacao;
                }
                if (confirmacao == "s" || confirmacao == "S")
                {
                    aluno.printInscricoes();
                    confirmacao = 'x';
                }
                cout << "Entre os IDs das turmas as quais deseja cancelar sua inscrição separados por espaço:" << endl;
                cout << "IDs: ";
                cin.ignore();
                getline(cin, IDs);
                aluno.cancelarInscricoes(IDs);
                break;
        }
        
    }

    return 0;
}

/*TO DO
Primários:
    -Abrir e Fechar conexão com o BD no construtor e destrutor
    -nao permitir se inscrever em turmas nao disponíveis (Por pŕe-requisitos e por vagas)
Secundários:
    -Trocar Vagas por Inscrições/Vagas 1/1 (transmormar em dinâmico)
    -Mensagem de confirmação (cancelarInscrições)
    -Inscrever outros alunos em turmas, mais exemplos prontos
    -overload operator << para usar em print turmas
    -Tratar erros
        (buscas nao encontradas)
Revisar:
    -Query printGrade() (muito grande)
*/