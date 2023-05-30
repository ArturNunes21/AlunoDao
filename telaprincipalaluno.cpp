#include "telaprincipalaluno.h"
#include "ui_telaprincipalaluno.h"
#include "aluno.h"
#include "alunodao.h"
#include <QMessageBox>
#include <QString>
#include <QStandardItemModel>
#include <QTableView>


TelaPrincipalAluno::TelaPrincipalAluno(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TelaPrincipalAluno)
{
    ui->setupUi(this);
}

TelaPrincipalAluno::~TelaPrincipalAluno()
{
    delete ui;
}

Artur::Aluno pAluno;
Artur::AlunoDAO pAlunoDao;

void TelaPrincipalAluno::atualizarTableView() {
    // Obter o modelo de dados atual da tabela
//    QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(ui->tableView->model());
    QStandardItemModel* model = new QStandardItemModel(this);

    // Verificar se o modelo de dados existe e se está correto
    if (!model) {
        qDebug() << "Modelo de dados da tabela não encontrado ou inválido.";
        qDebug() <<"Model = " << model;
        return;
    }

    // Limpar o modelo de dados existente
//    model->clear();
    model->removeRows(0, model->rowCount());

    // Obter a lista de alunos do DAO
    qDebug() << "Armazenando dados...";
    std::list<Artur::Aluno*>* listaAlunos = pAlunoDao.lerArquivo();    //lerArquivo() retorna uma lista de ponteiros para cada aluno
    qDebug() << "Tamanho da lista de alunos" << listaAlunos->size();

    // Verificar se a lista de alunos existe
    if (!listaAlunos) {
        qDebug() << "Lista de alunos não encontrada.";
        return;
    }

    // Preencher o modelo de dados com os alunos
    int row = 0;
    for (auto it = listaAlunos->begin(); it != listaAlunos->end(); ++it) {
        const Artur::Aluno* aluno = (*it);

        // Criar itens de dados para cada coluna
//        QStandardItem* itemMatricula = new QStandardItem(aluno->getMatricula());
//        QStandardItem* itemNome = new QStandardItem(aluno->getNome());

        // Adicionar os itens de dados ao modelo de dados
//        model->setItem(row, 0, itemMatricula);
//        model->setItem(row, 1, itemNome);
            model->setData(model->index(row, 0), aluno->getMatricula(), Qt::DisplayRole);
            model->setData(model->index(row, 1), aluno->getNome(), Qt::DisplayRole);



        // Incrementar o número de linhas
        ++row;
    }
    ui->tableView->setModel(model);

    // Liberar a memória da lista de alunos
    delete listaAlunos;
}


void TelaPrincipalAluno::on_btn_incluir_clicked()
{
    Artur::Aluno* pAluno = new Artur::Aluno();
    Artur::AlunoDAO* pAlunoDao = new Artur::AlunoDAO();
    QString matricula=ui->lineEdit_matricula->text();   //Pega matricula
    QString nome=ui->lineEdit_nome->text();            //Pega nome
    pAluno->setMatricula(matricula);                  //Atribui matricula ao objeto
    pAluno->setNome(nome);                           //Atribui nome ao objeto
    try{
        pAlunoDao->inserir(pAluno);                //Adiciona aluno ao arquivo se ainda não está
    }catch(QString &erro){
        QMessageBox::about(this,"",erro);
        return;
    }
    QMessageBox::about(this,"Sucesso.","Aluno adicionado com sucesso ao arquivo.");

    atualizarTableView();
}


void TelaPrincipalAluno::on_btn_consultar_clicked()
{
    QString matricula=ui->lineEdit_matricula->text();   //Recebe matricula
    try{
        pAlunoDao.buscar(matricula);  //Retorna ponteiro para aluno caso encontrado
    }catch(QString &erro){
        QMessageBox::about(this,"",erro);
        return;
    }
    //O aluno existe no arquivo
    QMessageBox::about(this, "Sucesso.", "Aluno encontrado no arquivo");

    atualizarTableView();
}

void TelaPrincipalAluno::on_pushButton_atualizar_clicked()
{
    Artur::Aluno* pAluno = new Artur::Aluno();  //Cria novo objeto da classe Aluno
    Artur::AlunoDAO* pAlunoDao = new Artur::AlunoDAO(); //Cria novo objeto da classe DAO
    QString matricula=ui->lineEdit_matricula->text();   //Pega matricula
    QString nome=ui->lineEdit_nome->text();            //Pega nome
    pAluno->setMatricula(matricula);                  //Atribui matricula ao objeto
    pAluno->setNome(nome);                           //Atribui nome ao objeto
    try{
        pAlunoDao->buscar(matricula);  //Verifica se aluno está no arquivo com base na matricula
    }catch(QString &erro){
        QMessageBox::about(this,"",erro);
        return;
    }
    //Se estiver, devemos atualizar seus dados
    try
    {
        pAlunoDao->alterar(pAluno); //Remove antigo objeto e adiciona o objeto atualizado na lista
    }
    catch(QString &erro)
    {
        QMessageBox::critical(this,"",erro);
        return;
    }

    QMessageBox::about(this, "Sucesso.", "Dados do aluno atualizados");
    atualizarTableView();
}


void TelaPrincipalAluno::on_pushButton_remover_clicked()
{
    Artur::AlunoDAO* pAlunoDao = new Artur::AlunoDAO(); //Cria novo objeto da classe DAO
    QString matricula = ui->lineEdit_matricula->text();
    try
    {
    pAlunoDao->deletar(matricula);
    }
    catch(QString &erro)
    {
        QMessageBox::critical(this,"",erro);
        return;
    }

    QMessageBox::about(this, "Sucesso.", "Aluno removido");
    atualizarTableView();
}


void TelaPrincipalAluno::on_pushButton_clicked()
{
    atualizarTableView();
}

