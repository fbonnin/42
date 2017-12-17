<h1>Travaux de Florent Bonnin à l'école 42 depuis avril 2017.</h1>

Actuellement tous les travaux sont en langage C.

<h3>libft</h3>
Bibliothèque de fonctions variées réutilisables dans plusieurs projets. On y trouve une imitation de la fonction printf. La Libft est enrichie tout au long du cursus à 42.


<h2>Projets d'Algorithmique</h2>

<h3>push_swap</h3>
Trier des nombres avec deux piles et un jeu d'instructions limité. Différents algorithmes de tri sont implémentés, dont le tri fusion. Leurs performances sont évaluées à la correction.

<h3>lem-in</h3>
Trouver la manière la plus rapide de déplacer N véhicules dans un graphe depuis un noeud de départ jusqu'à un noeud d'arrivée, en prenant en compte les éventuels embouteillages. Pour chaque véhicule, on effectue un parcours en largeur (Dijkstra) pour trouver le plus court chemin, en prenant en compte les retards provoqués par le passage des véhicules précédents. Par exemple, si un chemin est très fréquenté, il ne constitue plus un bon itinéraire.

<h3>fillit</h3>
2 contributeurs<br>
Problème d'optimisation. Agencer des pièces de formes variables pour former un carré de taille minimale. Un algorithme de backtracking (retour sur trace) est utilisé. S'il est impossible de former un carré de taille N, on tente de former un carré de taille N + 1, et ainsi de suite.

<h3>corewar</h3>
3 contributeurs<br>
Corewar est un jeu dans lequel des programmes s'affrontent dans une arène virtuelle. L'arène est une mémoire circulaire dans laquelle sont placées les instructions des différents programmes. Les programmes sont exécutés en parallèle dans le même espace mémoire. Ils ont donc la possibilité de s'écrire les uns sur les autres, donnant ansi au jeu une grande  complexité. Le projet consiste à coder d'une part une machine virtuelle capable d'exécuter les programmes, et d'autre part un programme assembleur capable de compiler un code écrit dans un langage type assembleur en bytecode compréhensible par la machine virtuelle.


<h2>Projets d'environnement Unix</h2>

<h3>ls</h3>
Imitation de la commande unix ls. Parcours récursif d'un répertoire et de ses sous-répertoires. Ce projet permet de comprendre en détail le système de fichiers et sa manipulation avec des fonctions standards.


<h2>Projets de Graphisme</h2>

Les projets de graphisme sont réalisés avec une bibliothèque graphique bas niveau fournie par l'école : la miniLibX. Ils ne peuvent être compilés qu'à l'école.

<h3>fdf</h3>
Rendu 3D d'un terrain en relief en représentation fil de fer (points reliés par des segments). Réalisation d'une perspective parallèle.

<h3>fractol</h3>
Logiciel d'exploration de fractales (Mandelbrot, Julia, Burning Ship) avec possibilité de se déplacer dans plan et de zoomer/dézoomer. Gestion des évènements clavier et souris.


<h2>Infos complémentaires</h2>

1. Si le nombre de contributeurs n'est pas specifié, c'est qu'il s'agit d'un projet solo.

2. Chaque projet a un sujet au format pdf.

3. A 42, il est généralement interdit d'utiliser des fonctions que l'on n'a pas codées soit-même. L'utilisation de la bibliothèque standard n'est pas permise.
