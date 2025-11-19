# Proof of Concept (PoC) – Runtime Process Modification

> ⚠️ Ce PoC est destiné aux systèmes **UNIX** uniquement.

## Introduction

Ce dossier contient un **Proof of Concept** démontrant la possibilité de modifier un processus en cours d'exécution à l'aide de techniques de manipulation mémoire. L'objectif est d'illustrer le principe de modification dynamique d’une application, qui servira de base à un projet plus ambitieux utilisant ce mécanisme.

Deux fichiers sont fournis :

- `vulnerable.c` : un programme "victime" à exécuter.
- `exploit.c` : un programme "attaquant" exploitant la vulnérabilité.

## Compilation

Compilez les fichiers comme suit :

```bash
gcc vulnerable.c -Wall -o vulnerable
gcc vulnerable_raylib.c -Wall -lraylib -o vulnerable // Version plus visuelle avec raylib
                                                     // Commandes :
                                                     //    - ZQSD : Déplacements
                                                     //    - F    : Affiche les informations du joueur
gcc exploit.c -Wall -o exploit
```

## Utilisation

1. **Lancer le programme vulnérable** :

   Dans un terminal :

   ```bash
   ./vulnerable
   ```

   Ce programme attendra qu'une valeur soit modifiée.

2. **Exécuter l'exploit** :

   Dans un autre terminal, récupérez le PID du processus `vulnerable`, soit manuellement, soit automatiquement via `ps`, puis lancez l’exploit :

   ```bash
   sudo ./exploit $(ps aux | grep '[v]ulnerable' | awk 'NR==1 {print $2}')
   ```

   > ℹ️ L'utilisation de `sudo` est requise car, par défaut, la plupart des systèmes Linux ont le paramètre `/proc/sys/kernel/yama/ptrace_scope` défini à `1`. Cela limite l’attachement à un processus uniquement à ses enfants. Deux options s’offrent à vous :
   > 
   > - Utiliser `sudo` (recommandé).
   > - Modifier temporairement la politique de sécurité en exécutant :
   >
   >   ```bash
   >   echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope
   >   ```

## Objectif

Ce PoC n'est qu'une **démonstration technique**. Il sera intégré ultérieurement dans un projet plus vaste visant à exploiter la modification en runtime d'applications pour des usages plus avancés (debug, instrumentation, etc.).

## Avertissement

Ce code est fourni **à des fins éducatives uniquement**. N'utilisez jamais ce type de mécanisme sans autorisation explicite. Toute utilisation malveillante est strictement interdite.
