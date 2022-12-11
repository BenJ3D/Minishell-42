<h1 align="center">Minishell</h1>

Premier projet 42 à faire en duo, nous devons reproduire les fonctionnalitées de base d'un shell : bash.

Ce mini shell qui doit implémenter :

- Les variables d'environnement
- Les redirections et les pipes
- Lq gestion des quotes et double quotes
- Les herdocs
- L'historique des commandes
- La gestion des codes d'erreur
- Les signaux <kbd>ctrl</kbd> +  <kbd>c</kbd>, <kbd>ctrl</kbd> +  <kbd>d</kbd>, <kbd>ctrl</kbd> + <kbd> \ </kbd>

Le travail se découpe en 3 grandes parties :

<h2 align="left">Le parsing</h2>

L'objectif ici est d'analyser et de découper les commandes entrées par l'utilisateur, de retourner les erreurs de syntaxes (le cas échéant), puis de préparer les données pour l'envoi à la partie éxecution.

![image](https://user-images.githubusercontent.com/49345674/206907247-f69ff28b-985c-491d-8184-ef4147d0613e.png)

<h2 align="left">L'execution</h2>

Il faut ici analyser les commandes qui doivent être éxécutées, notamment préparer, s'il y en a, les pipes et rédirections puis rechercher si la commande éxiste à l'aide de la varaible environnement PATH pour essayer de l'éxécuter avec tous ses arguments ou renvoyer l'erreur adéquate.

![image](https://user-images.githubusercontent.com/49345674/206907622-7ede78d7-da42-45f6-a979-8b0cc2317abd.png)
![image](https://user-images.githubusercontent.com/49345674/206910263-5ce9b5b8-4d4a-427c-86f9-3452b51d3aa4.png)

<h2 align="left">Les builtins</h2>
Ne devions recoder et implémenter les builtins suivantes :

- `echo` (avec l'option -n)
- `cd` (uniquement avec le chemin relatif ou absolu)
- `pwd` (sans aucune option)
- `export` (sans aucune option)
- `unset` (sans aucune option)
- `env` (sans aucune option ou argument)
- `exit` (sans aucune option)

![image](https://user-images.githubusercontent.com/49345674/206907930-77516d62-a503-4b16-907a-bb24a1795170.png)

### Compilation :

Pour compiler le projet, exécutez la commande suivante :

```
make
```

### Execution :

```
./minishell
```

### Demo :
![2022-12-11 15-19-35](https://user-images.githubusercontent.com/49345674/206909462-cfa7ed08-981c-4f39-a496-68a0df8d9ab6.gif)
![2022-12-11 15-22-08](https://user-images.githubusercontent.com/49345674/206909465-0c02661d-37f7-4fd6-90cc-414989a21884.gif)
![2022-12-11 15-23-55](https://user-images.githubusercontent.com/49345674/206909467-bba10126-ac87-495b-922f-3620ac340088.gif)
![2022-12-11 15-24-53](https://user-images.githubusercontent.com/49345674/206909470-756fba27-5177-4dae-93c2-4eba883c8695.gif)


