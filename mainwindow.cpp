#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Remplir la combobox avec les genres
    ui->comboBox_genre->addItem("Roman");
    ui->comboBox_genre->addItem("Policier");
    ui->comboBox_genre->addItem("Science-fiction");
    ui->comboBox_genre->addItem("Fantasy");
    ui->comboBox_genre->addItem("Biographie");

    // Créer le modèle pour la listview
    m_model = new QStringListModel(this);
    ui->listView_livres->setModel(m_model);

    // Désactiver les boutons de modification et de suppression
    ui->button_modifier->setEnabled(false);
    ui->button_supprimer->setEnabled(false);

    // Connecter les boutons à leurs fonctions respectives
        connect(ui->button_ajouter, SIGNAL(clicked()), this, SLOT(on_ajouter_livre_clicked()));
        connect(ui->button_modifier, SIGNAL(clicked()), this, SLOT(on_modifier_livre_clicked()));
        connect(ui->button_rechercher, SIGNAL(clicked()), this, SLOT(on_rechercher_livre_clicked()));
        connect(ui->button_supprimer, SIGNAL(clicked()), this, SLOT(on_supprimer_livre_clicked()));
        connect(ui->listView_livres, SIGNAL(clicked(QModelIndex)), this, SLOT(on_listview_livres_clicked(QModelIndex)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_livre_clicked()
{
    // Récupérer les informations saisies par l'utilisateur
    QString titre = ui->lineEdit_titre->text();
    QString auteur = ui->lineEdit_auteur->text();
    int annee = ui->spinBox_annee->value();
    QString genre = ui->comboBox_genre->currentText();

    // Vérifier que les champs obligatoires sont remplis
    if (titre.isEmpty() || auteur.isEmpty() || annee == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }

    // Créer un nouveau livre à partir des informations saisies
    Livre nouveau_livre(titre, auteur, annee, genre);

    // Ajouter le nouveau livre à la liste des livres
    m_livres.append(nouveau_livre);

    // Mettre à jour l'affichage de la liste des livres
    afficher_livres();

    // Effacer les champs de saisie
    vider_champs_livre();

    // Désactiver les boutons de modification et de suppression
    ui->button_modifier->setEnabled(false);
    ui->button_supprimer->setEnabled(false);
}

void MainWindow::on_modifier_livre_clicked()
{
    // Vérifier qu'un livre est sélectionné
    if (m_index_livre_selectionne == -1) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un livre à modifier.");
        return;
    }

    // Récupérer les informations saisies par l'utilisateur
    QString nouveau_titre = ui->lineEdit_titre->text();
    QString nouveau_auteur = ui->lineEdit_auteur->text();
    int nouveau_annee = ui->spinBox_annee->value();
    QString nouveau_genre = ui->comboBox_genre->currentText();

    // Vérifier que les champs obligatoires sont remplis
    if (nouveau_titre.isEmpty() || nouveau_auteur.isEmpty() || nouveau_annee == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }

    // Mettre à jour les informations du livre sélectionné
    m_livres[m_index_livre_selectionne].set_titre(nouveau_titre);
    m_livres[m_index_livre_selectionne].set_auteur(nouveau_auteur);
    m_livres[m_index_livre_selectionne].set_annee(nouveau_annee);
    m_livres[m_index_livre_selectionne].set_genre(nouveau_genre);

    // Mettre à jour l'affichage de la liste des livres
    afficher_livres();

    // Effacer les champs de saisie
    vider_champs_livre();

    // Désactiver les boutons de modification et de suppression
    ui->button_modifier->setEnabled(false);
    ui->button_supprimer->setEnabled(false);
}

void MainWindow::on_supprimer_livre_clicked()
{
    // Vérifier qu'un livre est sélectionné
    if (m_index_livre_selectionne == -1) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un livre à supprimer.");
        return;
    }

    // Supprimer le livre sélectionné de la liste des livres
    m_livres.removeAt(m_index_livre_selectionne);

    // Mettre à jour l'affichage de la liste des livres
    afficher_livres();

    // Réinitialiser l'index du livre sélectionné
    m_index_livre_selectionne = -1;

    // Effacer les champs de saisie
    vider_champs_livre();

    // Désactiver les boutons de modification et de suppression
    ui->button_modifier->setEnabled(false);
    ui->button_supprimer->setEnabled(false);
}

void MainWindow::on_rechercher_livre_clicked()
{
    // Récupérer le critère de recherche saisi par l'utilisateur
    QString critere = QInputDialog::getText(this, "Recherche de livre", "Entrez le critère de recherche :");

    // Vérifier que le critère de recherche n'est pas vide
    if (critere.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un critère de recherche.");
        return;
    }

    // Parcourir la liste des livres et afficher ceux qui correspondent au critère de recherche
    QStringList livres_correspondants;
    for (const Livre &livre : m_livres) {
        if (livre.get_titre().contains(critere, Qt::CaseInsensitive) ||
            livre.get_auteur().contains(critere, Qt::CaseInsensitive) ||
            QString::number(livre.get_annee()).contains(critere) ||
            livre.get_genre().contains(critere, Qt::CaseInsensitive)) {
            livres_correspondants.append(livre.to_string());
        }
    }

    // Afficher les livres correspondants dans la listview
    m_model->setStringList(livres_correspondants);

    // Désactiver les boutons de modification et de suppression
    ui->button_modifier->setEnabled(false);
    ui->button_supprimer->setEnabled(false);
}

void MainWindow::afficher_livres()
{
    // Créer une liste de chaînes de caractères à partir de la liste des livres
    QStringList livres_en_string;
    for (const Livre &livre : m_livres) {
        livres_en_string.append(livre.to_string());
    }

    // Mettre à jour le modèle de la listview avec la nouvelle liste de chaînes de caractères
    m_model->setStringList(livres_en_string);
}

void MainWindow::remplir_champs_livre_selectionne()
{
    // Vérifier qu'un livre est sélectionné
    if (m_index_livre_selectionne == -1) {
        return;
    }

    // Remplir les champs de saisie avec les informations du livre sélectionné
    ui->lineEdit_titre->setText(m_livres[m_index_livre_selectionne].get_titre());
    ui->lineEdit_auteur->setText(m_livres[m_index_livre_selectionne].get_auteur());
    ui->spinBox_annee->setValue(m_livres[m_index_livre_selectionne].get_annee());
    ui->comboBox_genre->setCurrentText(m_livres[m_index_livre_selectionne].get_genre());

    // Activer les boutons de modification et de suppression
    ui->button_modifier->setEnabled(true);
    ui->button_supprimer->setEnabled(true);
}

void MainWindow::vider_champs_livre()
{
    // Effacer les champs de saisie
    ui->lineEdit_titre->clear();
    ui->lineEdit_auteur->clear();
    ui->spinBox_annee->setValue(0);
    ui->comboBox_genre->setCurrentIndex(0);
}

void MainWindow::on_listView_livres_clicked(const QModelIndex &index)
{
    // Mettre à jour l'index du livre sélectionné
    m_index_livre_selectionne = index.row();

    // Remplir les champs de saisie avec les informations du livre sélectionné
    remplir_champs_livre_selectionne();
}
