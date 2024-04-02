//---------- Interface de la classe <Lecture> (fichier Lecture.h) ----------------
#if ! defined ( LECTURE_H )
#define LECTURE_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Lecture>
/*
    La classe Lecture permet de lire un fichier log et de stocker les informations
    relatives à ce fichier. Elle permet de lire les lignes du fichier log, en excluant
    les lignes correspondant à des extensions exclues, à des heures hors intervalle
    et à des urls locales.
 */
//
//------------------------------------------------------------------------

class Lecture 
{
    //----------------------------------------------------------------- PUBLIC
    public :
        //----------------------------------------------------- Méthodes publiques
        vector<string> LireLigne(bool& fini);
        //Mode d'emploi : Lit une ligne du fichier log et stocke les informations relatives à cette ligne

        //-------------------------------------------- Constructeurs - destructeur
        Lecture(string nomFichier, vector<string> extensions_exclues = {}, string intervalle_temps = "", string localurl = "");
        //Mode d'emploi : Constructeur de la classe Lecture

        ~Lecture();
        //Mode d'emploi : Destructeur de la classe Lecture

    //------------------------------------------------------------------ PRIVE
    private :
        //----------------------------------------------------- Méthodes privées
        
        //----------------------------------------------------- Attributs privés
        string nomFichier;
        vector<string> excluded_extensions;
        string urlLocal;
        string time_interval;
        ifstream fich;
};


#endif