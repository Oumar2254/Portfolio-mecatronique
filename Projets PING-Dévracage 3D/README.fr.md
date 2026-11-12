# Conception d'une pince adaptative à deux doigts pour le dévracage robotisé

**Conception mécanique · SolidWorks · Impression 3D · Robotique industrielle · Mécatronique**

[English](./README.md) | [Français](./README.fr.md)

## Présentation du projet

Ce travail a été réalisé en **dernière année de formation d'ingénieur à l'ESIGELEC** (2025–2026), dans le cadre du **PING 62 — Un dévracage 3D intelligent pour robots collaboratifs**, un projet académique collectif.

Le projet global portait sur la détection et la saisie automatisées d'objets à l'aide d'un bras Universal Robots et d'un système de perception mobilisant notamment Python et ROS 2. **Ma contribution personnelle concernait la conception mécanique d'une pince adaptative à deux doigts**, et non le développement des logiciels de vision ou de commande du robot.

La solution proposée visait à prendre en compte des objets de géométries variées et à permettre un contact souple. Elle a abouti à un modèle SolidWorks, une mise en plan, un rapport de justification technique et un **prototype mécanique imprimé en 3D**. Le prototype **n'a pas été soumis à des essais de préhension**.

## Mes contributions personnelles

J'ai personnellement réalisé :

- L'analyse du besoin de préhension pour des objets de formes variées, notamment coniques et creuses.
- La comparaison de solutions : pinces parallèles, pinces adaptatives à deux doigts, pinces à trois doigts et ventouses.
- Le choix et la justification d'un concept de pince adaptative à deux doigts.
- La conception et la modélisation 3D du mécanisme sous SolidWorks.
- La préparation de vues d'assemblage et d'une mise en plan cotée.
- La rédaction du rapport de justification du choix du préhenseur.

Le système de dévracage dans son ensemble relevait du **travail collectif**. Les modèles de vision, la détection des objets, la planification des prises et les logiciels robotiques décrits dans le rapport global ne sont pas présentés comme mes contributions individuelles.

## Démarche de conception

### 1. Analyse du besoin et choix du concept

L'objectif de l'étude était d'envisager **une préhension souple** d'objets de formes différentes, dans un contexte de dévracage. Les solutions comparées étaient :

| Solution | Principaux compromis étudiés |
| --- | --- |
| Pince parallèle à deux mors | Simplicité et répétabilité, mais adaptation plus limitée aux géométries irrégulières |
| Pince adaptative à deux doigts | Potentiel d'adaptation grâce à la compliance mécanique |
| Pince à trois doigts | Multiplication des contacts, avec davantage de complexité et d'encombrement |
| Préhension par ventouse | Adaptée à certaines surfaces, mais dépendante de la zone accessible et de l'étanchéité |

Une pince adaptative à deux doigts a été retenue comme piste de conception. **Les avantages envisagés sont des objectifs de conception, non des performances validées expérimentalement.**

### 2. Concept mécanique proposé

Le mécanisme envisagé comporte deux doigts articulés, des segments reliés par des liaisons mécaniques et un concept de compliance reposant sur un ressort. Le rapport évoque aussi une motorisation par servomoteurs, sans que le prototype ait été réalisé comme un ensemble motorisé et piloté électroniquement.

Les efforts de préhension, la raideur du ressort et le comportement final du mécanisme n'ont **pas été dimensionnés ou validés expérimentalement**. Le terme *adaptatif* désigne ici le concept visé, et non une pince opérationnelle validée.

### 3. Modélisation SolidWorks

*La vue CAO SolidWorks sera affichée ici après l'ajout de l'image au dépôt.*

J'ai modélisé sous SolidWorks les doigts, articulations, biellettes et supports du mécanisme. Le travail CAO comprenait également l'agencement du mécanisme à ressort proposé ainsi qu'une mise en plan d'assemblage avec plusieurs vues, coupes et cotations.

### 4. Prototype imprimé en 3D

Un prototype mécanique du concept a été fabriqué par **impression 3D**. Il permettait de matérialiser le modèle CAO, mais ne constituait pas une validation fonctionnelle de la pince. Aucun essai de saisie ni aucune intégration complète de la motorisation et de l'électronique de commande n'ont été réalisés.

## Résultats et limites

**Éléments obtenus :**

- Choix argumenté d'un concept mécanique et rédaction de sa justification.
- Modèle 3D SolidWorks et mise en plan d'assemblage.
- Prototype mécanique imprimé en 3D.

**Éléments non finalisés ou non validés :**

- Calcul des efforts de préhension et dimensionnement de la raideur du ressort.
- Choix définitif des matériaux et vérification mécanique.
- Intégration des actionneurs et de l'électronique.
- Essais de préhension sur des objets de géométries différentes.

Ce projet constitue donc **une étude de conception et de prototypage mécanique**, et non un préhenseur robotique fonctionnel et validé.

## Documents techniques

- [Rapport de justification du choix du gripper](./Doc%20r%C3%A9capitulatif_justification%20choix%20Gripper%20adaptatif%20deux%20doigts.pdf) — déjà présent dans le dépôt.

Le document technique global PING 62 est utilisé uniquement pour présenter le contexte du travail collectif ; il n'est pas publié ici comme une réalisation personnelle.

## Compétences mises en pratique

Analyse et sélection de concepts mécaniques · Modélisation 3D SolidWorks · Mise en plan d'assemblage · Justification technique · Prototypage par impression 3D · Collaboration dans un projet robotique pluridisciplinaire

---

**ESIGELEC — Projet académique collectif de dernière année (2025–2026)**  
**Contribution personnelle : étude du préhenseur, modélisation SolidWorks et rapport de justification.**