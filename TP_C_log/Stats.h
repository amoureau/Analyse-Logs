//---------- Interface de la classe <Stats> (fichier Stats.h) ----------------
#if ! defined ( STATS_H )
#define STATS_H

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
// Rôle de la classe <Stats>
/*
    La classe Stats permet de stocker les informations relatives aux statistiques
    des pages web consultées. Elle permet de stocker les informations relatives
    aux pages web consultées, de gérer le top 10 des pages les plus consultées
    et de stocker les informations relatives à la liste d'adjacence des pages web.
 */
//
//------------------------------------------------------------------------

class Stats 
{
    //----------------------------------------------------------------- PUBLIC
    public :
        //----------------------------------------------------- Méthodes publiques
        vector<string> GetTop10() const;
        //Mode d'emploi : Renvoie le top 10 des pages les plus consultées

        unordered_map<string, int> GetNbReferences() const;
        //Mode d'emploi : Renvoie le nombre de références pour chaque page web

        unordered_map<string, unordered_map<string, int>> GetListeAdjacence() const;
        //Mode d'emploi : Renvoie la liste d'adjacence des pages web

        void MajListeAdjacence(vector<string> ligne_log);
        //Mode d'emploi : Met à jour la liste d'adjacence à partir d'une ligne du fichier log
        

        //-------------------------------------------- Constructeurs - destructeur
        Stats();
        //Mode d'emploi : Constructeur par défaut de la classe Stats

        ~Stats();
        //Mode d'emploi : Destructeur de la classe Stats

    //------------------------------------------------------------------ PRIVE
    protected :
        //----------------------------------------------------- Méthodes protégées
        void GererTop10(string urlRecept);
        //Mode d'emploi : Gère le top 10 des pages les plus consultées

        //----------------------------------------------------- Attributs protégés
        unordered_map<string, unordered_map<string,int>> listeAdjacence;
        unordered_map<string, int> nbReferences;
        vector<string> top10;
};

#endif