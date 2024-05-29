#include "livre.h"

Livre::Livre(const QString &titre, const QString &auteur, int annee, const QString &genre)
    : m_titre(titre), m_auteur(auteur), m_annee(annee), m_genre(genre)
{
}

QString Livre::get_titre() const
{
    return m_titre;
}

QString Livre::get_auteur() const
{
    return m_auteur;
}

int Livre::get_annee() const
{
    return m_annee;
}

QString Livre::get_genre() const
{
    return m_genre;
}

void Livre::set_titre(const QString &nouveau_titre)
{
    m_titre = nouveau_titre;
}

void Livre::set_auteur(const QString &nouveau_auteur)
{
    m_auteur = nouveau_auteur;
}

void Livre::set_annee(int nouveau_annee)
{
    m_annee = nouveau_annee;
}

void Livre::set_genre(const QString &nouveau_genre)
{
    m_genre = nouveau_genre;
}

QString Livre::to_string() const
{
    return m_titre + " - " + m_auteur + " (" + QString::number(m_annee) + ")";
}
