#include <iostream> 
#include <string>
#include <vector>
#include "Lecture.h"
#include "Stats.h"
#include "Affichage.h"
#include <algorithm>
using namespace std;

int main(int argc, char** argv) { // On récupère les arguments pour avoir les options puis le nom de fichier log
    if(argc < 2){ // Vérifie si au moins 2 arguments sont passés en ligne de commande sinon renvoie un message d'erreur
        cout << "Usage : ./main [options] nomdufichier.log" << endl; 
        return 1; // Quitte le programme avec un code d'erreur
    }
    
    vector<string> options; // Vecteur pour stocker les options passées en ligne de commande
    vector<string> excluded_extensions; // Vecteur pour stocker les extensions de fichiers à exclure
    string time_interval; // Chaîne de caractères pour stocker l'intervalle horaire
    string dot_file = ""; // Chaîne de caractères pour stocker le nom du fichier .dot
    bool gen_png = false; // Booléen pour indiquer si le fichier .png doit être généré
    
    for(int i = 1; i < argc-1; i++){ // Parcourt les arguments passés en ligne de commande
        string option = argv[i]; // Récupère l'option courante
        
        if(option == "-g"){ // Vérifie si l'option est "-g"
            if(i+1 >= argc -1 || argv[i+1][0] == '-'){ // Vérifie si le nom de fichier .dot est spécifié sinon renvoie un message d'erreur
                cout << "Nom de fichier non renseigné : un nom sera attribué arbitrairement (graphe.dot)" << endl; 
                dot_file = "graphe.dot"; // Attribue un nom arbitraire au fichier .dot
            }
            else{
                dot_file = argv[i+1]; // Stocke le nom du fichier .dot
                if (dot_file.size() < 5 || dot_file.substr(dot_file.size()-4) != ".dot") { // Vérifie si le fichier .dot a une extension valide
                    cout << "Fichier .dot invalide: " << dot_file << endl; // Sinon Affiche un message d'erreur
                    return 1; // Quitte le programme avec un code d'erreur
                }
                i++; // Passe à l'argument suivant
            }
        }

        else if(option == "-e"){ // Vérifie si l'option est "-e"
            excluded_extensions = {"js", "css", "png", "jpg", "bmp", "gif", "ico"}; // Initialise les extensions de fichiers à exclure
        }

        else if(option == "-t"){ // Vérifie si l'option est "-t"
            if(i+1 >= argc -1 || argv[i+1][0] == '-'){ // Vérifie si l'intervalle horaire est spécifié
                cout << "Veuillez préciser une plage horaire "  << endl; // Sinon affiche un message d'erreur
                return 1; // Quitte le programme avec un code d'erreur
            }

            time_interval = argv[i+1]; // Stocke l'intervalle horaire
            if (time_interval.size() == 1) {
                time_interval = "0" + time_interval; // Ajoute un 0 devant si l'heure est sur un seul chiffre, ex: -t 2 -> -t 02
            }

            if (time_interval.size() != 2 || !all_of(time_interval.begin(), time_interval.end(), ::isdigit)) { // Vérifie si l'intervalle horaire est valide
                cout << "Plage horaire invalide : " << time_interval << endl; // Sinon affiche un message d'erreur
                return 1; // Quitte le programme avec un code d'erreur
            }

            int hour = stoi(time_interval); // Convertit l'intervalle horaire en entier
            if (hour < 0 || hour > 23) { // Vérifie si l'intervalle horaire est valide
                cout << "Plage horaire invalide: " << time_interval << endl; // Sinon affiche un message d'erreur
                return 1; // Quitte le programme avec un code d'erreur
            }

            i++; // Passe à l'argument suivant
        }

        //Option pour générer automatiquement le fichier .png
        else if(option == "-p"){
            gen_png = true;
        }

        else{
            cout << "Option invalide: " << option << endl; // Affiche un message d'erreur si l'option est invalide
            return 1; // Quitte le programme avec un code d'erreur
        }
        
        options.push_back(option); // Ajoute l'option au vecteur des options
    } 

    if (dot_file == "" && gen_png) { // Vérifie si l'option -p est spécifiée sans l'option -g
        cout << "Option -p invalide sans option -g" << endl;
        return 1;
    }

    string log_file; // Chaîne de caractères pour stocker le nom du fichier log

    // Vérifie que le dernier argument est bien un fichier .log
    if (string(argv[argc-1]).size() < 5 || string(argv[argc-1]).substr(string(argv[argc-1]).size()-4) != ".log") {
        cout << "Fichier log invalide: " << argv[argc-1] << endl; // Affiche un message d'erreur
        return 1; // Quitte le programme avec un code d'erreur
    }

    else log_file = argv[argc-1]; // Stocke le nom du fichier log
    Stats stats;
    Affichage Affichage;
    Lecture lec(log_file, excluded_extensions, time_interval,"http://intranet-if.insa-lyon.fr");

    bool fini = false; // Variable booléenne pour indiquer si la lecture du fichier log est terminée
    while (!(fini)){ // Boucle tant que la lecture du fichier log n'est pas terminée
        vector<string> ligne_log = lec.LireLigne(fini); // Lit une ligne du fichier log
        if (ligne_log.size() != 0){
            stats.MajListeAdjacence(ligne_log); // Crée la liste d'adjacence à partir de la ligne lue
        }
    }
    vector<string> top10 = stats.GetTop10();
    Affichage.AfficherTop10(top10, stats.GetNbReferences());
    if (dot_file != "") {
        Affichage.AfficherGraphe(stats.GetListeAdjacence(), gen_png, dot_file);
    }
  
    return 0; // Quitte le programme avec un code de succès
}
