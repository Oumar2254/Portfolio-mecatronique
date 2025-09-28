class DictionnaireOrdonne :

    def __init__(self, base = {}, **donnees) :

        """Constructeur de notre objet."""

        self._cles = []    #liste contenant les clés du dictionnaire
        self._valeurs = [] #liste contenant les valeurs associées aux clés du dictionnaire

        #On vérifie que 'base' est un dictionnaire exploitable

        if type(base) not in (dict, DictionnaireOrdonne) :
            raise TypeError ("Le type attendu est un dictionnaire (usuel ou ordonné).")
        
        #On récupère les données de 'base'
        for cle in base :
            self[cle] = base[cle]
        #On récupère les données de 'donnees'

        for cle in donnees :
            self[cle] = donnees[cle]

    
    def __getitem__(self, cle):
        """Renvoie la valeur correspondant à la clé si elle existe,
         lève une exception KeyError sinon. """
        
        if cle not in self._cles :
            raise KeyError ("La clé {} ne se trouve pas dans le dictionnaire.".format(cle))
        else :
            indice = self._cles.index(cle)
            return self._valeurs[indice]
        
        
    def __setitem__(self, cle, valeur) :
          """Méthode spéciale appelée quand on cherche à modifier une clé présente dans le dictionnaire.
          Si la clé n'est pas présente, on l'ajoute à la fin du dictionnaire."""

          if cle not in self._cles :
            self._cles.append(cle)
            self._valeurs.append(valeur)
          else :
              indice = self._cles.index(cle)
              self._valeurs[indice] = valeur


    def __delitem__(self, cle) :
       """Méthode appelée quand on souhaite supprimer une clé."""
       if cle not in self._cles :
           raise KeyError("La clé {} n'existe pas.". format(cle))
       else :
           indice = self._cles.index(cle)
           del self._cles[indice]
           del self._valeurs[indice]


    def __repr__(self) :

        """Représentation de notre objet. C'est cette chaîne qui sera affichée lorqu'on saisit directement le dictionnaire dans l'interpréteur, ou en utilisant la fonction 'repr'.""" 
        
        chaine ="{"
        premier_passage=True
        for cle, valeur in self.items() :
            if not premier_passage :
                chaine += ", " #On ajoute la virgule comme séparateur
            else :
                premier_passage = False
            chaine += repr(cle) + " : " + repr(valeur)
        chaine += "}"
        return chaine
    
    
    def __str__(self) :
        """Fonction appelée quand on souhaite afficher le dictionnaire grâce à la fonction 'print' ou le convertir en chaîne grâce au constructeur"""

        return repr(self)
    
    
    def items(self) :
         """Renvoie un générateur contenant les couples (cle, valeur)."""

         for i, cle in enumerate(self._cles) :
             valeur = self._valeurs[i]
             yield (cle, valeur)


    def sort(self) :
        """Méthode permettant de trier le dictionnaire en fonction des clés."""
        #On trie les clés
        cles_triees = sorted(self._cles)

        #On crée une liste de valeurs, encore vide
        valeurs = []

        #On parcours ensuite la liste des clés triées
        for cle in cles_triees :
            valeur = self[cle]
            valeurs.append(valeur)
        #Enfin on met à jour notre liste de clés et de valeurs
        self._cles = cles_triees
        self._valeurs = valeurs 

    
    def __iter__(self) :
        """Méthode de parcours de l'objet. On renvoie l'itérateur de clés."""
        return iter(self)
    
             
    def __contains__(self, cle) :
        """Renvoie True si la clé est dans la liste des clés, False sinon."""
        return cle in self._cles
    
    
    def len(self) :
        "Renvoie la taille du dictionnaire."
        return len(self._cles)
    
    
    def keys (self):
        """Cette méthode renvoie la liste des clés."""
        return list(self._cles) #retourne sous forme de liste les clés du dictionnaire
    
    
    def values (self) :
        """Cette méthode renvoie la liste des valeurs."""
        return list(self._valeurs) #retourne sous forme de liste les valeurs du dictionnaire
    
    
    def __add__(self, autre_objet):
        """On renvoie un nouveau dictionnaire contenant les deux dictionnaires mis bout à bout (d'abord self puis autre_objet )."""
        
        if type(autre_objet) is not type(self) :

            raise TypeError ("Impossible de concaténer {} et {}".format(type(self), type(autre_objet)))
        else :
            nouveau =DictionnaireOrdonne()
            #On commence par copier self dans le dictionnaire 
            for cle, valeur in self.items() :
                nouveau[cle] = valeur
            #On copie ensuite autre_objet
            for cle, valeur in autre_objet.items() :
                nouveau[cle] = valeur
            return nouveau
        

    def reverse(self) :
        """Inversion du dictionnaire"""
        #On crée deux liste vides qui contiendront le nouvel ordre des clés et valeurs
        cles = []
        valeurs = []

        for cle, valeur in self.items() :
            #On ajoute les clés et valeurs au début de la liste

            cles.insert(0, cle)
            valeurs.insert(0, valeur)
        #On met ensuite à jour nos listes
        self._cles = cles
        self._valeurs = valeurs

        



    
    