# Coupe de France de Robotique 2025 — Développement logiciel des PAMIs

**Robotique embarquée · ESP32-C3 · C++ / Arduino · Machines d'états · Intégration logicielle**

## Contexte du projet

Dans le cadre de la participation de notre équipe ESIGELEC à la Coupe de France de Robotique 2025, un robot principal était accompagné de petits robots auxiliaires appelés **PAMIs**. Ces derniers étaient facultatifs et permettaient de réaliser des actions pour gagner des points supplémentaires.

L'équipe disposait de **trois PAMIs**, chacun positionné différemment sur la table de jeu. Mon travail concernait principalement **leur logiciel embarqué**, et non le développement du robot principal ou la conception matérielle des PAMIs.

J'ai développé l'essentiel d'une **structure logicielle commune**, ensuite adaptée aux séquences attendues de chacun des trois PAMIs. Les trois robots étaient équipés de servomoteurs.

## Mes contributions

J'ai écrit la majeure partie du firmware C++ / Arduino des PAMIs, notamment :

- La **machine d'états** organisant les phases de fonctionnement : attente, déplacement, pivot, actionnement et arrêt.
- La logique de **commande PWM des moteurs** et de transition entre les phases de déplacement.
- L'utilisation du **comptage des impulsions d'encodeurs**, via interruptions, pour déclencher les changements d'état.
- La gestion du **démarrage par tirette**.
- Le pilotage des **servomoteurs** et la prise en compte de la couleur de l'équipe.
- L'**adaptation des séquences** selon la position de chaque PAMI sur la table.
- Les essais et ajustements logiciels réalisés sur les robots physiques.

**Travail d'équipe :** la partie relative aux **capteurs de distance ToF** comprend une contribution d'un coéquipier. Je ne revendique pas la conception ou l'assemblage du matériel ; j'ai seulement participé à quelques manipulations matérielles au début du projet.

## Environnement technique

| Élément | Technologie / composant |
| --- | --- |
| Microcontrôleur | ESP32-C3 |
| Langage et framework | C++ / Arduino |
| Environnement de développement utilisé | PlatformIO |
| Capteurs de distance | 3 × VL6180X (ToF) |
| Suivi des déplacements | Encodeurs des deux moteurs |
| Actionneurs | Deux moteurs et un servomoteur par PAMI |
| Communication capteurs | I²C |
| Bibliothèques présentes dans le code | `Wire`, `Adafruit_VL6180X`, `ESP32Servo`, `FastLED` |

## Fonctionnement du firmware

### 1. Initialisation

La fonction `setup()` configure notamment la communication série, le bus I²C, les capteurs ToF, les sorties de commande moteur, les entrées des encodeurs et leurs interruptions, le servomoteur et la LED.

### 2. Machine d'états

Le fonctionnement suit une séquence d'états définie dans `main.cpp` :

| État | Fonction prévue |
| --- | --- |
| `INITIALISATION` | Attente du démarrage et remise à zéro des compteurs |
| `ETAT_1` | Première séquence de déplacement |
| `ETAT_2` | Pivot |
| `ETAT_3` | Deuxième séquence de déplacement |
| `ETAT_SERVOS` | Actionnement du servomoteur |
| `ARRET` | Commande d'arrêt |

Certaines transitions reposent sur l'atteinte de **seuils d'impulsions des encodeurs**. La couleur de l'équipe intervient également dans le choix de certaines commandes moteur.

Cette structure a servi de base aux adaptations logicielles des trois PAMIs. Le dépôt contient **un seul fichier source représentatif**, et non les trois variantes individualisées.

### 3. Déplacements et choix de commande

Dans la version finale, les moteurs sont pilotés par des **consignes PWM fixes** ; les impulsions des encodeurs servent à suivre la progression des séquences et à déterminer certains changements d'état.

Une régulation en boucle fermée de type **PID** avait été essayée pendant le développement. Son comportement n'étant pas suffisamment satisfaisant lors des essais, j'ai choisi de **ne pas la conserver** dans la version utilisée pour la compétition.

Il ne s'agit donc pas d'un asservissement PID actif dans le code publié. Cette décision illustre un ajustement de la stratégie de commande à partir des observations faites sur le système réel, sans prétendre démontrer une meilleure précision par des mesures comparatives.

### 4. Obstacles, démarrage et actionnement

Le code intègre la lecture des capteurs ToF, avec comparaison des distances à un seuil et application d'une commande d'arrêt lorsqu'un obstacle est détecté durant certaines phases.

Il gère également le démarrage par tirette, la sélection de la couleur de l'équipe, la LED d'état et une séquence de mouvement du servomoteur.

## Essais et validation

Le firmware a été utilisé comme base logicielle sur **trois PAMIs physiques**, avec des adaptations propres à leur position sur la table de jeu. Les principales fonctions ont été testées sur les robots réels : commandes moteur, séquences de déplacement, prise en compte des encodeurs, détection d'obstacles et actionnement.

Les essais ont également conduit à des ajustements logiciels, dont l'abandon de la régulation PID initialement expérimentée.

**Limites des éléments publiés :** ce dépôt ne présente pas de protocole de validation détaillé, de résultats quantitatifs de précision des déplacements ni de résultats individuels des PAMIs sur le terrain de compétition. Aucune vidéo n'est utilisée ici comme preuve de navigation autonome.

## Code source et reproductibilité

- [`main.cpp`](./main.cpp) : version finale du firmware représentatif de la structure utilisée pendant la compétition.

Le code est conservé comme **archive technique du projet**. Le dépôt ne contient pas à ce jour le fichier de configuration PlatformIO complet, le schéma de câblage ni les adaptations propres aux trois PAMIs. Une compilation et une reproduction autonomes du système ne sont donc pas garanties à partir de ce seul dossier.

## Compétences mises en pratique

- Programmation embarquée en C++ / Arduino.
- Conception d'une logique de contrôle par machine d'états.
- Gestion d'interruptions et exploitation des encodeurs.
- Commande des moteurs et des servomoteurs.
- Intégration logicielle de périphériques sur microcontrôleur.
- Adaptation d'une base logicielle à plusieurs robots.
- Essais et mise au point sur systèmes physiques, dans un projet collectif.

---

**Projet collectif — ESIGELEC, Coupe de France de Robotique 2025.**  
**Contribution personnelle principale : développement et adaptation du logiciel embarqué des trois PAMIs.**
