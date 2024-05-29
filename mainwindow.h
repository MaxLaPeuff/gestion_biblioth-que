#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QStringListModel>
#include "livre.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_livre_clicked();
    void on_modifier_livre_clicked();
    void on_supprimer_livre_clicked();
    void on_rechercher_livre_clicked();
    void on_listView_livres_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QList<Livre> m_livres;
    QStringListModel *m_model;
    int m_index_livre_selectionne;

    void afficher_livres();
    void remplir_champs_livre_selectionne();
    void vider_champs_livre();
};
#endif // MAINWINDOW_H
