//#include <windows.h>
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
double ex = 5;
double ey = 5;
double ez = 5;
double lx = 0;
double ly = 0;
double lz = 0;
double winHt = 15.0; // half-height of the window

void setLight(float x, float y, float z){
    // set the light source properties
    GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat light_position[] = {x, y, z, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}

//<<<<<<<<<<<<<<< wall >>>>>>>>>>>>>>>>
void wall(double thickness)
{ // draw thin wall with top = xz-plane, corner at origin, 1x1
    glPushMatrix();
    glTranslated(0.5, 0.5 * thickness, 0.5);
    glScaled(1.0, thickness, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();
}

//<<<<<<<<<<<<<<<<<< tableLeg >>>>>>>>>>>>>>>>>>>
void tableLeg(double thick, double len)
{
    glPushMatrix();
    glTranslated(0, len/2, 0);
    glScaled(thick, len, thick);
    glutSolidCube(1.0);
    glPopMatrix();
}
//<<<<<<<<<<<<<<<<<<<<<<< table >>>>>>>>>>>>>>>>>>>>
void table(double topWid, double topThick, double legThick, double legLen){
    // draw the table top
    glPushMatrix();
    glTranslated(0, legLen, 0);
    glScaled(topWid, topThick, topWid);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // draw legs
    double dist = 0.95 * topWid/2.0 - legThick / 2.0;
    glPushMatrix();
    glTranslated(dist, 0, dist);
    tableLeg(legThick, legLen);
    glTranslated(0, 0, -2 * dist);
    tableLeg(legThick, legLen);
    glTranslated(-2 * dist, 0, 2*dist);
    tableLeg(legThick, legLen);
    glTranslated(0, 0, -2*dist);
    tableLeg(legThick, legLen);
    glPopMatrix();
    }
//<<<<<<<<<<<<<<<<<<<<<<< chair >>>>>>>>>>>>>>>>>>>>
void chair(double topWid, double topThick, double legThick, double legLen){
    // draw chair top
    glPushMatrix();
    glTranslated(0, legLen, 0);
    glScaled(topWid, topThick, topWid);
    glutSolidCube(1.0);
    glPopMatrix();
    // draw chair back
    glPushMatrix(); 
    glTranslated(topWid/2, topWid/2 + legLen, 0);
    glRotated(90,0,0,1);
    glScaled(topWid, topThick, topWid);
    glutSolidCube(1.0);
    glPopMatrix();
    // draw legs
    double dist = 0.95 * topWid/2.0 - legThick / 2.0;
    glPushMatrix();
    glTranslated(dist, 0, dist);
    tableLeg(legThick, legLen);
    glTranslated(0, 0, -2 * dist);
    tableLeg(legThick, legLen);
    glTranslated(-2 * dist, 0, 2*dist);
    tableLeg(legThick, legLen);
    glTranslated(0, 0, -2*dist);
    tableLeg(legThick, legLen);
    glPopMatrix();
}

//<<<<<<<<<<<<<<<<<<<<<<< stander >>>>>>>>>>>>>>>>>>>>
void stander(void){
    glPushMatrix();
    glScaled(0.3,1.2,0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0, 0.6+0.15, -0.25);
    glScaled(0.3,0.3,0.01);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0, 0.6+0.15, 0.25);
    glScaled(0.3,0.3,0.01);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.15, 0.6+0.15, 0);
    glScaled(0.01,0.3,0.5);
    glutSolidCube(1.0);
    glPopMatrix();
}

//<<<<<<<<<<<<<<<<<<<<<<< book shelf >>>>>>>>>>>>>>>>>>>>
void bookshelf(double len,double wid,double hei){
    for (int i=0;i<4;i++){
        glPushMatrix();
        glTranslated(0,i*(hei/3),0);
        glScaled(len,1,wid);
        wall(0.02);
        glPopMatrix();
    }
    
    glPushMatrix();
    glScaled(len,hei,1);
    glRotated(-90.0,1.0, 0.0, 0.0);
    wall(0.02);
    glPopMatrix;
    
    /*for (int j=0;j<2;j++){
        glPushMatrix();
        glTranslated(j*len,0,wid);
        glScaled(1,hei,wid);
        glRotated(90.0, 0.0, 0.0, 1.0);
        wall(0.02);
        glPopMatrix();
    }
    */
    
}

//<<<<<<<<<<<<<<<<<<<<<<< room 300 >>>>>>>>>>>>>>>>>>>>
void room300(void){
    // draw wall and floor 9x8x3
    glPushMatrix();
    glScaled(9,1,8);
    wall(0.02);
    glPopMatrix();
    
    glPushMatrix();
    glRotated(90.0, 0.0, 0.0, 1.0);
    glScaled(3,1,8);
    wall(0.02); // wall #2: in yz-plane
    glPopMatrix();
    
    glPushMatrix();
    glRotated(-90.0,1.0, 0.0, 0.0);
    glScaled(9,1,3);
    wall(0.02); // wall #3: in xy-plane
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(9,0,0);
    glRotated(90.0, 0.0, 0.0, 1.0);
    glScaled(3,1,8);
    wall(0.02);
    glPopMatrix();
    
    // draw wall with doors
    glPushMatrix();
    glTranslated(0,0,8);
    glPushMatrix();
    glTranslated(0,2,0);
    glRotated(-90.0,1.0, 0.0, 0.0);
    glScaled(9,1,1);
    wall(0.02);
    glPopMatrix();
    glPushMatrix();
    glRotated(-90.0,1.0, 0.0, 0.0);
    glScaled(2,1,2);
    wall(0.02);
    glPopMatrix();
    glPushMatrix();
    glTranslated(3.5,0,0);
    glRotated(-90.0,1.0, 0.0, 0.0);
    glScaled(2,1,2);
    wall(0.02);
    glPopMatrix();
    glPushMatrix();
    glTranslated(7,0,0);
    glRotated(-90.0,1.0, 0.0, 0.0);
    glScaled(2,1,2);
    wall(0.02);
    glPopMatrix();
    glPopMatrix();
    
    //draw board in yz plane
    glPushMatrix();
    glTranslated(0.02,0.5,1);
    glRotated(90.0, 0.0, 0.0, 1.0);
    glScaled(1.5,1,6);
    wall(0.05); // wall #2: in yz-plane
    glPopMatrix();
    
    //draw stander
    glPushMatrix();
    glTranslated(1,0.6,1);
    stander();
    glPopMatrix();
    
    //draw sets of table and chairs
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            glPushMatrix();
            glTranslated(2+i*1.8,0,0.3+1.2+j*2.1);
            glScaled(1,1,2);
            table(0.7,0.1,0.02,0.7);
            glPopMatrix();
            
            glPushMatrix();
            glTranslated(2.35+i*1.8,0,0.3+1.5+j*2.1);
            chair(0.5,0.1,0.02,0.4);
            glPopMatrix();
            
            glPushMatrix();
            glTranslated(2.35+i*1.8,0,0.3+0.85+j*2.1);
            chair(0.5,0.1,0.02,0.4);
            glPopMatrix();
        }
    }
    
    //draw book shelf
    glPushMatrix();
    glTranslated(3,0,0.04);
    bookshelf(4,0.3,2);
    glPopMatrix();
    
}

//<<<<<<<<<<<<<<<<<<<<<<< room 303 >>>>>>>>>>>>>>>>>>>>
void room303(void){
    // draw wall and floor 4x5x3
    glPushMatrix();
    glScaled(4,1,5);
    wall(0.02);
    glPopMatrix();
    
    glPushMatrix();
    glRotated(90.0, 0.0, 0.0, 1.0);
    glScaled(3,1,5);
    wall(0.02); // wall #2: in yz-plane
    glPopMatrix();
    
    glPushMatrix();
    glRotated(-90.0,1.0, 0.0, 0.0);
    glScaled(4,1,3);
    wall(0.02); // wall #3: in xy-plane
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0,0,5);
    glRotated(-90.0,1.0, 0.0, 0.0);
    glScaled(4,1,3);
    wall(0.02);
    glPopMatrix();
    
    // draw set of table and chairs
    glPushMatrix();
    glTranslated(1,0,1);
    table(1,0.1,0.02,0.7);
    glPushMatrix();
    glTranslated(0.5,0,0);
    chair(0.5,0.1,0.02,0.4);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0,0,0.5);
    glRotated(-90,0,1,0);
    chair(0.5,0.1,0.02,0.4);
    glPopMatrix();
    glPopMatrix();
    
    // draw set of table and chairs
    glPushMatrix();
    glTranslated(1.7,0,2.7);
    glPushMatrix();
    glTranslated(1,0,1);
    table(1,0.1,0.02,0.7);
    glPopMatrix();
    glPushMatrix();
    glTranslated(1.5,0,1);
    chair(0.5,0.1,0.02,0.4);
    glPopMatrix();
    glPushMatrix();
    glTranslated(1,0,1.5);
    glRotated(-90,0,1,0);
    chair(0.5,0.1,0.02,0.4);
    glPopMatrix();
    glPushMatrix();
    glTranslated(1,0,0.5);
    glRotated(90,0,1,0);
    chair(0.5,0.1,0.02,0.4);
    glPopMatrix();
    glPopMatrix();
}

//<<<<<<<<<<<<<<<<<<<<<<< room small >>>>>>>>>>>>>>>>>>>>
void room300small(void){
    // draw wall and floor 2.5x2.5x3
    glPushMatrix();
    glScaled(2.5,1,2.5);
    wall(0.02);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(2.5,0,0);
    glRotated(90.0, 0.0, 0.0, 1.0);
    glScaled(3,1,2.5);
    wall(0.02); // wall #2: in yz-plane
    glPopMatrix();
    
    glPushMatrix();
    glRotated(-90.0,1.0, 0.0, 0.0);
    glScaled(2.5,1,3);
    wall(0.02); // wall #3: in xy-plane
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0,0,2.5);
    glRotated(-90.0,1.0, 0.0, 0.0);
    glScaled(2.5,1,3);
    wall(0.02); // wall #3: in xy-plane
    glPopMatrix();
    
    // draw set of table and chairs
    glPushMatrix();
    glTranslated(1,0,1);
    table(1,0.1,0.02,0.7);
    glPushMatrix();
    glTranslated(0.5,0,0);
    chair(0.5,0.1,0.02,0.4);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0,0,0.5);
    glRotated(-90,0,1,0);
    chair(0.5,0.1,0.02,0.4);
    glPopMatrix();
    glPopMatrix();
}

//<<<<<<<<<<<<<<<<<<<<<<< room 304 >>>>>>>>>>>>>>>>>>>>
void room304(void){
    // draw wall and floor 2.5x4x3
    glPushMatrix();
    glScaled(2.5,1,4);
    wall(0.02);
    glPopMatrix();
    
    glPushMatrix();
    glRotated(90.0, 0.0, 0.0, 1.0);
    glScaled(3,1,4);
    wall(0.02); // wall #2: in yz-plane
    glPopMatrix();
    
    glPushMatrix();
    glRotated(-90.0,1.0, 0.0, 0.0);
    glScaled(2.5,1,3);
    wall(0.02); // wall #3: in xy-plane
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(2.5,0,0);
    glRotated(90.0, 0.0, 0.0, 1.0);
    glScaled(3,1,4);
    wall(0.02); // wall #2: in yz-plane
    glPopMatrix();
    
    // draw set of table and chairs
    glPushMatrix();
    glTranslated(1,0,2);
    table(1,0.1,0.02,0.7);
    glPushMatrix();
    glTranslated(0.5,0,0);
    chair(0.5,0.1,0.02,0.4);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0,0,0.5);
    glRotated(-90,0,1,0);
    chair(0.5,0.1,0.02,0.4);
    glPopMatrix();
    glPopMatrix();
}

//<<<<<<<<<<<<<<<<<<<<<<< room 308 >>>>>>>>>>>>>>>>>>>>
void room308(void){
    // draw wall and floor 2.5x5x3
    glPushMatrix();
    glScaled(2.5,1,5);
    wall(0.02);
    glPopMatrix();
    
    glPushMatrix();
    glRotated(90.0, 0.0, 0.0, 1.0);
    glScaled(3,1,5);
    wall(0.02); // wall #2: in yz-plane
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0,0,5);
    glRotated(-90.0,1.0, 0.0, 0.0);
    glScaled(2.5,1,3);
    wall(0.02); // wall #3: in xy-plane
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(2.5,0,0);
    glRotated(90.0, 0.0, 0.0, 1.0);
    glScaled(3,1,5);
    wall(0.02); // wall #2: in yz-plane
    glPopMatrix();
    
    // draw set of table and chairs
    glPushMatrix();
    glTranslated(1,0,2);
    table(1,0.1,0.02,0.7);
    glPushMatrix();
    glTranslated(0.5,0,0);
    chair(0.5,0.1,0.02,0.4);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0,0,0.5);
    glRotated(-90,0,1,0);
    chair(0.5,0.1,0.02,0.4);
    glPopMatrix();
    glPopMatrix();
}

//<<<<<<<<<<<<<<<<<<<<<<< bathroom >>>>>>>>>>>>>>>>>>>>
void toilet(void){
    // draw wall and floor 1.5x5x3
    glPushMatrix();
    glScaled(1.5,1,5);
    wall(0.02);
    glPopMatrix();
    
    glPushMatrix();
    glRotated(90.0, 0.0, 0.0, 1.0);
    glScaled(3,1,5);
    wall(0.02); // wall #2: in yz-plane
    glPopMatrix();
    
    glPushMatrix();
    glRotated(-90.0,1.0, 0.0, 0.0);
    glScaled(1.5,1,3);
    wall(0.02); // wall #3: in xy-plane
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(1.5,0,0);
    glRotated(90.0, 0.0, 0.0, 1.0);
    glScaled(3,1,5);
    wall(0.02); // wall #2: in yz-plane
    glPopMatrix();
}

//<<<<<<<<<<<<<<<<<<<<<<< main function cst 3rd floor >>>>>>>>>>>>>>>>>>>>
void cst3rdfloor(void){
    room300();
    glPushMatrix();
    glTranslated(6,0,8);
    glRotated(90.0,0.0, 0.0, 1.0);
    glScaled(3,1,3);
    wall(0.02); // wall #3: in xy-plane
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(-4,0,11);
    //group1
    room303();
    glPushMatrix();
    glTranslated(0,0,5);
    toilet();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-1.5,0,5);
    toilet();
    glPopMatrix();
    glPushMatrix();
    glTranslated(1.5,0,5);
    room300small();
    glPopMatrix();
    //
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(1.5,0,11);
    //group2
    room300small();
    glPushMatrix();
    glTranslated(2.5,0,0);
    room304();
    glPopMatrix();
    glPushMatrix();
    glTranslated(0,0,5);
    room300small();
    glPushMatrix();
    glTranslated(0,0,2.5);
    room300small();
    glPopMatrix();
    glPushMatrix();
    glTranslated(2.5,0,0);
    room308();
    glPopMatrix();
    //
    glPopMatrix();
}

//<<<<<<<<<<<<<<<<<<<<< display >>>>>>>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    
    // set properties of the surface material
    GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f}; // gray
    GLfloat mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat mat_shininess[] = {50.0f};
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
    
    // set the light source properties
    GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat light_position0[] = {4.5f, 6.0f, 4.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
    
    GLfloat light_position1[] = {2.0f, 6.0f, 13.0f, 0.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightIntensity);
    
    GLfloat light_position2[] = {7.0f, 6.0f, 13.0f, 0.0f};
    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightIntensity);
    
    // set the camera
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-winHt*64/48.0, winHt*64/48.0, -winHt, winHt, 0, 100.0);
    //glFrustum(-winHt*64/48.0, winHt*64/48.0, -winHt, winHt, 0, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(ex, ey, ez, lx, ly, lz, 0.0,1.0,0.0);
    
    // start drawing
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clear the screen
    
    cst3rdfloor();
    
    glFlush();
    glutSwapBuffers();
    
}

//<<<<<<<<<<<<<<<<<<<<<<< keyboard function >>>>>>>>>>>>>>>>>>>>
void myKeyboardFunc(unsigned char key, int x, int y){
    switch(key)
    {
        case 'w': ey += 0.5; break;
        case 's': ey -= 0.5; break;
        case 'd': ex += 0.5; break;
        case 'a': ex -= 0.5; break;
        case 'e': ez += 0.5; break;
        case 'q': ez -= 0.5; break;
        case 'i': ly += 0.2; break;
        case 'k': ly -= 0.2; break;
        case 'l': lx += 0.2; break;
        case 'j': lx -= 0.2; break;
        case 'o': lz += 0.2; break;
        case 'u': lz -= 0.2; break;
        case 'z': winHt -= 0.5; break; //zoom in      //ex -= 0.5; ey -= 0.5; ez -= 0.5; break;
        case 'c': winHt += 0.5; break; //zoom out     //ex += 0.5; ey += 0.5; ez += 0.5; break;
        case 'b': ex=1.6; ey=1.6; ez=1.6; lx=0; ly=1.6; lz=0; break;
        case 'g': ex = 5; ey = 5; ez = 5; lx = 0; ly = 0; lz = 0; break;
        case 'v': ex = 7; ey = 17; ez = 18.5; lx = -1.2; ly = -18; lz = 0; break;
    }
    std::cout << " EX " << ex << " EY " << ey  << " EZ " << ez << " LX " << lx << " LY " << ly << " LZ " << lz << std::endl;
    glutPostRedisplay();
}
//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
    std::cout << "w: increase EY" << std::endl;
    std::cout << "s: decrease EY" << std::endl;
    std::cout << "d: increase EX" << std::endl;
    std::cout << "a: decrease EX" << std::endl;
    std::cout << "e: increase EZ" << std::endl;
    std::cout << "q: decrease EY" << std::endl;
    std::cout << "i: increase LY" << std::endl;
    std::cout << "k: increase LY" << std::endl;
    std::cout << "l: increase LX" << std::endl;
    std::cout << "j: decrease LX" << std::endl;
    std::cout << "o: increase LZ" << std::endl;
    std::cout << "u: decrease LZ" << std::endl;
    std::cout << "z: zoom in" << std::endl;
    std::cout << "c: zoom out" << std::endl;
    std::cout << "g: reset to original position" << std::endl;
    std::cout << "v: go to the position to see the whole object" << std::endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB| GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D scene");
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboardFunc);
    glEnable(GL_LIGHTING); // enable the light source
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST); // for hidden surface removal
    glEnable(GL_NORMALIZE); // normalize vectors for proper shading
    glClearColor(0.3f,0.3f,0.7f,0.0f); // background is light gray
    glViewport(0, 0, 640, 480);
    glutMainLoop();
    
    return 0;
}

