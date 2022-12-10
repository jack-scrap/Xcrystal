#pragma once

#include "util.h"

class Shad {
	public:
		GLuint _id;

		Shad(std::string name, int stage);

		~Shad();
};

class Prog {
	public:
		GLuint _id;

		Prog(std::string vtxName, std::string fragName);

		void use();

		void unUse();

		~Prog();
		
		enum stage {
			VTX,
			FRAG
		};
};
