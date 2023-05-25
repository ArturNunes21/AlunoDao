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
    QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(ui->tableView->model());

    // Verificar se o modelo de dados existe e se está correto
    if (!model) {
        qDebug() << "Modelo de dados da tabela não encontrado ou inválido.";
        return;
    }

    // Limpar o modelo de dados existente
    model->clear();

    // Obter a lista de alunos do DAO
    std::list<QString>* listaAlunos = pAlunoDao.listar();

    // Verificar se a lista de alunos existe
    if (!listaAlunos) {
        qDebug() << "Lista de alunos não encontrada.";
        return;
    }

    // Preencher o modelo de dados com os alunos
    int row = 0;
    for (auto it = listaAlunos->begin(); it != listaAlunos->end(); ++it) {
        const Artur::Aluno* aluno = *it;

        // Criar itens de dados para cada coluna
        QStandardItem* itemMatricula = new QStandardItem(aluno->getMatricula());
        QStandardItem* itemNome = new QStandardItem(aluno->getNome());

        // Adicionar os itens de dados ao modelo de dados
        model->setItem(row, 0, itemMatricula);
        model->setItem(row, 1, itemNome);

        // Incrementar o número de linhas
        ++row;
    }

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
    QString matricula=ui->lineEdit_matricula->text();
    Artur::Aluno* aluno=nullptr;
    try{
        aluno=pAlunoDao.buscar(matricula);
    }catch(QString &erro){
        QMessageBox::about(this,"",erro);
        return;
    }
    QString nome = aluno->getNome();
    QString mat = aluno->getMatricula();
    QMessageBox::about(this, "Sucesso.", "Aluno encontrado no arquivo");

    atualizarTableView();
}














