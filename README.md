# 🚀 Projet de Programmation Système (MiniShell et Utilitaires UNIX)

Ce dépôt regroupe les solutions des Travaux Pratiques (TP) en Programmation Système. L'objectif principal est de comprendre et d'implémenter les mécanismes de base du système d'exploitation UNIX/Linux, en créant notre propre petit interpréteur de commandes (un **MiniShell**) et divers outils de gestion de processus.

---

## 🎯 Objectifs du Projet

Le projet vise à maîtriser trois domaines fondamentaux :

1.  **Gestion des Processus** : Créer, exécuter, synchroniser et gérer l'état des processus en utilisant `fork()`, `exec()`, et `wait()`.
2.  **Gestion des Entrées/Sorties (I/O)** : Manipuler les descripteurs de fichiers (`open`, `close`, `dup`) pour effectuer des **redirections** (`<`, `>`, `|`).
3.  **Synchronisation et Communication** : Utiliser les **tubes (`pipe()`)** pour la communication inter-processus et les **signaux (`signal()`)** pour le contrôle et la gestion du temps.

---

## 🛠️ Technologies et Outils Utilisés

* **Langage de Programmation :** C
* **Appels Système Clés :**
    * `fork()`, `exec()`, `wait()` : Pour la gestion des processus.
    * `pipe()`, `dup()`, `close()` : Pour les communications et les redirections.
    * `signal()`, `kill()` : Pour la gestion des signaux.
    * `time_t`, `time()` : Pour le suivi du temps et les rapports d'exécution.
* **Produit Final :** Un interpréteur de commandes capable d'exécuter des commandes de manière synchrone et asynchrone, et de gérer les redirections.

---

## 📂 Structure du Dépôt

Le code est organisé par thème de TP pour une meilleure clarté :

* **`TP1_Processus`** : Fonctions d'analyse de commandes (`Ligne2Argv`) et programmes d'exécution (`Executer`, `ExecFileBatch`).
* **`TP2_Signaux`** : Exercices autour de la capture de signaux (`SIGINT`) et des minuteries (`Timeout`).
* **`TP3_Redirection_IO`** : Implémentation des mécanismes d'E/S de bas niveau, des tubes et du verrouillage (`lockf`).

---

## ⚙️ Démarrage Rapide

Pour compiler un exercice, naviguez dans le dossier correspondant et utilisez `gcc` :

```bash
# Exemple pour compiler un programme
gcc -o nom_executable chemin/vers/fichier.c -Wall