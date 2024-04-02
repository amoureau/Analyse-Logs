//---------- Réalisation de la classe <Stats> (fichier Stats.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Stats.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
vector<string> Stats::GetTop10() const {
    return top10;
} //----- Fin de GetTop10

unordered_map<string, int> Stats::GetNbReferences() const {
    return nbReferences;
} //----- Fin de GetNbReferences

unordered_map<string, unordered_map<string, int>> Stats::GetListeAdjacence() const {
    return listeAdjacence;
} //----- Fin de GetListeAdjacence

void Stats::MajListeAdjacence(vector<string> ligne_log) {
    string urlRecept = ligne_log[6]; // URL de la page réceptrice
    string urlEnvoie = ligne_log[10]; // URL de la page émettrice
    listeAdjacence[urlEnvoie][urlRecept]++; // Incrémente le compteur de références entre les deux pages
    nbReferences[urlRecept]++; // Incrémente le compteur de références total de la page réceptrice
    GererTop10(urlRecept); // Met à jour le top 10 des pages les plus référencées
} //----- Fin de MajListeAdjacence



Stats::Stats() { 
    // On stocke les lignes du fichier, sous forme de vecteur contenant les éléments séparés, dans un vecteur tableau_log
        #ifdef MAP
    cout << "Appel au constructeur de <Stats>" << endl;
        #endif
} //----- Fin de Stats

Stats::~Stats() { 
    // On supprime le vecteur contenant les lignes du fichier
        #ifdef MAP
    cout << "Appel au destructeur de <Stats>" << endl;
        #endif 
} //----- Fin de ~Stats


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void Stats::GererTop10(string urlRecept) {
    // Vérifie si l'URL de la page réceptrice n'est pas déjà présente dans le top 10
    if (find(top10.begin(), top10.end(), urlRecept) == top10.end()) {
        // Si le top 10 n'est pas encore plein, ajoute l'URL de la page réceptrice
        if (top10.size() < 10 ) {
            top10.push_back(urlRecept);
        }
        // Sinon, remplace la dernière URL du top 10 si l'URL de la page réceptrice a plus de références
        else if (nbReferences[urlRecept] > nbReferences[top10[9]]) {
            top10[9] = urlRecept;
            // Trie le top 10 en fonction du nombre de références de chaque page
            vector<string>::iterator it = top10.end()-1;
            while (it != top10.begin() && nbReferences[*it] > nbReferences[*(it-1)]) {
                iter_swap(it, it-1);
                it--;
            }
        }
    }   
    else {
        // Si l'URL de la page réceptrice est déjà présente dans le top 10, met à jour sa position en fonction du nombre de références
        vector<string>::iterator it = find(top10.begin(), top10.end(), urlRecept);
        while (it != top10.begin() && nbReferences[*it] > nbReferences[*(it-1)]) {
            iter_swap(it, it-1);
            it--;
        }
    }
} //----- Fin de GererTop10