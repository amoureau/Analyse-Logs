//---------- Réalisation de la classe <Affichage> (Affichage.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Affichage.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Affichage::AfficherTop10(vector<string> top10, unordered_map<string, int> nbReferences){
    if (top10.size() == 0){
        cout << "Le Top 10 est vide" << endl; // Affiche un message si le Top 10 est vide
    }
    else{
        cout << "Top 10 des pages les plus consultées : " << endl; // Affiche un message pour indiquer le début du Top 10
        for (int i = 0; i < top10.size(); i++){  // Affiche chaque page du Top 10 avec le nombre de hits correspondant
            cout << i+1 << " - " << top10[i] << " (" << nbReferences[top10[i]] << " hits)" << endl;
        }
    }
} //----- Fin de AfficherTop10

void Affichage::AfficherGraphe(unordered_map<string, unordered_map<string, int>> adjacence, bool png, string nomFichier){
    ofstream fichier(nomFichier, ios::out | ios::trunc); // Ouvre un fichier en mode écriture et tronque le contenu existant
    if(fichier){
        fichier << "digraph {" << endl;
        for (auto it = adjacence.begin(); it != adjacence.end(); it++){ // Parcourt la liste d'adjacence
            for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++){ // Parcourt les valeurs associées à chaque clé du graphe
                fichier << it2->first << " -> " << it->first << " [label=" << it2->second << "];" << endl; // Écrit une ligne représentant une relation dans le graphe
            }
        }
        fichier << "}" << endl; 
        fichier.close(); 
        if (png){
        std::string nomFichierSortie = nomFichier.substr(0, nomFichier.find_last_of(".")) + ".png";
        std::system(("dot -Tpng -o " + nomFichierSortie + " " + nomFichier).c_str()); // Exécute la commande système pour générer une image PNG à partir du fichier graphe.dot
        std::system(("eog " + nomFichierSortie).c_str()); // Exécute la commande système pour ouvrir l'image PNG avec l'application eog
        }
    }
    else{
        cerr << "Erreur à l'ouverture !" << endl; // Affiche un message d'erreur si le fichier n'a pas pu être ouvert
    }
} //----- Fin de AfficherGraphe

// Constructeur
Affichage::Affichage()
{
    #ifdef MAP
        cout << "Appel au constructeur de <Affichage>" << endl;
    #endif 
} //----- Fin de Affichage
 
// Destructeur
Affichage::~Affichage()
{
    #ifdef MAP
        cout << "Appel au destructeur de <Affichage>" << endl;
    #endif
} //----- Fin de ~Affichage