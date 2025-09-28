from random import randrange
from donnees import *
from fonctions import *

#Nom du fichier stockant les scores
nom_fichier_scores = "scores"
#------------------------
scores=recup_scores()
#On récupère un nom d'utilisateur

utilisateur= recup_nom_joueur()

#Si l'utilisateur n'a pas encore de score, on l'ajoute
if utilisateur not in scores.keys() :
     scores[utilisateur] = 0


continuer=True
while continuer :
    
    indice= randrange(len(Liste_des_mots))
    chaine_mot = Liste_des_mots[indice].lower() #Mot à trouver
    liste_1 = ["*"] * len(chaine_mot)
    print("\nMot à deviner :", chaine_liste_1)
    
    nb_chances=nb_coups

    while nb_chances > 0 and (chaine_mot.capitalize()!= "".join(liste_1)) :
              
        aleg=-1
        while aleg < 0 or len(lettre_entree) !=1 :
            lettre_entree = input("Veuillez entrer une lettre : ")

            try :
                lettre_entree=str(lettre_entree)
            except ValueError :
                print("Vous n'avez pas saisi une valeur correcte.")
                continue

            if not contient_lettres(lettre_entree) or len(lettre_entree) != 1:
                   print("Veuillez entrer une seule lettre alphabétique.")
            else :
                 aleg = 1

        for k in range (len(liste_1)):
             
            if lettre_entree == liste_1[k].lower() :
                  print("Cette lettre a déjà été saisie. Une nouvelle doit être saisie.")

        if lettre_entree in chaine_mot :
             
                  
             for j in range(len(chaine_mot)):
                
                if (chaine_mot[j] == lettre_entree) and (liste_1[j]=="*") :
                        if j== 0 :
                            liste_1[j] = lettre_entree.upper()
                        else :
                             liste_1[j]=lettre_entree
                        print("Bravo ! Bonne lettre :", "".join(liste_1))
                
                     
        else :
             nb_chances-=1
             print("Lettre absente : ", "".join(liste_1))
                      
                        
        #i+=1
            
    if chaine_mot.capitalize() == "".join(liste_1) : #on s'assure de mettre la première lettre de chaine_mot en majucule avant toute comparaison
             
             print("Félicitations ! Vous avez trouvé le bon mot : {}".format(chaine_mot.capitalize()))
             
    else : 
         print("PENDU ! Vous avez perdu.")
         print("Le bon mot est :",chaine_mot)
           
    
    scores[utilisateur] += nb_chances #Calcul du score

    reponse = input("Appuyez sur Entrée pour continuer, ou tapez 'q' pour quitter : ")
    
    if reponse.lower() == 'q':
        print("Fin du jeu.")
        continuer = False
#La partie est finie, on enregistre les scores
enregistrer_scores(scores)
#On affiche les scores de l'utilisateur
print("Vous finissez la partie avec {}".format(scores[utilisateur]))

#On met en pause le système
os.system("pause")