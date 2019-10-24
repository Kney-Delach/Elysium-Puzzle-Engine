/**
 * FILENAME		: Serializer.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 15/10/2019
 * Description	: This file contains the implementation of the serializer used throughout Elysium, 
				  it handles both writing and reading files.
 */
#pragma once
#include <fstream>
#include <string>
#include "Core/Utility/InputHandler.h"

namespace Elysium
{
	namespace Serialize
	{
		template <typename T>
		class FileManager
		{
		public:
			static void Serializer(T& object);
			static void Deserializer(T& object);
		private:
			FileManager() = default;
			~FileManager() = default;
		};
		template<typename T>
		void FileManager<T>::Serializer(T& object)
		{
			std::string input; 
			std::ofstream filestream;
			for (;;)
			{
				Utility::InputHandler::HandleInput("Enter the name of the file (or full path) you would like to save this object to:\n", input);
				filestream.open(input.c_str());
				if (filestream)	
					break;
				std::cout << "Failed to write to that file.";
			}	
			filestream << object;
			filestream.close();
		}

		template<typename T>
		void FileManager<T>::Deserializer(T& object)
		{
			std::string input;
			std::ifstream filestream;
			for (;;)
			{
				Utility::InputHandler::HandleInput("Enter the name of the file (or full path) of configurations which you would like to import:\n", input);
				filestream.open(input.c_str());
				if (filestream) 
					break;
				std::cout << "Failed to read from that file. - "; 
			}
			filestream >> object;
			filestream.close();
		}
	}
}