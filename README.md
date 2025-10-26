# C_project
Made for ESIEA C project

compilation :

Depuis le dossier "src" : gcc -Wall -g passfinder.c -o passfinder

note: le Makefile est présent dans le dossier src.

Utilisation du programme :

passfinder Path-to-wordlist/wordlist.txt sha256digest

exemple:

./passfinder password.txt 9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08

Output :

loaded 1000000 words into table.
	... with 355233 collisions
Found !! Password is --->  test

Etapes réalisées dans le projet :

1- Choix de l'approche <hashtables> vs <binary tries> :
    Après de nombreuses recherches, il semblerait que la rapidité de recherche dans une <hashtable> s'avère généralement meilleure.
    L'arbre binaire de recherche (binary trie) s'avère généralement plus stable, offrant un comportement moins "aggressif" pours les insertions et les requêtes, expliquant une vitesse d'exécution plus faible au profit de la stabilité.
    Le parcours de recherche à travers les noeuds d'un arbre de recherche est généralement plus stable au détriment de la rapidité de recherche comparé à la vitesse de recherche dans une table de hachage.
  
    Idéalement, une table de hachage permets une requête de recherche "constante", permettant qu'une recherche soit réalisée dans le même temps indifférement du nombre d'éléments contenu.

2 - Prise en main et compréhension des <hash-tables> :
    Afin de réaliser le projet en réalisant une table de hachage, j'ai du réaliser différentes recherches et me renseigner sur le fonctionnement des tables de hachages afin d'en comprendre le fonctionnement et de le mettre en pratique.
    Dans ce contexte, j'ai réalisé de nombreux tests avec différents codes.

3 - Fonctionnement et Fonctions algorithmiques des <hash-tables> : 
    Afin d'indexer les éléments dans la "table", une <hash-table> prend une entrée et lui attribue le numéro d'index (int) obtenu en passant l'entrée à travers un algorithme (fonction) de hachage définit.
    Plus le nombre d'entrées est important, plus le nombre de collisions (Même numéro d'index de deux éléments, survenant lorsque deux éléments ont obtenu le même résultat en "résultat" ("digest") de hachage.) est important.

    Plus le nombre de collision est élevé lors de l'insertion d'une entrée dans la table, plus les performances d'une table de hachage se dégrade. La rapidité de chargement en mémoire d'une table de hachage est intrinsèquement liée au nombre de collisions. Moins il se produit de collision lors des insertions, plus la table de hachage est considérée performante.
    L'emploi d'un algorithme de hachage considéré "plus robuste" et/ou "plus complexe" permet de réduire le nombre de collisions. Néanmoins, plus une fonction de hachage est complexe, plus il faudra de temps et de mémoire pour le calcul de numéro d'index de chaque entrée. Afin d'optimiser les performances il est donc nécessaire de trouver un équilibre entre le nombre de collisions et la vitesse d'éxécution de l'algorithme de hachage.

    Dans ce contexte il est généralement préférable d'utilisé un algorithme de hachage non cryptographique.
    https://en.wikipedia.org/wiki/List_of_hash_functions#Non-cryptographic_hash_functions

4 - Fonctionnement du programme :

    Ce programme utilise la fonction de hachage "Fowler–Noll–Vo hash" (FNV Hash) en version 1a. Différents tests ont été réalisés avec d'autres fonctions de hachages connues (FNV1, MurmurHash, Jenkins hash function..) ou une fonction de hachage rudimentaire (entrée += entrée[i]) et des wordlists de différentes tailles.
    La fonction FNV-1a s'est révélée être le meilleur compromis entre nombre de collisions et vitesse d'éxécution lors des différents tests.

    L'implémentation du SHA256 permet de générer lors de chaque entrée le "digest"(en SHA256) résultant de l'entrée. Chaque entrée est ensuite stockée sous la forme ".key=digest(sha256), .obj=entrée". Dans le cadre de l'utilisation de dictionnaires de mots de passes c'est donc : '.key=hash(sha256), .obj=motdepasse'. Le numéro d'index est définit par le digest(FNV-1a) de l'entrée (donc ici, du mot de passe du dictionnaire).

    Ceci permet donc de retrouver rapidement le mot de passe associé à son "digest"(sha256).

5 - Axes d'améliorations :

    Pour le moment, seul la fonction "SHA256" est implémentée. D'autres fonctionnalités de hachages doivent être implémentés afin de permettre la recherche des "digest" de différentes fonctions de hachages et d'en trouver les correspondances. Idéalement, cette implémentation devra se faire de paire avec l'ajout de fonctionnalités permettant de passer en argument de commande le choix de la fonction de hashage (exemple : | passfinder wordlist.txt sha256 9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08 | ou alors | passfinder wordlist.txt fdfedc01c66e9ea2817508ca1097df2f | qui permettrait tous deux d'obtenir "Rocket".).

autre : 
/*TODO : get a working implementation of different cryptographic hash functions (md5, sha1, sha512...) if possible.
Work on the reverse lookup function (yet producing weird behaviors).

work on a well-rounded binary trie version of the project to compare performances.*/
  
