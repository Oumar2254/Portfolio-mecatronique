import os
import re
import pickle

from donnees import *

#----------fonctions du programme
def recup_nom_joueur () :
      """Fonction chargée de récupérer le nom de l'utilisateur.
             chiffres et lettres exclusivement.Si ce nom n'est pas valide, on appelle récursivement la fonction
pour en obtenir un nouveau"""

      nom_joueur = input("Entrez votre nom: ")
# On met la première lettre en majuscule et les autres en minuscules
      nom_joueur = nom_joueur.capitalize()
      if not nom_joueur.isalnum() :
           print("Ce nom est invalide.")
           return recup_nom_joueur()
      else :
           return nom_joueur
           
#-----------------
def recup_scores():
        """Cette fonction récupère les scores enregistrés si le
            fichier existe.
            Dans tous les cas, on renvoie un dictionnaire,
            soit l'objet dépicklé,
            soit un dictionnaire vide.
 
         On s'appuie sur nom_fichier_scores défini dans donnees.py""" 
        if os.path.exists(nom_fichier_scores) : #Le fichier existe
            #On le récupère
            fichier_scores = open(nom_fichier_scores, "rb")
            mon_depickler = pickle.Unpickler(fichier_scores)
            scores = mon_depickler.load()
            fichier_scores.close()
        else : #Le fichier n'existe pas
            scores = {}
        return scores
#-----------------------
def enregistrer_scores (scores) :
      """Cette fonction se charge d'enregistrer les scores dans
        le fichier
        nom_fichier_scores. Elle reçoit en paramètre le
        dictionnaire des scores
        à enregistrer""" 
      fichier_scores=open(nom_fichier_scores,"wb") #On écrase les anciens scores
      mon_pickler = pickle.Pickler(fichier_scores)
      mon_pickler.dump(scores)
      fichier_scores.close()

#---------------------------
def contient_lettres(texte) :
     return bool(re.search(r'[a-zA-ZéèêëàâäùûüçôöÉÈÊËÀÂÄÙÛÜÇÔÖ]', texte))