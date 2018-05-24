
# Projet de fin d'année 1ère SSI - Minuteur
 
## Introduction
Ce Minuteur consiste en notre projet de fin d'année de 1ère SSI, il sera codé à l'aide d'une carte Arduino.
Il s'agira d'un minuteur 2 digits réglable par 4 boutons poussoirs.
Notre groupe est constitué de Eyad Abdellatif, Colin Chouraki, Arthur Dauge et Marion Barthe.

### Matériel à disposition

* 1 carte Arduino M0 Pro + 1 plaque d'essais
* 1 boîte de composants pour le prototypage (Boîte incolore)
* 1 kit de démarrage Grove (Boîte verte) 
* 1 afficheur 4 digits Grove

### Cahier des charges

* Le système doit être conçu sous forme d'une __machine à
états finis__ cadencée à 10 Hz.
* L'utilisateur doit pouvoir de régler le nombre de minutes et de secondes:
    - Il appuie d'abord sur un bouton __réglage__:
        * Cela fait clignoter l'afficheur (avec la valeur __00:00__) toutes les 0.5 
        secondes.
    - Il doit ensuite incrémenter/decrémenter la valeur affichée du 1er digit  en appuyant surun bouton __gauche__ ou un bouton __droite__  :
        * Si la valeur affiche __00:59__ et que l'utilisateur souhaite incrémenter,
        on doit avoir __01:00__
    - Une fois la valeur choisie, il réappuie sur le bouton __réglage__:
        * Cela arrête le clignotement et fixe la dernière valeur affichée
    - Il appuie sur le bouton __démarrer__ pour démarrer le minuteur:  
        * Toutes les secondes, le 1er digit doit décrémenter (affichage des secondes
        qui passent).
        * Arrivé à __02:00__, par exemple, l'afficheur doit ensuite passer à __01:59__ 
        * Une fois arrivé à __00:00__, l'afficheur doit afficher __00:00__ en
        clignotant toutes les 0.5 secondes.
    - Il réappuie sur le bouton __démarrer__ pour stopper le minuteur
        * La valeur __00:00__ ne doit plus clignoter.
        
### Bête à corne

<p align="center">
  <img src="https://raw.githubusercontent.com/lycee-chaptal-sii/colin-marion-arthur-eyad/partie_communiquer/docs/bete%20a%20cornes.png?token=AiA3lZkPbn1K810Jq1GOGkG212CZM7cLks5bDqlDwA%3D%3D">
</p>

### Cahier des Charges

| Fonctions de Service                                       | Critères                                                          | Niveaux                                                                                                          | Flexibilité |
|:-----------------------------------------------------------|:------------------------------------------------------------------|:----------------------------------------------------------------------------------------------------------------------|:------------|
| FP1 : Permettre à l'utilisateur de mesurer un temps donné  | Machine à états finis                                             | Cadencée à 10 Hz                                                                                                 | F0          |
| FC1 : Pouvoir programmer le décompte de temps voulu        | Décrementation/Incrémentation + Sélection/Démarrer/Arrêter        | Boutons différents sauf pour Démarrer/Arrêter                                                                    | F0          |
| FC2 : Doit être alimenté                                   | Alimentation électrique                                           | 3,3 V                                                                                                                  | F0          |
| FC3 : Doit être facile d'utilisation                       | Boutons et afficheur                                              | 4 boutons Grove + afficheur 4 digits Grove                                                                         | F0          |
| FC4 : Comprendre le fonctionnement facilement              | Clignotement pour montrer l'activité                              | Clignotement de 0,5s quand 00:00 affiché                                                                         | F0          |

## Hardware

### Liste des composants

* 1 carte Arduino M0 Pro + 1 plaque d'essais
* 1 afficheur 4 digits Grove
* 4 boutons poussoirs
* 19 câbles de connexion
* 1 buzzer
* 2 led
* 2 résistances

### Schéma branchements Arduino

![Branchements Arduino](https://raw.githubusercontent.com/lycee-chaptal-sii/colin-marion-arthur-eyad/partie_communiquer/docs/schema.PNG?token=AiA3lWYiOy_aTa6bGpuvonCLa11UA_HNks5bDqd5wA%3D%3D)

## Software

### Diagramme d'états/transitions

![Diagramme d'états/transition](https://raw.githubusercontent.com/lycee-chaptal-sii/colin-marion-arthur-eyad/partie_communiquer/docs/diagramme%20etat.png?token=AiA3ldJzqxOyils5FIHxld--T9wRnzztks5bDqf1wA%3D%3D)
