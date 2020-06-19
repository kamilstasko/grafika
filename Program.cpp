#include "Program.h"
#include "Przeksztalcenia.h"

GLuint ProgramMPGK::VAO;
GLuint ProgramMPGK::VBO;
GLuint ProgramMPGK::IBO;
GLuint ProgramMPGK::programZShaderami;
GLuint ProgramMPGK::vertexShaderId;
GLuint ProgramMPGK::fragmentShaderId;
GLint ProgramMPGK::zmiennaShader;

GLint wybor = 2;
GLfloat pozycjaKameryX, pozycjaKameryY, pozycjaKameryZ;
GLfloat okoKameryX, okoKameryY;

ProgramMPGK::ProgramMPGK(void)
{
	wysokoscOkna = 768;
	szerokoscOkna = 1024;
	polozenieOknaX = 100;
	polozenieOknaY = 100;
}

ProgramMPGK::ProgramMPGK(int wysokoscOkna, int szerokoscOkna, int polozenieOknaX, int polozenieOknaY)
{
	this->wysokoscOkna = wysokoscOkna;
	this->szerokoscOkna = szerokoscOkna;
	this->polozenieOknaX = polozenieOknaX;
	this->polozenieOknaY = polozenieOknaY;
}

ProgramMPGK::~ProgramMPGK()
{

}

void ProgramMPGK::stworzenieOkna(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(szerokoscOkna, wysokoscOkna);
	glutInitWindowPosition(polozenieOknaX, polozenieOknaY);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Program");
}

void ProgramMPGK::inicjalizacjaGlew()
{
	GLenum wynik = glewInit();
	if (wynik != GLEW_OK)
	{
		std::cerr << "Nie udalo sie zainicjalizowac GLEW. Blad: " << glewGetErrorString(wynik) << std::endl;
		//system("pause");
		exit(1);
	}
}

void  ProgramMPGK::wyswietl()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static GLfloat zmiana = 0.0f;
	zmiana += 0.0005f;
	glUniform1f(zmiennaShader, abs(sinf(zmiana)));

	static GLfloat zmienKolor = 1;
	GLint zmienKolorUniform = glGetUniformLocation(programZShaderami, "zmienKolor");
	glUniform1f(zmienKolorUniform, zmienKolor);

	static GLfloat pozycjaKamery_x = 0.0;
	static GLfloat pozycjaKamery_y = 0.0;
	static GLfloat pozycjaKamery_z = 0.0;

	static GLfloat okoKamery_x = 0.0;
	static GLfloat okoKamery_y = 0.0;
	static GLfloat okoKamery_z = -1.0;

	static GLfloat goraKamery_x = 0.0;
	static GLfloat goraKamery_y = 1.0;
	static GLfloat goraKamery_z = 0.0;

	pozycjaKamery_x += pozycjaKameryX;
	pozycjaKamery_y += pozycjaKameryY;
	pozycjaKamery_z += pozycjaKameryZ;

	okoKamery_x += okoKameryX;
	okoKamery_y += okoKameryY;

	pozycjaKameryX = 0;
	pozycjaKameryY = 0;
	pozycjaKameryZ = 0;
	okoKameryX = 0;
	okoKameryY = 0;

	Macierz<4> w, s, r, t, p, kk, kp;
	Przeksztalcenia<4> q;

	s = q.macierzSkalowania3d(1, 1, 1);
	r = q.macierzObrotu3d(0, 1);
	t = q.macierzTranslacji3d(0, 0, 0);

	p = q.macierzPerspektyw(45, 786, 786, 3.0, 7.0);

	kk = q.kierunekKamery(new GLfloat[3]{ okoKamery_x, okoKamery_y, okoKamery_z }, new GLfloat[3]{ goraKamery_x, goraKamery_y, goraKamery_z });
	kp = q.polozenieKamery(pozycjaKamery_x, pozycjaKamery_y, pozycjaKamery_z);

	w = q.operacje(6, s, r, t, p, kk, kp);

	GLfloat* matrix = new GLfloat[16];

	unsigned x = 0;
	for (unsigned i = 0; i < 4; ++i)
	{
		for (unsigned j = 0; j < 4; ++j)
		{
			matrix[x++] = w.getData(i, j);
		}
	}

	GLfloat macierzUniform = glGetUniformLocation(programZShaderami, "macierz");
	glUniformMatrix4fv(macierzUniform, 1, GL_FALSE, matrix);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 4));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	if (wybor == 1)
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	else
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glutSwapBuffers();
}

void ProgramMPGK::usun()
{
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
	glDeleteProgram(programZShaderami);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteVertexArrays(1, &VAO);
}

void ProgramMPGK::stworzenieVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void ProgramMPGK::stworzenieVBO()
{
	GLfloat wierzcholki[] = {
		-0.4f, -0.4f, 0.0f, 1.0f,
		 1.0f,  0.0f, 0.0f, 1.0f,
		 0.4f, -0.4f, 0.4f, 1.0f,
		 0.0f,  1.0f, 0.0f, 1.0f,
		-0.4f,  0.4f, 0.0f, 1.0f,
		 0.0f,  0.0f, 1.0f, 1.0f,
		 0.4f,  0.4f, 0.4f, 1.0f,
		 0.5f,  0.5f, 0.0f, 1.0f
	};

	GLfloat wierzcholki2[] = {
		//przód
		-0.4f, -0.4f, 0.4f, 1.0f, //0
		1.0f,  0.0f, 0.0f, 1.0f, //red
		0.4f, -0.4f, 0.4f, 1.0f, //1
		1.0f,  0.0f, 0.0f, 1.0f, //red
		0.4f, 0.4f, 0.4f, 1.0f, //2
		1.0f,  0.0f, 0.0f, 1.0f, //red
		-0.4f, -0.4f, 0.4f, 1.0f, //0
		1.0f,  0.0f, 0.0f, 1.0f, //red
		0.4f, 0.4f, 0.4f, 1.0f, //2
		1.0f,  0.0f, 0.0f, 1.0f, //red
		-0.4f, 0.4f, 0.4f, 1.0f, //3
		1.0f,  0.0f, 0.0f, 1.0f, //red
		//góra
		-0.4f, 0.4f, 0.4f, 1.0f, //3
		0.0f,  0.0f, 1.0f, 1.0f, //blue
		0.4f, 0.4f, 0.4f, 1.0f, //2
		0.0f,  0.0f, 1.0f, 1.0f, //blue
		-0.4f, 0.4f, -0.4f, 1.0f, //4
		0.0f,  0.0f, 1.0f, 1.0f, //blue
		-0.4f, 0.4f, -0.4f, 1.0f, //4
		0.0f,  0.0f, 1.0f, 1.0f, //blue
		0.4f, 0.4f, 0.4f, 1.0f, //2
		0.0f,  0.0f, 1.0f, 1.0f, //blue
		0.4f, 0.4f, -0.4f, 1.0f, //5
		0.0f,  0.0f, 1.0f, 1.0f, //blue
		//prawa
		0.4f, 0.4f, -0.4f, 1.0f, //5
		0.0f,  1.0f, 1.0f, 1.0f, //cyan
		0.4f, 0.4f, 0.4f, 1.0f, //2
		0.0f,  1.0f, 1.0f, 1.0f, //cyan
		0.4f, -0.4f, 0.4f, 1.0f, //1
		0.0f,  1.0f, 1.0f, 1.0f, //cyan
		0.4f, 0.4f, -0.4f, 1.0f, //5
		0.0f,  1.0f, 1.0f, 1.0f, //cyan
		0.4f, -0.4f, 0.4f, 1.0f, //1
		0.0f,  1.0f, 1.0f, 1.0f, //cyan
		0.4f, -0.4f, -0.4f, 1.0f, //6
		0.0f,  1.0f, 1.0f, 1.0f, //cyan
		//dó³
		0.4f, -0.4f, -0.4f, 1.0f, //6
		0.0f,  1.0f, 0.0f, 1.0f, //lime
		0.4f, -0.4f, 0.4f, 1.0f, //1
		0.0f,  1.0f, 0.0f, 1.0f, //lime
		-0.4f, -0.4f, -0.4f, 1.0f, //7
		0.0f,  1.0f, 0.0f, 1.0f, //lime
		-0.4f, -0.4f, -0.4f, 1.0f, //7
		0.0f,  1.0f, 0.0f, 1.0f, //lime
		0.4f, -0.4f, 0.4f, 1.0f, //1
		0.0f,  1.0f, 0.0f, 1.0f, //lime
		-0.4f, -0.4f, 0.4f, 1.0f, //0
		0.0f,  1.0f, 0.0f, 1.0f, //lime
		//lewa
		-0.4f, -0.4f, -0.4f, 1.0f, //7
		0.5f, 0.0f, 0.5f, 1.0f, //purple
		-0.4f, -0.4f, 0.4f, 1.0f, //0
		0.5f, 0.0f, 0.5f, 1.0f, //purple
		-0.4f, 0.4f, -0.4f, 1.0f, //4
		0.5f, 0.0f, 0.5f, 1.0f, //purple
		-0.4f, 0.4f, -0.4f, 1.0f, //4
		0.5f, 0.0f, 0.5f, 1.0f, //purple
		-0.4f, -0.4f, 0.4f, 1.0f, //0
		0.5f, 0.0f, 0.5f, 1.0f, //purple
		-0.4f, 0.4f, 0.4f, 1.0f, //3
		0.5f, 0.0f, 0.5f, 1.0f, //purple
		//ty³
		-0.4f, -0.4f, -0.4f, 1.0f, //7
		1.0f,  1.0f, 0.0f, 1.0f, //yellow
		-0.4f, 0.4f, -0.4f, 1.0f, //4
		1.0f,  1.0f, 0.0f, 1.0f, //yellow
		0.4f, 0.4f, -0.4f, 1.0f, //5
		1.0f,  1.0f, 0.0f, 1.0f, //yellow
		0.4f, -0.4f, -0.4f, 1.0f, //6
		1.0f,  1.0f, 0.0f, 1.0f, //yellow
		-0.4f, -0.4f, -0.4f, 1.0f, //7
		1.0f,  1.0f, 0.0f, 1.0f, //yellow
		0.4f, 0.4f, -0.4f, 1.0f, //5
		1.0f,  1.0f, 0.0f, 1.0f, //yellow
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	if (wybor == 1)
		glBufferData(GL_ARRAY_BUFFER, sizeof(wierzcholki), wierzcholki, GL_STATIC_DRAW);
	else
		glBufferData(GL_ARRAY_BUFFER, sizeof(wierzcholki2), wierzcholki2, GL_STATIC_DRAW);
}

void ProgramMPGK::stworzenieIBO()
{
	GLuint indeksyTab[] = {
		0, 1, 2, 1, 2, 3,
	};

	GLuint indeksyTab2[] = {
		0,1,2,
		3,4,5,
		6,7,8,
		9,10,11,
		12,13,14,
		15,16,17,
		18,19,20,
		21,22,23,
		24,25,26,
		27,28,29,
		30,31,32,
		33,34,35
	};

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	if (wybor == 1)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeksyTab), indeksyTab, GL_STATIC_DRAW);
	else
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeksyTab2), indeksyTab2, GL_STATIC_DRAW);
}

void ProgramMPGK::stworzenieProgramu()
{
	programZShaderami = glCreateProgram();

	if (programZShaderami == 0)
	{
		std::cerr << "Blad podczas tworzenia programu shaderow." << std::endl;
		//system("pause");
		exit(1);
	}

	const char * vertexShader =
		"	#version 330 core \n																	\
			layout(location=0) in vec4 polozenie; \n												\
			layout(location=1) in vec4 kolorVS; \n													\
			uniform mat4 macierz; \n																\
			out vec4 kolorFS; \n																	\
			uniform float zmianaShader; \n															\
			void main()			 \n																	\
			{		 \n																				\
				gl_Position = macierz * polozenie; \n		\
				kolorFS = kolorVS; \n																\
			}";

	const char * fragmentShader =
		"	#version 330 core \n						\
			out vec4 kolor;	\n							\
			in vec4 kolorFS; \n							\
			void main()	\n								\
			{			\n								\
				kolor = kolorFS;	\n					\
			}";

	vertexShaderId = dodanieDoProgramu(programZShaderami, vertexShader, GL_VERTEX_SHADER);
	fragmentShaderId = dodanieDoProgramu(programZShaderami, fragmentShader, GL_FRAGMENT_SHADER);

	GLint linkowanieOK = 0;
	glLinkProgram(programZShaderami);
	glGetProgramiv(programZShaderami, GL_LINK_STATUS, &linkowanieOK);
	if (linkowanieOK == GL_FALSE) {
		GLint dlugoscLoga = 0;
		glGetProgramiv(programZShaderami, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		std::vector<GLchar> log(dlugoscLoga);
		glGetProgramInfoLog(programZShaderami, dlugoscLoga, NULL, &log[0]);
		std::cerr << "Blad podczas linkowania programu shaderow." << std::endl;
		for (std::vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i)
			std::cerr << *i;
		std::cerr << std::endl;
		glDeleteProgram(programZShaderami);
		//system("pause");
		exit(1);
	}

	GLint walidacjaOK = 0;
	glValidateProgram(programZShaderami);
	glGetProgramiv(programZShaderami, GL_VALIDATE_STATUS, &walidacjaOK);
	if (walidacjaOK == GL_FALSE) {
		GLint dlugoscLoga = 0;
		glGetProgramiv(programZShaderami, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		std::vector<GLchar> log(dlugoscLoga);
		glGetProgramInfoLog(programZShaderami, dlugoscLoga, NULL, &log[0]);
		std::cerr << "Blad podczas walidacji programu shaderow." << std::endl;
		for (std::vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i)
			std::cerr << *i;
		std::cerr << std::endl;
		glDeleteProgram(programZShaderami);
		//system("pause");
		exit(1);
	}

	glUseProgram(programZShaderami);

	/*
	zmiennaShader = glGetUniformLocation(programZShaderami, "zmianaShader");
	if (zmiennaShader == -1)
	{
		std::cerr << "Nie znalezion zmiennej uniform." << std::endl;
		//system("pause");
		exit(1);
	}
	*/
}

GLuint ProgramMPGK::dodanieDoProgramu(GLuint programZShaderami, const GLchar * tekstShadera, GLenum typShadera)
{
	GLuint shader = glCreateShader(typShadera);

	// 35633 -> vertex shader, 35632 -> fragment shader
	const GLchar * typShaderaTekst = typShadera == 35633 ? "vertex" : "fragment";

	if (shader == 0) {
		std::cerr << "Blad podczas tworzenia " << typShaderaTekst << " shadera." << std::endl;
		//system("pause");
		exit(0);
	}

	const GLchar * tekstShaderaTab[1];
	tekstShaderaTab[0] = tekstShadera;
	GLint dlugoscShadera[1];
	dlugoscShadera[0] = strlen(tekstShadera);
	glShaderSource(shader, 1, tekstShaderaTab, dlugoscShadera);

	glCompileShader(shader);
	GLint kompilacjaOK = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &kompilacjaOK);
	if (kompilacjaOK == GL_FALSE)
	{
		GLint dlugoscLoga = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		std::vector<GLchar> log(dlugoscLoga);
		glGetShaderInfoLog(shader, dlugoscLoga, NULL, &log[0]);
		std::cerr << std::endl;
		std::cerr << "Blad podczas kompilacji " << typShaderaTekst << " shadera." << std::endl;
		std::cerr << std::endl;
		std::cerr << "log: ";
		for (std::vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i)
			std::cerr << *i;
		std::cerr << std::endl;
		glDeleteShader(shader);
		//system("pause");
		exit(1);
	}

	glAttachShader(programZShaderami, shader);
	return shader;
}
void ProgramMPGK::sprawdzenieWersji()
{
	std::cout << "Wersja GLEW: " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << "Wersja VENDOR: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Wersja REDERER: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Wersja GL: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Wersja GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void Keyboard(unsigned char key, int x, int y)
{
	float value = 0.1;

	if (key == 'w')
	{
		pozycjaKameryY += value;
	}
	else
	{
		if (key == 's')
		{
			pozycjaKameryY -= value;
		}
		else
		{
			if (key == 'a')
			{
				pozycjaKameryX -= value;
			}
			else
			{
				if (key == 'd')
				{
					pozycjaKameryX += value;
				}
				else
				{
					if (key == 'q')
					{
						pozycjaKameryZ -= value;
					}
					else
					{
						if (key == 'e')
						{
							pozycjaKameryZ += value;
						}
						else
						{
							if (key == 'i')
							{
								okoKameryY -= value;
							}
							else
							{
								if (key == 'k')
								{
									okoKameryY += value;
								}
								else
								{
									if (key == 'j')
									{
										okoKameryX += value;
									}
									else
									{
										if (key == 'l')
										{
											okoKameryX -= value;
										}
										else
										{
											if (key == 'z')
											{
												glutLeaveMainLoop();
											}
											else
											{
												if (key == 'x')
												{
													glutFullScreen();
												}
												else
												{
													if (key == 'c')
													{
														glutReshapeWindow(786, 786);
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

int main(int argc, char** argv)
{
	std::cout << "STEROWANIE KAMERA:\n";
	std::cout << "Przejscie do trybu pelnego ekranu - x\n";
	std::cout << "Opuszczenie trybu pelnego ekranu - c\n";
	std::cout << "Wyjscie z programu - z\n";
	std::cout << "Przemieszczanie kamery:\n";
	std::cout << "\tlewo\t- a\n";
	std::cout << "\tprawo\t- d\n";
	std::cout << "\tgora\t- w\n";
	std::cout << "\tdol\t- s\n";
	std::cout << "\tprzod\t- q\n";
	std::cout << "\ttyl\t- e\n";
	std::cout << "Obrot kamery:\n";
	std::cout << "\tlewo\t- j\n";
	std::cout << "\tprawo\t- l\n";
	std::cout << "\tgora\t- i\n";
	std::cout << "\tdol\t- k\n\n";

	ProgramMPGK obiektMPGK(786, 786, 100, 100);

	obiektMPGK.stworzenieOkna(argc, argv);
	obiektMPGK.inicjalizacjaGlew();
	obiektMPGK.sprawdzenieWersji();
	obiektMPGK.stworzenieVAO();
	obiektMPGK.stworzenieVBO();
	obiektMPGK.stworzenieIBO();
	obiektMPGK.stworzenieProgramu();
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(obiektMPGK.wyswietl);
	glutIdleFunc(obiektMPGK.wyswietl);
	glutCloseFunc(obiektMPGK.usun);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glutMainLoop();

	//system("pause");
	return 0;
}
