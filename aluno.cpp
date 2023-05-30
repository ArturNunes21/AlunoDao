#include "aluno.h"

namespace Artur{

Aluno::Aluno()
{
}

Aluno::Aluno(QString mat, QString nome)
    : matricula(mat), nome(nome)
{
}

QString Aluno::getMatricula() const
{
    return matricula;
}

void Aluno::setMatricula(const QString &newMatricula)
{
    matricula = newMatricula;
}

QString Aluno::getNome() const
{
    return nome;
}

void Aluno::setNome(const QString &newNome)
{
    nome = newNome;
}

QString Aluno::getDados() const
{
    QString dados = matricula + ";" + nome;
    return dados;
}

}   //namespace
