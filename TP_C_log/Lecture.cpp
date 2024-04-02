//---------- Réalisation de la classe <Lecture> (fichier Lecture.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Lecture.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
vector<string> Lecture::LireLigne(bool& fini) {
    string ligne;
    vector<string> ligne_log;
    if (getline(fich, ligne)){ // Lecture d'une ligne du fichier
        string element;
        int index = 0;
        for (int i = 0; i < ligne.length(); i++) { // Parcourt la ligne caractère par caractère
            if (ligne[i] == ' ') { // Séparation des éléments de la ligne par un espace
                if (index == 8 && (element[0] != '2' && element[0] != '3')) {
                    return {}; // Retourne un vecteur vide si le return code n'est pas 2xx ou 3xx
                }

                if (!excluded_extensions.empty() && index == 6) { //exclure les extensions si demandé
                    size_t pos = element.find_last_of('.'); // Recherche de l'extension dans l'élément
                    if (pos != std::string::npos) {
                        string extension = element.substr(pos + 1);
                        for (auto j : excluded_extensions) {
                            if (extension == j) {
                                return {}; // Retourne un vecteur vide si l'extension est exclue
                            }
                        }
                    }
                }

                if (!time_interval.empty() && index == 4) { //exclure les heures hors intervalle si demandé
                    size_t pos = ligne.find('['); // Recherche de l'heure dans la ligne
                    if (pos != std::string::npos) {
                        string heure = ligne.substr(pos + 13, 2);
                        if (heure != time_interval) {
                            return {}; // Retourne un vecteur vide si l'heure est hors de l'intervalle
                        }
                    }
                }

                if (index == 6 || index == 10) { //enlever l'url Local des urls
                    //Enlever tout ce qui suit un ? ; ou # dans l'url
                    size_t pos_req = element.find_first_of("?;#"); // Recherche du premier caractère ? ; ou # dans l'élément
                    if (pos_req != std::string::npos) {
                        element.erase(pos_req); // Supprime tout ce qui suit le premier caractère trouvé
                    }
                    //Enlever l'url locale
                    size_t pos = element.find(urlLocal); // Recherche de l'url locale dans l'élément
                    if (pos != std::string::npos) {
                        element.erase(pos, urlLocal.size()); // Supprime l'url locale de l'élément
                    }
                    if (index == 6) {
                        if (element.back() == '/') {
                            element.pop_back(); // Supprime le dernier caractère s'il s'agit d'un '/'
                        }
                    }
                    if (index == 10 && element[element.size() - 2] == '/') {
                        element.erase(element.size() - 2, 1); // Supprime l'avant-dernier caractère s'il s'agit d'un '/'
                    }
                    //Remettre des guillemets au debut et à la fin s'il n'y en a pas
                    if (element[0] != '\"') {
                        element = "\"" + element; // Ajoute un guillemet au début de l'élément
                    }
                    if (element.size() == 1 || element[element.size() - 1] != '\"') {
                        element += "\""; // Ajoute un guillemet à la fin de l'élément
                    }
                }
                ligne_log.push_back(element); // Ajoute l'élément au vecteur ligne_log
                element = ""; // Réinitialise l'élément
                index++; // Incrémente l'index
            }
            else {
                element += ligne[i]; // Ajoute le caractère à l'élément
            }
        }
        ligne_log.push_back(element); // Ajoute le dernier élément au vecteur ligne_log
    }
    else {
        fini = true; // Indique que la lecture du fichier est terminée
    }
    
    return ligne_log; // Retourne le vecteur ligne_log
} //----- Fin de LireLigne



Lecture::Lecture(string nomFichier, vector<string> extensions_exclues, string intervalle_temps, string localurl) { 
    // On stocke les lignes du fichier, sous forme de vecteur contenant les éléments séparés, dans un vecteur tableau_log
    #ifdef MAP
    cout << "Appel au constructeur de <Lecture>" << endl;
    #endif 
    nomFichier = nomFichier;
    urlLocal = localurl;
    excluded_extensions = extensions_exclues;
    time_interval = intervalle_temps;
    fich.open(nomFichier); // Ouvre le fichier
    if (!fich.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier" << endl; // Affiche un message d'erreur si l'ouverture du fichier échoue
        exit(1); // Quitte le programme avec un code d'erreur
    }
    //Verifier que le fichier n'est pas vide
    if (fich.peek() == ifstream::traits_type::eof()) {
        cout << "Veuillez fournir un fichier contenant un log" << endl; // Affiche un message si le fichier est vide
        exit(1); // Quitte le programme avec un code d'erreur
    }
} //----- Fin de Lecture

Lecture::~Lecture() { 
    // On supprime le vecteur contenant les lignes du fichier
    #ifdef MAP
    cout << "Appel au destructeur de <Lecture>" << endl;
    #endif 
    if (fich.is_open()) {
        fich.close(); // Ferme le fichier
    }
} //----- Fin de ~Lecture
