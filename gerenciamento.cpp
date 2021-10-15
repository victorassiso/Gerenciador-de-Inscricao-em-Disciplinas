#include "gerenciamento.h"

Gerenciamento::Gerenciamento(string aluno_id): Requerimento(aluno_id)
{
    cout << "-Log: Gerenciamento criado!" << endl;
}

Gerenciamento::~Gerenciamento()
{
    cout << "-Log: Gerenciamento destruído!" << endl;
}

int Gerenciamento::printGrade()
{   try
    {
        //Abre Conexão com o Banco de Dados
        Postgres postgres;
        pqxx::connection con(postgres.getConnection_str());
        pqxx::work wrk(con);
        
        //PRINT GRADE
        string nomeDoCurso = selectNomeDoCurso(wrk);
        pqxx::result grade = selectGrade(wrk);
        pqxx::result periodos = selectPeriodosDoCurso(wrk);
        
        //Fecha Conexão com o BD
        con.disconnect();

        //Trata Resultados Vazios
        if (grade.size() < 1)
        {
            cout << "Tabela vazia ou erro (grade)" << endl;
            return -1;
        };
        if (nomeDoCurso.size() < 1)
        {
            cout << "Tabela vazia ou erro (curso)" << endl;
            return -1;
        };
        if (periodos.size() < 1)
        {
            cout << "Tabela vazia ou erro (periodos)" << endl;
            return -1;
        };

        //Print CABEÇALHO (Nome do Curso)
        int larguraMaxima = 50;
        int laterais = larguraMaxima - nomeDoCurso.size();
        
        cout << "+--------------------------------------------------------------------------+\n";
        if (laterais % 2 == 0)//Caso Par, divisão é igual
        {
            cout << "| " << setw(laterais/2) << "" << "Curso de Graduação em " << nomeDoCurso << setw(laterais/2) << "" << " |\n";
        } else {//Caso Ímpar, a segunda metade é acrescida em 1
            cout << "| " << setw(laterais/2) << "" << "Curso de Graduação em " << nomeDoCurso << setw(laterais/2+1) << "" << " |\n";
        };
        cout << "+--------------------------------------------------------------------------+\n";
        
        //Print PERIODO
        int row = 0;
        string requisitos;

        for (int p = 0; p < (int)periodos.size(); p++)
        {
            cout << "|" << setw(32) << "" << periodos[p][0] << "º Período" << setw(32) << "" << "|\n";
            cout << "+--------+------------------------------------------------+----------------+\n";
            cout << "| Código | Nome                                           |   Requisitos   |\n";
            cout << "+--------+------------------------------------------------+----------------+\n";

            //Print DISCIPLINAS por período
            while (grade[row][0] == periodos[p][0])
            {
                //Formata espaçamento da coluna dos Pré-requisitos
                requisitos = "";
                grade[row][3].size() > 0 ? requisitos = to_string(grade[row][3]) : requisitos = "      ";
                grade[row][4].size() > 0 ? requisitos += ", " + to_string(grade[row][4]) : requisitos += "        ";
                //Printa Linha (Row)
                cout << "| "
                     << grade[row][1] //Código
                     << " | "
                     << grade[row][2] //Nome
                     << setw(46 - grade[row][2].size()) //Preenche espaço do nome
                     << "" << " | "
                     << requisitos //Requisitos
                     << " | " << endl;
                row+=1;
            }
            cout << "+--------+------------------------------------------------+----------------+\n";
        };
        cout << endl;
    }
    catch (exception const &e)
    {
        cerr << e.what() << std::endl;
        return 1;
    }
    return 0;

    /* Template:
    +--------------------------------------------------------------------------+
    |       Curso de Graduação em Engenharia Eletrônica e de Computação        |
    +--------------------------------------------------------------------------+
    |                                1º Período                                |
    +--------+------------------------------------------------+----------------+
    | Código | Nome                                           |   Requisitos   |
    +--------+------------------------------------------------+----------------+
    | MAC238 | Cálculo III                                    | MAC128         |
    | MAC238 | Física III                                     | FIT112, MAC128 |
    +--------|------------------------------------------------+----------------+
    |                                2º Período                                |
    +--------+------------------------------------------------+----------------+
    | Código | Turma                                          |   Requisitos   |
    +--------+------------------------------------------------+----------------+
    | MAC238 | Cálculo III                                    | MAC128         |
    | MAC238 | Física III                                     | FIT112, MAC128 |
    +--------|------------------------------------------------+----------------+
    */
}

int Gerenciamento::printTurmasDisponiveis()
{
    try{
        //Abre Conexão com o BD
        Postgres postgres;
        pqxx::connection con(postgres.getConnection_str().c_str());
        pqxx::work wrk(con);
        
        //Realiza requirementos ao BD
        pqxx::result turmas = selectTurmasDisponiveis(wrk);
        
        //Fecha conxeão com o BD
        con.disconnect();

        //Começa lógica de Impressão
        if (turmas.size() < 1)
        {
            cout << "Tabela vazia ou erro (turmas)" << endl;
            return -1;
        };
        
        //CABEÇALHO
        cout << "+--------------------------------------------------------------------------+\n"
            << "|                           Turmas Disponíveis                             |\n"
            << "+--------------------------------------------------------------------------+\n";
        
        //PERIODO
        int row = 0;
        auto periodoAtual = turmas[0][0].as<int>();//Menor período
        auto periodoLimite = turmas[turmas.size()-1][0].as<int>();//Maior período

        while (row < turmas.size()-1)
        {
            cout << "|" << setw(32) << "" << periodoAtual << "º Período" << setw(32) << "" << "|\n";
            cout << "+--------+----------------------------------------------------+-------+----+\n";
            cout << "| Código | Nome                                               | Vagas | ID |\n";
            cout << "+--------+----------------------------------------------------+-------+----+\n";
            
            //DISCIPLINAS
            while (row < turmas.size() && turmas[row][0].as<int>() == periodoAtual)
            {
                cout << "| "
                    << turmas[row][1] //Código
                    << " | "
                    << turmas[row][2] //Descrição Turma
                    << setw(50 - turmas[row][2].size()) //Preenche espaço da descrição
                    << "" << " |   "
                    << turmas[row][3] //Vagas
                    << "   | "
                    << turmas[row][4] //Id
                    << setw(2- turmas[row][4].size()) //Preenche espaço no caso de números de apenas 1 algarismo
                    << "" << " | "  << endl;
                row+=1;
            }
            cout << "+--------+----------------------------------------------------+-------+----+\n";
            
            if (row < turmas.size()-1)
                periodoAtual = turmas[row][0].as<int>();
        };
        cout << endl;
    }
    catch (exception const &e)
    {
        cerr << e.what() << std::endl;
        return 1;
    }

   return 0;
   
    /* Template:
    +--------------------------------------------------------------------------+
    |                           Turmas Disponíveis                             |
    +--------------------------------------------------------------------------+
    |                                1º Período                                |
    +--------+----------------------------------------------------+-------+----+
    | Código | Turma                                              | Vagas | ID |
    +--------+----------------------------------------------------+-------+----+
    | MAC238 | Cálculo III - A                                    |  3/1  | 1  |
    | MAC238 | Cálculo III - B                                    |  2/1  | 1  |
    +--------|----------------------------------------------------+-------+----+
    |                                2º Período                                |
    +--------+----------------------------------------------------+-------+----+
    | Código | Turma                                              | Vagas | ID |
    +--------+----------------------------------------------------+-------+----+
    | MAC238 | Cálculo III - A                                    |  0/4  | 1  |
    | MAC238 | Cálculo III - B                                    |  5/9  | 1  |
    +--------|----------------------------------------------------+-------+----+
    */
}

int Gerenciamento::fazerInscricoes(string turmas_id)
{
    try
    {
        //Trata turmas_id vazio
        if (turmas_id.size() < 1)
        {
            cout << "Nenhuma turma foi selecionada" << endl;
            
            return 1;
        }

        //Abre conexão com o Banco de dados
        Postgres postgres;
        pqxx::connection con(postgres.getConnection_str().c_str());
        pqxx::work wrk(con);
        
        //Requere turmas disponíveis
        pqxx::result turmas = selectTurmasDisponiveis(wrk);

        //Fecha Conxeão com o BD
        con.disconnect();

        //Define timestamp
        string timestamp = dataTimestamp();
        
        //Transforma string turmas_id em um vetor de strings ID
        vector<string> vetorIDs = separaStringPorEspaco(turmas_id);
        
        //Valida IDs
        vector<string> vetorIDsValidados;
        for (int i = 0; i < vetorIDs.size(); i++)
        {
            if (!validaIDsNaTabela(turmas, 4, vetorIDs.at(i)))
            {
                cout << "ERRO: O ID '" << vetorIDs.at(i)
                     << "' é inválido ou você não tem os requisitos necessários para se inscrever nessa turma"
                     << endl;
            }
            else
                vetorIDsValidados.push_back(vetorIDs.at(i));
        }
        
        //Finaliza tentativa caso nenhum ID tenha sido validado
        if (vetorIDsValidados.size() == 0)
        {
            //Fecha conexão
            con.disconnect();
            return 0;
        }

        //Monta VALUES
        string values = "";
        for (int i = 0; i < vetorIDsValidados.size()-1; i++)
            values += "(" + getId() + ", '" + vetorIDsValidados.at(i) + "', '" + timestamp + "'), ";
        values += "(" + getId() + ", '" + vetorIDsValidados.at(vetorIDsValidados.size()-1) + "', '" + timestamp + "')";

        //Realiza o INSERT
        insertInscricoes(wrk, values);

        //Salva Alterações
        wrk.commit();

        //Fecha conexão
        con.disconnect();
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
    
    return 0;
}

int Gerenciamento::printInscricoes()
{
    try
    {
        //Abre conexão com o Banco de dados
        Postgres postgres;
        pqxx::connection con(postgres.getConnection_str().c_str());
        pqxx::work wrk(con);

        //Realiza Requisição ao BD
        pqxx::result inscricoes = selectInscricoes(wrk);

        //Trata Resposta vazia
        if (inscricoes.size() < 1)
        {
            cout << "Nenhuma inscrição foi encontrada" << endl;
            return -1;
        };
        
        //Realiza Requisição ao BD
        pqxx::result periodos = selectPeriodosDasInscricoes(wrk);

        //Trata Resposta vazia
        if (periodos.size() < 1)
        {
            cout << "Tabela vazia ou erro (periodos)" << endl;
            return -1;
        };
        
        //Fecha conexão com BD
        con.disconnect();
        
        //CABEÇALHO
        cout << "+--------------------------------------------------------------------------+\n"
            << "|                               Inscrições                                 |\n"
            << "+--------------------------------------------------------------------------+\n";
        
        //PERIODO
        int row = 0;
        //cout << periodos.size() << endl;
        
        for (int p = 0; p < (int)periodos.size(); p++)
        {
            cout << "|" << setw(32) << "" << periodos[p][0] << "º Período" << setw(32) << "" << "|\n";
            cout << "+--------+----------------------------------------------------+-------+----+\n";
            cout << "| Código | Nome                                               | Vagas | ID |\n";
            cout << "+--------+----------------------------------------------------+-------+----+\n";
            
            //DISCIPLINAS
            while (inscricoes[row][5] == periodos[p][0])
            {
                cout << "| "
                     << inscricoes[row][0] //Código
                     << " | "
                     << inscricoes[row][1] //Descrição
                     << setw(50 - inscricoes[row][1].size()) //Espaçamento descrição
                     << "" << " |  "
                     << inscricoes[row][2] //Numero de inscrições na turma
                     << "/"
                     << inscricoes[row][3] //Vagas
                     << "  | "
                     << inscricoes[row][4] //ID
                     << setw(2- inscricoes[row][4].size())
                     << "" << " | "  << endl;
                row+=1;
            }
            cout << "+--------+----------------------------------------------------+-------+----+\n";
        };
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }

    return 0;
}

int Gerenciamento::cancelarInscricoes(string turma_ids)
{
    try
    {
        //Retorna caso o vetor de turmas esteja vazio
        if (turma_ids.size() < 1)
        {
            cout << "Nenhuma turma foi selecionada" << endl;
            return 1;
        }
        
        //Abre conexão com o Banco de dados
        Postgres postgres;
        pqxx::connection con(postgres.getConnection_str().c_str());
        pqxx::work wrk(con);

        //Pede turmas inscritas
        pqxx::result inscricoes = selectInscricoes(wrk);

        //Transforma string turmas_id em um vetor de strings ID
        vector<string> vetorIDs = separaStringPorEspaco(turma_ids);

        //Valida IDs
        vector<string> vetorIDsValidados;
        for (int i = 0; i < vetorIDs.size(); i++)
        {
            if (!validaIDsNaTabela(inscricoes, 1, vetorIDs.at(i)))
            {
                cout << "ERRO: O ID '" << vetorIDs.at(i)
                     << "' é inválido ou você não se inscreveu nessa turma."
                     << endl;
            }
            else
                vetorIDsValidados.push_back(vetorIDs.at(i));
        }
        
        //Finaliza tentativa caso nenhum ID tenha sido validado
        if (vetorIDsValidados.size() == 0)
        {
            //Fecha conexão
            con.disconnect();
            return 0;
        }

        //Monta condicoes
        string condicoes = "";
        for (int i = 0; i < vetorIDs.size()-1; i++)
            condicoes += vetorIDs.at(i) + ", ";
        condicoes += vetorIDs.at(vetorIDs.size()-1);
        
        //Realiza DELETE
        pqxx::result cancelar = wrk.exec(
            "DELETE FROM inscricoes\
            WHERE aluno_id = " + getId() +
                "AND turma_id IN (" + condicoes + ");"
        );

        //Salva alterações no Banco de Dados
        wrk.commit();

        //Fecha Conexão com o Banco de dados
        con.disconnect();
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }

    return 0;
}

string Gerenciamento::dataTimestamp()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string year = to_string(1900 + ltm->tm_year);
    string month = to_string(1 + ltm->tm_mon);
    string day = to_string(ltm->tm_mday);
    string hour = to_string(ltm->tm_hour);
    string min = to_string(ltm->tm_min);
    string sec = to_string(ltm->tm_sec);
    string timestamp = year + "-" + month + "-" + day + " " + hour + ":" + min + ":" + sec;

    return timestamp;
}

vector<string> Gerenciamento::separaStringPorEspaco(string &str)
{
    string palavra = "";
    vector<string> vPalavras;
    int i = 0;
    int j = 0;

    //Varre str caracter por caracter separando as palavras por ' '
    for (i = 0; i < str.size(); i++)
    {
        if (str[i] != ' ')
            //Enquanto não encontra ' ', vai formando a string palavra
            palavra += str[i];

        else
        {
            //Quando encontra, insere palavra no vetor vPalavras
            if (palavra != "")//Trata o caso de uma entrada de múltiplos ' ' seguidos
                vPalavras.push_back(palavra);
        

            //Reseta palavra
            palavra = "";
        }
    }
    //Trata a última palavra
    if (palavra != "")
        vPalavras.push_back(palavra);

    return vPalavras;
}

bool Gerenciamento::validaIDsNaTabela(pqxx::result &tabela, int coluna, string &chave)
{
    bool encontrado;
    int j;

    for (j = 0; j < tabela.size(); j++)
    {
        //Varre tabela disponíveis comparando com o ID word
        if (to_string(tabela[j][coluna]) == chave && chave != "")
        {
           return true;
        }
    }
    return false;   
}


