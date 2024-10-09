
# Simulation d'un Système Planétaire

## Description
Ce projet est une simulation numérique d'un système planétaire réalisé en langage C. Il modélise un système similaire au système solaire, avec une étoile centrale et des planètes en orbite, soumises aux forces gravitationnelles.

Les résultats sont basés sur les lois de Newton et permettent d'étudier l'évolution du système au fil du temps. Cette simulation offre une visualisation en temps réel des orbites et du comportement des objets célestes.

## Auteurs
- [Aymeric Gros](https://github.com/Aymeric00)
- Maxence Besombes

## Structure du Projet
- **Moteur Physique** : Calcul des forces gravitationnelles, accélération et mise à jour des positions des planètes.
- **Moteur Graphique** : Affichage des planètes et de leur orbite en fonction des calculs du moteur physique.

## Scénarios Inclus
- **Scénario 1** : Comparaison avec les données réelles du système solaire.
- **Scénario 2** : Simulation avec un Soleil sans masse.
- **Scénario 3** : Simulation avec égalisation des masses de la Terre et de Mars.
- **Bonus** : Détermination de la planète la plus proche de la Terre en moyenne durant la simulation.

## Comment Exécuter le Projet
1. Clonez ce dépôt :
   ```bash
   git clone git@github.com:Aymeric00/simulation_systeme_planetaire.git
   ```
2. Compilez le projet avec `gcc` :
   ```bash
   #skeleton/ make main
   ```
3. Exécutez le programme :
   ```bash
   ./simulation
   ```


## Contributions
Les contributions sont les bienvenues. Pour toute modification, merci de créer une pull request ou de contacter les auteurs du projet.
