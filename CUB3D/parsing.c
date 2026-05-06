/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:57:15 by raantoin          #+#    #+#             */
/*   Updated: 2026/05/06 14:46:56 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parser()
{
	//open(file.cub)
	//read(file.cub)
	//put data into a structure
}

int	valid_map()
{
	
}

/*
remplir la map pour en faire un carre avant de lancer les tests? et faire de ces cases des espaces ?
maps invalides:
- si pas tout est ferme, on return message erreur. Pour verifier, on fait un floodfill dans une map copiee qui se lance dans chaque position(i, j) == '0' et
  on remplace la valeur par 2, si a la fin tout est remplit de 2 et qu'on n'est pas sorti ou quoi, cest bon. Verifier les coins aussi.
- verifier si le personnage est a l'interieur et pas l'exterieur. pour cela on peut remplacer sa valeur par 2 commes les espaces vides et verifier que tous les 2 ne sortent pas
- 6 characteres possibles, 1 pour un mur, 0 pour espace vide, et un seul N/S/E/W pour la position de depart du personnage avec son orientation.
le fichier cub contient les 4 textures de murs et ensuite la couleur du floor et celle du ceiling et enfin la map. Tout ce qui precede la map peut etre separe par des lignes vides.
Except for the map content which always has to be the last, each type of element can be set in any order in the file.
 If any misconfiguration of any kind is encountered in the file, the program must exit properly and return "Error\n" followed by an explicit error message of your choice.
*/
