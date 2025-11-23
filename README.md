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
- Mettre en place un build propre :
  - `exploit/` avec Makefile
  - `vulnerable/` avec Makefile
- Définir proprement la structure `Player` (position, vitesse, taille, etc.).
- Intégrer un système de 3D en FPS dans un petit monde (caméra, déplacements, souris).
- Ajout d'un crosshair custom
- Créer la plateforme "Out of Reach" avec le texte en hauteur.
- Fixer la logique de déplacement (ZQSD, limites du monde, vitesse cohérente) non contrôlé par raylib pour avoir une vitesse contrôlable par exemple.
- Première version du principe de l'application
- Menu start/pause
- Menu de settings
- Ajouter un affichage debug de la vitesse, position etc... du joueur (pour voir que l’exploit marche bien).


**Urgent**
- Rendre le texte illisible en reverse
- Faire un IHM pour l'exploit avec GTK


**A faire**
- Refaire le README propre avec explication de comment résoudre le challenge
- Améliorer le monde (ajouter des collisions au bord, des objet etc...)
- Gérer les collisions basiques (sol + quelques blocs).
- Améliorer le menu settings (fps, touches...)
- Afficher un hud ou des informations dans le décor avec les commandes importantes (je sais pas encore si il faut le faire, ça dépendra de si il y a plus que ZQSD en commandes)


**Optionelle**
- Intégrer la gravité (chute, sol, éventuellement jump).
- Ajouter des assets sympas (sol, blocs, ciel, texture minimale).
- Ajouter une petite UI (affichage instructions : "Atteins la plateforme en haut").
- Ajouter du son (bruit de pas, petit son quand on atteint la zone) (pas sûr de ça).
- Ajouter un menu paramètre où on peut changer par exemple la sensibilité, le crosshair, résolution etc...
- Si réalisable faire des interaction avec des bloc (un peu comme supraland), pouvoir déplacer, tourner des blocs
