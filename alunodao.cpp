#include "alunodao.h"
#include <QStringList>
#include <string>
#include <list>

namespace Artur{

AlunoDAO::AlunoDAO()
{
}

void AlunoDAO::inserir(Aluno* obj){//Create
   std::list<Artur::Aluno*>* lista = lerArquivo(); //Recebe uma lista com todos os objetos de alunos do arquivo
   if(this->buscarArquivo(obj->getMatricula())!=nullptr){   //Verifica se o aluno esta no arquivo
       throw QString("Matricula ja se encontra no arquivo.");    //se o aluno ja esta na lista, não é inserido novamente
   }else{
       lista->push_back(obj);   //Se o aluno não está no arquivo, é adicionado na lista
   }
   gravarArquivo(lista);    //Adiciona o novo aluno ao arquivo CSV
   lista = nullptr;
}
//Buscar aluno no arquivo
Aluno* AlunoDAO::buscarArquivo(QString const &id){  //Retorna um ponteiro para o aluno no arquivo, caso seja encontrado
    Aluno* a=nullptr;
    std::string linha;
    QString linhaQt;
    QStringList linhaQtList;
    std::ifstream arquivo;
    arquivo.open(enderecoArquivo);//Abrir arquivo
    if(arquivo.is_open()){
        while(getline(arquivo, linha)){
            linhaQt = QString::fromStdString(linha); //Passa a informação de uma string para uma QString
            linhaQtList = linhaQt.split(';');   //Separa cada coluna com o separador (";") e os coloca em uma lista
            if(linhaQtList[0] == id){
                a = new Aluno(linhaQtList[0], linhaQtList[1]);  //Verifica cada linha do arquivo buscando o aluno desejado
                break;
            }
        }
    }else{
            throw QString("Arquivo não pode ser aberto - buscarArquivo");
        }
    arquivo.close();//Fecha arquivo
    return a;   //Caso aluno não seja encontrado, retorna nullptr, senão, retorna ponteiro para o objeto
}
//Buscar aluno
Aluno* AlunoDAO::buscar(QString const &id){
    if(id==""){
        throw QString("Matricula não fornecida.");
    }
    Aluno* a = this->buscarArquivo(id);
    if(a != nullptr)
        return a;   //Retorna o ponteiro para o objeto
    else
        throw QString("Matricula não encontrada");
}
void AlunoDAO::alterar(Aluno* obj) {
    bool achou = false;
    std::list<Aluno*>* lista = this->lerArquivo();  //Lista com ponteiro de todos os objeto tipo Aluno
    std::list<Aluno*>::iterator it;
    for (it = lista->begin(); it != lista->end(); ++it) {   //Percorre todos os objetos da classe Aluno
        if ((*it)->getMatricula() == obj->getMatricula()) { //Encontra o objeto na lista
            it = lista->erase(it); // Remove obj_antigo da lista e avança o iterador
            lista->push_back(obj); // Insere obj na lista
            this->gravarArquivo(lista); // Grava lista
            achou = true;
            break; // Encerra o loop após a remoção do elemento
        }
    }
    if (!achou)
        throw QString("Aluno não encontrado");
}

//Deletar aluno
void AlunoDAO::deletar(QString const &id){//Delete
    bool achou=false;
    std::list<Aluno*>* lista = this->lerArquivo();  //Armazena a lista contendo todos os ponteiros para alunos em uma lista
    std::list<Aluno*>::iterator it;
    for(it = lista->begin(); it != lista->end(); ++it){
      if((*it)->getMatricula() == id){
          lista->erase(it);
          delete (*it);
          this->gravarArquivo(lista);
          achou = true;
          break;
      }
    }
    if (!achou)
        throw QString("Aluno não encontrado");
}
//Ler arquivo CSV
std::list<Aluno*>* AlunoDAO::lerArquivo(){
    std::list<Aluno*>* lista = new std::list<Aluno*>(); //cria uma nova lista de ponteiros
    Aluno* a=nullptr; //Cria um novo objeto
    std::string linha;
    QString linhaQt;
    QStringList linhaQtList;
    std::ifstream arquivo;
    arquivo.open(enderecoArquivo);
    if(arquivo.is_open()){
        while(getline(arquivo, linha)){
            linhaQt = QString::fromStdString(linha);    //Passa o valor de uma string para uma QString
            linhaQtList = linhaQt.split(';');   //Separa cada coluna com o separador (';') e adiciona cada elemento a uma lista
            a = new Aluno(linhaQtList[0], linhaQtList[1]);
            lista->push_back(a);    //Adiciona um novo objeto da classe aluno a lista de alunos
        }
    }else{
        throw QString("Arquivo não pode ser aberto - lerArquivo");
    }
    arquivo.close();//Fecha arquivo
    return lista;   //Retorna uma lista de ponteiros para objetos contendo matricula e nome de cada aluno
}
//Gravar Arquivo CSV
void AlunoDAO::gravarArquivo(std::list<Aluno*>* lista){
    std::ofstream arquivo;
    arquivo.open(enderecoArquivo);
    if(arquivo.is_open()){
        std::list<Aluno*>::iterator it;
        for(it = lista->begin(); it != lista->end(); ++it)
            arquivo << (*it)->getDados().toStdString()<<std::endl;  //adiciona os dados de cada objeto no arquivo
        arquivo.close();//Fecha arquivo
        delete lista;
    }else{
        throw QString("Arquivo não pode ser aberto - gravarArquivo");
    }
}
//Listar alunos
std::list<QString>* AlunoDAO::listar(){
    std::list<Artur::Aluno*>* listaAluno = lerArquivo();   //Armazena a lista contendo todos os ponteiros para alunos em uma lista
    std::list<QString>* lista = new std::list<QString>();
    std::list<Aluno*>::iterator it;
    for(it = listaAluno->begin(); it != listaAluno->end(); ++it){
        lista->push_back((*it)->getDados());    //adiciona os dados do objeto na lista
    }
    delete listaAluno;
    return lista;   //retorna os dados de cada objeto em uma lista de ponteiros
}

}   //namespace
