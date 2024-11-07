#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>
#include <QSslSocket>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->tab_norme->setModel(cl.afficher());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushAdd_clicked()
{
    int id = ui->le_id_3->text().toInt();
    QString nom = ui->le_nom_3->text();
    QString poste = ui->le_poste->text();
    QString prenom = ui->le_mail->text();
    int salaire = ui->le_salaire->text().toInt();

    Employe cl(id, nom, poste, prenom, salaire);
    bool test = cl.ajouter();

    if (test) {
        ui->tab_norme->setModel(cl.afficher());
        QMessageBox::information(nullptr, "RDI Center", "Ajout effectué.", QMessageBox::Cancel);

        ui->le_id_3->clear();
        ui->le_nom_3->clear();
        ui->le_poste->clear();
        ui->le_mail->clear();
        ui->le_salaire->clear();
    } else {
        QMessageBox::critical(nullptr, "RDI Center", "Ajout non effectué.", QMessageBox::Cancel);
    }
}

void MainWindow::on_pushModify_clicked()
{
    Employe cl;
    cl.setId(ui->le_id_10->text().toInt());
    cl.setNom(ui->le_nom_6->text());
    cl.setPoste(ui->le_poste_3->text());
    cl.setPrenom(ui->le_mail_3->text());
    cl.setSalaire(ui->le_salaire_3->text().toInt());

    bool check = cl.modifier();

    if (check) {
        ui->tab_norme->setModel(cl.afficher());

        QMessageBox::information(nullptr, "RDI Center", "Modification avec succès.", QMessageBox::Cancel);

        ui->le_id_10->clear();
        ui->le_nom_6->clear();
        ui->le_poste_3->clear();
        ui->le_mail_3->clear();
        ui->le_salaire_3->clear();
    } else {
        QMessageBox::critical(nullptr, "RDI Center", "Modification échouée.", QMessageBox::Cancel);
    }
}

void MainWindow::on_pushDelete_clicked()
{
    int id = ui->le_id_5->text().toInt();
    bool test = cl.supprimer(id);

    if (test) {
        ui->tab_norme->setModel(cl.afficher());
        QMessageBox::information(nullptr, "RDI Center", "Suppression effectuée.", QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, "RDI Center", "Suppression non effectuée.", QMessageBox::Cancel);
    }
    ui->le_id_5->clear();
}


void MainWindow::on_pushActualiser_clicked()
{
    ui->tab_norme->setModel(cl.afficher());
}



void MainWindow::on_tab_norme_activated(const QModelIndex &index)
{
    QString value = ui->tab_norme->model()->data(index).toString();
    ui->le_id_5->setText(value);
    ui->pdfLine->setText(value);

    QSqlQuery qry;

    qry.prepare("select * from EMPLOYE where id='" + value + "'");
    if (qry.exec()) {
        while (qry.next()) {
            ui->le_id_10->setText(qry.value(0).toString());
            ui->le_nom_6->setText(qry.value(1).toString());
            ui->le_poste_3->setText(qry.value(2).toString());
            ui->le_mail_3->setText(qry.value(3).toString());
            ui->le_salaire_3->setText(qry.value(4).toString());
        }
    }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QString searchValue = arg1;
    QSqlQueryModel *model = new QSqlQueryModel();

    // Filter the table based on the search value
    model->setQuery("SELECT * FROM CLIENT WHERE ID LIKE '%" + searchValue + "%' OR NOM LIKE '%" + searchValue + "%'");
    ui->tab_norme->setModel(model);
}



