#include<iostream>
#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include<math.h>
#include<cstdio>
#define PI  3.14159265358979323846
#include <cctype>

using namespace std;



///defining function name first in an abstract way as body is defined elsewhere.
void DayView();
void NightView();
void MonsoonView();

void DayRiver();
void RiverSide(); //Grass //Island-Portion

void Train();
void Bridge();
void Hill();

void DaySky();
void NightSky();
void MonsoonSky();

//void Idle();//<--- ! //Explained in MAIN FUNCTION
///


//For Cloud AM
void CircleForCloud(GLfloat a, GLfloat b, GLfloat r);
void Cloud1();
void Cloud2();

//RAIN//INPUT
void Rain(GLfloat a, GLfloat y);
void RainFall();
void RainAnimation(int value);
GLfloat RainPos = 10.0f; //This amount is above 1.0f. //Outside screen

//WAVES//INPUT
GLfloat position_waves = 0.0f, speed_waves = 0.1f ;
void animation_waves(int value);
void waves();

//CLOUDS//INPUT
void CloudAnimation1(int value);
void CloudAnimation2(int value);
GLfloat CloudPosition1 = 0.0f;
GLfloat CloudSpeed1 = 0.01f;
GLfloat CloudPosition2 = 0.0f;
GLfloat CloudSpeed2 = 0.01f;

//BIRDS//INPUT
void Birds();
void Birds(int value);
GLfloat BirdsPosition = 0.0f;
GLfloat BirdsSpeed = 0.01f;
//////////AM

//KEYBOARD-MOUSE-INPUT-SECTION
void handleMouse(int button, int state, int x, int y);
void handleKeypress(unsigned char key, int x, int y);
void InstructionsDisplay();

//UPDATE//BOAT TRANSLATION
void update(int value);
GLfloat position = 0.0f;
GLfloat speed = 0.01f;


void Sun();
void Moon();
void Star();


//TRAIN FUNCTIONS//
void Wheel_Rotation_Update(int value);
void Wheel_Translation_update(int value);
//TRAIN VARIABLES//
float wheel_angle1 = 0.0f;
float _moveTrain = 0.0f;

//NORMAL GENERAL VARIABLES //FOR PROJECT OVERALL
float x;
float y;
float radius;
float tringle1;
float twicePi;
int i;
//NORMAL GENERAL VARIABLES //FOR PROJECT OVERALL





/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);  // Initialize GLUT
    glutInitWindowSize(1200, 700); // Set the window's initial width & height
    glutCreateWindow("Everlasting Hardinge Bridge");
    glutDisplayFunc(DayView);

    //glutIdleFunc(Idle); //--? //Somewhow It enhances the running grahpics portion
    //in the screen and 32 bit gets faster response when modes changed in the project.
    //reduces graphics memory consumption size maybe

    glutKeyboardFunc(handleKeypress);
    glutMouseFunc(handleMouse);

    //INSTRUCTION PART
    InstructionsDisplay();


    ///
    glutTimerFunc(100, update, 0); //Most probably works for BOAT translation
    ///

    //Train Function calling Region //

    glutTimerFunc(20, Wheel_Translation_update, 0); //Add a timer
    glutTimerFunc(20, Wheel_Rotation_Update, 0); //Add a timer
    //////////////////////////////////

    ///Cloud Timer Function
    glutTimerFunc(40, CloudAnimation1, 0);
    glutTimerFunc(40, CloudAnimation2, 0);
    ///Cloud Timer Function

    //Rain Timer Function
    glutTimerFunc(100, RainAnimation, 0);
    //Rain Timer Function

    //River Waves Timer Function
    glutTimerFunc(80, animation_waves, 0);
    //River Waves Timer Function


    glutMainLoop(); //Enter the event-processing loop //Keeping the program running by Loop

    return 0;
}

void Idle()
{
    glutPostRedisplay();
}

void InstructionsDisplay()
{
  cout<<"\n-INSTRUCTIONS OF CONTROL-\n"<<endl;
  cout<<"\n->Mouse: \n"<<endl;
  cout<<"Mouse Left Button -> Increase the speed of the Boat."<<endl;
  cout<<"Mouse Right Button -> Decrease the speed of the Boat.\n\n"<<endl;
  cout<<"\n->Keyboard: \n"<<endl;
  cout<<"For 'N' -> 'Night Mode'"<<endl;
  cout<<"For 'D' -> 'Day Mode'"<<endl;
  cout<<"For 'M' -> 'Monsoon Mode'"<<endl;
  cout<<"For 'A' -> 'Pause Boat Movement'"<<endl;
  cout<<"For 'W' -> 'Resume Boat Movement'\n\n"<<endl;

}


//THE TEXT FUNCTION REGION
void text()
{
     ///TEXT///

        //Computer graphics Lab
        glColor3f(1.0,1.0,1.0);
		char string[]="Computer Graphics Project"; //Input for the display text
		glRasterPos2f(-0.7221325776206f,0.4890679005729f); // a random point location used here
		int len1=strlen(string);
		for(int i=0;i<len1;i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
		}
        //Section- [G]
        glColor3f(1.0,1.0,1.0);
		char string1[]="Supervised By MD. SIYAMUL ISLAM"; //Input for the display text
		glRasterPos2f(-0.7207369943644f,0.3885859061313f); // a random point location used here
		int len2=strlen(string1);
		for(int i=0;i<len2;i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string1[i]);
		}
        //Summer Semester: 2021<->2022
        glColor3f(1.0,1.0,1.0);
		char string2[]="Section:-[G] , Summer: 2022"; //Input for the display text
		glRasterPos2f(-0.7207369943644f,0.2964774112265f); // a random point location used here
		int len3=strlen(string2);
		for(int i=0;i<len3;i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string2[i]);
		}


    ///text///
}
//THE TEXT FUNCTION REGION

/////Control Button Region///////////////////////////////////////////////////////////////
///AM's Control Buttons. Need to put before other functions
void handleMouse(int button, int state, int x, int y) {
if (button == GLUT_LEFT_BUTTON)
{	speed += 0.015f;
}
if (button == GLUT_RIGHT_BUTTON)
{speed -= 0.015f;
 }
glutPostRedisplay();
}


void handleKeypress(unsigned char key, int x, int y) {
switch (key) {
        case 'd':
        glutDisplayFunc(DayView);

        glutPostRedisplay();
        break;

        case 'n':
        glutDisplayFunc(NightView);

        glutPostRedisplay();
        break;

        case 'm':
        glutDisplayFunc(MonsoonView);

        glutPostRedisplay();
        break;

        ///////
        case 'a':
        speed = 0.0f;
        glutPostRedisplay();
        break;
        case 'w':
        speed = 0.020f;
        glutPostRedisplay();
        break;




}
}
/////Control Button Region///////////////////////////////////////////////////////////////


//AM//DAY SECTION////////
void DayView()
{
    glClearColor(0.0f/255.0, 164.0f/255.0, 180.0f/255.0, 1.0f); //Peacock Blue
    glClear(GL_COLOR_BUFFER_BIT);

    DayRiver();
    waves();
    RiverSide();
    DaySky();
    Sun();


    glPushMatrix();
    glTranslatef(CloudPosition1,0,0);
    Cloud1();
    Cloud2();
    Birds();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(CloudPosition2,0,0);
    //Copy of cloud1
    glTranslatef(1.0,0,0);
    Cloud1();
    glLoadIdentity();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(CloudPosition2,0,0);
    //Copy of Cloud2
    glTranslatef(-1.1,0,0);
    Cloud2();
    glLoadIdentity();
    glPopMatrix();

    Hill();
    Train();
    Bridge();

    //TEXT REGION
    text();
    //TEXT REGION

    glFlush(); //Object out of Pipeline
    glutSwapBuffers();

}
//AM//DAY SECTION////////

//AM//NIGHT SECTION////////
void NightView(){
    glClearColor(19.0f/255.0, 41.0f/255.0, 75.0f/255.0, 1.0f); //MIDNIGHT BLUE
    glClear(GL_COLOR_BUFFER_BIT);


    NightSky();
    Star();
    Moon();
    waves();
    RiverSide();
    Hill();
    Train();
    Bridge();

glFlush();
//AM//NIGHT SECTION////////

//AM//MONSOON SECTION////////
}
void MonsoonView(){
    glClearColor(0.0f/255.0, 105.0f/255.0, 148.0f/255.0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    MonsoonSky();
    waves();
    RiverSide();
    Hill();
    Train();
    Bridge();

    // Rainfall //
    glPushMatrix();
    glScalef(0.5,0.5,0);
    glTranslatef(RainPos-4,RainPos,0);
    RainFall();
    glLoadIdentity();
    glPopMatrix();
    // Rainfall //


glFlush();
}
//AM//MONSOON SECTION////////

void Hill()
{
    //Hill color triple shaders used
    //Hill 1 MID
	glBegin(GL_POLYGON);            // These vertices form a closed polygon
	glColor3ub(113,169,44); //Color: Corn GREEN
    glVertex2f(-0.2639844307783, 0.3386462252265); //Z9
    glVertex2f(-0.1072184892347, 0.2598335502119); //A10
    glVertex2f(-0.0024445408673, 0.1887369423911); //B10

    glColor3ub(0,135,62); //Color: CHRISTMAS GREEN

    glVertex2f(0.3620191223822, 0.070492057805); //C10
    glVertex2f(-0.027393281879, -0.1882218301206); //D10
    glVertex2f(-0.4657216917397, -0.1882218301206); //E10

    glColor3ub(0,154,23); //Color: Grass GREEN

    glVertex2f(-0.6174331203943, 0.1751761383182); //M9
    glVertex2f(-0.4887078701618, 0.2274282005746); //F10
    glVertex2f(-0.2639844307783, 0.3386462252265); //Z9

	glEnd();

    //Hill 2 Left Most
	glBegin(GL_POLYGON);            // These vertices form a closed polygon

	glColor3ub(0,135,62); //Color: CHRISTMAS GREEN

    glVertex2f(-0.7309180987337, 0.2322392065228); //L9
    glVertex2f(-0.6174331203943, 0.1751761383182); //M9
    glVertex2f(-0.3950910095327, 0.0628624424353); //N9
    glVertex2f(-0.343738997913, 0.0473296883972); //O9
    glVertex2f(-0.2561716027084, 0.0231778853924); //P9

    glColor3ub(0,110,51); //Forest Green

    glVertex2f(-0.1564339091782, -0.1882218301206); //Q9
    glVertex2f(-0.8207512014721, -0.1882218301206); //R9


    glColor3ub(21,71,52); //Dark Green Green
    glVertex2f(-1.0, -0.1891568379695); //S9
    glVertex2f(-0.9995633299439, 0.1078545409982); //k9
    glVertex2f(-0.7309180987337, 0.2322392065228); //L9
	glEnd();

	//Hill 3 Right Most
	glBegin(GL_POLYGON);            // These vertices form a closed polygon

	glColor3ub(0,135,62); //Color: CHRISTMAS GREEN

    glVertex2f(0.9205491076306, 0.1248967651084); //H10
    glVertex2f(0.9936329962802, 0.0951143086627); //I10

    glColor3ub(78,91,49); //Army Green

    glVertex2f(1, -0.037); //B
    glVertex2f(1, -0.1882218301206); //J10
    glVertex2f(-0.027393281879, -0.1882218301206); //D10

    glColor3ub(0,110,51); //Forest Green

    glVertex2f(0.3620191223822, 0.070492057805); //C10
    glVertex2f(0.4311190792954, 0.0817133843885); //U9
    glVertex2f(0.5562150333278, 0.1651106870768); //V9
    glVertex2f(0.688250723675, 0.2383007924245); //G10

	glEnd();

}

///////////////////////////////WARNING//TRAIN SECTION IS LONG ONE///////////////////////
void Train()
{


/////////////////////////////////////////////////////////////////////////////////////////////'s Space For Train


    //ENGINE BODY
    glPushMatrix();
    glTranslatef(_moveTrain, 0.0f, 0.0f);
    //
	glBegin(GL_POLYGON);            // These vertices form a closed polygon
	glColor3ub(169,64,7); // WHISKEY BROWN


    //Train Main Body
	glVertex2f(-0.5357067148962f, -0.0058319497378f);
	glVertex2f(-0.5402900873903f, -0.00550677397f);
	glVertex2f(-0.555503030221f, -0.00550677397f);
	glVertex2f(-0.555503030221f, 0.0356043929654f);
	glVertex2f(-0.5471721329566f, 0.0356043929654f);
	glVertex2f(-0.5469447829024f, 0.0887401560994f);
	glVertex2f(-0.5437068173388f, 0.0929022329983f);
	glVertex2f(-0.5286188978175f, 0.0938526531257f);
	glVertex2f(-0.5249508732529f, 0.1133270398641f);
	glColor3ub(185,71,0);//RUST
	glVertex2f(-0.5270632957932f, 0.1206031619477f);
	glVertex2f(-0.27f, 0.12f);
	glVertex2f(-0.2580692998851, 0.1116078051309);
	glVertex2f(-0.2360937442026, 0.1111917832567);
	glVertex2f(-0.2239793126057f, 0.1155664391111f);
	glVertex2f(-0.2088362731097f, 0.1116965512399f);
	glVertex2f(-0.1398192584419f, 0.1111511011865f);
	glVertex2f(-0.1309247509378f, 0.1196731224481f);
	glVertex2f(-0.1091482843785f, 0.1196731224481f);
	glVertex2f(-0.095500410519f, 0.1198157877631f);
	glVertex2f(0.042670895973f, 0.1193477331943f);
	glVertex2f(0.042941209056f, 0.101597174081f);
	glVertex2f(0.0400578695046f, 0.096821642949f);
	glVertex2f(0.0399837270699f, 0.035167438671f);
	glVertex2f(0.0549593577634, 0.0348164473266);
	glVertex2f(0.0547253635338f, 0.0288495944722f);
	glVertex2f(0.0514872397621f, 0.0288503238223f);
	glVertex2f(0.0512646399626f, 0.0316996012563f);
	glVertex2f(0.0485934423682f, 0.0316996012563f);
	glVertex2f(0.0485489224083f, 0.0276037649449f);
	glVertex2f(0.0564082434454f, 0.0226021396372f);
	glVertex2f(0.0564633496041f, 0.0192406639558f);
	glVertex2f(0.0632965132843f, 0.0189651331622f);
	glVertex2f(0.063351619443f, 0.0089909184354f);
	glVertex2f(0.0523303877007f, 0.0089909184354f);
	glVertex2f(0.0522938502646f, -0.008257366436f);
	glVertex2f(0.0501678506116f, -0.0066983000238f);
	glVertex2f(0.026923587739f, -0.0063439667483f);
	glVertex2f(0.0269475754054f, 0.0014960095796f);
	glVertex2f(0.0113682450294f, 0.0013524212812f);
	glVertex2f(-0.0047420397539f, 0.0209166810224f);
	glVertex2f(-0.0248174601579f, 0.0210928199473f);
	glVertex2f(-0.0394739459484f, -0.0038489190294f);
	glVertex2f(-0.0561874823761f, -0.0038489190294f);
	glVertex2f(-0.07f, 0.02f);
	glVertex2f(-0.0928213067494f, 0.0193737562841f);
	glVertex2f(-0.1005219155553f, -0.0035770778041f);
	glVertex2f(-0.1198489337347f, -0.0035770778041f);
	glVertex2f(-0.1298005911731f, 0.0209416942113f);
	glVertex2f(-0.1542815368967f, 0.0213674497892f);
	glVertex2f(-0.1653511819196f, -0.0118414852795f);

	glVertex2f(-0.364134320111f, -0.0109512487956f);
	glVertex2f(-0.381864342706f, 0.019852426824f);
	glVertex2f(-0.4148543659489f, 0.0194044926197f);
	glVertex2f(-0.4146310759713f, -0.0116328142776f);
    glVertex2f(-0.4304f, -0.011f);
    glVertex2f(-0.4316011142748f, 0.0196277825974f);
    glVertex2f(-0.4666056383295f, 0.0198569862624f);
    glColor3ub(185,71,0);//RUST
    glVertex2f(-0.4767962352265f, -0.0116701728877f);
    glVertex2f(-0.4938336394137f, -0.0119886290407f);
    glVertex2f(-0.5042296841779f, 0.0195840429704f);
    glVertex2f(-0.5292177595114f, 0.0187647618119f);
    glVertex2f(-0.5357067148962f, -0.0058319497378f);




	glEnd();

	//Sub-body-sets //Windows and Others

	//Line parts in the engine::::
	     //White Lines
         glLineWidth(4.5);
         glBegin(GL_LINES);
         glColor3ub(254, 254, 254);
         glVertex2f(-0.3087733107707f, 0.0631240805117f);
         glVertex2f(0.025076982606f, 0.0611279651552f);
         glEnd();

         //White Lines
         glLineWidth(4.5);
         glBegin(GL_LINES);
         glColor3ub(254, 254, 254);
         glVertex2f(-0.3117674838055f, 0.0481532153378f);
         glVertex2f(0.0255760114451f, 0.0466561288204f);
         glEnd();

         //White Lines
         glLineWidth(4.5);
         glBegin(GL_LINES);
         glColor3ub(5, 5, 5);
         glVertex2f(-0.4092767500757f, 0.0747488325372f);
         glVertex2f(-0.3232534561752f, 0.0743374017706f);
         glEnd();
         //White Lines
         glLineWidth(4.5);
         glBegin(GL_LINES);
         glColor3ub(5, 5, 5);
         glVertex2f(-0.4086083085884f, 0.0593746783285f);
         glVertex2f(-0.3237162396968f, 0.0593746783285f);
         glEnd();
         //White Lines
         glLineWidth(4.5);
         glBegin(GL_LINES);
         glColor3ub(254, 254, 254);
         glVertex2f(-0.5225848583121f, 0.0810704017351f);
         glVertex2f(-0.435643498144f, 0.0810704017351f);
         glEnd();
         //White Lines
         glLineWidth(4.5);
         glBegin(GL_LINES);
         glColor3ub(254, 254, 254);
         glVertex2f(-0.5339636866367f, 0.0535123018863f);
         glVertex2f(-0.4391993819954f, 0.0533345076937f);
         glEnd();


         glLineWidth(10.5);
         glBegin(GL_LINES);
         glColor3ub(136,139,141); // Aluminum
         glVertex2f(-0.5268141933426f, 0.1242799042202f);
         glVertex2f(0.0426908017485f, 0.1222266045001f);
         glEnd();

         //Engine Front Steel Beams
         glLineWidth(8.5);
         glBegin(GL_LINES);
         glColor3ub(54,69,79); // Aluminum plate
         glVertex2f(0.0452354055069f, 0.0417565871767f);
         glVertex2f(0.0452354055069f, -0.0109636017436f);
         glEnd();

         glLineWidth(3.5);
         glBegin(GL_LINES);
         glColor3ub(54,69,79); // Aluminum plate
         glVertex2f(0.0480698242661f, 0.0389221684175f);
         glVertex2f(0.0687610812079f, 0.0162468183443f);
         glEnd();

         glLineWidth(3.5);
         glBegin(GL_LINES);
         glColor3ub(54,69,79); // Aluminum plate
         glVertex2f(0.0690445230838f, 0.0139792833369f);
         glVertex2f(0.0613915924341f, -0.0103967179918f);
         glEnd();

         glLineWidth(4.5);
         glBegin(GL_LINES);
         glColor3ub(54,69,79); // Aluminum plate
         glVertex2f(0.0188753110468f, -0.0137980205028f);
         glVertex2f(0.0669187090145f, -0.0137980205028f);
         glEnd();


         glLineWidth(4.5);
         glBegin(GL_LINES);
         glColor3ub(54,69,79); // Aluminum plate
         glVertex2f(0.0141985200942f, -0.0024603454662f);
         glVertex2f(0.024685869503f, -0.013231136751f);
         glEnd();
	//::::::::::::::::::::::::::::

    glBegin(GL_POLYGON);            // These vertices form a closed polygon
	glColor3ub(5,169,199); // Pacific Blue
	//Box0
    glVertex2f(-0.1259971934397f, 0.092301996608f); //G4
    glVertex2f(-0.0779388473056f, 0.0920884039585f); //H4

    glVertex2f(-0.0779388473056f, 0.0705155463605f); //I4
    glVertex2f(-0.1259971934397f, 0.07072913901f); //j4
    glEnd();

	//Box1
	glBegin(GL_POLYGON);            // These vertices form a closed polygon
	glColor3ub(5,169,199); // Pacific Blue
    glVertex2f(-0.0728292504609f, 0.0922854500128f); //K4
    glVertex2f(-0.0267856348602f, 0.0920646173241f); //L4

    glVertex2f(-0.027006467549f, 0.0702021811396f); //M4
    glVertex2f(-0.0732709158384f, 0.0703125974839f); //N4
    glEnd();
	//Box2
    glBegin(GL_POLYGON);            // These vertices form a closed polygon
	glColor3ub(5,169,199); // Pacific Blue
    glVertex2f(-0.0224047584394f, 0.0920884039585f); //O4
	glVertex2f(0.0236805117665f, 0.0919235576349f); //P4

	glVertex2f(0.0236805117665f, 0.0692290621604f); //Q4
	glVertex2f(-0.022715089869f, 0.0695951024099f); //R4
    glEnd();



	//Box3
    glBegin(GL_POLYGON);
	glColor3ub(136,139,141); // Aluminum
	glVertex2f(-0.36f, 0.02f);
	glVertex2f(-0.1646310280996f, 0.0193306623088f);

	glVertex2f(-0.1726224198394f, -0.0046435129103f);
	glVertex2f(-0.3539655400865f, -0.0037214292481f);
	glEnd();

	//Box4
	glBegin(GL_POLYGON);
	glColor3ub(136,139,141); // Aluminum
	glVertex2f(-0.3248264985519f, 0.1027183715868f);
	glVertex2f(-0.2770527282487f, 0.1027183715868f);

	glVertex2f(-0.2770632476372f, 0.0772726359969f);
	glVertex2f(-0.3248344111814f, 0.0774637206511f);
	glEnd();

	//Box5
	glBegin(GL_POLYGON);
	glColor3ub(136,139,141); // Aluminum
	glVertex2f(-0.3786137504316f, 0.1040547008261f);
	glVertex2f(-0.3301718155089f, 0.1037206185163f);

	glVertex2f(-0.3305058978187f, 0.0759917868018f);
	glVertex2f(-0.3789478327415f, 0.0763258691117f);
	glEnd();

    glPopMatrix();


//////////////////////////////////////////WHEEL////FUNCTION///DECALATION/DESINING///REGION////TRAIN //




//Wheel 1st//ENGINE WHEEL

///////Outer Wheel Steel

         glPushMatrix();
         glTranslatef(_moveTrain, 0.0f, 0.0f);
        //glRotatef(wheel_angle1, 0.0f, 0.0f,1.0f);
        //////////////////////////////

         x= -0.0136806691445f;
         y= -0.0053144350116f;
         radius = 0.0242405696435f;
         tringle1 = 50;

         twicePi = 2.0f * PI;

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(83,86,91); //WHEEL COLOR //Dark Grey
        glVertex2f(x, y);
        for(i = 0; i <= tringle1; i++)
        {
            glVertex2f(
                x + (radius * cos(i *  twicePi / tringle1)),
                y + (radius * sin(i * twicePi / tringle1))
            );
        }

        glEnd();
        //OBJECT END on popping

        glPopMatrix();
///////Inner


        glPushMatrix();
        glTranslatef(_moveTrain, 0.0f, 0.0f);
        //glRotatef(wheel_angle1, 0.0f, 0.0f,1.0f);
        //////////////////////////////




         x= -0.0136806691445;
         y= -0.0053144350116;
         radius = 0.013822671892251509;
         tringle1 = 50;;

         twicePi = 2.0f * PI;

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(190,195,198); //Wheel Rim Color Light Gray
        glVertex2f(x, y);
        for(i = 0; i <= tringle1; i++)
        {
            glVertex2f(
                x + (radius * cos(i *  twicePi / tringle1)),
                y + (radius * sin(i * twicePi / tringle1))
            );
        }
        glEnd();

        glPopMatrix();

        /////

         glPushMatrix();
         glTranslatef(_moveTrain, 0.0f, 0.0f);
         //glRotatef(wheel_angle1, 0.0f, 1.0f,0.0f);


         glLineWidth(4.5);
         glBegin(GL_LINES);
         glColor3ub(5, 5, 5); //Black
         glVertex2f(-0.013662142601f, 0.0188602826741f);
         glVertex2f(-0.013662142601f, -0.0296841399281f);
         glEnd();

         glPopMatrix();



        //OBJECT END on popping
//////////////////////////////////////////
//Wheel 2nd//ENGINE WHEEL

///////Outer Wheel Steel

         glPushMatrix();
         glTranslatef(_moveTrain, 0.0f, 0.0f);
        //glRotatef(wheel_angle1, 0.0f, 0.0f,1.0f);
        //////////////////////////////

         x= -0.0740287053467f;
         y= -0.0040691905186f;
         radius = 0.023796696935299576f;
         tringle1 = 50;

         twicePi = 2.0f * PI;

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(83,86,91); //WHEEL COLOR //Dark Grey
        glVertex2f(x, y);
        for(i = 0; i <= tringle1; i++)
        {
            glVertex2f(
                x + (radius * cos(i *  twicePi / tringle1)),
                y + (radius * sin(i * twicePi / tringle1))
            );
        }

        glEnd();
        //OBJECT END on popping

        glPopMatrix();
///////Inner


        glPushMatrix();
        glTranslatef(_moveTrain, 0.0f, 0.0f);
        //glRotatef(wheel_angle1, 0.0f, 0.0f,1.0f);
        //////////////////////////////

         x= -0.0740287053467f;
         y= -0.0040691905186f;
         radius = 0.015024067949083527f;
         tringle1 = 50;;

         twicePi = 2.0f * PI;

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(190,195,198); //Wheel Rim Color Light Gray
        glVertex2f(x, y);
        for(i = 0; i <= tringle1; i++)
        {
            glVertex2f(
                x + (radius * cos(i *  twicePi / tringle1)),
                y + (radius * sin(i * twicePi / tringle1))
            );
        }
        glEnd();

        glPopMatrix();

        /////
         /*
         glPushMatrix();
         //glRotatef(wheel_angle1, 0.0f, 1.0f,0.0f);


         glLineWidth(4.5);
         glBegin(GL_LINES);
         glColor3ub(5, 5, 5); //Black
         glVertex2f(-0.013662142601f, 0.0188602826741f);
         glVertex2f(-0.013662142601f, -0.0296841399281f);
         glEnd();

         glPopMatrix();
         */


        //OBJECT END on popping

////////////////////////////////////WHEEL////FUNCTION///DECALATION/DESINING///REGION////TRAIN //
/////
//Wheel 3rd//ENGINE WHEEL

///////Outer Wheel Steel

        glPushMatrix();
        glTranslatef(_moveTrain, 0.0f, 0.0f);
        //glRotatef(wheel_angle1, 0.0f, 0.0f,1.0f);
        //////////////////////////////

         x= -0.1346950271965f;
         y= -0.0042321938514f;
         radius = 0.023283819059376605f;
         tringle1 = 50;

         twicePi = 2.0f * PI;

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(83,86,91); //WHEEL COLOR //Dark Grey
        glVertex2f(x, y);
        for(i = 0; i <= tringle1; i++)
        {
            glVertex2f(
                x + (radius * cos(i *  twicePi / tringle1)),
                y + (radius * sin(i * twicePi / tringle1))
            );
        }

        glEnd();
        //OBJECT END on popping

        glPopMatrix();
///////Inner


        glPushMatrix();
        glTranslatef(_moveTrain, 0.0f, 0.0f);
        //glRotatef(wheel_angle1, 0.0f, 0.0f,1.0f);
        //////////////////////////////

         x= -0.1346950271965f;
         y= -0.0042321938514f;
         radius = 0.017504343840605875f;
         tringle1 = 50;;

         twicePi = 2.0f * PI;

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(190,195,198); //Wheel Rim Color Light Gray
        glVertex2f(x, y);
        for(i = 0; i <= tringle1; i++)
        {
            glVertex2f(
                x + (radius * cos(i *  twicePi / tringle1)),
                y + (radius * sin(i * twicePi / tringle1))
            );
        }
        glEnd();

        glPopMatrix();

        /////

         //glPushMatrix();
         //glRotatef(wheel_angle1, 1.0f, 0.0f,0.0f);

/*
         glLineWidth(4.5);
         glBegin(GL_LINES);
         glColor3ub(5, 5, 5); //Black
         glVertex2f(-0.013662142601f, 0.0188602826741f);
         glVertex2f(-0.013662142601f, -0.0296841399281f);
         glEnd();
*/
         //glPopMatrix();



        //OBJECT END on popping
/////////
//Wheel 4th//ENGINE WHEEL

///////Outer Wheel Steel

         glPushMatrix();
         glTranslatef(_moveTrain, 0.0f, 0.0f);
        //glRotatef(wheel_angle1, 0.0f, 0.0f,1.0f);
        //////////////////////////////

         x= -0.3933713872878f;
         y= -0.0038997852668f;
         radius = 0.024191343403391737f;
         tringle1 = 50;

         twicePi = 2.0f * PI;

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(83,86,91); //WHEEL COLOR //Dark Grey
        glVertex2f(x, y);
        for(i = 0; i <= tringle1; i++)
        {
            glVertex2f(
                x + (radius * cos(i *  twicePi / tringle1)),
                y + (radius * sin(i * twicePi / tringle1))
            );
        }

        glEnd();
        //OBJECT END on popping

        glPopMatrix();
///////Inner


        glPushMatrix();
        glTranslatef(_moveTrain, 0.0f, 0.0f);
        //glRotatef(wheel_angle1, 0.0f, 0.0f,1.0f);
        //////////////////////////////

         x= -0.3933713872878f;
         y= -0.0038997852668f;
         radius = 0.018015012492399965f;
         tringle1 = 50;;

         twicePi = 2.0f * PI;

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(190,195,198); //Wheel Rim Color Light Gray
        glVertex2f(x, y);
        for(i = 0; i <= tringle1; i++)
        {
            glVertex2f(
                x + (radius * cos(i *  twicePi / tringle1)),
                y + (radius * sin(i * twicePi / tringle1))
            );
        }
        glEnd();

        glPopMatrix();

        /////

         glPushMatrix();
         glTranslatef(_moveTrain, 0.0f, 0.0f);
         glRotatef(wheel_angle1, 1.0f, 0.0f,0.0f);


         glLineWidth(4.5);
         glBegin(GL_LINES);
         glColor3ub(5, 5, 5); //Black
         glVertex2f(-0.4150502545059f, -0.0022979998044f);
         glVertex2f(-0.3719171385735f, -0.0020801557845f);
         glEnd();

         glPopMatrix();



        //OBJECT END on popping
//////////
//Wheel 5th//ENGINE WHEEL

///////Outer Wheel Steel

         glPushMatrix();
         glTranslatef(_moveTrain, 0.0f, 0.0f);
        //glRotatef(wheel_angle1, 0.0f, 0.0f,1.0f);
        //////////////////////////////

         x= -0.4532618270733f;
         y= -0.0033827327304f;
         radius = 0.024025434923832783f;
         tringle1 = 50;

         twicePi = 2.0f * PI;

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(83,86,91); //WHEEL COLOR //Dark Grey
        glVertex2f(x, y);
        for(i = 0; i <= tringle1; i++)
        {
            glVertex2f(
                x + (radius * cos(i *  twicePi / tringle1)),
                y + (radius * sin(i * twicePi / tringle1))
            );
        }

        glEnd();
        //OBJECT END on popping

        glPopMatrix();
///////Inner


        glPushMatrix();
        glTranslatef(_moveTrain, 0.0f, 0.0f);
        //glRotatef(wheel_angle1, 1.0f, 0.0f,0.0f);
        //////////////////////////////

         x= -0.4532618270733f;
         y= -0.0033827327304f;
         radius = 0.018449996849126283;
         tringle1 = 50;;

         twicePi = 2.0f * PI;

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(190,195,198); //Wheel Rim Color Light Gray
        glVertex2f(x, y);
        for(i = 0; i <= tringle1; i++)
        {
            glVertex2f(
                x + (radius * cos(i *  twicePi / tringle1)),
                y + (radius * sin(i * twicePi / tringle1))
            );
        }
        glEnd();

        glPopMatrix();

        /////

         glPushMatrix();
         glTranslatef(_moveTrain, 0.0f, 0.0f);
         glRotatef(wheel_angle1, 1.0f, 0.0f,0.0f);


         glLineWidth(4.5);
         glBegin(GL_LINES);
         glColor3ub(5, 5, 5); //Black
         glVertex2f(-0.4705644222454f, -0.0030105277753f);
         glVertex2f(-0.4362919538154f, -0.0030105277753f);
         glEnd();

         glPopMatrix();



        //OBJECT END on popping

/////////
//Wheel 6th//ENGINE WHEEL

///////Outer Wheel Steel

         glPushMatrix();
         glTranslatef(_moveTrain, 0.0f, 0.0f);
        //glRotatef(wheel_angle1, 0.0f, 0.0f,1.0f);
        //////////////////////////////

         x= -0.5137709454626f;
         y= -0.0035412551748f;
         radius = 0.022985754448632368f;
         tringle1 = 50;

         twicePi = 2.0f * PI;

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(83,86,91); //WHEEL COLOR //Dark Grey
        glVertex2f(x, y);
        for(i = 0; i <= tringle1; i++)
        {
            glVertex2f(
                x + (radius * cos(i *  twicePi / tringle1)),
                y + (radius * sin(i * twicePi / tringle1))
            );
        }

        glEnd();
        //OBJECT END on popping

        glPopMatrix();
///////Inner


        glPushMatrix();
        glTranslatef(_moveTrain, 0.0f, 0.0f);
        //glRotatef(wheel_angle1, 0.0f, 0.0f,1.0f);
        //////////////////////////////

         x= -0.5137709454626f;
         y= -0.0035412551748f;
         radius = 0.018125015693723365;
         tringle1 = 50;;

         twicePi = 2.0f * PI;

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(190,195,198); //Wheel Rim Color Light Gray
        glVertex2f(x, y);
        for(i = 0; i <= tringle1; i++)
        {
            glVertex2f(
                x + (radius * cos(i *  twicePi / tringle1)),
                y + (radius * sin(i * twicePi / tringle1))
            );
        }
        glEnd();

        glPopMatrix();

        /////

         glPushMatrix();
         glTranslatef(_moveTrain, 0.0f, 0.0f);
         glRotatef(wheel_angle1, 1.0f, 0.0f,0.0f);


         glLineWidth(4.5);
         glBegin(GL_LINES);
         glColor3ub(5, 5, 5); //Black
         glVertex2f(-0.531068510743f, -0.0036696137066f);
         glVertex2f(-0.496796042313f, -0.0035377965204f);
         glEnd();

         glPopMatrix();



        //OBJECT END on popping

///////////////////////////////////////////////////////////////////////////////////////'s Closure For Train



     //out of the pipeline
    glutSwapBuffers();

}


//TRAIN FUNCTIONS//
void Wheel_Rotation_Update(int value) {

    wheel_angle1+=4.0f;
    if(wheel_angle1 > 360.0)
    {
        wheel_angle1-=360;
    }
	glutPostRedisplay(); //Notify GLUT that the display has changed

	glutTimerFunc(20, Wheel_Rotation_Update, 0); //Notify GLUT to call update again in 25 milliseconds
}

//movement of train - Translating stage
void Wheel_Translation_update(int value) {

 _moveTrain += .02;
if(_moveTrain > 1.3)
{
_moveTrain = -1.0;
}
glutPostRedisplay();
glutTimerFunc(96, Wheel_Translation_update, 0);
}

///////////////////////////////WARNING//TRAIN SECTION IS LONG ONE///////////////////////

////////////////////////////////////ANOMALY/////////////
void update(int value)
{
 //what this update function does? I need to know
    if(position <-1.0)
        position = 1.0f;

    position -= speed;

glutPostRedisplay();


glutTimerFunc(100, update, 0);
}
////////////////////////////////////ANOMALY/////////////

void Sun(){  //SUN-PORTION
    int i;
    GLfloat x=0.9f;
    GLfloat y=0.9f;
    GLfloat radius =0.2f;
    int tringle1 = 100; //above 5 means perfect circle //20 means amount of Lines in the Hexagon

    GLfloat twicePi = 2.0f * PI; //PI = 3.1416

    glBegin(GL_POLYGON);
    glColor3ub(245, 245, 40); //Color:- Yellow
    glVertex2f(x, y);
    for(i = 0; i <= tringle1; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / tringle1)),
            y + (radius * sin(i * twicePi / tringle1))
        );
    }
    glEnd();

}

void Moon()
{
    int i;

    GLfloat x=0.9f;
    GLfloat y=0.9f;
    GLfloat radius =0.2f;
    int triangleAmount = 100;

    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(236, 236, 236);
    glVertex2f(x, y);
    for(i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void DayRiver(){
    glBegin(GL_QUADS);
    glColor3ub(32, 160, 180); //Color: Peacock Blue
    glVertex2f(-1.0f,-0.26f); // 3RD Q x, y
    glVertex2f(-1.0f,-1.0f);
    glVertex2f(1.0f,-1.0f);
    glVertex2f(1.0f,-0.26f);
    glEnd();




}

void RiverSide(){
            //
            glPushMatrix();
            glTranslatef(position,0.01f, 0.0f);
            glBegin(GL_POLYGON);//Top Boat
            glColor3ub(0,0,0);
            glVertex2f(0.596f, -0.606f);
            glVertex2f(0.456f, -0.566f);
            glVertex2f(0.489f, -0.649f);
            glVertex2f(0.696f, -0.657f);
            glVertex2f(0.722f, -0.578f);
            glEnd();
            glBegin(GL_POLYGON);//Stripe
            glColor3ub(244,52,52);
            glVertex2f(0.589f, -0.629f);
            glVertex2f(0.713f, -0.606f);
            glVertex2f(0.704f, -0.629f);
            glVertex2f(0.591f, -0.653f);
            glVertex2f(0.476f, -0.621f);
            glVertex2f(0.469f, -0.598f);
            glEnd();
            glBegin(GL_POLYGON);//Outside hood
            glColor3ub(233,178,58);
            glVertex2f(0.607f, -0.606f);
            glVertex2f(0.551f, -0.594f);
            glVertex2f(0.553f, -0.507f);
            glVertex2f(0.567f, -0.487f);
            glVertex2f(0.673f, -0.491f);
            glVertex2f(0.682f, -0.515f);
            glVertex2f(0.684f, -0.594f);
            glEnd();
            glBegin(GL_POLYGON);//Inside hood
            glColor3ub(141,97,22);
            glVertex2f(0.604f, -0.523f);
            glVertex2f(0.604f, -0.606f);
            glVertex2f(0.607f, -0.606f);
            glVertex2f(0.558f, -0.594f);
            glVertex2f(0.560f, -0.515f);
            glVertex2f(0.571f, -0.499f);
            glVertex2f(0.593f, -0.499f);
            glEnd();
            glBegin(GL_POLYGON);//Bambooooo
            glColor3ub(141,97,22);
            glVertex2f(0.624f, -0.491f);
            glVertex2f(0.624f, -0.357f);
            glVertex2f(0.633f, -0.357f);
            glVertex2f(0.633f, -0.491f);
            glEnd();
            glBegin(GL_POLYGON);//Sailing portion
            glColor3ub(244,42,42);
            glVertex2f(0.698f, -0.436f);
            glVertex2f(0.704f, -0.364f);
            glVertex2f(0.582f, -0.364f);
            glVertex2f(0.571f, -0.428f);
            glVertex2f(0.580f, -0.475f);
            glVertex2f(0.711f, -0.475f);
            glEnd();
            glBegin(GL_POLYGON);//Bottom body
            glColor3ub(255,255,255);
            glVertex2f(0.518f, -0.542f);
            glVertex2f(0.482f, -0.538f);
            glVertex2f(0.480f, -0.57f);
            glVertex2f(0.527f, -0.586f);
            glEnd();
            glBegin(GL_POLYGON);//Upper body(Chest)
            glColor3ub(255,255,255);
            glVertex2f(0.502f, -0.542f);
            glVertex2f(0.489f, -0.542f);
            glVertex2f(0.484f, -0.503f);
            glVertex2f(0.509f, -0.503f);
            glEnd();
            glBegin(GL_POLYGON);//Face
            glColor3ub(255,219,143);
            glVertex2f(0.504f, -0.491f);
            glVertex2f(0.500f, -0.511f);
            glVertex2f(0.491f, -0.507f);
            glVertex2f(0.491f, -0.475f);
            glVertex2f(0.500f, -0.475f);
            glEnd();
            glBegin(GL_POLYGON);//Hair
            glColor3ub(0,0,0);
            glVertex2f(0.500f, -0.475f);
            glVertex2f(0.500f, -0.467f);
            glVertex2f(0.487f, -0.467f);
            glVertex2f(0.489f, -0.483f);
            glEnd();
            glBegin(GL_POLYGON);//Boat Paddle
            glColor3ub(0,0,0);
            glVertex2f(0.480f, -0.72f);
            glVertex2f(0.504f, -0.542f);
            glVertex2f(0.462f, -0.72f);
            glEnd();
            glPopMatrix();


            glPushMatrix();//Bottom Boat
            glTranslatef(-position,0.0f, 0.0f);
            glBegin(GL_POLYGON);
            glColor3ub(230,151,61);
            glVertex2f(-0.024f, -0.878f);
            glVertex2f(0.029f, -0.795f);
            glVertex2f(-0.229f, -0.795f);
            glVertex2f(-0.198f, -0.878f);
            glEnd();
            glBegin(GL_POLYGON);//Boat stripe bottom one
            glColor3ub(154,101,40);
            glVertex2f(-0.013f, -0.866f);
            glVertex2f(-0.004f, -0.847f);
            glVertex2f(-0.211f, -0.847f);
            glVertex2f(-0.204f, -0.862f);
            glEnd();
            glBegin(GL_POLYGON);//Boat stripe top one
            glColor3ub(154,101,40);
            glVertex2f(-0.002f, -0.839f);
            glVertex2f(-0.216f, -0.835f);
            glVertex2f(-0.218f, -0.819f);
            glVertex2f(0.011f, -0.823f);
            glEnd();
            glBegin(GL_POLYGON);//Bottom body
            glColor3ub(255,255,255);
            glVertex2f(-0.167f, -0.728f);
            glVertex2f(-0.202f, -0.728f);
            glVertex2f(-0.202f, -0.799f);
            glVertex2f(-0.142f, -0.795f);
            glEnd();
            glBegin(GL_POLYGON);//Upper body(Chest)
            glColor3ub(255,255,255);
            glVertex2f(-0.180f, -0.728f);
            glVertex2f(-0.196f, -0.732f);
            glVertex2f(-0.202f, -0.669f);
            glVertex2f(-0.173f, -0.669f);
            glEnd();
            glBegin(GL_POLYGON);//Face
            glColor3ub(255,195,92);
            glVertex2f(-0.176f, -0.649f);
            glVertex2f(-0.184f, -0.625f);
            glVertex2f(-0.200f, -0.629f);
            glVertex2f(-0.196f, -0.673f);
            glVertex2f(-0.182f, -0.669f);
            glEnd();
            glBegin(GL_POLYGON);//Hair
            glColor3ub(0,0,0);
            glVertex2f(-0.191f, -0.617f);
            glVertex2f(-0.202f, -0.629f);
            glVertex2f(-0.200f, -0.633f);
            glVertex2f(-0.184f, -0.629f);
            glVertex2f(-0.182f, -0.617f);
            glEnd();
            glBegin(GL_POLYGON); //Boat Paddle
            glColor3ub(0,0,0);
            glVertex2f(-0.211f, -0.93f);
            glVertex2f(-0.180f, -0.732f);
            glVertex2f(-0.200f, -0.926f);
            glEnd();

           glPopMatrix();



           //Grass Left side
            glBegin(GL_POLYGON);
            glColor3ub(77,201,24); //Green
            glVertex2f(-0.844f, -0.26f);
            glVertex2f(-0.467f, -0.89f);
            glColor3ub(170,219,30); //Bright Green
            glVertex2f(-0.467f, -1.005f);
            glVertex2f(-1.10f, -0.997f);
            glColor3ub(120,190,33); //Lime Green
            glVertex2f(-1.000f, -0.26f);
            glEnd();
            //Soil Left side
            glBegin(GL_POLYGON);
            glColor3ub(131,82,42);
            glVertex2f(-0.467f, -0.902f);
            glVertex2f(-0.467f, -1.001f);
            glVertex2f(-0.447f, -1.001f);
            glVertex2f(-0.447f, -0.902f);
            glVertex2f(-0.840f, -0.266f);
            glVertex2f(-0.842f, -0.266f);
            glEnd();

            //Tree 1
             glBegin(GL_POLYGON);//Tree body//Bark
            glColor3ub(145,99,18); //BROWN
            glVertex2f(-0.882f, -0.57f);
            glVertex2f(-0.889f, -0.428f);
            glVertex2f(-0.900f, -0.428f);
            glVertex2f(-0.904f, -0.578f);
            glVertex2f(-0.920f, -0.602f);
            glVertex2f(-0.896f, -0.578f);
            glVertex2f(-0.889f, -0.606f);
            glVertex2f(-0.889f, -0.578f);
            glVertex2f(-0.864f, -0.582f);
            glEnd();

            glBegin(GL_POLYGON);//Leaves portion
            glColor3ub(38,161,40); //Green
            glVertex2f(-0.896f, -0.325f);
            glVertex2f(-0.889f, -0.301f);
            glColor3ub(120,190,33); //Lime Green
            glVertex2f(-0.882f, -0.285f);
            glVertex2f(-0.867f, -0.293f);
            glVertex2f(-0.851f, -0.313f);
            glVertex2f(-0.849f, -0.341f);
            glVertex2f(-0.860f, -0.357f);
            glColor3ub(0,135,62); //Christmas Green
            glVertex2f(-0.860f, -0.368f);
            glVertex2f(-0.847f, -0.38f);
            glVertex2f(-0.847f, -0.412f);
            glVertex2f(-0.860f, -0.432f);
            glColor3ub(113,169,44); //Corn Green
            glVertex2f(-0.871f, -0.443f);
            glVertex2f(-0.882f, -0.44f);
            glVertex2f(-0.887f, -0.436f);
            glVertex2f(-0.900f, -0.428f);
            glVertex2f(-0.922f, -0.455f);
            glVertex2f(-0.933f, -0.447f);
            glVertex2f(-0.942f, -0.432f);
            glVertex2f(-0.947f, -0.412f);
            glVertex2f(-0.940f, -0.392f);
            glColor3ub(113,169,44); //Corn Green
            glVertex2f(-0.927f, -0.38f);
            glVertex2f(-0.940f, -0.364f);
            glVertex2f(-0.949f, -0.345f);
            glVertex2f(-0.949f, -0.333f);
            glColor3ub(0,110,51); //Forest Green
            glVertex2f(-0.942f, -0.309f);
            glVertex2f(-0.929f, -0.297f);
            glVertex2f(-0.907f, -0.305f);
            glEnd();

            glPushMatrix();//Tree 2
            glTranslatef(-0.090,-0.060, 0.0f);
            glBegin(GL_POLYGON);//Tree body// Bark
            glColor3ub(145,99,18);
            glVertex2f(-0.882f, -0.57f);
            glVertex2f(-0.889f, -0.428f);
            glVertex2f(-0.900f, -0.428f);
            glVertex2f(-0.904f, -0.578f);
            glVertex2f(-0.920f, -0.602f);
            glVertex2f(-0.896f, -0.578f);
            glVertex2f(-0.889f, -0.606f);
            glVertex2f(-0.889f, -0.578f);
            glVertex2f(-0.864f, -0.582f);
            glEnd();

            glBegin(GL_POLYGON);//Leaves Portion
            glColor3ub(38,161,40);
            glVertex2f(-0.896f, -0.325f);
            glColor3ub(0,110,51); //Forest Green
            glVertex2f(-0.889f, -0.301f);
            glVertex2f(-0.882f, -0.285f);
            glVertex2f(-0.867f, -0.293f);
            glVertex2f(-0.851f, -0.313f);
            glVertex2f(-0.849f, -0.341f);
            glColor3ub(0,135,62); //Christmas Green
            glVertex2f(-0.860f, -0.357f);
            glVertex2f(-0.860f, -0.368f);
            glVertex2f(-0.847f, -0.38f);
            glVertex2f(-0.847f, -0.412f);
            glColor3ub(113,169,44); //Corn Green
            glVertex2f(-0.860f, -0.432f);
            glVertex2f(-0.871f, -0.443f);
            glVertex2f(-0.882f, -0.44f);
            glVertex2f(-0.887f, -0.436f);
            glVertex2f(-0.900f, -0.428f);
            glColor3ub(0,135,62); //Christmas Green
            glVertex2f(-0.922f, -0.455f);
            glVertex2f(-0.933f, -0.447f);
            glVertex2f(-0.942f, -0.432f);
            glVertex2f(-0.947f, -0.412f);
            glColor3ub(113,169,44); //Corn Green
            glVertex2f(-0.940f, -0.392f);
            glVertex2f(-0.927f, -0.38f);
            glVertex2f(-0.940f, -0.364f);
            glColor3ub(0,110,51); //Forest Green
            glVertex2f(-0.949f, -0.345f);
            glVertex2f(-0.949f, -0.333f);
            glVertex2f(-0.942f, -0.309f);
            glVertex2f(-0.929f, -0.297f);
            glVertex2f(-0.907f, -0.305f);
            glEnd();
            glPopMatrix();


            glPushMatrix();//Tree 3
            glTranslatef(-0.030,-0.4, 0.0f);
            glBegin(GL_POLYGON);//Tree body//Bark
            glColor3ub(145,99,18);
            glVertex2f(-0.882f, -0.57f);
            glVertex2f(-0.889f, -0.428f);
            glVertex2f(-0.900f, -0.428f);
            glVertex2f(-0.904f, -0.578f);
            glVertex2f(-0.920f, -0.602f);
            glVertex2f(-0.896f, -0.578f);
            glVertex2f(-0.889f, -0.606f);
            glVertex2f(-0.889f, -0.578f);
            glVertex2f(-0.864f, -0.582f);
            glEnd();

            glBegin(GL_POLYGON);//Leaves Portion
            glColor3ub(38,161,40);
            glVertex2f(-0.896f, -0.325f);
            glVertex2f(-0.889f, -0.301f);
            glVertex2f(-0.882f, -0.285f);
            glColor3ub(113,169,44); //Corn Green
            glVertex2f(-0.867f, -0.293f);
            glVertex2f(-0.851f, -0.313f);
            glVertex2f(-0.849f, -0.341f);
            glVertex2f(-0.860f, -0.357f);
            glVertex2f(-0.860f, -0.368f);
            glColor3ub(113,169,44); //Corn Green
            glVertex2f(-0.847f, -0.38f);
            glVertex2f(-0.847f, -0.412f);
            glColor3ub(0,110,51); //Forest Green
            glVertex2f(-0.860f, -0.432f);
            glVertex2f(-0.871f, -0.443f);
            glVertex2f(-0.882f, -0.44f);
            glVertex2f(-0.887f, -0.436f);
            glVertex2f(-0.900f, -0.428f);
            glVertex2f(-0.922f, -0.455f);
            glVertex2f(-0.933f, -0.447f);
            glColor3ub(0,110,51); //Forest Green
            glVertex2f(-0.942f, -0.432f);
            glVertex2f(-0.947f, -0.412f);
            glVertex2f(-0.940f, -0.392f);
            glVertex2f(-0.927f, -0.38f);
            glColor3ub(0,135,62); //Christmas Green
            glVertex2f(-0.940f, -0.364f);
            glVertex2f(-0.949f, -0.345f);
            glVertex2f(-0.949f, -0.333f);
            glVertex2f(-0.942f, -0.309f);
            glVertex2f(-0.929f, -0.297f);
            glVertex2f(-0.907f, -0.305f);
            glEnd();
            glPopMatrix();


            glPushMatrix();//Tree 4
            glTranslatef(0.1,-0.4, 0.0f);
            glBegin(GL_POLYGON);//Tree body//Bark
            glColor3ub(145,99,18);
            glVertex2f(-0.882f, -0.57f);
            glVertex2f(-0.889f, -0.428f);
            glVertex2f(-0.900f, -0.428f);
            glVertex2f(-0.904f, -0.578f);
            glVertex2f(-0.920f, -0.602f);
            glVertex2f(-0.896f, -0.578f);
            glVertex2f(-0.889f, -0.606f);
            glVertex2f(-0.889f, -0.578f);
            glVertex2f(-0.864f, -0.582f);
            glEnd();

            glBegin(GL_POLYGON);//Leaves Portion
            glColor3ub(38,161,40);
            glVertex2f(-0.896f, -0.325f);
            glVertex2f(-0.889f, -0.301f);
            glVertex2f(-0.882f, -0.285f);
            glColor3ub(0,135,62); //Christmas Green
            glVertex2f(-0.867f, -0.293f);
            glVertex2f(-0.851f, -0.313f);
            glVertex2f(-0.849f, -0.341f);
            glVertex2f(-0.860f, -0.357f);
            glVertex2f(-0.860f, -0.368f);
            glVertex2f(-0.847f, -0.38f);
            glColor3ub(0,110,51); //Forest Green
            glVertex2f(-0.847f, -0.412f);
            glVertex2f(-0.860f, -0.432f);
            glVertex2f(-0.871f, -0.443f);
            glVertex2f(-0.882f, -0.44f);
            glVertex2f(-0.887f, -0.436f);
            glVertex2f(-0.900f, -0.428f);
            glVertex2f(-0.922f, -0.455f);
            glVertex2f(-0.933f, -0.447f);
            glVertex2f(-0.942f, -0.432f);
            glVertex2f(-0.947f, -0.412f);
            glColor3ub(0,135,62); //Christmas Green
            glVertex2f(-0.940f, -0.392f);
            glVertex2f(-0.927f, -0.38f);
            glVertex2f(-0.940f, -0.364f);
            glVertex2f(-0.949f, -0.345f);
            glVertex2f(-0.949f, -0.333f);
            glColor3ub(120,190,33); //Lime Green
            glVertex2f(-0.942f, -0.309f);
            glVertex2f(-0.929f, -0.297f);
            glVertex2f(-0.907f, -0.305f);
            glEnd();
            glPopMatrix();

            //Grass Right side

            glBegin(GL_POLYGON);
            glColor3ub(77,201,24);
            glVertex2f(1.000f, -0.260f);
            glColor3ub(120,190,33); //Lime Green
            glVertex2f(0.942f, -0.260f);
            glVertex2f(1.002f, -0.396f);
            glEnd();
            //Soil Right side
            glBegin(GL_POLYGON);
            glColor3ub(131,82,42);
            glVertex2f(1.00f, -0.396f);
            glVertex2f(0.942f, -0.260f);
            glVertex2f(1.002f, -0.424f);
            glEnd();
            //


}

//AM
void DaySky(){
    glBegin(GL_QUADS);
    glColor3ub(57, 162, 244);
    glVertex2f(-1.0f,1.0f);
    glColor3ub(177, 231, 247);
    glVertex2f(-1.0f,-0.15f);
    glVertex2f(1.0f,-0.15f);
    glVertex2f(1.0f,1.0f);
    glEnd();

}

void NightSky()
{
    glBegin(GL_QUADS);
    glColor3ub(3, 55, 95);
    glVertex2f(-1.0f,1.0f);
    glColor3ub(10, 15, 25);
    glVertex2f(-1.0f,-0.15f);
    glVertex2f(1.0f,-0.15f);
    glVertex2f(1.0f,1.0f);
    glEnd();
}

void MonsoonSky()
{
    glBegin(GL_QUADS);
    glColor3ub(0,61,108);
    glVertex2f(-1.0f,1.0f);
    glVertex2f(-1.0f,-0.15f);
    glColor3ub(109, 116, 130);
    glVertex2f(1.0f,-0.15f);
    glVertex2f(1.0f,1.0f);
    glEnd();
}

void CircleForCloud(GLfloat a, GLfloat b, GLfloat r){
    int i;
    GLfloat x= a;
    GLfloat y= b;
    GLfloat radius = r;
    int tringle1 = 20;

    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(216, 220, 229);
    glVertex2f(x, y);
    for(i = 0; i <= tringle1; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / tringle1)),
            y + (radius * sin(i * twicePi / tringle1))
        );
    }
    glEnd();

}

void Cloud1()
{
    CircleForCloud(-0.93f, 0.8f, 0.05f);
    CircleForCloud(-0.88f, 0.82f, 0.05f);
    CircleForCloud(-0.83f, 0.85f, 0.06f);
    CircleForCloud(-0.78f, 0.82f, 0.06f);
    CircleForCloud(-0.73f, 0.78f, 0.04f);
    CircleForCloud(-0.75f, 0.75f, 0.05f);
    CircleForCloud(-0.78f, 0.74f, 0.04f);
    CircleForCloud(-0.81f, 0.71f, 0.05f);
    CircleForCloud(-0.84f, 0.78f, 0.04f);
    CircleForCloud(-0.87f, 0.7f, 0.05f);
    CircleForCloud(-0.9f, 0.75f, 0.04f);

}

void CloudAnimation1(int value)
{
    if(CloudPosition1 > 1.8)
        CloudPosition1 = -1.6f;

    CloudPosition1 += CloudSpeed1;

    glutPostRedisplay();

    glutTimerFunc(40, CloudAnimation1, 0);
}

void Cloud2()
{
    CircleForCloud(0.93f, 0.8f, 0.05f);
    CircleForCloud(0.85f, 0.82f, 0.05f);
    CircleForCloud(0.8f, 0.85f, 0.06f);
    CircleForCloud(0.75f, 0.82f, 0.06f);
    CircleForCloud(0.7f, 0.78f, 0.04f);
    CircleForCloud(0.73f, 0.75f, 0.05f);
    CircleForCloud(0.78f, 0.76f, 0.04f);
    CircleForCloud(0.81f, 0.71f, 0.05f);
    CircleForCloud(0.84f, 0.78f, 0.04f);
    CircleForCloud(0.87f, 0.7f, 0.05f);
    CircleForCloud(0.9f, 0.75f, 0.04f);
}

void CloudAnimation2(int value)
{
    if(CloudPosition2 > 1.0)
        CloudPosition2 = -1.0f;

    CloudPosition2 += CloudSpeed2;
    glutPostRedisplay();

    glutTimerFunc(40, CloudAnimation2, 0);
}
///////////////////////////////////////////////RAIN-PORTION//////////////////////////////////////////
void RainAnimation(int value)
{

    if(RainPos <0.6) //Greater than 0.6 to 1.0
        RainPos = 1;

    RainPos -= 0.1; //RainPos = RainPos - 0.1

    glutPostRedisplay();

    //69ms / 69miliseconds //object movement will be slower if X ms increases.
    glutTimerFunc(69, RainAnimation, 0);
}

void Rain(GLfloat a, GLfloat b)
{
	glLineWidth(0.1); //Line or Tarin Drop Thickness
	glBegin(GL_LINES);
	glColor3ub(255,255,255); //White Color
	glVertex2f(a,b);
	glVertex2f(a-0.05,b-0.05); //Rain Drop Size in stick format

	glEnd();
}

void RainFall()
{
    float Y = 2.0; //Y START <-This Values will decide over
    //how rain falls in the screen
    //corner to corner specifically.

    for(int i=0; i<30; i++) //normal limit that the loop uses to get most correct
                            //trasnaltion factor.
    {
        float X = -3.0; //X START

        for(int j=0; j<45; j++)
        {
            X += 0.2 ; //X = X + 0.2

            Rain(X , Y);

        }
        Y -=0.2; //Y = Y - 0.2

    }
}
///////////////////////////////////////////////RAIN-PORTION//////////////////////////////////////////




// //Shader applied on Birds [Type: Kingfisher]
void Birds()//Birds
{
    //1st Bird
    glTranslatef(0.0,-0.2f, 0.0f);

    //Belly area
    glBegin(GL_POLYGON);

    glColor3ub(0,138,216); //Color:- Azure Blue

    glVertex2f(0.1f,0.8f);
    glVertex2f(0.11f,0.79f);
    glColor3ub(249,101,21); //Color:- Tiger Orange
    glVertex2f(0.12f,0.78f);
    glVertex2f(0.16f,0.77f);
    glColor3ub(203,96,21);  //Color:- BURNT ORANGE
    glVertex2f(0.19f,0.79f);
    glVertex2f(0.201f,0.8f);
    glEnd();

    //3rd Triangle as 2nd Wing
    glBegin(GL_TRIANGLES);
    glColor3ub(5,195,221); //Color:- AQUA BLUE
    glVertex2f(0.175f,0.8f);
    glVertex2f(0.15f,0.8f);
    glVertex2f(0.14f,0.84f);
    glEnd();

    //2nd Triangle as 1st a
    glBegin(GL_TRIANGLES);
    glColor3ub(0,138,216); //Color :- Azure Blue
    glVertex2f(0.175f,0.8f);
    glVertex2f(0.144f,0.8f);
    glVertex2f(0.12f,0.83f);
    glEnd();


	/////2nd bird////
	glBegin(GL_POLYGON);

    glColor3ub(0,138,216); //Color:- Azure Blue

    glVertex2f(-0.02f,0.8f);
    glVertex2f(-0.01f,0.79f);
    glColor3ub(249,101,21); //Color:- Tiger Orange
    glVertex2f(0.0f,0.78f);
    glVertex2f(0.04f,0.77f);
    glColor3ub(203,96,21);  //Color:- BURNT ORANGE
    glVertex2f(0.07f,0.79f);
    glVertex2f(0.081f,0.8f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(5,195,221); //Color:- AQUA BLUE
    glVertex2f(0.055f,0.8f);
    glVertex2f(0.03f,0.8f);
    glVertex2f(0.02f,0.84f);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3ub(0,138,216); //Color :- Azure Blue
    glVertex2f(0.055f,0.8f);
    glVertex2f(0.024f,0.8f);
    glVertex2f(0.0f,0.83f);
    glEnd();

    /////3rd bird/////
	glBegin(GL_POLYGON);

    glColor3ub(0,138,216); //Color:- Azure Blue

    glVertex2f(-0.72f,0.8f);
    glVertex2f(-0.71f,0.79f);
    glColor3ub(249,101,21); //Color:- Tiger Orange
    glVertex2f(-0.7f,0.78f);
    glVertex2f(-0.66f,0.77f);
    glColor3ub(203,96,21);  //Color:- BURNT ORANGE
    glVertex2f(-0.63f,0.79f);
    glVertex2f(-0.619f,0.8f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(5,195,221); //Color:- AQUA BLUE
    glVertex2f(-0.645f,0.8f);
    glVertex2f(-0.67f,0.8f);
    glVertex2f(-0.68f,0.84f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(0,138,216); //Color :- Azure Blue
    glVertex2f(-0.645f,0.8f);
    glVertex2f(-0.676f,0.8f);
    glVertex2f(-0.7f,0.83f);
    glEnd();

    //4th Bird
    glBegin(GL_POLYGON);

    glColor3ub(0,138,216); //Color:- Azure Blue

    glVertex2f(-0.6f,0.8f);
    glVertex2f(-0.59f,0.79f);
    glColor3ub(249,101,21); //Color:- Tiger Orange
    glVertex2f(-0.58f,0.78f);
    glVertex2f(-0.54f,0.77f);
    glColor3ub(203,96,21);  //Color:- BURNT ORANGE
    glVertex2f(-0.51f,0.79f);
    glVertex2f(-0.499f,0.8f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(5,195,221); //Color:- AQUA BLUE
    glVertex2f(-0.525f,0.8f);
    glVertex2f(-0.55f,0.8f);
    glVertex2f(-0.56f,0.84f);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3ub(0,138,216); //Color :- Azure Blue
    glVertex2f(-0.525f,0.8f);
    glVertex2f(-0.556f,0.8f);
    glVertex2f(-0.58f,0.83f);
    glEnd();
}

void BirdsAnimation(int value)
{
    if(BirdsPosition > 1.0)
        BirdsPosition = -1.0f;

    BirdsPosition += BirdsSpeed;
    glutPostRedisplay();

    glutTimerFunc(20, BirdsAnimation, 0);
}

void Bridge(){
  /* ====================*/
    ////////////////////////////////////////////////////////////////// SANI //Separate REGION
            ////Base Line [steel plate] built on top steel parts of all three pillars //
            ////

            /* ============================================*/
            glLineWidth(10.5);

	        glBegin(GL_LINES);
	        glColor3ub(128,5,0); //Medium Dark Red
	        glVertex2f(-1.0f, -0.037f);    // x, y
	        glVertex2f(1.0f, -0.037f);    // x, y

	        glEnd();
            /* ============================================*/


    ///////////////////////////////////////////////////////////////////////'s Space Closure








            glBegin(GL_POLYGON);//1st pillar bottom concrete part||ok
            glColor3ub(255,198,0); //Yellow
            glVertex2f(-0.265f, -0.345f);
            glVertex2f(-0.395f, -0.345f);
            glColor3ub(172,159,60); //Brass
            glVertex2f(-0.395f, -0.295f);
            glVertex2f(-0.265f, -0.295f);
            glEnd();
            glBegin(GL_POLYGON);//1st pillar middle concrete part||ok
            glColor3ub(255,198,0); //Yellow
            glVertex2f(-0.385f, -0.300f);
            glVertex2f(-0.385f, -0.145f);
            glColor3ub(172,159,60); //Brass
            glVertex2f(-0.275f, -0.145f);
            glVertex2f(-0.275f, -0.300f);
            glEnd();
            glBegin(GL_POLYGON);//1st pillar left 1st steel base||ok
            glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(-0.345f, -0.151f);
            glVertex2f(-0.345f, -0.045f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(-0.355f, -0.045f);
            glVertex2f(-0.355f, -0.151f);
            glEnd();
            glBegin(GL_POLYGON);//1st pillar left 2nd steel base||ok
            glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(-0.330f, -0.044f);
            glVertex2f(-0.330f, -0.155f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(-0.320f, -0.155f);
            glVertex2f(-0.320f, -0.044f);
            glEnd();
            glBegin(GL_POLYGON);//1st pillar left 3rd steel base||ok
            glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(-0.300f, -0.155f);
            glVertex2f(-0.300f, -0.045f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(-0.290f, -0.045f);
            glVertex2f(-0.290f, -0.155f);
            glEnd();
            glBegin(GL_POLYGON);//1st pillar top steel base||ok
            glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(-0.365f, -0.045f);
            glVertex2f(-0.282f, -0.045f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(-0.282f, -0.030f);
            glVertex2f(-0.365f, -0.030f);
            glEnd();

// HIMEL
            glBegin(GL_POLYGON); //1st pillar left bottom steel join base
            glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(-0.349f, -0.115f);
            glVertex2f(-0.327f, -0.092f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(-0.327f, -0.119f);
            glVertex2f(-0.351f, -0.139f);
            glEnd();

            glBegin(GL_POLYGON);//1st pillar right bottom steel join base
            glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(-0.298f, -0.119f);
            glVertex2f(-0.296f, -0.135f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(-0.324f, -0.119f);
            glVertex2f(-0.324f, -0.1f);
            glEnd();

            glBegin(GL_POLYGON);//1st pillar left top steel join base
            glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(-0.353f, -0.076f);
            glVertex2f(-0.353f, -0.1f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(-0.327f, -0.068f);
            glVertex2f(-0.329f, -0.056f);
            glEnd();

            glBegin(GL_POLYGON);//1st pillar right top steel join base
            glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(-0.291f, -0.076f);
            glVertex2f(-0.291f, -0.092f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(-0.322f, -0.072f);
            glVertex2f(-0.320f, -0.056f);
            glEnd();

            glBegin(GL_POLYGON);//2nd pillar bottom concrete part||ok
            glColor3ub(255,198,0); //Yellow
            glVertex2f(0.205f, -0.295f);
            glVertex2f(0.205f, -0.345f);
            glColor3ub(172,159,60); //Brass
            glVertex2f(0.340f, -0.345f);
            glVertex2f(0.340f, -0.295f);
            glEnd();
            glBegin(GL_POLYGON);//2nd pillar middle concrete part||ok
            glColor3ub(255,198,0); //Yellow
            glVertex2f(0.215f, -0.295f);
            glVertex2f(0.215f, -0.150f);
            glColor3ub(172,159,60); //Brass
            glVertex2f(0.330f, -0.150f);
            glVertex2f(0.330f, -0.295f);
            glEnd();
            glBegin(GL_POLYGON);//2nd pillar left 1st steel base
             glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(0.240f, -0.045f);
            glVertex2f(0.249f, -0.045f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(0.251f, -0.159f);
            glVertex2f(0.240f, -0.159f);
            glEnd();
            glBegin(GL_POLYGON);//2nd pillar left 2nd steel base
             glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(0.278f, -0.155f);
            glVertex2f(0.267f, -0.159f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(0.267f, -0.048f);
            glVertex2f(0.280f, -0.048f);
            glEnd();

            glBegin(GL_POLYGON);//2nd pillar left 3rd steel base
             glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(0.298f, -0.155f);
            glVertex2f(0.307f, -0.155f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(0.307f, -0.048f);
            glVertex2f(0.298f, -0.048f);
            glEnd();
            glBegin(GL_POLYGON);//2nd pillar top steel base
             glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(0.309f, -0.052f);
            glVertex2f(0.311f, -0.04f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(0.233f, -0.04f);
            glVertex2f(0.233f, -0.052f);
            glEnd();
            glBegin(GL_POLYGON);//2nd pillar left bottom steel join base
             glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(0.244f, -0.123f);
            glVertex2f(0.269f, -0.108f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(0.271f, -0.127f);
            glVertex2f(0.240f, -0.151f);
            glEnd();
            glBegin(GL_POLYGON);//2nd pillar left top steel join base
             glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(0.276f, -0.08f);
            glVertex2f(0.273f, -0.06f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(0.244f, -0.076f);
            glVertex2f(0.249f, -0.104f);
            glEnd();


            glBegin(GL_POLYGON);//2nd pillar right bottom steel join base
            glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(0.302f, -0.123f);
            glVertex2f(0.300f, -0.139f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(0.278f, -0.123f);
            glVertex2f(0.280f, -0.104f);
            glEnd();


            glBegin(GL_POLYGON);//2nd pillar right top steel join base
            glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(0.304f, -0.08f);
            glVertex2f(0.304f, -0.096f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(0.278f, -0.076f);
            glVertex2f(0.278f, -0.06f);
            glEnd();


            //THIRD PILLER
            //3rd pillar bottom concrete part||ok
            glBegin(GL_POLYGON);
            glColor3ub(255,198,0); //Yellow
            glVertex2f(0.760f, -0.347f);
            glVertex2f(0.92f, -0.347f);
            glColor3ub(172,159,60); //Brass
            glVertex2f(0.92f, -0.285f);
            glVertex2f(0.760f, -0.285f);
            glEnd();

            glBegin(GL_POLYGON);//3rd pillar middle concrete part||ok
            glColor3ub(255,198,0); //Yellow
            glVertex2f(0.90f, -0.159f);
            glVertex2f(0.90f, -0.289f);
            glColor3ub(172,159,60); //Brass
            glVertex2f(0.784f, -0.293f);
            glVertex2f(0.784f, -0.159f);
            glEnd();

            glBegin(GL_POLYGON);//3rd pillar top steel base
            glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(0.792f, -0.04f);
            glVertex2f(0.792f, -0.064f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(0.880f, -0.064f);
            glVertex2f(0.880f, -0.04f);
            glEnd();

            glBegin(GL_POLYGON);//3rd pillar left 1st steel base
            glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(0.800f, -0.159f);
            glVertex2f(0.800f, -0.06f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(0.811f, -0.06f);
            glVertex2f(0.811f, -0.159f);
            glEnd();

            glBegin(GL_POLYGON);//3rd pillar right 3rd steel base
            glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(0.875f, -0.064f);
            glVertex2f(0.875f, -0.159f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(0.864f, -0.159f);
            glVertex2f(0.864f, -0.064f);
            glEnd();
            glBegin(GL_POLYGON);//3rd pillar middle 3rd steel base
            glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(0.836f, -0.06f);
            glVertex2f(0.836f, -0.159f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(0.844f, -0.159f);
            glVertex2f(0.844f, -0.060f);
            glEnd();
            glBegin(GL_POLYGON);//3rd pillar join base left top
            glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(0.811f, -0.104f);
            glVertex2f(0.836f, -0.08f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(0.838f, -0.096f);
            glVertex2f(0.807f, -0.127f);
            glEnd();

            glBegin(GL_POLYGON);//3rd pillar join base left bottom
            glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(0.811f, -0.131f);
            glVertex2f(0.809f, -0.151f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(0.840f, -0.135f);
            glVertex2f(0.840f, -0.111f);
            glEnd();

            glBegin(GL_POLYGON);//3rd pillar join base right top
            glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(0.867f, -0.096f);
            glVertex2f(0.867f, -0.111f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(0.838f, -0.096f);
            glVertex2f(0.838f, -0.076f);
            glEnd();


            glBegin(GL_POLYGON);//3rd pillar join base right bottom

            glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(0.864f, -0.131f);
            glVertex2f(0.864f, -0.147f);
            glColor3ub(205,0,26); //CHERRY RED
            glVertex2f(0.842f, -0.131f);
            glVertex2f(0.842f, -0.111f);
            glEnd();

            //BRIDGE MAIN BASE

            ////////////////////////////BRIDGE BASE STEEL CORRECTION///////////////////////////////
            /* ============================================*/
            //Pillar Base Plate 1 //
            glLineWidth(11.5);

	        glBegin(GL_LINES);
	        glColor3ub(140,146,172); //Cool Grey
	        glVertex2f(-0.3742037194823f, -0.1585828484295f);    // x, y
	        glColor3ub(131,145,161); //Oxford Grey
	        glVertex2f(-0.2798216947015f, -0.1581439225477f);    // x, y
	        glEnd();

            /* ============================================*/
            //Pillar Base Plate 2 //
            glLineWidth(10.5);

	        glBegin(GL_LINES);
	        glColor3ub(140,146,172); //Cool Grey
	        glVertex2f(0.2235799962144f, -0.1606692451922f);    // x, y
	        glColor3ub(131,145,161); //Oxford Grey
	        glVertex2f(0.3259847152422f, -0.1606692451922f);    // x, y
	        glEnd();
            /* ============================================*/
            //Pillar Base Plate 3 //
            glLineWidth(10.5);

	        glBegin(GL_LINES);
	        glColor3ub(140,146,172); //Cool Grey
	        glVertex2f(0.7888471054085f, -0.1695446498903f);    // x, y
	        glColor3ub(131,145,161); //Oxford Grey
	        glVertex2f(0.893180043487f, -0.1695659776803f);    // x, y //
	        glEnd();
            /* ============================================*/

            //**********First span*************

            glBegin(GL_POLYGON);//Upper Steel

            glColor3ub(128,5,0); //MEDIUM DARK RED
            glVertex2f(-1.00, 0.249);
            glVertex2f(-0.450, 0.249);
            glVertex2f(-0.450, 0.199);
            glVertex2f(-1.00, 0.2);
            glEnd();

            glBegin(GL_POLYGON); //Curved part
            glColor3ub(129,4,4);
            glVertex2f(-0.452, 0.249);
            glVertex2f(-0.430, 0.225);
            glVertex2f(-0.425, 0.198);
            glVertex2f(-0.450, 0.198);
            glEnd();
            glBegin(GL_POLYGON); //right part
            glColor3ub(129,4,4);
            glVertex2f(-0.450, 0.199);
            glVertex2f(-0.425, 0.199);
            glVertex2f(-0.364, -0.044);
            glVertex2f(-0.390, -0.044);
            glEnd();
            glBegin(GL_POLYGON); //Crossed(Left)
            glColor3ub(129,4,4);
            glVertex2f(-0.69, 0.20);
            glVertex2f(-0.66, 0.20);
            glVertex2f(-0.78, -0.042);
            glVertex2f(-0.80, -0.020);
            glEnd();

            glBegin(GL_POLYGON);  //Crossed(right)
            glColor3ub(129,4,4);
            glVertex2f(-0.7883307362279, 0.1924294982769);
            glVertex2f(-0.7672196497199, 0.2113753451431);
            glVertex2f(-0.667077316284, -0.0278836352819);
            glVertex2f(-0.689271022613, -0.0462881722377);
            glEnd();

            glBegin(GL_POLYGON); //Middle left Steel
            glColor3ub(129,4,4);
            glVertex2f(-0.807, 0.2);
            glVertex2f(-0.781, 0.2);
            glVertex2f(-0.781, -0.048);
            glVertex2f(-0.807, -0.048);
            glEnd();

            glBegin(GL_POLYGON); //Middle Right Steel
            glColor3ub(129,4,4);
            glVertex2f(-0.681, 0.199);
            glVertex2f(-0.65, 0.2);
            glVertex2f(-0.6504792776411, -0.0451188675825);
            glVertex2f(-0.679, -0.044);
            glEnd();

            glBegin(GL_POLYGON); //Curved down left rod
            glColor3ub(129,4,4);
            glVertex2f(-0.480, -0.044);
            glVertex2f(-0.454, -0.044);
            glVertex2f(-0.454, 0.199);
            glVertex2f(-0.480, 0.199);
            glEnd();

            glBegin(GL_POLYGON); //left rod to middle
            glColor3ub(129,4,4);
            glVertex2f(-0.497, 0.207);
            glVertex2f(-0.466, 0.206);
            glVertex2f(-0.641, -0.050);
            glVertex2f(-0.663, -0.032);
            glEnd();

            glBegin(GL_POLYGON); //Right rod to middle
            glColor3ub(129,4,4);
            glVertex2f(-1, 0.2);
            glVertex2f(-0.960, 0.199);
            glVertex2f(-0.80, -0.027);
            glVertex2f(-0.819, -0.045);
            glEnd();

            glBegin(GL_POLYGON); //Curved down right rod
            glColor3ub(129,4,4);
            glVertex2f(-0.997, 0.210);
            glVertex2f(-0.971, 0.210);
            glVertex2f(-0.971, -0.0462);
            glVertex2f(-0.997, -0.0482);
            glEnd();


            //***********Forth SPAN**********

            glBegin(GL_POLYGON); //first part
            glColor3ub(129,4,4);
            glVertex2f(0.9554908257761, 0.2493463299449);
            glVertex2f(0.9689412900175, 0.1931284533598);
            glVertex2f(0.9038438868141, -0.044285605382);
            glVertex2f(0.8700445503025, -0.0449686189085);
            glEnd();

            glBegin(GL_POLYGON); //Curved Part
            glColor3ub(129,4,4);
            glVertex2f(0.955, 0.249);
            glVertex2f(0.997, 0.250);
            glVertex2f(0.997, 0.194);
            glVertex2f(0.969, 0.194);
            glEnd();

            glBegin(GL_POLYGON); //Right Rod
            glColor3ub(129,4,4);
            glVertex2f(0.967, 0.193);
            glVertex2f(0.990, 0.193);
            glVertex2f(0.990, -0.049);
            glVertex2f(0.967, -0.0432);
            glEnd();


            //*************SECOND SPAN***********

            glBegin(GL_POLYGON); //Right Rod
            glColor3ub(129,4,4);
            glVertex2f(-0.227, 0.191);
            glVertex2f(-0.198, 0.191);
            glVertex2f(-0.270, -0.0437);
            glVertex2f(-0.296, -0.0452);
            glEnd();


            glBegin(GL_POLYGON); //Curved Part right
            glColor3ub(129,4,4);
            glVertex2f(-0.227, 0.191);
            glVertex2f(-0.213, 0.219);
            glVertex2f(-0.182, 0.236);
            glVertex2f(-0.198, 0.191);
            glEnd();

            glBegin(GL_POLYGON); //Upper middle Rod
            glColor3ub(129,4,4);
            glVertex2f(-0.183, 0.236);
            glVertex2f(0.144, 0.236);
            glVertex2f(0.144, 0.190);
            glVertex2f(-0.198, 0.191);
            glEnd();

            glBegin(GL_POLYGON); //Curved Part Left
            glColor3ub(129,4,4);
            glVertex2f(0.144, 0.236);
            glVertex2f(0.1637385385556, 0.2139303925152);
            glVertex2f(0.1691466312553, 0.1907528523738);
            glVertex2f(0.144, 0.190);
            glEnd();

            glBegin(GL_POLYGON); //Right ROD Part
            glColor3ub(129,4,4);
            glVertex2f(0.144, 0.190);
            glVertex2f(0.1691466312553, 0.1907528523738);
            glVertex2f(0.2255453122659, -0.0441128877253);
            glVertex2f(0.192501595372, -0.0422413992469);
            glEnd();

            glBegin(GL_POLYGON); //Curved down left rod
            glColor3ub(129,4,4);
            glVertex2f(-0.198, 0.191);
            glVertex2f(-0.1702724017098, 0.1928406192222);
            glVertex2f(-0.1693829299916, -0.0445094218754);
            glVertex2f(-0.1970051581348, -0.043720215357);
            glEnd();

            glBegin(GL_POLYGON); //Curved down Right rod
            glColor3ub(129,4,4);
            glVertex2f(0.116, 0.192);
            glVertex2f(0.139, 0.192);
            glVertex2f(0.139, -0.0443);
            glVertex2f(0.115, -0.0443);
            glEnd();

            glBegin(GL_POLYGON); //Middle Left ROD
            glColor3ub(129,4,4);
            glVertex2f(-0.1, 0.2);
            glVertex2f(-0.076, 0.197);
            glVertex2f(-0.076, -0.049);
            glVertex2f(-0.1, -0.05);
            glEnd();

            glBegin(GL_POLYGON); //MIDDLE RIGHT ROD
            glColor3ub(129,4,4);
            glVertex2f(0.0248828875626, 0.1994715012481);
            glVertex2f(0.05, 0.2);
            glVertex2f(0.05, -0.043);
            glVertex2f(0.0253998710633, -0.0455786780814);
            glEnd();

            glBegin(GL_POLYGON); // RIGHT ROD to middle rod
            glColor3ub(129,4,4);
            glVertex2f(0.0362785287034, -0.0254738874898);
            glVertex2f(0.1062980468459, 0.1977507301782);
            glVertex2f(0.1256458807094, 0.1813618126985);
            glVertex2f(0.05, -0.05);
            glEnd();

            glBegin(GL_POLYGON); // Left ROD to middle left rod
            glColor3ub(129,4,4);
            glVertex2f(-0.1819768901479, 0.1863907805893);
            glVertex2f(-0.1596786069234, 0.1980695632314);
            glVertex2f(-0.0924219509987, -0.0346969503167);
            glVertex2f(-0.1128913680193, -0.046978600529);
            glEnd();




            glBegin(GL_POLYGON); //Crossed(right)
            glColor3ub(129,4,4);
            glVertex2f(0.0121652894378, 0.1963104007408);
            glVertex2f(0.0345885949497, 0.1854491121335);
            glVertex2f(-0.0656155515564, -0.0520977806327);
            glVertex2f(-0.0859366721765, -0.0380832146878);
            glEnd();


            glBegin(GL_POLYGON);  //Crossed(left)
            glColor3ub(129,4,4);
            glVertex2f(-0.0863396173499, 0.1816118555649);
            glVertex2f(-0.0680681005968, 0.1973614931867);
            glVertex2f(0.0362785287034, -0.0254738874898);
            glVertex2f(0.0155631397974, -0.0499810389166);
            glEnd();


//*********Third SPAN***********
            glBegin(GL_POLYGON); //Right Rod
            glColor3ub(129,4,4);
            glVertex2f(0.3410067809383, 0.1974237086397);
            glVertex2f(0.3702262003154, 0.1977217208615);
            glVertex2f(0.3370352364324, -0.0444981361362);
            glVertex2f(0.3066534185731, -0.0449067664228);
            glEnd();


            glBegin(GL_POLYGON); //Curved Part left
            glColor3ub(129,4,4);
            glVertex2f(0.3066534185731, -0.0449067664228);
            glVertex2f(0.3410067809383, 0.1974237086397);
            glVertex2f(0.3697893277848, 0.2345624787642);
            glVertex2f(0.3702262003154, 0.1977217208615);
            glEnd();

            glBegin(GL_POLYGON); //upper ROD
            glColor3ub(129,4,4);
            glVertex2f(0.370, 0.235);
            glVertex2f(0.738, 0.235);
            glVertex2f(0.738, 0.197);
            glVertex2f(0.370, 0.197);
            glEnd();

            glBegin(GL_POLYGON); //Curved Part right
            glColor3ub(129,4,4);
            glVertex2f(0.735, 0.234);
            glVertex2f(0.755, 0.217);
            glVertex2f(0.765, 0.192);
            glVertex2f(0.738, 0.192);
            glEnd();

            glBegin(GL_POLYGON); //left Rod
            glColor3ub(129,4,4);
            glVertex2f(0.738, 0.193);
            glVertex2f(0.766, 0.193);
            glVertex2f(0.793, -0.045);
            glVertex2f(0.766, -0.045);
            glEnd();


         glBegin(GL_POLYGON); //Curved down left rod
            glColor3ub(129,4,4);
            glVertex2f(0.366, 0.198);
            glVertex2f(0.391, 0.198);
            glVertex2f(0.391, -0.045);
            glVertex2f(0.366, -0.045);
            glEnd();

            glBegin(GL_POLYGON); //Curved down Right rod
            glColor3ub(129,4,4);
            glVertex2f(0.710, 0.199);
            glVertex2f(0.735, 0.200);
            glVertex2f(0.735, -0.050);
            glVertex2f(0.710, -0.049);
            glEnd();


            glBegin(GL_POLYGON); //Middle Left ROD
            glColor3ub(129,4,4);
            glVertex2f(0.4547475632951, 0.2003170892393);
            glVertex2f(0.4838364289779, 0.1998240576175);
            glVertex2f(0.4838364289779, -0.0461987216318);
            glVertex2f(0.4547475632951, -0.0471847848753);
            glEnd();

            glBegin(GL_POLYGON); //MIDDLE RIGHT ROD
            glColor3ub(129,4,4);
            glVertex2f(0.608, 0.201);
            glVertex2f(0.634, 0.201);
            glVertex2f(0.634, -0.049);
            glVertex2f(0.608, -0.049);
            glEnd();

            glBegin(GL_POLYGON); //Crossed(right)
            glColor3ub(129,4,4);
            glVertex2f(0.470, 0.192);
            glVertex2f(0.493, 0.206);
            glVertex2f(0.619, -0.031);
            glVertex2f(0.598, -0.049);
            glEnd();


            glBegin(GL_POLYGON);  //Crossed(left)
            glColor3ub(129,4,4);
            glVertex2f(0.606, 0.211);
            glVertex2f(0.628, 0.196);
            glVertex2f(0.487, -0.050);
            glVertex2f(0.463, -0.031);
            glEnd();

            glBegin(GL_POLYGON); // RIGHT ROD to middle rod
            glColor3ub(129,4,4);
            glVertex2f(0.7035447802876, 0.2049987635653);
            glVertex2f(0.7259960495361, 0.193773128941);
            glVertex2f(0.6366067367874, -0.0490331903391);
            glVertex2f(0.6199516423663, -0.0317220851494);
            glEnd();

            glBegin(GL_POLYGON); // Left ROD to middle left rod
            glColor3ub(129,4,4);
            glVertex2f(0.3789043966186, 0.1952171702031);
            glVertex2f(0.398491712675, 0.2142890305738);
            glVertex2f(0.4671679747387, -0.0335673843006);
            glVertex2f(0.4491679316613, -0.0514117052107);
            glEnd();



            ////////////////////////////BRIDGE BASE STEEL CORRECTION///////////////////////////////
            //
	        /* ============================================*/
            /* ============================================*/
            ////
            //Pillar 1 Line //
            /* ============================================*/
            glLineWidth(5.5);

	        glBegin(GL_LINES);
	        glColor3ub(140,146,172); //Cool Grey
	        glVertex2f(-0.3718745074874f, -0.0536676048809f);    // x, y
	        glVertex2f(-0.2750019827876f, -0.0536676048809f);    // x, y
	        glEnd();
            /* ============================================*/
            //Pillar 2 Line //
            /* ============================================*/
            glLineWidth(5.5);

	        glBegin(GL_LINES);
	        glColor3ub(140,146,172); //Cool Grey
	        glVertex2f(0.2279685398511f, -0.0558845631863f);    // x, y
	        glVertex2f(0.3150442130592f, -0.0557661627826f);    // x, y
	        glEnd();
            /* ============================================*/
            //Pillar 3 Line //
            /* ============================================*/
            glLineWidth(5.5);

	        glBegin(GL_LINES);
	        glColor3ub(140,146,172); //Cool Grey
	        glVertex2f(0.7985567436757f, -0.0685687066667f);    // x, y
	        glVertex2f(0.8771402305493f, -0.0682684234758f);    // x, y
	        glEnd();
            /* ============================================*/
            ////Base Line [steel plate] built on top steel parts of all three pillars //

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animation_waves(int value)
{

    if(position_waves > 1.0)
    {
        position_waves = -1.0f;
    }

    position_waves += speed_waves;

    glutPostRedisplay();


    glutTimerFunc(300, animation_waves, 0);
}

void waves()
{
    glLineWidth(0.6);

    glPushMatrix();

    glTranslatef(position_waves,0,0);

    glBegin(GL_LINES);
    glColor3ub(255,255,255);

    glVertex2f(-0.1f,-0.4f);
    glVertex2f(0.0f,-0.4f);

    glVertex2f(-0.2f,-0.7f);
    glVertex2f(-0.1f,-0.7f);

    glVertex2f(0.5f,-0.6f);
    glVertex2f(0.4f,-0.6f);

    glVertex2f(0.6f,-0.45f);
    glVertex2f(0.7f,-0.45f);

    glVertex2f(-0.9f,-0.9f);
    glVertex2f(-0.8f,-0.9f);

    glVertex2f(0.6f,-0.82f);
    glVertex2f(0.7f,-0.82f);

    glVertex2f(0.6f,-0.82f);
    glVertex2f(0.7f,-0.82f);

    glEnd();

    glPopMatrix();

    glEnd();
}


////////////////WARNING////////////////STARS CODE IS LONG/////////////////////////////////
void Star()
{


    glTranslatef(0.0,0.8,0.0);                              // star 1

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();


    glTranslatef(0.37,0.8,0.0);                              // star 2

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(0.65,0.7,0.0);                      // star 3

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(0.73,0.9,0.0);                          // star 4

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(0.3,0.76,0.0);                          // star 6

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(0.81,0.78,0.0);                          // star 7

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(0.57,0.84,0.0);                              // star 8

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(0.4,0.9,0.0);                              // star 8

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(0.7,0.83,0.0);                              // star 9

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(0.1,0.72,0.0);                              // star 10

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(-0.4,0.7,0.0);                              // star 11

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(-0.75,0.75,0.0);                              // star 12

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(-0.1,0.89,0.0);                              // star 13

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(-0.6,0.84,0.0);                              // star 14

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(-0.2,0.78,0.0);                              // star 15

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(-0.2,0.73,0.0);                              // star 16

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(-0.1,0.81,0.0);                              // star 17

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(-0.63,0.77,0.0);                              // star 18

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(-0.8,0.7,0.0);                              // star 19

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(-0.4,0.7,0.0);                              // star 20

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(-0.8,0.84,0.0);                              // star 21

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();

    glTranslatef(0.2,0.88,0.0);                              // star 22

    glScalef(0.1,0.1,0.0);
    glBegin(GL_POLYGON); // start middle part
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 1
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(0.03f,0.0f);
    glVertex2f(0.0f,0.07f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 2
    glColor3ub(255,255,255);
    glVertex2f(-0.03f,0.0f);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 3
    glColor3ub(255,255,255);
    glVertex2f(-0.04f,-0.05f);
    glVertex2f(-0.07f,-0.14f);
    glVertex2f(0.0f,-0.09f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 4
    glColor3ub(255,255,255);
    glVertex2f(0.0f,-0.09f);
    glVertex2f(0.07f,-0.14f);
    glVertex2f(0.04f,-0.05f);

    glEnd();

    glBegin(GL_TRIANGLES); // star triangle 5
    glColor3ub(255,255,255);
    glVertex2f(0.04f,-0.05f);
    glVertex2f(0.1f,0.0f);
    glVertex2f(0.03f,0.0f);

    glEnd();

    glLoadIdentity();


    glLoadIdentity();
}

