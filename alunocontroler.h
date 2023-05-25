#ifndef ALUNOCONTROLER_H
#define ALUNOCONTROLER_H
#include "aluno.h"
#include "alunodao.h"
#include <list>

namespace Artur{

class AlunoControler
{
public:
    AlunoControler();
private:
    Aluno* a;
    AlunoDAO daoAluno;
    std::list<Aluno*>* alunos;
};

}   //namespace
#endif // ALUNOCONTROLER_H
