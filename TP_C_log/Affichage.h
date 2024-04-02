//---------- Interface de la classe <Lecture> (fichier Lecture.h) ----------------
#if ! defined ( AFFICHAGE_H )
#define AFFICHAGE_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Affichage>
/*
    La classe Affichage permet d'afficher les informations relatives aux statistiques
    des pages web consultées. Elle permet d'afficher le top 10 des pages les plus consultées
    et de générer un fichier .dot et une image .png représentant le graphe des pages web.
 */
//
//------------------------------------------------------------------------

class Affichage
{
    //----------------------------------------------------------------- PUBLIC
    public :
        //----------------------------------------------------- Méthodes publiques
        void AfficherTop10(vector<string> top10, unordered_map<string, int> nbReferences);
        //Mode d'emploi : Affiche le top 10 des pages les plus consultées
        void AfficherGraphe(unordered_map<string, unordered_map<string, int>> graphe, bool png, string nomFichier = "graphe.dot");

        //Mode d'emploi : Génère un fichier .dot et une image .png représentant le graphe des pages web

        //-------------------------------------------- Constructeurs - destructeur
        Affichage();
        //Mode d'emploi : Constructeur de la classe Affichage

        ~Affichage();
        //Mode d'emploi : Destructeur de la classe Affichage


    private :
        //----------------------------------------------------- Méthodes privées
        
        //----------------------------------------------------- Attributs privés

};

#endif