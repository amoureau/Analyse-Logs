Manuel d’utilisation du programme
Notre programme permet d’analyser un fichier log consignant des requêtes faites sur 
l’intranet INSA. Il permet notamment d’en tirer des statistiques et de créer un graphe via GraphViz
pour visualiser ces requêtes.
Utilisation :
Pour utiliser le programme, il faut commencer par réaliser les étapes de compilation. Celles-ci 
sont réalisées automatiquement en écrivant dans le terminal
$make
Cela crée alors un exécutable nommé analog.
Le programme prend en paramètres le nom du fichier de log ainsi qu’une série d’options facultatives 
en ligne de commande : 
$./analog [options] nomfichier.log
Le fichier doit forcément être au format « .log » pour ne pas avoir d’erreur.
Par défaut, c’est-à-dire quand il n’y a aucune option, le programme affiche sur la console sous forme 
textuelle la liste des 10 pages (ou moins s’il y en a moins de 10) les plus consultés par ordre décroissant 
de popularité. S'il y a des ex aequo au niveau du nombre de hits, l’affichage se fait en fonction de l'ordre 
chronologique, c'est à dire l'ordre dans lequel le site est arrivé dans le log. Aucun fichier “.dot” n’est 
généré dans ce cas. 
Les options en ligne de commande sont les suivantes : 
[-g [nomfichier.dot] [-p]]
Cette option permet de produire un fichier au format GraphViz (« .dot ») du graphe analysé. Chaque 
document apparaîtra sous la forme d’un nœud et chaque arc indiquera le nombre de parcours 
associés.
Sans précision d’un nom de fichier « .dot », un fichier nommé « graphe.dot » est créé par défaut. Si 
un nom de fichier est donné juste après -g, le fichier créé aura ce nom (ici « nomfichier.dot »).
Le paramètre -p permet de créer et d’ouvrir le fichier « .png » qui correspond au graphe. Ce fichier 
aura même nom que le « .dot ».
[-e]
Cette option permet d’exclure tous les documents qui ont une extension de type image, css ou 
javascript. La liste des extensions exclues est la suivante : {"js", "css", "png", "jpg", "bmp", "gif", "ico"}.
[-t heure]
Cette option permet de ne prendre en compte que les hits qui sont dans le créneau horaire 
correspondant à l’intervalle [heure, heure+1[.
On peut cumuler ces options et écrire :
$./analog [-g [nomfichier.dot] [-p]] [-e] [-t heure] nomfichier.log
Théo Clouscard – Alexandre Moureau B3206
Florian Le Vasseur – Eugénie Palisser – Lina Mahjoub B3212
