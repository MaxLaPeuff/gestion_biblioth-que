#ifndef LIVRE_H
#define LIVRE_H

#include <QString>

class Livre
{
public:
    Livre(const QString &titre, const QString &auteur, int annee, const QString &genre);

    QString get_titre() const;
    QString get_auteur() const;
    int get_annee() const;
    QString get_genre() const;

    void set_titre(const QString &nouveau_titre);
    void set_auteur(const QString &nouveau_auteur);
    void set_annee(int nouveau_annee);
    void set_genre(const QString &nouveau_genre);

    QString to_string() const;

private:
    QString m_titre;
    QString m_auteur;
    int m_annee;
    QString m_genre;
};

#endif // LIVRE_H
