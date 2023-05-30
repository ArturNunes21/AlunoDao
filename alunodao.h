#ifndef ALUNODAO_H
#define ALUNODAO_H

#include "dao.h"  // Inclua o arquivo que contém a definição completa da classe DAO
#include "aluno.h"
#include <list>
#include <QString>
#include <fstream>
#include <string>

namespace Artur {

class AlunoDAO : public DAO<Aluno> {  // Certifique-se de que a definição completa da classe DAO esteja disponível
public:
    AlunoDAO();
    void inserir(Aluno* obj);  // Create
    Aluno* buscar(QString const &id);  // Read
    void alterar(Aluno* obj);  // Update
    void deletar(QString const &id);  // Delete
    std::list<QString>* listar();
    std::list<Aluno*>* lerArquivo();

private:
    Aluno* buscarArquivo(QString const& id);
    void gravarArquivo(std::list<Aluno*>* lista);
    QString nomeArquivo;
    std::string enderecoArquivo = "C:/Users/Artur.Resende/Documents/Artur Nunes/Codigos QT/AlunoDao-main/AlunoDao-main/alunos.txt.txt";
};

}  // namespace

#endif // ALUNODAO_H
