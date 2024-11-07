#include "employe.h"

Employe::Employe() {}

Employe::Employe(int id, QString nom, QString poste, QString prenom, int salaire)
{
    this->id = id;
    this->nom = nom;
    this->poste = poste;
    this->prenom = prenom;
    this->salaire = salaire;
}

bool Employe::ajouter()
{
    QSqlQuery query;
    QString id_string = QString::number(id);
    QString salaire_string = QString::number(salaire);

    query.prepare("INSERT INTO EMPLOYE (ID, NOM, POSTE, PRENOM, SALAIRE) "
                  "VALUES (:id, :nom, :poste, :prenom, :salaire)");

    query.bindValue(":id", id_string);
    query.bindValue(":nom", nom);
    query.bindValue(":poste", poste);
    query.bindValue(":prenom", prenom);
    query.bindValue(":salaire", salaire_string);

    return query.exec();
}

bool Employe::modifier()
{
    QSqlQuery query;
    QString id_string = QString::number(id);
    QString salaire_string = QString::number(salaire);
    query.prepare("UPDATE EMPLOYE SET NOM=:nom, POSTE=:poste, PRENOM=:prenom, SALAIRE=:salaire WHERE ID=:id");

    query.bindValue(":id", id_string);
    query.bindValue(":nom", nom);
    query.bindValue(":poste", poste);
    query.bindValue(":prenom", prenom);
    query.bindValue(":salaire", salaire_string);

    return query.exec();
}

QSqlQueryModel *Employe::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM EMPLOYE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Salaire"));

    return model;
}

bool Employe::supprimer(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM EMPLOYE WHERE ID=:id");
    query.bindValue(":id", id);

    return query.exec();
}




