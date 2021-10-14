//#include "aluno.h"
#include "postgres.h"
#include "gerenciamento.h"
#include "menu.h"
#include <iomanip>
#include <pqxx/pqxx>

int main ()
{
    //Inicializa objetos e variáveis do menu
    Menu menu;
    int opcao = 0;
    int login = 0;
    bool confirmacao = false;
    string login_str = "";
    string IDs = "";
    
    //Abre Looping principal
    while (opcao != 7 )
    {   
        //Abre tela de Login
        if (login == 0)
        {
            menu.printTelaDeLogin();//Printa Tela de Login
            login = menu.getOpcaoLogin(); //Pede e valida entrada do usuário
        }
        
        //Inicializa Aluno
        static Gerenciamento aluno(to_string(login));
        if (aluno.getId() == "-1")
        {
            return 1;
        }

        //Menu Principal
        menu.printMenuPrincipal();
        opcao = menu.getOpcaoMenu();

        //Trata a opção escolhida
        switch (opcao)
        {
            case 7: //Finaliza o programa
                cout << "Saindo..." << endl;
                aluno.~Gerenciamento();
                break;
            case 6: //Troca de aluno
                aluno.~Gerenciamento();
                login = 0;
                break;
            case 1: //Printa grade
                aluno.printGrade();
                menu.pressioneEnterParaContinuar();
                break;
            case 2: //Printa turmas disponíveis
                aluno.printTurmasDisponiveis();
                menu.pressioneEnterParaContinuar();
                break;
            case 3: //Printa inscricoes
                aluno.printInscricoes();
                menu.pressioneEnterParaContinuar();
                break;
            case 4: //Realiza inscricoes
                cout << "Obs.: Deseja, antes, imprimir a tabela de turmas disponíveis? ";
                confirmacao = menu.confirma();
                if (confirmacao)
                    aluno.printTurmasDisponiveis();
                
                cout << "Entre os IDs das turmas as quais deseja inscrever-se separados por espaço:" << endl;
                cout << "IDs: ";
                cin.ignore();
                getline(cin, IDs);
                aluno.fazerInscricoes(IDs);
                break;
            case 5: //Cancela inscricoes
                cout << "Obs.: Deseja, antes, imprimir as suas inscricoes? ";
                confirmacao = menu.confirma();
                if (confirmacao)
                    aluno.printInscricoes();
                
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
    -Validar IDs Turmas no menu
    -Trocar Vagas por Inscrições/Vagas 1/1 (transmormar em dinâmico)
    -Mensagem de confirmação (cancelarInscrições)
Secundários:
    -nao permitir se inscrever em turmas nao disponíveis (Por pŕe-requisitos e por vagas)
    -Tratar erros
    -(?)Abrir e Fechar conexão com o BD no construtor e destrutor
    -(buscas nao encontradas)
Revisar:
    -Query printGrade() (muito grande)
*/