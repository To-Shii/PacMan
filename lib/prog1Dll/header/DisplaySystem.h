#pragma once
#include <Windows.h>
#include <conio.h>
#include "Color.h"
#include <string>
#include <fstream>
/*
	=============CREDIT=============
	- Author : Quentin OBJ3D
*/

#ifdef MYTOOL_EXPORTS
#define DISPLAYSYSTEM_API __declspec(dllexport)
#else
#define DISPLAYSYSTEM_API __declspec(dllimport)
#endif

#include <iostream>
#include <regex>

using namespace std;
typedef unsigned int u_int;

/// <summary>
/// Structure avec x (ligne) y (colonne) pour la position du curseur
/// </summary>
struct Coord
{
	int x;
	int y;
};
namespace Tools
{
	namespace Console
	{
		/// <summary>
		/// Permet d'afficher ou non le texte en multicolore
		/// <param name="RT_OFF">d�sactiv�</param>
		/// <param name="RT_CHAR">Couleur al�atoire pour chaque caract�re</param>
		/// <param name="RT_TEXT">Couleur al�atoire � chaque ligne</param>
		/// </summary>
		enum DISPLAYSYSTEM_API RainbowType
		{
			RT_OFF,
			RT_CHAR,
			RT_TEXT
		};

		//////////////////////////
		/*		CONSOLE			*/
		//////////////////////////

		DISPLAYSYSTEM_API COORD GetConsoleCursorPosition();

		/// <summary>
		/// Permet de d�finir la position du curseur dans la console
		/// </summary>
		/// <param name="_x">ligne</param>
		/// <param name="_y">Colonne</param>
		/// <param name="_cursor"> Affiche ou non la barre '|' du curseur</param>
		DISPLAYSYSTEM_API void SetCursorPosition(const u_int& _x, const u_int& _y, const bool _cursor = false);

		/// <summary>
		/// Permet de r�cup�rer la position du centre de la console
		/// </summary>
		/// <returns>Retourne les coordonn�es X (ligne) et Y (colonne)</returns>
		DISPLAYSYSTEM_API Coord GetCenterConsole();

		//////////////////////////////
		/*		SINGLE LINE			*/
		//////////////////////////////

		/// <summary>
		/// Permet d'afficher au centre de la console une ligne de texte avec la possibilit� de d�caler l'affichage du centre (padding)
		/// Attention � ne pas mettre de endl ou de '\n'
		/// </summary>
		/// <param name="_text">Le texte � afficher</param>
		/// <param name="_type">Permet de choisir de mettre le texte en multicolore ou non</param>
		/// <param name="_padding">D�cale l'affichage du centre</param>
		/// <param name="_exitKey">Touche � appuyer pour quitter (Echap par d�faut)</param>
		DISPLAYSYSTEM_API void DisplayCenterLine(const string& _text, const RainbowType& _type = RT_OFF, const Coord& _padding = { 0, 0 }, const int _exitKey = 27);

		/// <summary>
		/// Permet d'afficher au centre de la console une ligne de texte avec la possibilit� de d�caler l'affichage du centre (padding)
		/// et de retourner la touche s�lectionn�.
		/// Attention � ne pas mettre de endl ou de '\n'
		/// </summary>
		/// <param name="_text">Le texte � afficher</param>
		/// <param name="_type">Permet de choisir de mettre le texte en multicolore ou non</param>
		/// <param name="_input">Permet de renvoyer la valeur de la touche appuy�</param>
		/// <param name="_padding">D�cale l'affichage du centre</param>
		DISPLAYSYSTEM_API void DisplayCenterLineWithInput(const string& _text, int& _input, const RainbowType& _type = RT_OFF, const Coord& _padding = { 0, 0 });

		/// <summary>
		/// Permet d'afficher une fois au centre de la console une ligne de texte avec la possibilit� de d�caler l'affichage du centre (padding)
		/// Attention � ne pas mettre de endl ou de '\n'
		/// </summary>
		/// <param name="_text">Le texte � afficher</param>
		/// <param name="_type">Permet de choisir de mettre le texte en multicolore ou non</param>
		/// <param name="_padding">D�cale l'affichage du centre</param>
		DISPLAYSYSTEM_API void DisplayOnceCenterLine(const string& _text, const RainbowType& _type = RT_OFF, const Coord& _padding = { 0, 0 });

		//////////////////////////////
		/*		MULTI LINE			*/
		//////////////////////////////

		/// <summary>
		/// Permet d'afficher au centre de la console des lignes de textes avec la possibilit� de d�caler l'affichage du centre (padding)
		/// et de choisir quelle touche il faut appuyer pour quitter l'affichage.
		/// Attention � ne pas mettre de endl ou de '\n'
		/// </summary>
		/// <param name="_textArray">Liste des mots � afficher par ligne</param>
		/// <param name="_size">Taille de la liste _textArray</param>
		/// <param name="_type">Permet de choisir de mettre le texte en multicolore ou non</param>
		/// <param name="_padding">D�cale l'affichage du centre</param>
		/// <param name="_exitKey">Touche � appuyer pour quitter (Echap par d�faut)</param>
		DISPLAYSYSTEM_API void DisplayCenterMultiLine(const vector<string>& _textArray, const RainbowType& _type = RT_OFF, const Coord& _padding = { 0, 0 }, const int _exitKey = 27);

		/// <summary>
		/// Permet d'afficher au centre de la console des lignes de textes avec la possibilit� de d�caler l'affichage du centre (padding)
		/// et de retourner la touche s�lectionn�.
		/// Attention � ne pas mettre de endl ou de '\n'
		/// </summary>
		/// <param name="_textArray">Liste des mots � afficher par ligne</param>
		/// <param name="_size">Taille de la liste _textArray</param>
		/// <param name="_type">Permet de choisir de mettre le texte en multicolore ou non</param>
		/// <param name="_input">Permet de renvoyer la valeur de la touche appuy�</param>
		/// <param name="_padding">D�cale l'affichage du centre</param>
		DISPLAYSYSTEM_API void DisplayCenterMultiLineWithInput(const vector<string>& _textArray, int& _input, const RainbowType& _type = RT_OFF, const Coord& _padding = { 0, 0 });

		/// <summary>
		/// Permet d'afficher une fois au centre de la console des lignes de textes avec la possibilit� de d�caler l'affichage du centre (padding)
		/// Attention � ne pas mettre de endl ou de '\n'
		/// </summary>
		/// <param name="_textArray">Liste des mots � afficher par ligne</param>
		/// <param name="_size">Taille de la liste _textArray</param>
		/// <param name="_type">Permet de choisir de mettre le texte en multicolore ou non</param>
		/// <param name="_padding">D�cale l'affichage du centre</param>
		/// <returns></returns>
		DISPLAYSYSTEM_API void DisplayOnceCenterMultiLine(const vector<string>& _textArray, const RainbowType& _type = RT_OFF, const Coord& _padding = { 0, 0 });

		DISPLAYSYSTEM_API void DisplayAnimatedCenterMultiLine(const string& _filePath, const string& _filePrefix, const u_int& _quantity, const u_int& _size, const RainbowType& _type = RT_OFF, const Coord& _padding = { 0, 0 });

	}
}