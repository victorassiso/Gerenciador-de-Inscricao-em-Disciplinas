//#include "aluno.h"
#include "postgres.h"
#include "gerenciamento.h"
#include "menu.h"

int main ()
{
    //Inicializa objetos e variáveis do menu
    Menu menu;
    int opcao = 0;
    int login = -1;
    bool confirmacao = false;
    string IDs = "";
    
    //Abre Looping principal
    while (opcao != 7 )
    {   
        //Abre tela de Login
        if (login == -1)
        {
            menu.printTelaDeLogin();//Printa Tela de Login
            login = menu.getOpcaoLogin(); //Pede e valida entrada do usuário
            if (login == 0)
            {
                cout << "Saindo..." << endl;
                return 0;
            }
        }

        //Cria objeto estático aluno     
        static Gerenciamento aluno(to_string(login));

        //Altera o aluno caso a opção 6 seja selecionada
        if (opcao == 6)
            aluno.setAluno(to_string(login));

        //Erro ao Inicializar objeto aluno
        if (aluno.getId() == "-1")
        {
            login = menu.getOpcaoLogin(); //Pede e valida entrada do usuário
            if (login == 0)
            {
                cout << "Saindo..." << endl;
                return 0;
            }
            opcao = 6;
        }
        else
        {
            //Menu Principal
            menu.printMenuPrincipal();
            opcao = menu.getOpcaoMenu();

            //Trata a opção escolhida
            switch (opcao)
            {
                case 7: //Finaliza o programa
                    cout << "Saindo..." << endl;
                    return 0;
                    break;
                case 6: //Troca de aluno
                    login = -1;
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
                    getline(cin, IDs);
                    aluno.fazerInscricoes(IDs);
                    IDs = "";
                    break;
                case 5: //Cancela inscricoes
                    cout << "Obs.: Deseja, antes, imprimir as suas inscricoes? ";
                    confirmacao = menu.confirma();
                    if (confirmacao)
                        aluno.printInscricoes();
                    
                    cout << "Entre os IDs das turmas as quais deseja cancelar sua inscrição separados por espaço:" << endl;
                    cout << "IDs: ";
                    getline(cin, IDs);
                    aluno.cancelarInscricoes(IDs);
                    IDs = "";
                    break;
                    
            }  
        }
    }

    return 0;
}

/*TO DO
Primários:
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