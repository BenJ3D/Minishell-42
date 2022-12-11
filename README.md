<h1 align="center">Minishell</h1>

Premier projet 42 à faire en duo, nous devons reproduire les fonctionnalitées de base d'un shell : bash.

Nous devons recréer un mini shell qui doit implémenter :

- Les variables d'environnement
- Les redirections et les pipes
- Les quotes et double quotes
- Les herdocs
- L'historique des commandes
- La gestion des codes retour d'erreur
- Les signaux <kbd>ctrl</kbd> +  <kbd>c</kbd>, <kbd>ctrl</kbd> +  <kbd>d</kbd>, <kbd>ctrl</kbd> + <kbd> \ </kbd>

Le travail se découpe en 3 grandes parties :

<h2 align="left">Le parsing</h2>

L'objectif ici est d'analyser et de découper les commandes entrées par l'utilisateur, le cas échéant de retourner les erreurs de syntaxe, puis de préparer les données pour l'envoi à la partie éxecution.

<h2 align="left">L'execution</h2>

Il faut ici analyser les commandes qui doivent être éxécutée, notament préparer s'il y en a les pipes et rédirection, rechercher si la commande éxiste à l'aide de la varaible environnement PATH, et essayer de l'éxécuter avec tous ses arguments.

<h2 align="left">Les builtins</h2>




