`git init`

`git clone adresse_du_répertoire`

sert à télécharger le répertoire qui se trouve à en ligne (sur github)

`git remote add origin adresse_du_répertoire`

sert à utiliser *origin* à la de l'*adresse_du_répertoire* par la suite

`cd nom_du_répertoire`

`git add fichier`

pour ajouter *fichier* au répertoire local

`git add .`

pour ajouter TOUS les fichiers au répertoire local

`git commit -m "commentaire"`

`git pull origin`

sert à fusionner le répertoire en ligne avec le répertoire git locale

`git push origin`

`git rm fichier`

suprimme *fichier* du répertoire git locale

`git push origin --delete branche`

sert à suprimmer la branche *branche*

1 - DEMARAGE
 
0) installer GitHub
1) aller sur GitHub et cloner l'URL du projet ("clone or download"->copier l'URL)
2) aller dans son terminal et se placer dans le dossier ou on veut travailler
3) Taper "git clone URL" (URL = copier coller de étape 1) : le dossier de travail du groupe à été copié sur votre machine
4) se placer dans ce dossier de travail et taper "git init" : votre dossier est initialiser pour utiliser les commandes

2 - RECUPERER LES DERNIERES MODIFS DU FICHIER GITHUB

1) Se placer dans le repertoire de travail de notre ordinateur 
2) Taper "git pull origin master" (vous avez mis à jour votre répertoire avec toutes les dernières modifs)



3 - METTRE A JOUR DES MODIFS QUE J'AI FAIT

-> si je fais des modifs des fichiers présente dans le repertoire de travail il faut que je les mettent à jour sur le site
1) Taper "git add nomdufichier.xxx" ou "git add ." (permet de mettre à jour tous les fichiers du dossier)
2) Taper "git commit -m message" (vous devez indiquer quelles sont les modifs faites à la place de message)
3) Taper "git push origin master" (vous poussez vos modifs sur le dossier principal en ligne)


4 - SUPPRIMER UN FICHIER 

1) Taper "git rm nomdufichier.xxx" (le fichier est supprimer de votre repertoire)
2) Ne pas oublier de mettre à jour cette suppression sur GitHub (partie 3)

5 - TRAVAILLER SUR DIFFERENTES BRANCHES
-> les branches permettent de diviser le travail (exemple on peut avoir une branche pour chaque grosse partie du programme)

1) Taper "git branch" : affiche toutes les branches du projet, dont celle ou vous êtes
2) Taper "git branch nomdelabranche" : créer une branche dans le projet 
3) Taper "git checkout nomdelabranche" : vous vous placer dans la branche

6 - METTRE DES MODIFS D'UNE BRANCHE VERS UNE AUTRE

1) Se placer dans la branche ou on veut importer les modifs
2) Taper "git merge nombrancheimport" : on importe les modifs de la branche "nombrancheimport" dans la branche ou on se trouve


