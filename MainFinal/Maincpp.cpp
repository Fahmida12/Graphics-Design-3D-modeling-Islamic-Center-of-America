#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<Windows.h>
#include<GL/glut.h>

#define PI 3.1416

double cameraAngle, cameraAngleDelta;
int canDrawGrid;

double cameraHeight;	
double cameraRadius;

int num_texture  = -1;

GLuint cylimg, ballimg, ballimg2, grassimg, grassimg2, grassimg3, grassimg4, wallimg, stimg, wimg, door, door2, door3, wall, up , Gimg , Road, Road2,Road3, Cimg ,
		up2, up3, skyimg, skyimg2, winimg , Lightimg1, Lightimg2, Lightimg3, woodimg;



int kochLevel;

double x,y,direction;

void reset(){

	x=0;
	y=0;
	direction = 0;

}

void leftRotate(double angle){

	direction +=angle;
}

void rightRotate(double angle){

	direction -=angle;
}

void drawStraightline(double length){


	double newx,newy;
	newx = x + length*cos(PI*direction/180);
	newy = y + length*sin(PI*direction/180);
	glBegin(GL_LINES);{

		glVertex2f(x,y);
		glVertex2f(newx,newy);

	}glEnd();

	x=newx;
	y=newy;

}

void drawkochCurve(double order, double length)

{
	if(order==0)
		drawStraightline(length);
	else{

		drawkochCurve(order-1,length/3.0);
		leftRotate(60);
		drawkochCurve(order-1,length/3.0);
		rightRotate(120);
		drawkochCurve(order-1,length/3.0);
		leftRotate(60);
		drawkochCurve(order-1,length/3.0);
	}
}

void drawSnowFlake(int order){

	drawkochCurve(order,15);
	rightRotate(120);
	drawkochCurve(order,15);
	rightRotate(120);
	drawkochCurve(order,15);

}


int LoadBitmapImage(char *filename)
{
    int i, j=0;
    FILE *l_file;
    unsigned char *l_texture;

    BITMAPFILEHEADER fileheader;
    BITMAPINFOHEADER infoheader;
    RGBTRIPLE rgb;

    num_texture++;

    if( (l_file = fopen(filename, "rb"))==NULL) return (-1);

    fread(&fileheader, sizeof(fileheader), 1, l_file);

    fseek(l_file, sizeof(fileheader), SEEK_SET);
    fread(&infoheader, sizeof(infoheader), 1, l_file);

    l_texture = (byte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
    memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);
	for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)
		{
				fread(&rgb, sizeof(rgb), 1, l_file);

				l_texture[j+0] = rgb.rgbtRed;
				l_texture[j+1] = rgb.rgbtGreen;
				l_texture[j+2] = rgb.rgbtBlue;
				l_texture[j+3] = 255;
				j += 4;
		}
    fclose(l_file);

    glBindTexture(GL_TEXTURE_2D, num_texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    free(l_texture);

    return (num_texture);

}

void loadImage()
{
	skyimg= LoadBitmapImage("image/sky2.bmp");
	woodimg = LoadBitmapImage("image/wood2.bmp");
	//winimg= LoadBitmapImage("image/gggll2.bmp");
	//winimg= LoadBitmapImage("image/gl5555.bmp");
	winimg= LoadBitmapImage("image/G_4.bmp");
	Lightimg1 = LoadBitmapImage("image/LL5.bmp");
	Lightimg2 = LoadBitmapImage("image/LL2.bmp");
	Lightimg3 = LoadBitmapImage("image/LL10.bmp");
	grassimg = LoadBitmapImage("image/grass.bmp");
	grassimg2 = LoadBitmapImage("image/gr6.bmp");
	grassimg3 = LoadBitmapImage("image/gr12.bmp");
	grassimg4 = LoadBitmapImage("image/gr13.bmp");
	wallimg = LoadBitmapImage("image/waL33.bmp");
	cylimg = LoadBitmapImage("image/W66.bmp");
	Cimg= LoadBitmapImage("image/a22.bmp");
	ballimg = LoadBitmapImage("image/GL77.bmp");
	ballimg2 = LoadBitmapImage("image/ffd.bmp");
	Gimg = LoadBitmapImage("image/G_4.bmp");
	stimg = LoadBitmapImage("image/a28.bmp");
	wimg = LoadBitmapImage("image/a28.bmp");
	up = LoadBitmapImage("image/a21.bmp");
	up2 = LoadBitmapImage("image/a31.bmp");
	up3 = LoadBitmapImage("image/a22.bmp");
	door = LoadBitmapImage("image/mm3.bmp");
	door2 = LoadBitmapImage("image/dor4.bmp");
	door3 = LoadBitmapImage("image/dor1.bmp");
	wall = LoadBitmapImage("image/ww4.bmp");
	Road = LoadBitmapImage("image/rr2.bmp");
	Road2 = LoadBitmapImage("image/rr77.bmp");
	Road3 = LoadBitmapImage("image/a18.bmp");
	printf("Load successful");
}

//sky

void Sky(double x, double y, double z){

//full	

	glPushMatrix();{
	//glColor3f(.34,.456,.101);//rgb(87,116,26)
		glTranslatef(0,670,0);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,skyimg);

		glBegin(GL_QUADS);{
			//glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(0,0);
			glVertex3f(-5000,0,-5000);
			glTexCoord2f(0,1);
			glVertex3f(5000,0,-5000);
			glTexCoord2f(1,0);
			glVertex3f(5000,0,5000);
			glTexCoord2f(1,1);
			glVertex3f(-5000,0,5000);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//front

	glPushMatrix();{

		glTranslatef(0,660,-390);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,skyimg);

		glBegin(GL_QUADS);{
	
			glTexCoord2f(0,0);
			glVertex3f(-2000,0,-100);
			glTexCoord2f(0,1);
			glVertex3f(2000,0,-100);
			glTexCoord2f(1,0);
			glVertex3f(2000,0,2000);
			glTexCoord2f(1,1);
			glVertex3f(-2000,0,2000);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

}

//side sky

void sideSky1(double x, double y, double z){

	//left

		glPushMatrix();{

		glTranslatef(-1500,2000,0);
		glRotatef(90,0,0,1);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,skyimg);

		glBegin(GL_QUADS);{
		
			glTexCoord2f(0,0);
			glVertex3f(-4000,0,-5000);
			glTexCoord2f(0,1);
			glVertex3f(4000,0,-5000);
			glTexCoord2f(1,0);
			glVertex3f(4000,0,5000);
			glTexCoord2f(1,1);
			glVertex3f(-4000,0,5000);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

}

/////////// Field 

void Field(double x, double y, double z){

glPushMatrix();{

	glColor3f(.34,.456,.101);//rgb(87,116,26)
	glTranslatef(0,0,1);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,grassimg);

	glBegin(GL_QUADS);{
		//glColor3f(1.0f,1.0f,1.0f); 
		glTexCoord2f(0,0);
        glVertex3f(-660,-620,0);
		glTexCoord2f(0,1);
        glVertex3f(660,-620,0);
		glTexCoord2f(1,0);
        glVertex3f(660,650,0);
		glTexCoord2f(1,1);
        glVertex3f(-660,650,0);
	}glEnd();

	glDisable(GL_TEXTURE_2D);

}glPopMatrix();

}
///Road

void Road_flor(double x, double y, double z){

		glPushMatrix();{
			
			glColor3f(1,1,1);
			glTranslatef(0,0,.5);
			glScalef(170,158,0);
			glutSolidCube(.2);
	
		}glPopMatrix();

//middle

		glPushMatrix();{

			//glColor3f(.34,.456,.101);//rgb(87,116,26)
			glTranslatef(0,0,1.5);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,Road3);

			glBegin(GL_QUADS);{
				//glColor3f(1.0f,1.0f,1.0f); 
				glTexCoord2f(0,0);
				glVertex3f(-85,-420,0);
				glTexCoord2f(0,1);
				glVertex3f(85,-420,0);
				glTexCoord2f(1,0);
				glVertex3f(85,180,0);
				glTexCoord2f(1,1);
				glVertex3f(-85,180,0);
			}glEnd();

				glDisable(GL_TEXTURE_2D);

		}glPopMatrix();

//front

	glPushMatrix();{

		//glColor3f(.34,.456,.101);//rgb(87,116,26)
		glTranslatef(0,-520,1.5);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,Road);

		glBegin(GL_QUADS);{
			//glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(0,0);
			glVertex3f(-660,-100,0);
			glTexCoord2f(0,1);
			glVertex3f(660,-100,0);
			glTexCoord2f(1,0);
			glVertex3f(660,100,0);
			glTexCoord2f(1,1);
			glVertex3f(-660,100,0);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//side 1

	glPushMatrix();{

		//glColor3f(.34,.456,.101);//rgb(87,116,26)
		glTranslatef(-110,0,1.5);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,Road2);

		glBegin(GL_QUADS);{
			//glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(0,0);
			glVertex3f(-14,-420,0);
			glTexCoord2f(0,1);
			glVertex3f(14,-420,0);
			glTexCoord2f(1,0);
			glVertex3f(14,160,0);
			glTexCoord2f(1,1);
			glVertex3f(-14,160,0);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//side 2

	glPushMatrix();{

		//glColor3f(.34,.456,.101);//rgb(87,116,26)
		glTranslatef(110,0,1.5);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,Road2);

		glBegin(GL_QUADS);{
			//glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(0,0);
			glVertex3f(-14,-420,0);
			glTexCoord2f(0,1);
			glVertex3f(14,-420,0);
			glTexCoord2f(1,0);
			glVertex3f(14,160,0);
			glTexCoord2f(1,1);
			glVertex3f(-14,160,0);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

/// side border right

	glPushMatrix();{
			
			glColor3f(.9,.9,.9);
			glTranslatef(370,-415,3);
			glScalef(585,10,9);
			glutSolidCube(1);
	
	}glPopMatrix();

/// side border left

	glPushMatrix();{
			
			glColor3f(.9,.9,.9);
			glTranslatef(-370,-415,3);
			glScalef(585,10,9);
			glutSolidCube(1);
	
	}glPopMatrix();

}

//// Garden 1

void Garden(double x, double y, double z){

	glTranslatef(x,y,z);
					GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,grassimg2);

		glTranslatef(-43,-70,15);
		glScalef(1,2.5,0);

		glBegin(GL_QUADS);{
		
			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(0,1);
			glVertex3f(-15,2,0);
			glTexCoord2f(0,0);
			glVertex3f(-15,-2.5,0);
			glTexCoord2f(1,0);
			glVertex3f(17,-2.5,0);
			glTexCoord2f(1,1);
			glVertex3f(17,2,0);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//flower 1

glPushMatrix();{
	
	glColor3f(1,1,.8);
	glTranslatef(-33,-71.5,15);
	glRotatef(95,3,0,0);
	glutSolidDodecahedron();

}glPopMatrix();

//flower 2

	glPushMatrix();{
	
	glColor3f(1,0,.4);
	glTranslatef(-40,-73,15);
	//glRotatef(95,3,0,0);
	glutSolidDodecahedron();

}glPopMatrix();

//flower 3

glPushMatrix();{
	
	glColor3f(1,.8,0);
	glTranslatef(-47,-71.5,15);
	glRotatef(95,3,0,0);
	glutSolidDodecahedron();

}glPopMatrix();

//flower 4

glPushMatrix();{
	
	glColor3f(1,.2,.4);
	glTranslatef(-54,-73,15);
	glRotatef(95,3,0,0);
	glutSolidDodecahedron();

}glPopMatrix();

}

//// Garden  2

void Garden_2(double x, double y, double z){

	glTranslatef(x,y,z);
					GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,grassimg3);

		glTranslatef(-42.5,-80,9);
		glScalef(1,2.5,0);

		glBegin(GL_QUADS);{
		
			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(0,1);
			glVertex3f(-14,2,0);
			glTexCoord2f(0,0);
			glVertex3f(-14,-4,0);
			glTexCoord2f(1,0);
			glVertex3f(13,-4,0);
			glTexCoord2f(1,1);
			glVertex3f(13,2,0);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//flower 1

glPushMatrix();{
	
	glColor3f(1,1,.4);
	glTranslatef(-33,-81.5,9);
	glRotatef(95,3,0,0);
	glutSolidDodecahedron();

}glPopMatrix();

//flower 2

	glPushMatrix();{
	
	glColor3f(.8,0,0);
	glTranslatef(-40,-83,9);
	//glRotatef(95,3,0,0);
	glutSolidDodecahedron();

}glPopMatrix();

//flower 3

glPushMatrix();{
	
	glColor3f(1,1,.8);
	glTranslatef(-47,-81.5,9);
	glRotatef(95,3,0,0);
	glutSolidDodecahedron();

}glPopMatrix();

//flower 4

glPushMatrix();{
	
	glColor3f(1,.4,0);
	glTranslatef(-54,-83,9);
	glRotatef(95,3,0,0);
	glutSolidDodecahedron();

}glPopMatrix();

}

/////// Tree

void Tree(double x, double y, double z){

	glTranslatef(x,y,z);
					GLUquadricObj *quadric = gluNewQuadric();
/// tree low part

	glPushMatrix();{

		glColor3f(.9,.9,.9); 
		glTranslatef(330,-20,0);	
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,woodimg);  
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);

		gluCylinder(cylinder_obj,9,2, 110, 20, 20);

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

/// tree up part 1

	glPushMatrix();{

		glColor3f(.9,.9,.9); 
		glTranslatef(330,-20,70);	
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,grassimg2);  
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);

		gluCylinder(cylinder_obj,40,.2, 50, 20, 20);

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

/// tree up part 2

	glPushMatrix();{

		glColor3f(.9,.9,.9); 
		glTranslatef(330,-20,85);	
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,grassimg2);  
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);

		gluCylinder(cylinder_obj,35,.2, 50, 20, 20);

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

/// tree up part 3

	glPushMatrix();{

		glColor3f(.9,.9,.9); 
		glTranslatef(330,-20,100);	
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,grassimg2);  
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);

		gluCylinder(cylinder_obj,30,.2, 50, 20, 20);

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

/// tree up part 4

	glPushMatrix();{

		glColor3f(.9,.9,.9); 
		glTranslatef(330,-20,115);	
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,grassimg2);  
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);

		gluCylinder(cylinder_obj,25,.2, 50, 20, 20);

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

/// tree up part 5

	glPushMatrix();{

		glColor3f(.9,.9,.9); 
		glTranslatef(330,-20,130);	
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,grassimg2);  
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);

		gluCylinder(cylinder_obj,20,.2, 45, 20, 20);

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

}

/// Light Post

void Light_post(double x, double y, double z){

	glTranslatef(x,y,z);
					GLUquadricObj *quadric = gluNewQuadric();

//cylinder low

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 

		glTranslatef(110,-170,0);
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,Lightimg3);  
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);
		gluCylinder(cylinder_obj,4,2,7, 20, 20);
		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//cylinder up

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 

		glTranslatef(110,-170,0);
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,Lightimg1);  
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);
		gluCylinder(cylinder_obj,1.5,1.5, 88, 20, 20);
		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

/// sphere 

	glPushMatrix();{

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		glColor4f(1,1,1,.8);
		glTranslatef(110,-170,95);

		glutSolidSphere(8,10,3);

	}glPopMatrix();

/// Light sphere 

	glPushMatrix();{

		if(canDrawGrid==1)
		{
			glColor3f(1,1,1);
		}
		else
		{
			glColor3f(1,1,.4);
		
		}

		
		glTranslatef(110,-170,92);

		glutSolidSphere(5.5,15,17);

	}glPopMatrix();

}

//// Main Gate

void Main_gate(double x, double y, double z){

//right

	glPushMatrix();{
			
			glColor3f(.9,.9,.9);
			glTranslatef(70,-415,50);
			glScalef(8,8,95);
			glutSolidCube(1);
	
	}glPopMatrix();

/// design sphere bottom right

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,Lightimg1);

		GLUquadricObj *qObj = gluNewQuadric();	
		gluQuadricTexture(qObj, GL_TRUE);

		glTranslatef(70,-415,50);
		gluSphere(qObj, 8, 10, 3);

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

/// design sphere top right

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,Lightimg1);

		GLUquadricObj *qObj = gluNewQuadric();	
		gluQuadricTexture(qObj, GL_TRUE);

		glTranslatef(70,-415,101);
		gluSphere(qObj, 4, 15, 17);

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

/// cyl design right

	glPushMatrix();{

		glColor3f(.9,.9,.9); 
		glTranslatef(50,-415,105);	
		glRotatef(-60,0,1,0);
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,Lightimg2);  
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);

		gluCylinder(cylinder_obj,2,1, 50, 20, 20);

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//left

	glPushMatrix();{
			
			glColor3f(.9,.9,.9);
			glTranslatef(-70,-415,50);
			glScalef(8,8,95);
			glutSolidCube(1);
	
	}glPopMatrix();

/// design sphere bottom left

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,Lightimg1);

		GLUquadricObj *qObj = gluNewQuadric();	
		gluQuadricTexture(qObj, GL_TRUE);

		glTranslatef(-70,-415,50);
		gluSphere(qObj, 8, 10, 3);

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

/// design sphere 2 top left

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,Lightimg1);

		GLUquadricObj *qObj = gluNewQuadric();	
		gluQuadricTexture(qObj, GL_TRUE);

		glTranslatef(-70,-415,101);
		gluSphere(qObj, 4, 15, 17);

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

/// cyl design right

	glPushMatrix();{

		glColor3f(.9,.9,.9); 
		glTranslatef(-50,-415,105);		
		glRotatef(60,0,1,0);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,Lightimg2);  
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);

		gluCylinder(cylinder_obj,2,1, 50, 20, 20);

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//kochcurve middle

	glPushMatrix();{

		reset();
		glColor3f(1,1,1);
		glTranslatef(-7,-416,130);
		glRotatef(90,1,0,0);
		glLineWidth(2);
		
		drawkochCurve(6,15);

	}glPopMatrix();

//snowflake left

glPushMatrix();{

		reset();
		glColor3f(1,1,1);
		glTranslatef(-65,-417,105);
		glRotatef(90,1,0,0);
		glLineWidth(2);
		
		drawSnowFlake(7);

	}glPopMatrix();

//snowflake right

glPushMatrix();{

		reset();
		glColor3f(1,1,1);
		glTranslatef(50,-417,105);
		glRotatef(90,1,0,0);
		glLineWidth(2);
		
		drawSnowFlake(7);

	}glPopMatrix();

}

///small Gombuj low part

void Gombuj_1(double x, double y, double z){

		glTranslatef(x,y,z);
					GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,Gimg);
	
		GLUquadricObj *qObj = gluNewQuadric();
	
		gluQuadricTexture(qObj, GL_TRUE);

		glTranslatef(-43,-50,73);
		gluSphere(qObj, 12.2, 15, 17);

		glDisable(GL_TEXTURE_2D);
			
	}glPopMatrix();

}

/// small gombuj up part

void Gombuj_2(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,ballimg);

		GLUquadricObj *qObj = gluNewQuadric();
	
		gluQuadricTexture(qObj, GL_TRUE);

		double equ[4];

		glTranslatef(-43,-50,76);
		gluSphere(qObj, 12.6, 13.1, 13.1);

		glDisable(GL_TEXTURE_2D);
			
	}glPopMatrix();

}

///Big Gombuj 3 Low part

void Gombuj_3(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,Gimg);

		GLUquadricObj *qObj = gluNewQuadric();	
		gluQuadricTexture(qObj, GL_TRUE);

		glTranslatef(0,70,100);
		gluSphere(qObj, 51.3, 15, 17);

		glDisable(GL_TEXTURE_2D);
			
	}glPopMatrix();

}

/// Big Gombuj 4 up part

void Gombuj_4(double x, double y, double z){
	
	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,ballimg);
	
		GLUquadricObj *qObj = gluNewQuadric();
	
		gluQuadricTexture(qObj, GL_TRUE);
	
		glTranslatef(0,70,105);
		gluSphere(qObj, 50, 15, 17);

		glDisable(GL_TEXTURE_2D);
			
	}glPopMatrix();

}

///Top Floor Big cyl

void Top_cyl(double x, double y, double z){


	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 

		glTranslatef(0,70,90);
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,cylimg);  
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);
		gluCylinder(cylinder_obj,90, 90, 15, 25, 25);
		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

}

// Big Gombuj Low Part Cyl

void Top_cyl_2(double x, double y, double z){

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 

		glTranslatef(0,70,105);
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,Cimg);  
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);

		gluCylinder(cylinder_obj,50, 50, 10, 25, 25);
		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

}

/// Big Gombuj up cone Design

void Top_cone1(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	//cone
	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,ballimg2);

		GLUquadricObj *qObj = gluNewQuadric();
		gluQuadricTexture(qObj, GL_TRUE);

		glTranslatef(0,70,154);
		glutSolidCone(15,15,20,20);	

		glDisable(GL_TEXTURE_2D);
	
	}glPopMatrix();

///torus

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,ballimg2);

		GLUquadricObj *qObj = gluNewQuadric();	
		gluQuadricTexture(qObj, GL_TRUE);
	
		glTranslatef(0,70,153.5);

		glutSolidTorus(1,10.5,3,200);

	glDisable(GL_TEXTURE_2D);
	
	}glPopMatrix();

//cyl

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 

		glTranslatef(0,70,155);
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,ballimg);  
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);
		gluCylinder(cylinder_obj,1, 1, 30, 10, 10);
		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//ball

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,ballimg);

		GLUquadricObj *qObj = gluNewQuadric();
	
		gluQuadricTexture(qObj, GL_TRUE);
	
		glTranslatef(0,70,175);
		gluSphere(qObj, 4, 15, 17);

		glDisable(GL_TEXTURE_2D);
			
	}glPopMatrix();

}

/// Small Gombuj up Cone design

void Top_cone2(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	//cone
	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,ballimg2);

		GLUquadricObj *qObj = gluNewQuadric();
		gluQuadricTexture(qObj, GL_TRUE);

		glTranslatef(-43,-50,88.5);

		glutSolidCone(4.7,8,20,20);	

		glDisable(GL_TEXTURE_2D);
	
	}glPopMatrix();

//torus

	glPushMatrix();{
	
		glColor3f(1.0f,1.0f,1.0f); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,ballimg2);

		GLUquadricObj *qObj = gluNewQuadric();	
		gluQuadricTexture(qObj, GL_TRUE);
	
		glTranslatef(-43,-50,88);

		glutSolidTorus(1,5,3,10);

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

/////   cylinder

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 

		glTranslatef(-43,-50,90);
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,ballimg);  
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);

		gluCylinder(cylinder_obj,.3, .3, 15, 10, 10);
		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

/////   ball

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,ballimg);
	
		GLUquadricObj *qObj = gluNewQuadric();
		gluQuadricTexture(qObj, GL_TRUE);

		glTranslatef(-43,-50,101);
		gluSphere(qObj,1.7, 15, 17);

		glDisable(GL_TEXTURE_2D);
			
	}glPopMatrix();

}

//// Pillar Top cone Design

void Top_cone3(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

//cone
	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,ballimg2);

		GLUquadricObj *qObj = gluNewQuadric();
	
		gluQuadricTexture(qObj, GL_TRUE);

		glTranslatef(-220,17,221);
		glutSolidCone(15,25,20,20);	

		glDisable(GL_TEXTURE_2D);
	
	}glPopMatrix();

//torus

	glPushMatrix();{
	
		glColor3f(1.0f,1.0f,1.0f); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,ballimg2);

		GLUquadricObj *qObj = gluNewQuadric();	
		gluQuadricTexture(qObj, GL_TRUE);
	
		glTranslatef(-220,17,220.5);

		glutSolidTorus(1,10.5,3,200);

	glDisable(GL_TEXTURE_2D);

}glPopMatrix();

/// cyl

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 

		glTranslatef(-220,17,223.5);
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,ballimg);  
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);

		gluCylinder(cylinder_obj,1, 1, 40, 10, 10);

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//ball

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,ballimg);

		GLUquadricObj *qObj = gluNewQuadric();
		gluQuadricTexture(qObj, GL_TRUE);

		glTranslatef(-220,17,250);
		gluSphere(qObj, 4, 15, 17);

		glDisable(GL_TEXTURE_2D);
			
	}glPopMatrix();

}

///  Big Pillar 

void Pillar(double x, double y, double z){

		glTranslatef(x,y,z);
					GLUquadricObj *quadric = gluNewQuadric();

//low part design 1

		glPushMatrix();{

			glColor3f(1.0f,1.0f,1.0f); 

			glTranslatef(-220,17,0);
	
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,wall);  
	
			GLUquadricObj *cylinder_obj = gluNewQuadric();
			gluQuadricTexture(cylinder_obj, GL_TRUE);
			gluCylinder(cylinder_obj,20,15, 14, 25, 25);
			glDisable(GL_TEXTURE_2D);

		}glPopMatrix();


//part 1

		glPushMatrix();{

			glColor3f(1.0f,1.0f,1.0f); 

			glTranslatef(-220,17,0);
	
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,wallimg);  
	
			GLUquadricObj *cylinder_obj = gluNewQuadric();
			gluQuadricTexture(cylinder_obj, GL_TRUE);
			gluCylinder(cylinder_obj,15,15, 72, 25, 25);
			glDisable(GL_TEXTURE_2D);

		}glPopMatrix();

//part2

	glPushMatrix();{

		glColor3f(1,1,1);

		glTranslatef(-220,17,72);
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);
		gluCylinder(cylinder_obj,15,15, 10, 25, 25);
	
	}glPopMatrix();

// part 3

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 

		glTranslatef(-220,17,82);
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wallimg);  
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);
		gluCylinder(cylinder_obj,15,15, 50, 25, 25);
		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

// part 4

	glPushMatrix();{

		glColor3f(1,1,1);

		glTranslatef(-220,17,132);
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);
		gluCylinder(cylinder_obj,15,15, 7, 25, 25);

	}glPopMatrix();

// part 5

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f);

		glTranslatef(-220,17,139);
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wallimg);  
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);
		gluCylinder(cylinder_obj,15,15, 20, 25, 25);
		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

// part 6

	glPushMatrix();{

		glColor3f(1,1,1);

		glTranslatef(-220,17,159);
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);
		gluCylinder(cylinder_obj,15,18, 16, 25, 25);

	}glPopMatrix();

// part 7

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f);

		glTranslatef(-220,17,176);
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wallimg);  
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);
		gluCylinder(cylinder_obj,12,12, 18, 20, 25);
		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

// part 8

	glPushMatrix();{

		glColor3f(1,1,1);

		glTranslatef(-220,17,194);
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);
		gluCylinder(cylinder_obj,12,12, 15, 25, 25);

	}glPopMatrix();

//under cone and uper part design 

	glPushMatrix();{

		glColor3f(1,1,1);

		glTranslatef(-220,17,209);
	
		GLUquadricObj *cylinder_obj = gluNewQuadric();
		gluQuadricTexture(cylinder_obj, GL_TRUE);

		gluCylinder(cylinder_obj,12,16,7, 25, 25);

	}glPopMatrix();

//torus 1

		glPushMatrix();{
	
			glColor3f(1,1,1);

			GLUquadricObj *qObj = gluNewQuadric();
			gluQuadricTexture(qObj, GL_TRUE);
	
			glTranslatef(-220,17,10);

			glutSolidTorus(1,17,12,10);

		}glPopMatrix();

//torus 2

	glPushMatrix();{
	
		glColor3f(.87,.87,.87);

		GLUquadricObj *qObj = gluNewQuadric();
		gluQuadricTexture(qObj, GL_TRUE);
	
		glTranslatef(-220,17,80);
	
		glutSolidTorus(1,16,30,10);

	}glPopMatrix();

//torus 3

	glPushMatrix();{
	
		glColor3f(.87,.87,.87);

		GLUquadricObj *qObj = gluNewQuadric();	
		gluQuadricTexture(qObj, GL_TRUE);
	
		glTranslatef(-220,17,140);

		glutSolidTorus(1.5,16,40,10);

	}glPopMatrix();

//torus 5

	glPushMatrix();{
	
		glColor3f(0,.5,.5);

		GLUquadricObj *qObj = gluNewQuadric();
		gluQuadricTexture(qObj, GL_TRUE);
	
		glTranslatef(-220,17,143);

		glutSolidTorus(1,15.5,40,10);

	}glPopMatrix();

//torus 6

	glPushMatrix();{
	
		glColor3f(0,.5,.5);

		GLUquadricObj *qObj = gluNewQuadric();	
		gluQuadricTexture(qObj, GL_TRUE);
	
		glTranslatef(-220,17,163);

		glutSolidTorus(1,15.5,40,10);

	}glPopMatrix();

//(Big part Design) solid storus 7

	glPushMatrix();{
	
		glColor3f(1.0f,1.0f,1.0f); 

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,up3);

		GLUquadricObj *qObj = gluNewQuadric();
		gluQuadricTexture(qObj, GL_TRUE);
	
		glTranslatef(-220,17,175);

		glutSolidTorus(5,15,5,10);

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//(Big part Design) wire torus 7

	glPushMatrix();{
	
		glColor3f(1,1,1);

		GLUquadricObj *qObj = gluNewQuadric();
		gluQuadricTexture(qObj, GL_TRUE);
	
		glTranslatef(-220,17,175);
	
		glutWireTorus(5,15.5,3.5,10);

	}glPopMatrix();

///// torus 8

	glPushMatrix();{
	
		glColor3f(0,.5,.5);

		GLUquadricObj *qObj = gluNewQuadric();
		gluQuadricTexture(qObj, GL_TRUE);
	
		glTranslatef(-220,17,205);

		glutSolidTorus(1,13,40,10);

	}glPopMatrix();

//(Big Part 2 ) solid torus 9

	glPushMatrix();{

		glColor3f(1.0f,1.0f,1.0f); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,up3);

		GLUquadricObj *qObj = gluNewQuadric();
		gluQuadricTexture(qObj, GL_TRUE);
	
		glTranslatef(-220,17,216);

		glutSolidTorus(5,12,5,10);

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//(Big Part 2 ) Wire torus 9

	glPushMatrix();{
	
		glColor3f(1,1,1);

		GLUquadricObj *qObj = gluNewQuadric();
		gluQuadricTexture(qObj, GL_TRUE);
	
		glTranslatef(-220,17,216);
	
		glutWireTorus(5,12.5,3,10);

	}glPopMatrix();

}

///(Big Tous) top base floor

void Top_base(double x, double y, double z){

	glPushMatrix();{
	
		glColor3f(1,1,1);
		glTranslatef(0,70,105);
		glutWireTorus(90,2,2.5,500);
		//glutSolidTorus(90,2,2.5,200);
	
	}glPopMatrix();

}

//// Stair

void stair(double x, double y, double z)
{
		glTranslatef(x,y,z);
					GLUquadricObj *quadric = gluNewQuadric();

		glPushMatrix();{
			glColor3f(.6,.6,.6);
			glScalef(60,150,4);
			glTranslatef(0,-.1,.5);
			glutSolidCube(1);

		}glPopMatrix();

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,stimg);

		glTranslatef(0,-15,4.5);
		glScalef(1,2.5,0);

		glBegin(GL_QUADS);{
		
			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(0,1);
			glVertex3f(-30,30,0);
			glTexCoord2f(0,0);
			glVertex3f(-30,-30,0);
			glTexCoord2f(1,0);
			glVertex3f(30,-30,0);
			glTexCoord2f(1,1);
			glVertex3f(30,30,0);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

}

/// Stair Bordar wall 1

void Low_waL1(double x, double y, double z){

		glTranslatef(x,y,z);
					GLUquadricObj *quadric = gluNewQuadric();

		glPushMatrix();{
			
				glColor3f(.6,.6,.6);
				glTranslatef(-42,-70,7);
				glScalef(32,12,15);
				glutSolidCube(1);
	
		}glPopMatrix();

		glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wimg);

		glTranslatef(-58,-76.5,0);

		glBegin(GL_QUADS);{
		
			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(0,1);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(32,0,0);
			glTexCoord2f(1,0);
			glVertex3f(32,0,15);
			glTexCoord2f(1,1);
			glVertex3f(0,0,15);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

/// garden

	glPushMatrix();{

		Garden(0,0,0);

	}glPopMatrix();

}

/// Stair Bordar wall 2

void Low_waL2(double x, double y, double z){
	
		glTranslatef(x,y,z);
					GLUquadricObj *quadric = gluNewQuadric();

		glPushMatrix();{
			
			glColor3f(.7,.7,.7);
			glTranslatef(-43,-80,4);
			glScalef(27,20,8);
			glutSolidCube(1);
	
		}glPopMatrix();

		glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wimg);

		glTranslatef(-56,-90.5,-1);

		glBegin(GL_QUADS);{
		
			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(0,1);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(26,0,0);
			glTexCoord2f(1,0);
			glVertex3f(26,0,10);
			glTexCoord2f(1,1);
			glVertex3f(0,0,10);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//// garden

	glPushMatrix();{

		Garden_2(0,0,0);

	}glPopMatrix();

}

/////// window 1

void Window_1(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		//glColor4f(0,.5,0,.5);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,winimg);

		glTranslatef(-68,-31.5,7);
		glRotatef(180,0,0,1);

		/*glBegin(GL_QUADS);{

			glColor4f(0,.5,.5,.7); 
			glVertex3f(0,0,0);
			glColor4f(0,.6,.6,.7); 
			glVertex3f(12,0,0);
			glColor4f(0,.5,.5,.7);
			glVertex3f(12,0,37);
			glColor4f(0,.6,.6,.7);
			glVertex3f(0,0,37);
		}glEnd();*/

		glBegin(GL_QUADS);{

			glColor4f(1.0f,1.0f,1.0f,.9); 
			glTexCoord2f(0,1);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(12,0,0);
			glTexCoord2f(1,0);
			glVertex3f(12,0,31);
			glTexCoord2f(1,1);
			glVertex3f(0,0,31);
		}glEnd();


		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//triangle

	glPushMatrix();{

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,winimg);

		glTranslatef(-68,-31.5,38);
		glRotatef(180,0,0,1);

		glBegin(GL_TRIANGLES);{
			glColor4f(1.0f,1.0f,1.0f,.9); 
			glTexCoord2f(0,1);
			glVertex3f(0, 0, 0); 
			glTexCoord2f(0,0);
			glVertex3f(12, 0, 0);
			glTexCoord2f(1,0);	
			glVertex3f(6, 0,4);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

}

/////// window 2

void Window_2(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,winimg);

		glTranslatef(-68,-31.5,3);
		glRotatef(180,0,0,1);

		glBegin(GL_QUADS);{

			glColor4f(1.0f,1.0f,1.0f,.9); 
			glTexCoord2f(0,1);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(12,0,0);
			glTexCoord2f(1,0);
			glVertex3f(12,0,13);
			glTexCoord2f(1,1);
			glVertex3f(0,0,13);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//triangle

	glPushMatrix();{

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,winimg);

		glTranslatef(-68,-31.5,16);
		glRotatef(180,0,0,1);

		glBegin(GL_TRIANGLES);{
			glColor4f(1.0f,1.0f,1.0f,.9); 
			glTexCoord2f(0,1);
			glVertex3f(0, 0, 0); 
			glTexCoord2f(0,0);
			glVertex3f(12, 0, 0);
			glTexCoord2f(1,0);	
			glVertex3f(6, 0,4);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

}

void Window_3(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,winimg);

		glTranslatef(80,-50,3);
		glRotatef(180,0,0,1);

		glBegin(GL_QUADS);{

			glColor4f(1.0f,1.0f,1.0f,.9); 
			glTexCoord2f(0,1);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(6,0,0);
			glTexCoord2f(1,0);
			glVertex3f(6,0,13.5);
			glTexCoord2f(1,1);
			glVertex3f(0,0,13.5);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//triangle

	glPushMatrix();{

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,winimg);

		glTranslatef(80,-50,16.5);
		glRotatef(180,0,0,1);

		glBegin(GL_TRIANGLES);{
			glColor4f(1.0f,1.0f,1.0f,1); 
			glTexCoord2f(0,1);
			glVertex3f(0, 0, 0); 
			glTexCoord2f(0,0);
			glVertex3f(6, 0, 0);
			glTexCoord2f(1,0);	
			glVertex3f(3, 0,5);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

}

void Window_4(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,winimg);

		glTranslatef(80,-50,3);
		glRotatef(180,0,0,1);

		glBegin(GL_QUADS);{

			glColor4f(1.0f,1.0f,1.0f,.9); 
			glTexCoord2f(0,1);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(4,0,0);
			glTexCoord2f(1,0);
			glVertex3f(4,0,12);
			glTexCoord2f(1,1);
			glVertex3f(0,0,12);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

}

/// texture wall leftright

void texture_wall(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wall);

		glTranslatef(-57.5,-30.5,0);
		glRotatef(180,0,0,1);

	glBegin(GL_QUADS);{

		glColor3f(1.0f,1.0f,1.0f); 
		glTexCoord2f(1,0);
		glVertex3f(0,0,0);
		glTexCoord2f(0,0);
		glVertex3f(33.5,0,0);
		glTexCoord2f(0,1);
		glVertex3f(33.5,0,58.9);
		glTexCoord2f(1,1);
		glVertex3f(0,0,58.9);
	}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//under

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wallimg);

		glTranslatef(-57.5,-31,1);
		glRotatef(180,0,0,1);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(33,0,0);
			glTexCoord2f(0,1);
			glVertex3f(33,0,37);
			glTexCoord2f(1,1);
			glVertex3f(0,0,37);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

// window

	glPushMatrix();{

		Window_1(0,0,0);

	}glPopMatrix();

}

//texture wall 1st floor rotate

void texture_wall_2(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wall);

		glTranslatef(67,-66.5,0);
		glRotatef(0,1,0,1);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(72,0,0);
			glTexCoord2f(0,1);
			glVertex3f(72,0,59);
			glTexCoord2f(1,1);
			glVertex3f(0,0,59);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//under

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wallimg);

		glTranslatef(67,-67,1);
		glRotatef(0,1,0,1);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(72,0,0);
			glTexCoord2f(0,1);
			glVertex3f(72,0,37);
			glTexCoord2f(1,1);
			glVertex3f(0,0,37);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//window 1

	glPushMatrix();{

		glRotatef(0,1,0,1);
		Window_1(165,-37,2);

	}glPopMatrix();

//window 2

	glPushMatrix();{

		glRotatef(0,1,0,1);
		Window_1(190,-37,2);

	}glPopMatrix();

/*//window 3

glPushMatrix();{

	glRotatef(0,1,0,1);
	Window_1(195,-37,2);

}glPopMatrix();*/

}

///texture wall second floor rotate

void texture_wall_3(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wall);

		glTranslatef(64,-62,36);
		glRotatef(0,1,0,1);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(71,0,0);
			glTexCoord2f(0,1);
			glVertex3f(71,0,54);
			glTexCoord2f(1,1);
			glVertex3f(0,0,54);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//under

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wallimg);

		glTranslatef(64,-62.5,45);
		glRotatef(0,1,0,1);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(71,0,0);
			glTexCoord2f(0,1);
			glVertex3f(71,0,30);
			glTexCoord2f(1,1);
			glVertex3f(0,0,30);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//window 1

	glPushMatrix();{

		glRotatef(0,1,0,1);
		Window_2(155,-32,60);

	}glPopMatrix();

//window 2

	glPushMatrix();{

		glRotatef(0,1,0,1);
		Window_2(175,-32,60);

	}glPopMatrix();

//window 3

	glPushMatrix();{

		glRotatef(0,1,0,1);
		Window_2(195,-32,60);

	}glPopMatrix();

}

//texture wall 2nd floor front

void texture_wall_4(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wall);

		glTranslatef(85,-28,60);
		glRotatef(180,0,0,1);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(170,0,0);
			glTexCoord2f(0,1);
			glVertex3f(170,0,30);
			glTexCoord2f(1,1);
			glVertex3f(0,0,30);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//under

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wallimg);

		glTranslatef(85,-28.5,45);
		glRotatef(180,0,0,1);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(170,0,0);
			glTexCoord2f(0,1);
			glVertex3f(170,0,30);
			glTexCoord2f(1,1);
			glVertex3f(0,0,30);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//window

	glPushMatrix();{

		Window_1(75,2.5,40);

	}glPopMatrix();

//window 2

	glPushMatrix();{

		Window_2(150,2.5,60);

	}glPopMatrix();

//window 3

	glPushMatrix();{

		Window_2(0,2.5,60);

	}glPopMatrix();

///window back 1

	glPushMatrix();{

		Window_2(-35,205.5,60);

	}glPopMatrix();

///window back 2

	glPushMatrix();{

		Window_2(175,205.5,60);

	}glPopMatrix();

}

/// texture wall pilar with window

void texture_wall_5(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wall);

		glTranslatef(232,19,0);
		glRotatef(180,0,0,1);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(465,0,0);
			glTexCoord2f(0,1);
			glVertex3f(465,0,85);
			glTexCoord2f(1,1);
			glVertex3f(0,0,85);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//under

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wallimg);

		glTranslatef(232,18.5,10);
		glRotatef(180,0,0,1);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(465,0,0);
			glTexCoord2f(0,1);
			glVertex3f(465,0,60);
			glTexCoord2f(1,1);
			glVertex3f(0,0,60);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//window 1

	glPushMatrix();{

		Window_3(100,65,55);

	}glPopMatrix();

//window 2

	glPushMatrix();{

		Window_3(100,65,15);

	}glPopMatrix();

//window 3

	glPushMatrix();{

		Window_3(-260,65,55);

	}glPopMatrix();

//window 4

	glPushMatrix();{

		Window_3(-260,65,15);

	}glPopMatrix();

//window pillar 1

	glPushMatrix();{

		Window_3(135,52,55);

	}glPopMatrix();

//window pillar 2

	glPushMatrix();{

		Window_3(135,52,15);

	}glPopMatrix();

//window pillar 3

	glPushMatrix();{

		Window_3(-295,52,55);

	}glPopMatrix();

//window pillar 4

	glPushMatrix();{

		Window_3(-295,52,15);

	}glPopMatrix();

//window pillar 5

	glPushMatrix();{

		Window_4(135,52,85);

	}glPopMatrix();

//window pillar 6

	glPushMatrix();{

		Window_4(135,52,110);

	}glPopMatrix();

//window pillar 7

	glPushMatrix();{

		Window_4(135,82,100);

	}glPopMatrix();

//window pillar 8

	glPushMatrix();{

		Window_4(135,52,145);

	}glPopMatrix();

//window pillar 9

	glPushMatrix();{

		Window_4(135,82,145);

	}glPopMatrix();

//window pillar 10

	glPushMatrix();{

		Window_4(135,55,180);

	}glPopMatrix();

//window pillar 11

	glPushMatrix();{

		Window_4(135,79,180);

	}glPopMatrix();

///////////////////////////// left part
// window pillar 12

	glPushMatrix();{

		Window_4(-295,52,85);

	}glPopMatrix();

// window pillar 13

	glPushMatrix();{

		Window_4(-295,52,110);

	}glPopMatrix();

//window pillar 14

	glPushMatrix();{

		Window_4(-295,82,100);

	}glPopMatrix();

//window pillar 15

	glPushMatrix();{

		Window_4(-295,52,145);

	}glPopMatrix();

//window pillar 16

	glPushMatrix();{

		Window_4(-295,82,145);

	}glPopMatrix();

//window pillar 17

	glPushMatrix();{

		Window_4(-295,55,180);

	}glPopMatrix();

//window pillar 18

	glPushMatrix();{

		Window_4(-295,79,180);

	}glPopMatrix();

}

// texture wall pilar right side

void texture_wall_6(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wall);

		glTranslatef(231,19,0);
		glRotatef(90,0,0,1);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(102,0,0);
			glTexCoord2f(0,1);
			glVertex3f(102,0,85);
			glTexCoord2f(1,1);
			glVertex3f(0,0,85);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();


//under

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wallimg);

		glTranslatef(231.5,19,10);
		glRotatef(90,0,0,1);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(102,0,0);
			glTexCoord2f(0,1);
			glVertex3f(102,0,60);
			glTexCoord2f(1,1);
			glVertex3f(0,0,60);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

}

// texture wall  pillar back side

void texture_wall_11(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wall);

		glTranslatef(149,121,0);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(83,0,0);
			glTexCoord2f(0,1);
			glVertex3f(83,0,85);
			glTexCoord2f(1,1);
			glVertex3f(0,0,85);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//under

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wallimg);

		glTranslatef(149,121.5,10);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(83,0,0);
			glTexCoord2f(0,1);
			glVertex3f(83,0,60);
			glTexCoord2f(1,1);
			glVertex3f(0,0,60);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//window 1

	glPushMatrix();{

		Window_3(110,173,55);

	}glPopMatrix();

//window 2

	glPushMatrix();{

		Window_3(110,173,15);

	}glPopMatrix();

}

// texture wall  1st floor right side

void texture_wall_7(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wall);

		glTranslatef(154.5,-2.5,0);
		glRotatef(90,0,0,1);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(182,0,0);
			glTexCoord2f(0,1);
			glVertex3f(182,0,59);
			glTexCoord2f(1,1);
			glVertex3f(0,0,59);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

}

// texture wall 2nd floor right side

void texture_wall_8(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wall);

		glTranslatef(149,0,58);
		glRotatef(90,0,0,1);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(173.5,0,0);
			glTexCoord2f(0,1);
			glVertex3f(173.5,0,33);
			glTexCoord2f(1,1);
			glVertex3f(0,0,33);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

}

//////   texture wall  1st floor back side

void texture_wall_9(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wall);

		glTranslatef(-155,179.5,0);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(310,0,0);
			glTexCoord2f(0,1);
			glVertex3f(310,0,59);
			glTexCoord2f(1,1);
			glVertex3f(0,0,59);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

}

// texture wall 2nd floor back part

void texture_wall_10(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wall);

		glTranslatef(-149,173.5,59);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(299,0,0);
			glTexCoord2f(0,1);
			glVertex3f(299,0,32);
			glTexCoord2f(1,1);
			glVertex3f(0,0,32);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

}

/////// front side wall

void side_waL1(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{
			
		glColor3f(1,1,1);
		glTranslatef(-42,-46,31);
		glScalef(17,18,33);
		glutSolidCube(2);
	
	}glPopMatrix();

///texure wall

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wall);

		glTranslatef(-25,-64.5,14);
		glRotatef(180,0,0,1);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(33,0,0);
			glTexCoord2f(0,1);
			glVertex3f(33,0,50);
			glTexCoord2f(1,1);
			glVertex3f(0,0,50);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

//under

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,wallimg);

		glTranslatef(-25.5,-65,1);
		glRotatef(180,0,0,1);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(33,0,0);
			glTexCoord2f(0,1);
			glVertex3f(33,0,42);
			glTexCoord2f(1,1);
			glVertex3f(0,0,42);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

/// Window

	glPushMatrix();{

		Window_1(33,-34,6);

	}glPopMatrix();

}

//// Main Door

void door_wall(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glColor3f(1,1,.8);
		glTranslatef(0,-30,40);
		glScalef(25,15,27);
		glutSolidCube(2);

	}glPopMatrix();

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,door);

		glTranslatef(25,-45.5,13);
		glRotatef(180,0,0,1);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(50,0,0);
			glTexCoord2f(0,1);
			glVertex3f(50,0,55);
			glTexCoord2f(1,1);
			glVertex3f(0,0,55);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

}

///Back Door with window

void Back_door(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,door2);

		glTranslatef(-40,180,0);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(65,0,0);
			glTexCoord2f(0,1);
			glVertex3f(65,0,59);
			glTexCoord2f(1,1);
			glVertex3f(0,0,59);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

	////up window part

	glPushMatrix();{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,door3);

		glTranslatef(-27,174,59);

		glBegin(GL_QUADS);{

			glColor3f(1.0f,1.0f,1.0f); 
			glTexCoord2f(1,0);
			glVertex3f(0,0,0);
			glTexCoord2f(0,0);
			glVertex3f(40,0,0);
			glTexCoord2f(0,1);
			glVertex3f(40,0,31);
			glTexCoord2f(1,1);
			glVertex3f(0,0,31);
		}glEnd();

		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();

/// back window 1


	glPushMatrix();{

		Window_1(-60,213,0);

	}glPopMatrix();

/// back window 2


	glPushMatrix();{

		Window_1(150,213,0);

	}glPopMatrix();

/// back window 3


	glPushMatrix();{

		Window_1(-10,213,0);

	}glPopMatrix();

/// back window 4


	glPushMatrix();{

		Window_1(200,213,0);

	}glPopMatrix();

}

///back wall 1

void back_waL1(double x, double y, double z){

	glPushMatrix();{

		glColor3f(1,1,.8);
		glTranslatef(0,30,28);
		glScalef(90,60,32);
		glutSolidCube(2);
		
	}glPopMatrix();

}

/// 1st floor back wall 

void back_waL2(double x, double y, double z){

	glPushMatrix();{

		glColor3f(1,1,.8);
		glTranslatef(0,29,62);
		glScalef(85,55,30);
		glutSolidCube(2);

	}glPopMatrix();

}

void back_waL3(double x, double y, double z){

	glPushMatrix();{

		glColor3f(1,1,.8);
		glTranslatef(0,89,28);
		glScalef(154,90,32);
		glutSolidCube(2);

	}glPopMatrix();
}

///  back wall 2nd floor

void back_waL4(double x, double y, double z){

glPushMatrix();{
	glColor3f(1,1,.8);
	glTranslatef(0,88,62);
	glScalef(148,85,30);
	glutSolidCube(2);
}glPopMatrix();

}

//// Pilar wall

void middle_waLL(double x, double y, double z){

	glPushMatrix();{

		glColor3f(1,1,.8);
		glTranslatef(0,70,30);
		glScalef(230,50,55);
		glutSolidCube(2);
	}glPopMatrix();

}

// small gombuj middle up floor 

void up_wall_m(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{
			
		glColor3f(1,1,1);
		glTranslatef(1,-45.5,68);
		glScalef(265,150,8);
		glutSolidCube(.2);
	
	}glPopMatrix();

	glPushMatrix();{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,up);

	glTranslatef(1,-45.5,68.9);
	glScalef(.9,.6,0);


	glBegin(GL_QUADS);{
		
		glColor3f(1.0f,1.0f,1.0f); 
		glTexCoord2f(0,1);
		glVertex3f(-30,30,0);
		glTexCoord2f(0,0);
		glVertex3f(-30,-30,0);
		glTexCoord2f(1,0);
		glVertex3f(30,-30,0);
		glTexCoord2f(1,1);
		glVertex3f(30,30,0);
	}glEnd();

	glDisable(GL_TEXTURE_2D);

}glPopMatrix();

}

///up wall pillar

void up_wall_pillar(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,up);

	glTranslatef(200,73,85);
	glScalef(.9,.6,0);


	glBegin(GL_QUADS);{
		
		glColor3f(1.0f,1.0f,1.0f); 
		glTexCoord2f(0,1);
		glVertex3f(-60,80,0);
		glTexCoord2f(0,0);
		glVertex3f(-60,-90,0);
		glTexCoord2f(1,0);
		glVertex3f(37,-90,0);
		glTexCoord2f(1,1);
		glVertex3f(37,80,0);
	}glEnd();

	glDisable(GL_TEXTURE_2D);

}glPopMatrix();

}

void up_wall_LR(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,up);

	glTranslatef(-35,-45.5,70.5);
	glScalef(.9,.5,0);


	glBegin(GL_QUADS);{
		
		glColor3f(1.0f,1.0f,1.0f); 
		glTexCoord2f(0,1);
		glVertex3f(-30,47,0);
		glTexCoord2f(0,0);
		glVertex3f(-30,-47,0);
		glTexCoord2f(1,0);
		glVertex3f(15,-47,0);
		glTexCoord2f(1,1);
		glVertex3f(15,47,0);
	}glEnd();

	glDisable(GL_TEXTURE_2D);

}glPopMatrix();

}

/// Roftop floor

void top_wall_tex1(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,up);

	glTranslatef(0,45,94);
	glScalef(.9,.5,0);


	glBegin(GL_QUADS);{
		
		glColor3f(1.0f,1.0f,1.0f); 
		glTexCoord2f(0,1);
		glVertex3f(-166,260,0);
		glTexCoord2f(0,0);
		glVertex3f(-166,-100,0);
		glTexCoord2f(1,0);
		glVertex3f(166,-100,0);
		glTexCoord2f(1,1);
		glVertex3f(166,260,0);
	}glEnd();

	glDisable(GL_TEXTURE_2D);

}glPopMatrix();

}

void up_wall_d1(double x, double y, double z){

	glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

	glPushMatrix();{
			
		glColor3f(1,1,1);
		glTranslatef(-42,-49,65);
		glScalef(170,158,10);
		glutSolidCube(.2);
	
	}glPopMatrix();

glPushMatrix();{

	glColor3f(1,1,.8);
		glTranslatef(-42.5,-49,67);
		glScalef(175,170,10);
		glutSolidCube(.2);

}glPopMatrix();

glPushMatrix();{

glColor3f(1,1,1);
		glTranslatef(-42.5,-49,69);
		glScalef(185,180,10);
		glutSolidCube(.2);

}glPopMatrix();

}

void up_wall_d2(double x, double y, double z){

	glPushMatrix();{
			glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();
	
		glColor3f(1,1,1);
		glTranslatef(0,28,60);
		glScalef(920,600,10);
		glutSolidCube(.2);
	
	}glPopMatrix();

}

void up_wall_d3(double x, double y, double z){

	glPushMatrix();{
			glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();
	
		glColor3f(1,1,1);
		glTranslatef(0,25,92);
		glScalef(890,550,10);
		glutSolidCube(.2);
	
	}glPopMatrix();
}

void up_wall_b1(double x, double y, double z){

	glPushMatrix();{
			glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();
	
		glColor3f(1,1,1);
		glTranslatef(0,89,60);
		glScalef(1550,920,10);
		glutSolidCube(.2);
	
	}glPopMatrix();

}

void up_wall_b2(double x, double y, double z){

	glPushMatrix();{
			glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();
	
		glColor3f(1,1,1);
		glTranslatef(0,86,92);
		glScalef(1520,880,10);
		glutSolidCube(.2);
	
	}glPopMatrix();
}


//////Rotate

void up_wall_d4(double x, double y, double z){
	glRotatef(0,0,0,1);
	glPushMatrix();{
		glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

		glColor3f(1,1,1);
		glTranslatef(104,-7,59.5);
		glScalef(350,611,10);
		glutSolidCube(.2);
	
	}glPopMatrix();
}

void up_wall_d5(double x, double y, double z){
	glRotatef(0,0,0,1);
	glPushMatrix();{
		glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

		glColor3f(1,1,1);
		glTranslatef(103,-5,91.5);
		glScalef(350,611,10);
		glutSolidCube(.2);
	
	}glPopMatrix();
}


//1st floor
void Rotate_wall_1(double x, double y, double z){
	
	glRotatef(25,0,0,1);
	glPushMatrix();{

		glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

		glColor3f(1,1,.8);
		glTranslatef(104,-11,29.5);
		glScalef(35,55,29.5);
		//glScalef(35,20,29.5);
		glutSolidCube(2);
	}glPopMatrix();
}


//2nd floor

void Rotate_wall_2(double x, double y, double z){
	
	glRotatef(0,0,0,1);
	glPushMatrix();{

		glTranslatef(x,y,z);
				GLUquadricObj *quadric = gluNewQuadric();

		glColor3f(1,1,.8);
		glTranslatef(100,-10,71);
		//glScalef(35,50,20);
		glScalef(35,10,20);
		glutSolidCube(2);
	}glPopMatrix();
	
}

void display(){
	//codes for Models, Camera
	
	//clear the display
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(.6,.8,1,0);	//color blue
	//glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//clear buffers to preset values

	/***************************
	/ set-up camera (view) here
	****************************/ 
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);		//specify which matrix is the current matrix

	//initialize the matrix
	glLoadIdentity();				//replace the current matrix with the identity matrix [Diagonals have 1, others have 0]

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(0,-150,20,	0,0,0,	0,0,1);
	gluLookAt(cameraRadius*sin(cameraAngle), -cameraRadius*cos(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	
	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/**************************************************
	/ Grid and axes Lines(You can remove them if u want)
	***************************************************/
	// draw the three major AXES
	/*glBegin(GL_LINES);
		//X axis
		glColor3f(0, 1, 0);	//100% Green
		glVertex3f(-150, 0, 0);
		glVertex3f( 150, 0, 0);
		
		//Y axis
		glColor3f(0, 0, 1);	//100% Blue
		glVertex3f(0, -150, 0);	// intentionally extended to -150 to 150, no big deal
		glVertex3f(0,  150, 0);*/
		
		/*//Z axis
		glColor3f(1, 1, 1);	//100% White
		glVertex3f( 0, 0, -150);
		glVertex3f(0, 0, 150);
	glEnd();*/

	//some gridlines along the field
	/*int i;
	if(canDrawGrid){
	glColor3f(0.5, 0.5, 0.5);	//grey
		glBegin(GL_LINES);
			for(i=-10;i<=10;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -100, 0);
				glVertex3f(i*10,  100, 0);

				//lines parallel to X-axis
				glVertex3f(-100, i*10, 0);
				glVertex3f( 100, i*10, 0);
			}
		glEnd();
	}*/
	

	/****************************
	/ Add your objects from here
	****************************/

//////The Field

	Field(0,0,0);

//////The Road

Road_flor(0,0,0);

///// Tree right

Tree(0,0,0);

///// Tree left

glPushMatrix();{

	Tree(-660,0,0);

}glPopMatrix();

/// Main Gate

Main_gate(0,0,0);

///Right side Lightpost 1

glPushMatrix();{

	Light_post(0,0,0);

}glPopMatrix();

///Right side Lightpost 2

glPushMatrix();{

	Light_post(0,-90,0);

}glPopMatrix();

///Right side Lightpost 3

glPushMatrix();{

	Light_post(0,-180,0);

}glPopMatrix();

///left side Lightpost 1

glPushMatrix();{

	Light_post(-220,0,0);

}glPopMatrix();

///left side Lightpost 2

glPushMatrix();{

	Light_post(-220,-90,0);

}glPopMatrix();

///left side Lightpost 3

glPushMatrix();{

	Light_post(-220,-180,0);

}glPopMatrix();

//////The sky

glPushMatrix();{

	Sky(0,0,0);

}glPopMatrix();

////side sky left

	sideSky1(0,0,0);

///// side sky right

glPushMatrix();{

	glRotatef(180,0,0,1);
	sideSky1(1500,0,0);

}glPopMatrix();

/// front sky

glPushMatrix();{

	glRotatef(90,0,0,1);
	sideSky1(1500,0,0);

}glPopMatrix();

/// Top floor Big cyl

Top_cyl(0,0,0);

/// Big gombuj low part cylinder

Top_cyl_2(0,0,0);

///top base floor (Big wire torus)

Top_base(0,0,0);

///back wall 1

back_waL1(0,0,0);

/// texture wall left 

glPushMatrix();{

	texture_wall(0,0,0);

}glPopMatrix();

/// texture wall right

glPushMatrix();{

	texture_wall(147.5,0,0);

}glPopMatrix();

///texture wall 2nd floor front

texture_wall_4(0,0,0);

//texture wall pillar wall

	texture_wall_5(0,0,0);

//texture wall pillar right side

glPushMatrix();{

	texture_wall_6(0,0,0);

}glPopMatrix();

//texture wall pillar left side

glPushMatrix();{

	texture_wall_6(-462,0,0);

}glPopMatrix();

/// texture wall 1st floor right side

glPushMatrix();{

	texture_wall_7(0,0,0);

}glPopMatrix();

/// texture wall 1st floor left side

glPushMatrix();{

	texture_wall_7(-309,1,0);

}glPopMatrix();


/// texture wall 2nd floor right side

glPushMatrix();{

	texture_wall_8(0,0,0);

}glPopMatrix();

/// texture wall 2nd floor left side

glPushMatrix();{

	texture_wall_8(-298,1,0);

}glPopMatrix();

/// texture wall 1st floor back side

texture_wall_9(0,0,0);

/// texture wall 2nd floor back side

texture_wall_10(0,0,0);

/// texture wall pilar back side right

texture_wall_11(0,0,0);

/// texture wall pilar back side Left

glPushMatrix();{

	texture_wall_11(-380,0,0);

}glPopMatrix();


//// 1st floor back wall 2

	//back_waL2(0,0,0);

/// back wall 3

	//back_waL3(0,0,0);

//// 2nd floor back wall 4

back_waL4(0,0,0);

/// Pillar middle wall

	//middle_waLL(0,0,0);

////stair

stair(0,0,0);

//stair 2

glPushMatrix();{

	stair(0,6,4);

}glPopMatrix();

//stair 3

glPushMatrix();{

	stair(0,12,8);

}glPopMatrix();

// stair border wall left 1

Low_waL1(0,0,0);

/// stair border wall right 1

glPushMatrix();{

	Low_waL1(84,0,0);

}glPopMatrix();

//stair boder wall left 2

Low_waL2(0,0,0);

/// stair borderwall right 2

glPushMatrix();{

	Low_waL2(86,0,0);

}glPopMatrix();

//Main Door wall

	door_wall(0,0,0);

// Back Door

	Back_door(0,0,0);

///Front side wall left

	side_waL1(0,0,0);

/// Front side wall right

glPushMatrix();{

	side_waL1(84,0,0);

}glPopMatrix();

//small gombuj  middle up floor

	up_wall_m(0,0,0);

// up wall pillar right

	up_wall_pillar(0,0,0);

/// up wall pillar left

glPushMatrix();{

	up_wall_pillar(-380,0,0);

}glPopMatrix();

//up wall left/right

	up_wall_LR(0,0,0); 

	glPushMatrix();{

		up_wall_LR(85,0,0);

	}glPopMatrix();

//Rooftop Floor texture

	top_wall_tex1(0,0,0);

//up wall design 1

	up_wall_d1(0,0,0);

	glPushMatrix();{

		up_wall_d1(85,0,0);

	}glPopMatrix();

/// up wall design 2

	up_wall_d2(0,0,0);

/// up wall design 3

	up_wall_d3(0,0,0);

/// up wall back 1

	up_wall_b1(0,0,0);

// up wall back 2

	up_wall_b2(0,0,0);

///////// Pilar letf

Pillar(0,0,0);

////////// Pilar Right

glPushMatrix();{
	Pillar(435,0,0);

}glPopMatrix();

///  small Gombuj low part left

Gombuj_1(0,0,0);

// small gombuj low part right

glPushMatrix();{
	Gombuj_1(85,0,0);

}glPopMatrix();

/// small gombuj up part left 

Gombuj_2(0,0,0);

/// small gombuj up part right

glPushMatrix();{
	
	Gombuj_2(85,0,0);

}glPopMatrix();

//// big Gombuj low part

Gombuj_3(0,0,0);

// big gombuj up part

Gombuj_4(0,0,0);

/// (Big Gombuj) Top cone 1

Top_cone1(0,0,0);

////(small Gombuj cone) top cone 2

Top_cone2(0,0,0);

glPushMatrix();{
	Top_cone2(85,0,0);

}glPopMatrix();

/// (Pillar cone ) top cone 3

Top_cone3(0,0,0);

glPushMatrix();{
	Top_cone3(435,0,0);

}glPopMatrix();

//////// Rotate

//1st floor side wall rotate 1
	
	Rotate_wall_1(0,0,0);

glPushMatrix();{

	glRotatef(-75,0,0,1);
	Rotate_wall_1(-208,1,0);

}glPopMatrix();

///texture wall 1st floor

texture_wall_2(0,0,0);

glPushMatrix();{

	glRotatef(-49,-0,0,1);
	texture_wall_2(-207.5,2.5,0);

}glPopMatrix();

// texture wall 2nd floor

texture_wall_3(0,0,0);

glPushMatrix();{

	glRotatef(-50,-0,0,1);
	texture_wall_3(-199,1,0);

}glPopMatrix();

//2nd floor side wall rotate 2
	
	Rotate_wall_2(0,0,0);

glPushMatrix();{

	glRotatef(-50,0,0,1);
	Rotate_wall_2(-201,1,0);

}glPopMatrix();

/// up wall design 4
	
	up_wall_d4(0,0,0);

	glPushMatrix();{
	glRotatef(-50,0,0,1);
	up_wall_d4(-208,0,1);
}glPopMatrix();

/// up wall design 5
	
	up_wall_d5(0,0,0);

	glPushMatrix();{
	glRotatef(-50,0,0,1);
	up_wall_d5(-207,0,0);
}glPopMatrix();


	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void animate(){
	//codes for any changes in Models, Camera
	
	cameraAngle += cameraAngleDelta;	// camera will rotate at 0.002 radians per frame.
	
	//codes for any changes in Models

	//MISSING SOMETHING? -- YES: add the following
	glutPostRedisplay();	//this will call the display AGAIN

}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':	//reverse the rotation of camera
			cameraAngleDelta = -cameraAngleDelta;
			break;

		case '2':	//increase rotation of camera by 10%
			cameraAngleDelta *= 5;
			break;

		case '3':	//decrease rotation
			cameraAngleDelta /= 5;
			break;

		case '8':	//toggle grids
			canDrawGrid = 1 - canDrawGrid;
			break;
			
		case 'p':	//toggle grids
			cameraAngleDelta = 0;
			break;
		case 'r':	//toggle grids
			cameraAngleDelta = .001;
			break;		

		default:
			break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraRadius += 10;
			break;
		case GLUT_KEY_UP:		// up arrow key
			if(cameraRadius > 10)
				cameraRadius -= 10;
			break;

		case GLUT_KEY_RIGHT:
			cameraAngle += 0.01;
			break;
		case GLUT_KEY_LEFT:
			cameraAngle -= 0.01;
			break;

		case GLUT_KEY_PAGE_UP:
			cameraHeight += 10;
			break;
		case GLUT_KEY_PAGE_DOWN:
			cameraHeight -= 10;
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			cameraAngleDelta = 0.001; 
			break;

		case GLUT_KEY_END:
			cameraAngleDelta = 0;
			break;

		default:
			break;
	}
}

void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				cameraAngleDelta = -cameraAngleDelta;	
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}

void init(){
	//codes for initialization

	loadImage();

	cameraAngle = 0;	//angle in radian
	cameraAngleDelta = 0.0001;
	canDrawGrid = 1;

	cameraHeight = 200;
	cameraRadius = 620;
	//clear the screen
	glClearColor(0,0,0, 0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);
	
	//initialize the matrix
	glLoadIdentity();

	/*
		gluPerspective() — set up a perspective projection matrix

		fovy -         Specifies the field of view angle, in degrees, in the y direction.
        aspect ratio - Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
        zNear -        Specifies the distance from the viewer to the near clipping plane (always positive).
        zFar  -        Specifies the distance from the viewer to the far clipping plane (always positive).
    */
	
	gluPerspective(70,	1,	0.1,	10000.0);
	
}

int main(int argc, char **argv){
	
	glutInit(&argc,argv);							//initialize the GLUT library
	
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	
	/*
		glutInitDisplayMode - inits display mode
		GLUT_DOUBLE - allows for display on the double buffer window
		GLUT_RGBA - shows color (Red, green, blue) and an alpha
		GLUT_DEPTH - allows for depth buffer
	*/
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	

	glutCreateWindow("Some Title");

	init();						//codes for initialization

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	//ADD keyboard listeners:
	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);

	//ADD mouse listeners:
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}