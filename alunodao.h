#ifndef ALUNODAO_H
#define ALUNODAO_H

#include "dao.h"  // Inclua o arquivo que contém a definição completa da classe DAO
#include "aluno.h"
#include <list>
#include <QString>
#include <fstream>

namespace Artur {

class AlunoDAO : public DAO<Aluno> {  // Certifique-se de que a definição completa da classe DAO esteja disponível
public:
    AlunoDAO();
    void inserir(Aluno* obj);  // Create
    Aluno* buscar(QString const &id);  // Read
    void alterar(Aluno* obj);  // Update
    void deletar(QString const &id);  // Delete
    std::list<QString>* listar();

private:
    Aluno* buscarArquivo(QString const& id);
    void gravarArquivo(std::list<Aluno*>* lista);
    QString nomeArquivo;
    std::list<Aluno*>* lerArquivo();
};

}  // namespace

#endif // ALUNODAO_H
