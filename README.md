# OutOfReach

**OutOfReach** est un mini-jeu développé en **C/C++ avec raylib** servant de support à un petit **challenge de reverse engineering**.  
Le joueur évolue dans une scène simple, avec une plateforme hors d’atteinte contenant un texte.  
Objectif : modifier en mémoire une variable du joueur, par exemple `player.speed` pour atteindre cette zone impossible à atteindre légalement.

## Concept du challenge

- Le jeu démarre avec un joueur trop lent pour accéder à la plateforme en hauteur.
- Un texte (ou autre récompense) est affiché tout en haut.
- Un exploit externe permet de :
  - récupérer le PID du jeu,
  - trouver la base ELF et l’offset de la structure `Player`,
  - localiser `player.speed`,
  - modifier la vitesse directement dans la RAM.
- Une fois la vitesse changée, le joueur peut atteindre la zone "Out Of Reach".

## ▶️ Compilation

### Jeu vulnérable :

```bash
cd vulnerable
make
```

### Exploit :

```bash
cd exploit
make
```

## Exécution

Dans un terminal, lance le jeu :

```bash
./vulnerable
```

Dans un autre terminal :

```bash
sudo ./exploit $(ps aux | grep '[v]ulnerable' | awk 'NR==1 {print $2}')
```

## Objectif final

Atteindre la plateforme trop haute grâce à l’injection de valeur dans la RAM.  
Sans exploit → impossible.  
Avec exploit → vitesse augmentée → accès au texte.

## TODO
**Fait**
- Un prof of concept du projet.


**Urgent**
- Mettre en place un build propre :
  - `vulnerable/` avec Makefile
  - `exploit/` avec Makefile
- Définir proprement la structure `Player` (position, vitesse, taille, etc.).
- Intégrer un système de 3D en FPS dans un petit monde (caméra, déplacements, souris).
- Fixer la logique de déplacement (ZQSD, limites du monde, vitesse cohérente).

**A faire**
- Ajouter un affichage debug de la vitesse du joueur (pour voir que l’exploit marche bien).
- Gérer les collisions basiques (sol + quelques blocs).
- Intégrer la gravité (chute, sol, éventuellement jump).
- Créer la plateforme "Out of Reach" avec le texte en hauteur.
- Refaire le README propre avec explication de comment résoudre le challenge


**Optionelle**
- Ajouter des assets sympas (sol, blocs, ciel, texture minimale).
- Ajouter une petite UI (affichage instructions : "Atteins la plateforme en haut").
- Ajouter du son (bruit de pas, petit son quand on atteint la zone) (pas sûr de ça).
