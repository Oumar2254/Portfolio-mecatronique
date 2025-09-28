L'objectif de ce programme est de créer une classe, destinée à produire des objets
 conteneurs, des dictionnaires ordonnés.
 L'idée, assez simplement, est de stocker nos données dans deux listes :
 la première contenant nos clés;
 la seconde contenant les valeurs correspondantes.
 L'ordre d'ajout sera ainsi important, on pourra trier et inverser ce type de dictionnaire.
  Voici la liste des mécanismes que notre classe devra mettre en oeuvre.
 1. On doit pouvoir créer le dictionnaire de plusieurs façons :
 Vide : on appelle le constructeur sans lui passer aucun paramètre et le diction
naire créé est donc vide.
 Copié depuis un dictionnaire : on passe en paramètre du constructeur un dictionnaire que l'on copie par la suite dans notre objet. On peut ainsi écrire
 constructeur(dictionnaire) et les clés et valeurs contenues dans le dictionnaire sont copiées dans l'objet construit.
 Pré-rempli grâce à des clés et valeurs passées en paramètre : comme les dictionnaires usuels, on doit ici avoir la possibilité de pré-remplir notre objet avec
 des couples clés-valeurs passés en paramètre (constructeur(cle1 = valeur1,
 cle2 = valeur2, ...)).
 2. Les clés et valeurs doivent être couplées. Autrement dit, si on cherche à suppri
mer une clé, la valeur correspondante doit également être supprimée. Les clés et
 valeurs se trouvant dans des listes de même taille, il suffira de prendre l'indice
 dans une liste pour savoir quel objet lui correspond dans l'autre. Par exemple, la
 clé d'indice 0 est couplée avec la valeur d'indice 0.
 3. On doit pouvoir interagir avec notre objet conteneur grâce aux crochets, pour
 récupérer une valeur (objet[cle]), pour la modifier (objet[cle] = valeur) ou
 pour la supprimer (del objet[cle]).
