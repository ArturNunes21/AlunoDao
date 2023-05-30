#ifndef TELAPRINCIPALALUNO_H
#define TELAPRINCIPALALUNO_H

#include <QMainWindow>
//#include "alunocontroler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TelaPrincipalAluno; }
QT_END_NAMESPACE

class TelaPrincipalAluno : public QMainWindow
{
    Q_OBJECT

public:
    TelaPrincipalAluno(QWidget *parent = nullptr);
    ~TelaPrincipalAluno();

private slots:
    void atualizarTableView();
    void on_btn_incluir_clicked();
    void on_btn_consultar_clicked();

    void on_pushButton_atualizar_clicked();

    void on_pushButton_remover_clicked();

    void on_pushButton_clicked();

private:
    Ui::TelaPrincipalAluno *ui;
    //AlunoControler controlador;
};
#endif // TELAPRINCIPALALUNO_H
