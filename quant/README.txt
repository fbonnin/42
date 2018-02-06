Le projet a été développé sous linux.

Pour compiler, utiliser la commande "make".

Pour lancer le programme, utiliser la commande "./scraping".

Cela lance le téléchargement et le parsing des données, de 2017 à aujourd'hui.

Les données extraites sont placées dans la base de données "database.csv".

Les pdf sont placés dans le dossier "pdf" et nommés "0.pdf", "1.pdf", "2.pdf", ...

Au total, 5460 pdf seront téléchargés.

Le téléchargement peut durer plusieurs heures.

Si vous ne souhaitez pas attendre, vous pouvez trouver le résultat dans le fichier result.csv.

Le projet comporte 3 parties : download, parsing, tools

Le fichier scraping.h indique où se trouve le code de chaque fonction.
