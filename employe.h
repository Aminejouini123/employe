#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>

class Employe
{
public:
    int id;
    QString nom, poste, prenom;
    int salaire;

public:
    Employe();
    Employe(int, QString, QString, QString, int);

    int getId() const { return id; }
    QString getNom() const { return nom; }
    QString getPoste() const { return poste; }
    QString getPrenom() const { return prenom; }
    int getSalaire() const { return salaire; }

    // Setters
    void setId(int id_c) { id = id_c; }
    void setNom(QString nom_c) { nom = nom_c; }
    void setPoste(QString poste_c) { poste = poste_c; }
    void setPrenom(QString prenom_c) { prenom = prenom_c; }
    void setSalaire(int salaire_c) { salaire = salaire_c; }

    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier();
};

#endif
