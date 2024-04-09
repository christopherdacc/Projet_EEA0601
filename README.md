# Projet_EEA0601 (Partie IHM)

Programmation en langage C sur MPLAB X IDE d'un microcontrôleur (dsPIC30F4012) pour un système d'IHM d'un robot.
Ce robot a pour fonction de suivre une trajectoire (suit une ligne dessinée par terre), détecter les obstacles et changer de direction pour poursuivre son chemin et une interface IHM pour pouvoir entrer des informations au microcontrôleur avec 3 boutons.

"Séances de travail surveillées et supplémentaires avec tâches réalisées"

* Séance 1 (24/01/2024):
      Explication du projet par les professeurs.
  
* Séance 2 (31/01/2024):
      Branchement d'un afficheur LCD (EA DOGM163W-A) et allumage du rétroéclairage.

* Séance 2.1 sup (02/02/2024):
      programmation et affichage de 'Bonjour le monde!' sur l'écran LCD.
  
* Séance 3 (07/02/2024):
      Branchement des boutons avec leurs résistances spécifiques.

* Séance 4 (14/02/2024):
      Programmation des boutons pour savoir s'ils sont appuyés ou non en affichant leurs états sur l'écran LCD.

* Séance 5 (21/02/2024):
      Rajout des librairies sur Eagle.
      Réalisation du schéma de la carte électronique sur Eagle.

* Séance 5.1 sup (22/02/2024):
      Finalisation du schéma de la carte électronique sur Eagle.
      Début de la réalisation de la carte électronique sur Eagle ainsi que le typon.
* Séance 5.2 sup (23/02/2024):
      Début de la programmation d'un menu avec les options de test des boutons et changement de l'éclairage de l'écran.

* Travail Vacances 6 (du 24/02/2024 au 02/03/2024):
      Finalisation du code menu (prototype)
      Erreur de Build du code.

* Séance 6.1 test du code (05/03/2024):
      Test du code et correction du build error.
      Nouveau probleme code ne marche pas comme on veux.

* Séance 7 (06/03/2024):
      Correction du Schéma de la carte.
      On a commencé a realisé la carte.
      Un peut de modification du code pour qu'il marche (ne marche toujours pas).

* Séance 7.1 sup (07/03/2024):
      Correction de l'affichage du menu (sélection de choix marche bien mais les choix ne marchent pas a 100%)

* Séance 7.2 sup (11/03/2024):
      Correction de la fonction délai.
      Travail sur le compte rendu.

* Séance 8 (13/03/2024):
      On a continué le routage des pistes.
      On a changer les pates des boutons et de l'ecran pour mettre les pates des boutons sur les pates CN qui permettent les interuptions sur front.
  
* Séance 9 (20/03/2024):
      On a finit la carte électronique avec le dimentionnement des pistes de +5V (0.05 inch) et pistes de signaux (0.024).
      On a cassé les angles et tout ca pour evité le rayonnement electromagnetique.

* Séance 10 (27/03/2024):
      On a percé la carte pour pouvoir souder les composants decu.

* Séance 10.1 sup (28/03/2024):
      On a réalisé le test de continuité a l'ohm mètre.
      On a resouder une piste défectueuse.
      On a souder tout les composants sur la carte.
* Séance 11 (03/04/2024):
      Reprogrammation du test des boutons en utilisant des iterruptions.
      Interruptions fonctionnent mais que sur le bouton 3.

* Séance 11.1 sup (09/04/2024):
      Correction du code de l'interruption (Fonctionnement parfait des boutons).
      Essai d'integrer la structure Keyboard avec les objets, mais pas de success.
      Changement du bouton rouge.
      Pendant le test du code, on a rencontrer un probleme de fonctionnement du microcontrolleur.
      Probleme de cablage au niveau de l'alimentation du microcontrolleur.



