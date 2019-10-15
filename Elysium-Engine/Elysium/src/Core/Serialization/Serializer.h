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
		template<typename T>
		class Serializer
		{
		public:
			Serializer() : m_InputHandler(new Utility::InputHandler()) {};
			~Serializer() = default;
			void Serialize(T& object) const ;
			void Deserialize(T& object);
		private:
			Utility::InputHandler* m_InputHandler;
		};

		template<typename T>
		void Serializer<T>::Serialize(T& object) const
		{
			std::string input; 
			std::ofstream filestream;
			for (;;)
			{
				m_InputHandler->HandleInput("Enter the name of the file (or full path) you would like to save this object to:\n", input);
				filestream.open(input.c_str());
				if (filestream)	break;	 //todo: Maybe implement exceptions here? 
				std::cout << "Failed to write to that file.";
			}
			filestream << object;
			filestream.close();
		}

		template<typename T>
		void Serializer<T>::Deserialize(T& object)
		{
			std::string input;
			std::ifstream filestream;
			for (;;)
			{
				m_InputHandler->HandleInput("Enter the name of the file (or full path) of configurations which you would like to import:\n", input);
				filestream.open(input.c_str());
				if (filestream) break;	//todo: Maybe implement exceptions here? 
				std::cout << "Failed to write to that file."; 
			} 
			filestream >> object;
			filestream.close();
		}
	}
}