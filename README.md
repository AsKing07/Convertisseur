# Convertisseur

Ce dépôt contient un utilitaire de conversion d'unités développé en C++ avec le framework Qt. L'application permet de convertir librement entre différentes unités du système métrique et impérial, telles que les lignes, les pouces, les pieds, les yards, les miles, les millimètres, les centimètres, les mètres et les kilomètres.

## Fonctionnalités

- Conversion entre différentes unités : ligne, pouce, pied, yard, mile, millimètre, centimètre, mètre, kilomètre.
- Enregistrement des conversions précédemment effectuées dans une base de données locale.
- Réinitialisation de la base de données pour supprimer les enregistrements existants.
- Consultation des anciennes conversions sauvegardées dans la base de données.

## Configuration requise

- Qt Creator (ou tout autre environnement de développement compatible avec le framework Qt).
- Bibliothèque Qt (version 5 ou ultérieure).

## Comment compiler le projet

1. Clonez le dépôt sur votre machine locale :

   ```bash
   git clone https://github.com/AsKing07/convertisseur.git
   ```

2. Ouvrez le projet dans Qt Creator.

3. Configurez les kits de compilation pour pointer vers votre installation de Qt.

4. Compilez le projet en appuyant sur le bouton de construction (ou en utilisant la combinaison de touches Ctrl + R).

5. Exécutez l'application en appuyant sur le bouton de lecture (ou en utilisant la combinaison de touches Ctrl + R).

## Base de données

La base de données utilisée pour stocker les conversions se trouve dans le dossier "Build". Le fichier de base de données porte le nom "conversions.db".

## Remarques

- Veillez à sélectionner les unités appropriées lors des conversions pour obtenir des résultats précis.

- Les conversions peuvent inclure de légères marges d'erreur en raison des limitations des nombres à virgule flottante. Pour des calculs plus précis, vous pouvez envisager d'utiliser des bibliothèques telles que `BigDecimal`.

- Ce projet est fourni à titre d'exemple et à des fins éducatives.

## Auteur

[Charbel SONON](github.com/AsKing07)

N'hésitez pas à contribuer au projet en ouvrant des pull requests ou en signalant des problèmes.

Merci d'utiliser notre Convertisseur d'unités ! Bonnes conversions !
```
