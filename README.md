Ultimate-Magic
==============

Mon premier RPG, je vise quelque chose d'assez bien codé (model MVC) qui à long terme sera un RPG orienté magie, gestion du mana sans trop d'évolution du personnage en conservant les skills.

======= GAMEPLAY ========
  * Les sorts
  Lancer un sort consiste à charger une barre de magie. Chaque pourcentage peut être un élément différent, offrant 
  la possibilité de combiner des parties d'éléments (50% feu, 10%eau, 3%divin etc)
  Chaque élément est stocké dans une barre de mana élément (une barre pour le feu, une autre pour l'eau) et celles-ci ne se rechargent
  qu'en présence d'un élément du décor qui sert de puit.
  * Le corps à corps 
  AUCUN, mais possibilité d'invoquer par magie des armes, armures etc.
  * Evolution du personnage
  L'utilisation d'un type de sort croît la puissance de ce sort tel que:
    Quelqu'un qui utilise le feu a des fin de destruction deviendra plus fort en puissance magique, tandis que le buffer
    healer grandira en soins magiques etc. La croissance doit se faire par exécution critique* et efficace sur un ennemi; les
    sorts dans le vide n'auront ainsi pas (ou peu) de conséquence sur l'évolution du personnage.
  * L'histoire ?
  A déterminer, je prône un accès très rapide mais progressif à chaque élément. J'envisage un système principalement de 
  stage avec seulement certains puits contre certains ennemis; tandis qu'entre chaque stage le joueur a la possibilité
  d'aller s'entrainer dans un open-world plus large et plus simple. Ainsi l'histoire est fluide et difficile et dépend
  du farm et de l'expérience du joueur.
  * STUFF
  Je pense un système de drop avec quantité d'objet permettant la spécialisation de telle ou telle branche. Ainsi 
  on pourrait droper un baton de feu, favorisant la destruction, serti d'une pierre de déflégration etc..
  Le loot dépendra effectivement des ennemis tués, j'aimerais un open-world avec de trèèèèès nombreux boss, des 
  challenges.
  * Généralités
  Je veux qu'absolument TOUT dans le jeu (sauf le moteur) dépende d'un facteur chance positif; si le joueur est compétent il
  s'en sortira toujours, mais il aura sur les drop, sur le nombre d'ennemi, le niveau etc, je veux que tout soit sur
  un fond aléatoire !
  
======== VERSIONNAGE =====
* Version 0
  | Un moteur compétent dans le déplacement du open-world, un ennemi tuable, un joueur controlé. Un élément de magie sans charge
  |et un loot.
* Version 0.1
  | Incorporation de la barre de charge de sort et d'un second élément.
* Version 0.2
  | Implémentation d'un équipement
* Version 0.3
  | Implémentation de tous les éléments. 
  | Implémentation d'effets (buff & debuff)
* Version 0.4
  | Ajustement des différents éléments et leur rôles.
  | Implémentation de nouveaux ennemis toujours statiques.
* Version 0.5
  | Implémentation d'une IA à peine plus intelligente que ma petite soeur.
* Version ....
  | 
  | 
  | 
  | 
* Version 1
  | Un stage, un monde, un équippement varié, des ennemis variés, de la magie concentrable et des dialogues.
  | 
  | 
  | 
