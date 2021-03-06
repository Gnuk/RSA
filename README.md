RSA
===

# Introduction

Cette suite de programme vous permet de :
* génerer des clés RSA
* chiffrer un message
* le déchiffrer
* le signer
* le vérifier

Ce programme utilise des grands entiers (GMP) pour assurer la sécurité.

#Compilation

Rendez-vous dans le dossier RSA pour compiler et utiliser les programmes:

	cd RSA && make clean && make

# Programmes

## gencle

#### Lancer le programme

	./gencle [t] ([file])

> [t] : nombre de bits pour générer les clés ( temps correct jusqu'à 2048 bits)
> ([file]) : Optionel: nom du fichier privée dans lequel sauvegarder les clés (par défaut ~/.my_rsa)

#### Description

Ce programme génére les clés publiques et les clés privées. Ces clés sont affichées puis stockées dans un fichier privé (lectures et écritures autorisées seulement pour l'utilisateur courant).

## Chiffre

#### Lancer le programme

Le programme chiffre ce qui se trouve sur l'entrée standard. On peut par exemple lui envoyer :

	cat monMessage.txt | ./chiffre [n] [b] [t]

> [n] [b] : clé publique avec laquelle vous voulez chiffrer
> [t] : taille des blocks pour découper (en bits)

#### Description

Ce programme chiffre le message placé dans l'entrée standard avec la clé passée en paramètre et renvoie le résultat sur la sortie standard.

## Dechiffre

#### Lancer le programme

Le programme déchiffre ce qui se trouve sur l'entrée standard. On peut par exemple lui envoyer :

	cat monMessageChiffre.txt | ./dechiffre [file]

> [file] : fichier générer par gencle (dans lequel se trouve votre clé privée)

#### Description

Ce programme déchiffre le message placé dans l'entrée standard avec la clé située dans gencle (générée auparavant) et renvoie le résultat sur la sortie standard.

#### Chiffrer et déchiffrer

	cat msg.txt | ./chiffre 1062080754043853759 2478996599 32 | ./dechiffre

## MessageToSha1

#### Lancer le programme

Le programme encode un message (de l'entrée standard) en SHA-1. On peut par exemple lui envoyer :

	cat monMessageChiffre.txt | ./msgToSha1

#### Description

Ce programme encode en sha1 le message placé dans l'entrée standard et renvoie le résultat sur la sortie standard.

Peut être utilisé pour faire un checksum SHA-1 sur le message, et de l'envoyer par exemple à signe pour signer le message avec.

## Signe

#### Lancer le programme

Le programme signe un message (de l'entrée standard) avec la clé privée du fichier privée générée auparavant . On peut par exemple lui envoyer le sha1 du message, puis l'enregistrer dans un fichier :

	cat monMessageChiffre.txt | ./msgToSha1 | ./signe >> signature.txt

#### Description

Ce programme signe le message placé dans l'entrée standard et renvoie le résultat sur la sortie standard.

## Verifie

_todo_