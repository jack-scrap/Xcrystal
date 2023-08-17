#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "disp.h"
#include "prog.h"
#include "util.h"

int main() {
	Disp disp("Xcrystal", 240, 180);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	const GLfloat vtc[] = {
		0.0, -2.0, 0.0,
		-1.0, 0.0, -1.0,
		1.0, 0.0, -1.0,

		0.0, -2.0, 0.0,
		-1.0, 0.0, 1.0,
		1.0, 0.0, 1.0,

		0.0, -2.0, 0.0,
		-1.0, 0.0, -1.0,
		-1.0, 0.0, 1.0,

		0.0, -2.0, 0.0,
		1.0, 0.0, -1.0,
		1.0, 0.0, 1.0,

		0.0, 2.0, 0.0,
		-1.0, 0.0, -1.0,
		1.0, 0.0, -1.0,

		0.0, 2.0, 0.0,
		-1.0, 0.0, 1.0,
		1.0, 0.0, 1.0,

		0.0, 2.0, 0.0,
		-1.0, 0.0, -1.0,
		-1.0, 0.0, 1.0,

		0.0, 2.0, 0.0,
		1.0, 0.0, -1.0,
		1.0, 0.0, 1.0
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof vtc, vtc, GL_STATIC_DRAW);

	glm::mat4 model = glm::mat4(1.0);

	glm::mat4 view = glm::lookAt(glm::vec3(5, 7, 5), glm::vec3(0, 2, 0), glm::vec3(0, 1, 0));
	glm::mat4 proj = glm::perspective(glm::radians(45.0), 240.0 / 180.0, 0.1, 100.0);

	Prog prog("main", "solid");

	prog.use();

	GLint attrPos = glGetAttribLocation(prog._id, "pos");
	glVertexAttribPointer(attrPos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
	glEnableVertexAttribArray(attrPos);

	GLint uniModel = glGetUniformLocation(prog._id, "model");
	GLint uniView = glGetUniformLocation(prog._id, "view");
	GLint uniProj = glGetUniformLocation(prog._id, "proj");

	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	prog.unUse();

	// Ground
	GLuint vaoGround;
	glGenVertexArrays(1, &vaoGround);
	glBindVertexArray(vaoGround);

	GLuint vboGround;
	glGenBuffers(1, &vboGround);
	glBindBuffer(GL_ARRAY_BUFFER, vboGround);

	GLfloat vtcGround[] = {
		-100.0, 0.0, -100.0,
		100.0, 0.0, -100.0,
		100.0, 0.0, 100.0,

		100.0, 0.0, 100.0,
		-100.0, 0.0, -100.0,
		-100.0, 0.0, 100.0
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof vtcGround, vtcGround, GL_STATIC_DRAW);

	Prog progGround("main", "ground");

	glm::mat4 modelGround = glm::mat4(1.0);

	glm::mat4 viewGround = glm::lookAt(glm::vec3(5, 7, 5), glm::vec3(0, 2, 0), glm::vec3(0, 1, 0));
	glm::mat4 projGround = glm::perspective(glm::radians(45.0), 240.0 / 180.0, 0.1, 100.0);

	progGround.use();

	GLint attrPosGround = glGetAttribLocation(prog._id, "pos");
	glVertexAttribPointer(attrPosGround, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
	glEnableVertexAttribArray(attrPosGround);

	GLint uniModelGround = glGetUniformLocation(prog._id, "model");
	GLint uniViewGround = glGetUniformLocation(prog._id, "view");
	GLint uniProjGround = glGetUniformLocation(prog._id, "proj");

	glUniformMatrix4fv(uniModelGround, 1, GL_FALSE, glm::value_ptr(modelGround));
	glUniformMatrix4fv(uniViewGround, 1, GL_FALSE, glm::value_ptr(viewGround));
	glUniformMatrix4fv(uniProjGround, 1, GL_FALSE, glm::value_ptr(projGround));

	progGround.unUse();

	SDL_Event e;
	unsigned int i = 0;
	while (disp.open) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				SDL_Quit();
			}
		}

		disp.clear(0, 0, 0, 1);

		glBindVertexArray(vao);
		prog.use();

		model = glm::translate(glm::mat4(1.0), glm::vec3(0, 2.5 + (sin(i / 50.0) / 5.0), 0));
		model = glm::rotate(model, (GLfloat) (i / 100.0), glm::vec3(0, 1, 0));

		glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 2 * 2 * 2 * 3);

		prog.unUse();
		glBindVertexArray(0);

		// Ground
		glBindVertexArray(vaoGround);
		progGround.use();

		glDrawArrays(GL_TRIANGLES, 0, 2 * 2 * 3);

		prog.unUse();
		glBindVertexArray(0);

		disp.update();

		i++;
	}

	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &vao);
}
