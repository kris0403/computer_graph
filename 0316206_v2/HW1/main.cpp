#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "glut.h"
#include "mesh.h"
using namespace std;
class sc
{
public:
	sc::sc()
	{
		fstream scene_file;//讀scene_file
		scene_file.open("scene.scene");
		//scene_file.open("scene2.scene");
		char scene[100];
		if (!scene_file){//如果開啟檔案失敗，fp為0；成功，fp為非0
			cout << "Fail to open file: " << "scene.scene" << endl;
		}
		object_num = 0;
		while (!scene_file.eof())//TO DO
		{
			scene_file >> scene;
			scene_file >> scene;
			obj_file_name[object_num] = scene;
			object[object_num] = new mesh(scene);
			for (int i = 0; i < 10; i++)
			{
				scene_file >> scene;
				num[object_num][i] = atof(scene);
			}
			object_num++;
		}
		object_num--;//object_num會多1
		scene_file.close();//讀完scene_file
	}
	string get_obj_file_name(int i)
	{
		return obj_file_name[i];
	}
	double get_num(int i, int j)
	{
		return num[i][j];
	}
	mesh* get_object(int i)
	{
		return object[i];
	}
	int get_object_num()
	{
		return object_num;
	}
	void change_num_tx(int i,int j)
	{
		num[i][7] = j;
	}
	void change_num_ty(int i, int j)
	{
		num[i][8] = j;
	}
	void set_start_x_y(int i, int j)
	{
		start_x = i;
		start_y = j;
	}
	int get_start_x()
	{
		return start_x;
	}
	int get_start_y()
	{
		return start_y;
	}
	void set_key_num(int k)
	{
		key_num = k;
	}
	int get_key_num()
	{
		return key_num;
	}
	void move(int a, int b, int w, int h)
	{
		if (key_num >= 0)
		{
			num[key_num][7] += (a - start_x) / (double)13;
			num[key_num][8] -= (b - start_y) / (double)13;
			
		}

	}
private:
	string obj_file_name[100];//obj_file_name
	double num[100][10];//各個scene數值
	mesh *object[100];
	int object_num;//有幾個object
	int key_num;
	int start_x;
	int start_y;
};
sc s;
class vi
{
	public:
		vi::vi()
		{
			fstream view_file;//讀view_file
			char view_name[] = "view.view";
			//char view_name[] = "scene2.view";
			view_file.open(view_name, ios::in);
			char temp[100];
			string view[23];
			float view_num[23];
			if (!view_file){//如果開啟檔案失敗，fp為0；成功，fp為非0
				cout << "Fail to open file: " << view_name << endl;
			}
			for (int i = 0; i < 23; i++)
			{
				view_file >> temp;
				if (i == 0 || i == 4 || i == 8 || i == 12 || i == 14 || i == 16 || i == 18)
				{
					view[i] = temp;
				}
				else
				{
					view[i] = temp;
					view_num[i] = atof(temp);
				}
			}
			eye[0] = view_num[1];
			eye[1] = view_num[2];
			eye[2] = view_num[3];
			vat[0] = view_num[5];
			vat[1] = view_num[6];
			vat[2] = view_num[7];
			vup[0] = view_num[9];
			vup[1] = view_num[10];
			vup[2] = view_num[11];
			fovy = view_num[13];
			dnear = view_num[15];
			dfar = view_num[17];
			viewpoint[0] = view_num[19];
			viewpoint[1] = view_num[20];
			viewpoint[2] = view_num[21];
			viewpoint[3] = view_num[22];
			view_file.close();//讀完view_file
		}
		void change_fovy(int i)
		{
			fovy = i;
		}
		void change_width(GLsizei w)
		{
			viewpoint[2] = w;
		}
		void change_height(GLsizei h)
		{
			viewpoint[3] = h;
		}
		int get_viewpoint(int i)
		{
			return viewpoint[i];
		}
		double get_eye(int i)
		{
			return eye[i];
		}
		int get_vat(int i)
		{
			return vat[i];
		}
		int get_vup(int i)
		{
			return vup[i];
		}
		int get_fovy()
		{
			return fovy;
		}
		int get_dnear()
		{
			return dnear;
		}
		int get_dfar()
		{
			return dfar;
		}
		void change_eye(double x, double y, double z)
		{
			eye[0] = x;
			eye[1] = y;
			eye[2] = z;
		}
		void change_vat(int x, int y, int z)
		{
			vat[0] = x;
			vat[1] = y;
			vat[2] = z;
		}
	private:
		int viewpoint[4];
		double eye[3];
		double vat[3];
		int vup[3];
		int fovy;
		int dnear;
		int dfar;
};
vi v_i;
class li
{
public:
	li::li()
	{
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				light[i][j] = 0;
			}
		}
		fstream light_file;//讀light_file
		char light_name[] = "light.light";
		//char light_name[] = "scene2.light";
		light_file.open(light_name, ios::in);
		char line[100];
		char* te;
		light_counter = 0;
		while (light_file.getline(line, sizeof(line), '\n'))
		{
			if (line[0] == 'l')
			{
				te = strtok(line, " ");
				te = strtok(NULL, " ");
				int j = 0;
				while (te != NULL)
				{
					light[light_counter][j] = atof(te);
					j++;
					te = strtok(NULL, " ");
				}
				light_counter++;
			}
			else if (line[0] == 'a')
			{
				te = strtok(line, " ");
				int i = 0;
				while (te != NULL)
				{
					
					te = strtok(NULL, " ");
					if (te != NULL)
						ambient[i] = atof(te);
					else
					{
						break;
					}
					i++;
				}
			}
		}
		light_file.close();//讀完light_file
	}
	float get_light(int i, int j)
	{
		return light[i][j];
	}
	float* get_ambient()
	{
		return ambient;
	}
	void set_ambient(int i, float j)
	{
		ambient[i] = j;
	}
	int get_light_counter()
	{
		return light_counter;
	}
private:
	float light[100][12];
	float ambient[4];
	int light_counter;//light_counter就是現在有幾盞燈
};
li l;
void lighting()
{
	glShadeModel(GL_SMOOTH);

	// z buffer enable
	glEnable(GL_DEPTH_TEST);

	// enable lighting
	glEnable(GL_LIGHTING);

	for (int i = 0; i < l.get_light_counter(); i++)
	{
		GLfloat light_position[] = { l.get_light(i, 0), l.get_light(i, 1), l.get_light(i, 2), 1.0f };
		GLfloat light_ambient[] = { l.get_light(i, 3), l.get_light(i, 4), l.get_light(i, 5), 1.0f };
		GLfloat light_diffuse[] = { l.get_light(i, 6), l.get_light(i, 7), l.get_light(i, 8), 1.0f };
		GLfloat light_specular[] = { l.get_light(i, 9), l.get_light(i, 10), l.get_light(i, 11), 1.0f };
		// set light property
		glEnable(GL_LIGHT0 + i);
		glLightfv(GL_LIGHT0 + i, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0 + i, GL_SPECULAR, light_specular);
		glLightfv(GL_LIGHT0 + i, GL_AMBIENT, light_ambient);
	}
	l.set_ambient(3,1.0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, l.get_ambient());
}
void display()
{
	glClearColor(0.0f,0.0f,0.0f,0.0f);//clear the buffer
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//viewing and modeling transformation
	glViewport(v_i.get_viewpoint(0), v_i.get_viewpoint(1), (GLsizei)v_i.get_viewpoint(2), (GLsizei)v_i.get_viewpoint(3));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(v_i.get_fovy(), (float)(v_i.get_viewpoint(2) / v_i.get_viewpoint(3)), v_i.get_dnear(), v_i.get_dfar());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(v_i.get_eye(0), v_i.get_eye(1), v_i.get_eye(2),//eye
		v_i.get_vat(0), v_i.get_vat(1), v_i.get_vat(2),//center
		v_i.get_vup(0), v_i.get_vup(1), v_i.get_vup(2));//up
	
	lighting();

	//glRotated(s.get_num(s.get_key_num(), 3), v_i.get_vup(0), v_i.get_vup(1), v_i.get_vup(2));

	for (int j = 0; j < s.get_object_num(); j++)
	{
		glPushMatrix();
		glTranslated(s.get_num(j, 7), s.get_num(j, 8), s.get_num(j, 9));
		glRotated(s.get_num(j, 3), s.get_num(j, 4), s.get_num(j, 5), s.get_num(j, 6));
		glScaled(s.get_num(j, 0), s.get_num(j, 1), s.get_num(j, 2));

		int lastMaterial = -1;
		for (size_t i = 0; i < s.get_object(j)->fTotal; ++i)
		{
			// set material property if this face used different material
			if (lastMaterial != s.get_object(j)->faceList[i].m)
			{
				lastMaterial = (int)s.get_object(j)->faceList[i].m;
				glMaterialfv(GL_FRONT, GL_AMBIENT, s.get_object(j)->mList[lastMaterial].Ka);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, s.get_object(j)->mList[lastMaterial].Kd);
				glMaterialfv(GL_FRONT, GL_SPECULAR, s.get_object(j)->mList[lastMaterial].Ks);
				glMaterialfv(GL_FRONT, GL_SHININESS, &s.get_object(j)->mList[lastMaterial].Ns);
				//you can obtain the texture name by object->mList[lastMaterial].map_Kd
				//load them once in the main function before mainloop
				//bind them in display function here
			}
			glBegin(GL_TRIANGLES);
			for (size_t tt = 0; tt<3; ++tt)
			{
				//textex corrd. s.get_object(j)->tList[s.get_object(j)->faceList[i][tt].t].ptr;
				//glTexCoord2fv(s.get_object(j)->tList[s.get_object(j)->faceList[i][tt].t].ptr);
				glNormal3fv(s.get_object(j)->nList[s.get_object(j)->faceList[i][tt].n].ptr);
				glVertex3fv(s.get_object(j)->vList[s.get_object(j)->faceList[i][tt].v].ptr);
			}
			glEnd();
		}
		glPopMatrix();
	}
	glutSwapBuffers();
	glutPostRedisplay();
}
void reshape(GLsizei w, GLsizei h)
{
	v_i.change_width(w);
	v_i.change_height(h);
}
float normalize(float x, float y, float z)
{
	
	return sqrtf(pow(x, 2)+pow(y, 2)+pow(z, 2));
}
void mouse(int button,int state,int x,int y)
{
	int ke = s.get_key_num();
	s.set_start_x_y(s.get_num(ke, 7), s.get_num(ke, 8));
	if (button == GLUT_LEFT_BUTTON)
	{
		/*if (state == GLUT_UP)
		{
			s.set_start_x_y(-1, -1);
		}
		else */if (state == GLUT_DOWN)
		{
			s.set_start_x_y(x, y);
		}
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		/*if (state == GLUT_UP)
		{
			s.set_start_x_y(-1, -1);
		}
		else*/ if (state == GLUT_DOWN)
		{
			s.set_start_x_y(x, y);
		}
	}
	/*if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			s.set_start_x_y(-x, y);
		}
		else if (state == GLUT_DOWN)
		{
			s.set_start_x_y(-x, -y);
		}
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			s.set_start_x_y(x, y);
		}
		else if (state == GLUT_DOWN)
		{
			s.set_start_x_y(x, -y);
		}
	}*/
	
}
void mouse_motion(int x, int y)
{
	int ke = s.get_key_num();
	s.move(x, y, v_i.get_viewpoint(2), v_i.get_viewpoint(3));
	s.set_start_x_y(x, y);
	//glutPostRedisplay();//display did
}
#define pi 3.1415926
void keyboard(unsigned char key, int x, int y)
{
	double theta = 30*pi/180;
    double x_i, y_i, z_i;
	switch (key)
	{
		case 'w'://zoom in
			x_i = v_i.get_vat(0) - v_i.get_eye(0);
			y_i = v_i.get_vat(1) - v_i.get_eye(1);
			z_i = v_i.get_vat(2) - v_i.get_eye(2);
			v_i.change_eye(v_i.get_eye(0) + x_i / 4, v_i.get_eye(1) + y_i / 4, v_i.get_eye(2) + z_i / 4);
			break;
		case 'a'://move left
			x_i = (v_i.get_eye(0)*cos(theta) + v_i.get_eye(2)*sin(theta));
			y_i = v_i.get_eye(1);
			z_i = (v_i.get_eye(2)*cos(theta) - v_i.get_eye(0)*sin(theta));
			v_i.change_eye(x_i, y_i, z_i);
			break;
		case 's'://zoom out
			x_i = v_i.get_vat(0) - v_i.get_eye(0);
			y_i = v_i.get_vat(1) - v_i.get_eye(1);
			z_i = v_i.get_vat(2) - v_i.get_eye(2);
			v_i.change_eye(v_i.get_eye(0) - x_i / 4, v_i.get_eye(1) - y_i / 4, v_i.get_eye(2) - z_i / 4);
			break;
		case 'd'://move right
			x_i = v_i.get_eye(0)*cos((-1)*theta) + v_i.get_eye(2)*sin((-1)*theta);
			y_i = v_i.get_eye(1);
			z_i = (-1)*v_i.get_eye(0)*sin((-1)*theta) + v_i.get_eye(2)*cos((-1)*theta);
			v_i.change_eye(x_i, y_i, z_i);
			break;
		case '1':
			s.set_key_num('1' - '0' - 1);
			break;
		case '2':
			s.set_key_num('2' - '0' - 1);
			break;
		case '3':
			s.set_key_num('3' - '0' - 1);
			break;
		case '4':
			s.set_key_num('4' - '0' - 1);
			break;
		case '5':
			s.set_key_num('5' - '0' - 1);
			break;
		case '6':
			s.set_key_num('6' - '0' - 1);
			break;
		case '7':
			s.set_key_num('7' - '0' - 1);
			break;
		case '8':
			s.set_key_num('8' - '0' - 1);
			break;
		case '9':
			s.set_key_num('9' - '0' - 1);
			break;
		default:
			break;
	}
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Planet");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouse_motion);
	glutMainLoop();
	return 0;
	system("pause");
}
