#define GL_GLEXT_PROTOTYPES

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "render.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"



GLuint vbo[4];		//identyfikatory buforow wierzcholkow
GLuint vao[2];		//identyfikatory tablic wierzcholkow
GLuint ebo;		//identyfikator bufora elementow

GLuint shaderProgram;
GLint vertexShader;	//identyfikator shadera wierzcholkow
GLint fragmentShader;   //identyfikator shadera fragmentow
GLint posAttrib, colAttrib;	//

glm::mat4 viewMatrix = glm::mat4();
glm::mat4 projectionMatrix = glm::mat4(); //marzerz widoku i rzutowania
GLfloat fi = 0;


//-------------Atrybuty wierzcholkow------------------------------------------

	GLfloat ver_triangle[] = {	//wspolrzedne wierzcholkow trojkata
		 0.0f,  1.0f, 0.0,
		 1.0f,  0.0f, 0.0,
		-1.0f,  0.0f, 0.0
	};

	GLfloat col_triangle[] = {	//kolory wierzcholkow trojkata
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	GLfloat ver_rectangle[] = {	//wspolrzedne wierzcholkow prostokata
		 0.5f,  0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
	};

	GLfloat col_rectangle[] = {	//kolory wierzcholkow prostokata
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f
	};

	GLuint elements[] = { //prostokat skladamy z dwoch trojkatow
		0, 1, 2,		  //indeksy wierzcholkow dla pierwszego trojkata
		0, 2, 3,			  //indeksy wierzcholkow dla drugiego trojkata

    0,1,4,
    1,4,5,

    0,3,4,
    3,4,7,

    2,3,6,
    3,6,7,

    1,2,5,
    2,5,6,

    4,5,6,
    4,6,7
	};

  GLfloat ver_pipe[78];
  GLfloat col_pipe[78];
	

//----------------------------kod shadera wierzcholkow-----------------------------------------

const GLchar* vShader_string =
{
  "#version 130\n"\

  "in vec3 position;\n"\
  "in vec3 color;\n"\
  "out vec3 Color;\n"\
  "uniform mat4 transformMatrix;\n"\
  "void main(void)\n"\
  "{\n"\
  "  gl_Position = transformMatrix * vec4(position, 1.0);\n"\
  "  Color = color;\n"\
  "}\n"
};

//----------------------------kod shadera fragmentow-------------------------------------------
const GLchar* fShader_string =
{
  "#version 130\n"\
  "in  vec3 Color;\n"\
  "out vec4 outColor;\n"\

  "void main(void)\n"\
  "{\n"\
  "  outColor = vec4(Color, 1.0);\n"\
  "}\n"
};


//------------------------------------------------zmiana rozmiaru okna---------------------------

void resizeGLScene(unsigned int width, unsigned int height)
{
    if (height == 0) height = 1; // zabezpiecznie dla okna o zerowej wysokosci
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
}


//----------------------------------tworzenie, wczytanie, kompilacja shaderow-------------------------

int initShaders(void)
{
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShader_string, NULL);
    glCompileShader(vertexShader);
    
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (status == GL_TRUE)
      std::cout << "Kompilacja shadera wierzcholkow powiodla sie!\n";
    else
    {
      std::cout << "Kompilacja shadera wierzcholkow NIE powiodla sie!\n";
      return 0;
     }
     
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShader_string, NULL); 
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (status == GL_TRUE)
      std::cout << "Kompilacja shadera fragmentow powiodla sie!\n";
    else
    {
      std::cout << "Kompilacja shadera fragmentow NIE powiodla sie!\n";
      return 0;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    
    //glBindFragDataLocation(shaderProgram, 0, "outColor"); 

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    return 1;
}



//--------------------------------------------funkcja inicjujaca-------------------------------------
int initGL(void)
{
  int mul = 0;
   for (int i = 0; i < 72; i+=3)
   {
    ver_pipe[i] = 0.5*sin(mul*M_PI/6);
    ver_pipe[i+1] = 0.5*cos(mul*M_PI/6);
    if (i%2==0) {
      ver_pipe[i+2] = -0.5f;

      col_pipe[i] = 1.0f;
      col_pipe[i+1] = 0.0f;
      col_pipe[i+2] = 0.0f;
    }
    else {
      ver_pipe[i+2] = 0.5f;
      mul++;

      col_pipe[i] = 0.0f;
      col_pipe[i+1] = 0.0f;
      col_pipe[i+2] = 1.0f;
    }
   }
   ver_pipe[72] = 0.5*sin(0.0);
   ver_pipe[73] = 0.5*cos(0.0);
   ver_pipe[74] = -0.5f;
   ver_pipe[75] = 0.5*sin(0.0);
   ver_pipe[76] = 0.5*cos(0.0);
   ver_pipe[77] = 0.5f;

   col_pipe[72] = 1.0f;
   col_pipe[73] = 0.0f;
   col_pipe[74] = 0.0f;
   col_pipe[75] = 0.0f;
   col_pipe[76] = 0.0f;
   col_pipe[77] = 1.0f;
   


    if(initShaders())
    {   

      glEnable(GL_DEPTH_TEST);
      glDepthFunc(GL_LEQUAL); 
      glGenVertexArrays(2, vao); //przypisanie do vao identyfikatorow tablic
      glGenBuffers(4, vbo);	   //przypisanie do vbo identyfikatorow buforow
      glGenBuffers(1, &ebo);

      posAttrib = glGetAttribLocation(shaderProgram, "position"); //pobranie indeksu tablicy atrybutow wierzcholkow okreslajacych polozenie
            glEnableVertexAttribArray(posAttrib);
      colAttrib = glGetAttribLocation(shaderProgram, "color");    //pobranie indeksu tablicy atrybutow wierzcholkow okreslajacych kolor
            glEnableVertexAttribArray(colAttrib);
      
      glBindVertexArray(vao[0]);					//wybor tablicy
        
      glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); 							//powiazanie bufora z odpowiednim obiektem (wybor bufora) 
      glBufferData(GL_ARRAY_BUFFER, sizeof(ver_pipe), ver_pipe, GL_STATIC_DRAW); 	//skopiowanie danych do pamieci aktywnego bufora
      glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				//okreslenie organizacji danych w tablicy wierzcholkow
      glEnableVertexAttribArray(posAttrib);							//wlaczenie tablicy
      
      glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(col_pipe), col_pipe, GL_STATIC_DRAW);
      glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(colAttrib);
      
      glBindVertexArray(vao[1]);

      glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(ver_rectangle), ver_rectangle, GL_STATIC_DRAW);
      glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(posAttrib);

      glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(col_rectangle), col_rectangle, GL_STATIC_DRAW);
      glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(colAttrib);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
            
      //macierz widoku (okresla polozenie kamery i kierunek w ktorym jest skierowana) 
      viewMatrix = glm::lookAt(glm::vec3(0.0f, 3.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)); 
      //macierz rzutowania perspektywicznego
      projectionMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 1.0f, 10.0f);		

 	    return 1;
    }
    else
	    return 0;
}

//------------------------------------------renderowanie sceny-------------------------------------

void pyramid(int n, glm::mat4 current_trans_matrix, float fi) {
  glBindVertexArray(vao[0]);
  //glDrawArrays(GL_TRIANGLE_STRIP, 0, 26); //rysowanie trojkata

  glm::mat4 scale;
  glm::mat4 trans;
  glm::mat4 rot;
  glm::mat4 btr = current_trans_matrix;
  glm::mat4 tr;

  for (int i = 0; i < n; i++) {
    float s = 1.0f/(1.5f);
    scale = glm::scale(glm::mat4(), glm::vec3(s, s, s));
    trans = glm::translate(glm::mat4(), glm::vec3(0.0f, s+0.5f, 0.0f));
    rot = glm::rotate(glm::mat4(), glm::radians(fi), glm::vec3(0.0f, 1.0f, 0.0f));
    fi += 0.5f;

    tr = btr * scale * trans * rot;
    btr = tr;

    GLint transformMatrixUniformLocation = glGetUniformLocation(shaderProgram, "transformMatrix");  
    glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(tr)); 

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 26); //rysowanie trojkata

  }
}


int drawGLScene(int counter)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    glm::mat4 translationMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));  		//macierz przesuniecia o zadany wektor
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(), glm::radians(fi), glm::vec3(0.0f, 1.0f, 0.0f)); //macierz obrotu o dany kat wokol wektora
		
    glm::mat4 transformMatrix = projectionMatrix * viewMatrix * translationMatrix ; //wygenerowanie macierzy uwzgledniajacej wszystkie transformacje


    GLint transformMatrixUniformLocation = glGetUniformLocation(shaderProgram, "transformMatrix");  //pobranie polozenia macierzy bedacej zmienna jednorodna shadera
    glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix)); //zapisanie macierzy bedacej zmienna jednorodna shadera wierzcholkow
    

    //glBindVertexArray(vao[0]);
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 26); //rysowanie trojkata
    pyramid(7, transformMatrix, fi);

    float s = 1.0f/(1.5f);
    glm::mat4 b = transformMatrix * glm::scale(glm::mat4(), glm::vec3(s, s, s)) * glm::translate(glm::mat4(), glm::vec3(0.0f, s-0.5f, 0.0f));
    transformMatrixUniformLocation = glGetUniformLocation(shaderProgram, "transformMatrix");  
    glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(b)); 

    glBindVertexArray(vao[1]);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); //rysowanie prostokata

    fi += 0.5;
 
    glFlush();

    return 1;    
}

//----------------------------------------------------porzadki--------------------------------------

void deleteAll()
{
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glDeleteBuffers(4, vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(2, vao);
}
