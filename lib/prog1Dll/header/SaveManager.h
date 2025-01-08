#pragma once
#pragma warning(disable : 4984)

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <type_traits>

#include <vector>

#include "FileStream.h"
#include "DynamicArray.h"

#define if_c if constexpr

#define CRYPT if(encryptionKey) _stream.Crypt()
#define UNCRYPT if(encryptionKey) _stream.Uncrypt()

using namespace std;

typedef ios_base ib;

namespace Tools
{
	class MYTOOL_API SaveManager
	{
		string path;
		string* encryptionKey;

	public:
		SaveManager(const string& _path);
		SaveManager(const string& _path, const string& _encryptionKey);
		~SaveManager();

		/// <summary>
		/// Sauvegarder une donn�e
		/// </summary>
		/// <typeparam name="T">Type de la donn�e</typeparam>
		/// <param name="_key">Cl�</param>
		/// <param name="_data">Valeur</param>
		template<typename T>
		void SaveData(const string& _key, const T& _data)
		{
			FileStream _stream = GetStream(ios_base::in | ios_base::out);
			const string& _sData = _key + ":" + Convert<T, string>(_data) + "\n";
			UNCRYPT;
			if (KeyExists(_key))
			{
				vector<int> _keyPos = GetKeyIndex(_key);
				_stream.RemoveLine(GetKeyIndex(_key)[1]);
			}
			FileStream _add = GetStream(ios_base::app);
			_add.SetIsCryptFile(false);
			_add.Write(_sData);
			CRYPT;
		}
		 
		/// <summary>
		/// Obtenir une donn�e � partir de sa cl�
		/// </summary>
		/// <typeparam name="T">Type de la donn�e</typeparam>
		/// <param name="_key">Cl�</param>
		/// <returns>Donn�e</returns>
		template<typename T>
		T GetData(const string& _key)
		{
			FileStream _stream = GetStream(ios_base::out | ios_base::in);
			UNCRYPT;
			if (!KeyExists(_key))
			{
				CRYPT;
				throw exception("Key doesn't exist");
			}
			string _lineValue = _stream.ReadLine(GetKeyIndex(_key)[1]);
			vector<string> _tokens = SplitString(_lineValue, ":");
			unsigned int _contentParts = _tokens.size();
			string _totalContent = "";

			for (unsigned int _i = 1; _i < _contentParts; _i++)
			{
				_totalContent += string(_i > 1 ? ":" : "") + _tokens[_i];
			} // Tout �a au cas o� la cha�ne r�cup�r�e contient le symbole :
 
			CRYPT;

			return Convert<string, T>(_totalContent);
		}

		/// <summary>
		/// V�rifier si une cl� donn�e existe
		/// </summary>
		/// <param name="_key">string : cl�</param>
		/// <returns>bool : existe ?</returns>
		bool KeyExists(const string& _key) const;


	private:
		/// <summary>
		/// Cr�er le fichier
		/// </summary>
		void FileCreate() const;

		/// <summary>
		/// V�rifier si le fichier existe
		/// </summary>
		/// <returns>bool</returns>
		bool FileExists() const;

		/// <summary>
		/// Construire un FileStream
		/// </summary>
		/// <param name="_openmode">Mode d'�criture</param>
		/// <returns>FileStream</returns>
		inline FileStream GetStream(const int _openmode) const;

		/// <summary>
		/// R�cup�rer l'index de la cl� et la ligne sur laquelle elle se trouve
		/// </summary>
		/// <param name="_key">Cl�</param>
		/// <returns>DynamicArray<int> (0 : index | 1 : ligne) | -1 si non trouv�e</returns>
		vector<int> GetKeyIndex(const string& _key) const;
		
		/// <summary>
		/// M�thode pour recr�er le split d'un string
		/// </summary>
		/// <param name="_text">string : � split</param>
		/// <param name="_separator">char : sur quoi split</param>
		/// <returns>vector : tableau de string</returns>
		vector<string> SplitString(const string& _text, const char* _separator) const;

		/// <summary>
		/// Convertisseur entre types
		/// </summary>
		/// <typeparam name="Input">Type d'entr�e</typeparam>
		/// <typeparam name="Result">Type de sortie attendu</typeparam>
		/// <param name="_input">Valeur</param>
		/// <returns>Valeur en type attendu</returns>
		template<typename Input, typename Result>
		Result Convert(const Input& _input) const
		{
			// Si les types sont identiques
			if_c(is_same<Input, Result>::value) return _input;

			// Si l'entr�e est un type arithm�tique (comme int, float)
			if_c(is_arithmetic_v<Input>) return to_string(_input);

			// Si le R�sultat est arithm�tique et que l'input est une cha�ne de caract�re
			if_c(is_same_v<Input, string> || is_same_v<Input, const char*>) {
				if_c(is_arithmetic_v<Result>) {
					istringstream iss(_input);
					Result result;
					if (!(iss >> result)) {
						throw runtime_error("Conversion failed: invalid input string for numeric conversion.");
					}
					return result;
				}
			}

			// Si l'entr�e est un tableau de caract�res (char[])
			if_c(is_same<Input, char*>::value) {
				return static_cast<Result>(string(_input)); // Convertit const char[] en std::string
			}
			else if constexpr (is_same<Input, int>::value) return to_string(_input);
			else if constexpr (is_same<Input, bool>::value) return (_input ? "true" : "false");
			else if constexpr (is_same<Input, char>::value) return _input[0];

			throw exception("Unable to convert type");
		}


	};
}




