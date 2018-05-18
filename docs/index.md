
# Projet de fin d'année 1ère SSI - Minuteur
 
Ce Minuteur consiste en notre projet de fin d'année de 1ère SSI, il sera codé à l'aide d'une carte Arduino.
Il s'agira d'un minuteur 2 digits réglable par 4 boutons poussoirs.
Notre groupe est constitué de _Eyad Abdellatif, Colin Chouraki, Arthur Dauge et Marion Barthe_.

## Matériel à disposition

* 1 carte Arduino M0 Pro + 1 plaque d'essais
* 1 boîte de composants pour le prototypage (Boîte incolore)
* 1 kit de démarrage Grove (Boîte verte) 
* 1 afficheur 4 digits Grove

## Cahier des charges

* La conception du système doit être réalisée sous forme d'une __machine à
états finis__ cadencée à 10 Hz.
* L'utilisateur doit être en mesure de régler le nombre de minutes et de secondes:
    - Il appuie d'abord sur un bouton __réglage__:
        * Cela fait clignoter l'afficheur (avec la valeur __00:00__) toutes les 0.5 
        secondes.
    - Il appuie ensuite soit sur un bouton __gauche__ ou un bouton __droite__
    pour incrémenter/decrémenter la valeur affichée du 1er digit:
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


#### Header 4

*   This is an unordered list following a header.
*   This is an unordered list following a header.
*   This is an unordered list following a header.

##### Header 5

1.  This is an ordered list following a header.
2.  This is an ordered list following a header.
3.  This is an ordered list following a header.

###### Header 6

| head1        | head two          | three |
|:-------------|:------------------|:------|
| ok           | good swedish fish | nice  |
| out of stock | good and plenty   | nice  |
| ok           | good `oreos`      | hmm   |
| ok           | good `zoute` drop | yumm  |

### There's a horizontal rule below this.

* * *

### Here is an unordered list:

*   Item foo
*   Item bar
*   Item baz
*   Item zip

### And an ordered list:

1.  Item one
1.  Item two
1.  Item three
1.  Item four

### And a nested list:

- level 1 item
  - level 2 item
  - level 2 item
    - level 3 item
    - level 3 item
- level 1 item
  - level 2 item
  - level 2 item
  - level 2 item
- level 1 item
  - level 2 item
  - level 2 item
- level 1 item

### Small image

![Octocat](https://assets-cdn.github.com/images/icons/emoji/octocat.png)

### Large image

![Branching](https://guides.github.com/activities/hello-world/branching.png)


### Definition lists can be used with HTML syntax.

<dl>
<dt>Name</dt>
<dd>Godzilla</dd>
<dt>Born</dt>
<dd>1952</dd>
<dt>Birthplace</dt>
<dd>Japan</dd>
<dt>Color</dt>
<dd>Green</dd>
</dl>

```
Long, single-line code blocks should not wrap. They should horizontally scroll if they are too long. This line should be long enough to demonstrate this.
```

```
The final element.
```
