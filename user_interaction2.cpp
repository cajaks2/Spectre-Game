
//includes areas for keyboard control, mouse control, resizing the window
//and draws a spinning rectangle

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <math.h>
#include <iostream>
#include "Player.h"
#include "wglext.h"
int	mouse_x=0, mouse_y=0;
bool LeftPressed = false;
int screenWidth=854, screenHeight=480;
bool keys[256];
float spin=0;
int countStuck=0;
int firerate=0;
int firerate2=0;
int mission=0;
int missionEnemy=0;
	/*
1) top left
2) bottom left
3) top right
4) bottom right
*/
Player Player1 = Player(-7, 10,0,0,1,0);
Player Back = Player(-1000,300,1000,-50,1,1);
Player BackStar = Player(-1000,100,1000,-50,1,3);
Player Score = Player( 45, 40,70,30,1,20); 

Player BlockFloor= Player(-100,-.1,120,-5,1,5);
Player BlockFloorTop= Player(-60,25,60,20,1,5);
Player BlockFloorLeft= Player(-22,20,-20,0,1,10);
Player BlockFloorRight = Player(120,52,122,0,1,10);
Player lowBlockV= Player(100, 3, 112, 1,1, 5, 2,true);
Player BlockFloor2ndTop= Player(-100,55,120,50,1,5);
Player lowBlockH =  Player(65, 25, 77,23,1,5,1,true);
Player BlockFloorLeftCage= Player(-62,20,-60,0,1,10);
Player BlockFloorWall= Player(-102,52,-100,0,1,10);
Player cageBlockV= Player(-80, 3, -68, 1,1, 5, 2,true);
Player onetrueGod=Player(-55,13,-50, 8, 1,8,0,true,true,false);
	Player bottom=  Player(-129,-.1,154,-5,1,5);
	Player bottom1=Player(60,52,64,0,1,10);
	Player bottom2=Player(-30, 3, -18, 1,1, 5, 2,true); //vert?
	Player bottom3= Player(35, 30, 47,28,1,5,1,true); //horizontal 
	Player bottom4=Player(-80,52,-76,1,0,10);
	Player bottom5=Player(-8,52,-4,16,1,10);
	Player bottom6=Player(30, 3, 42, 1,1, 5, 2,true);
	Player bottom7=Player(-52, 3, -40, 1,1, 5, 2,true);
	Player bottom8=Player(-55,17,-50,12,1,8,0,true,true,false);
	Player bottom9=Player(-55,25,-50,20, 1,8,0,true,true,false);
	Player bottom10=Player(-55,35,-50,30, 1,8,0,true,true,false);
	Player bottom11=Player(25,35,30,30,1,8,0,true,true,false);//right room 
	Player bottom12=Player(25,25,30,20, 1,8,0,true,true,false);
	Player bottom13=Player(60,52,64,0,1,10);
	Player topThing=Player(-36,57,64,52,1,5);
	Player topThing2=Player(-80,57,-58,52,1,5);
	Player secndRoomLeft=Player(-80,100,-76,52,1,10);
	Player secndRoomCeil=Player(-80,104,100,100,1,5);
	Player secndRoomRight=Player(100,104,104,20,1,10);
	Player secndRoomfloor=Player(60,0,120,-5,1,5);
	Player DropBot=Player(68,40,73,35, 1,8,0,true,true,false); //drop
	Player vertDrop= Player(68, 45, 80, 43,1, 5, 2,true);
	Player DropBot2=Player(68,50,73,45, 1,8,0,true,true,false);
	Player DropBot3=Player(68,30,73,25, 1,8,0,true,true,false);
	Player large=  Player(160,-.1,200,-5,1,5,3,false);
	Player mainroof= Player(-130,145,200,140,1,5);
	Player mainwall= Player(202, 145,206,0,1,10);
	Player leftwall=Player(-130,145,-126,0,1,10);
	Player vertDropLeft= Player(-115, 105, -103, 102,1, 5, 2,true);
	Player vertDropRight= Player(-100, 105, -88, 102,1, 5, 2,true);
	Player DropBot4=Player(-115,50,-110,45, 1,8,0,true,true,false);
	Player DropBot5=Player(-115,30,-110,25, 1,8,0,true,true,false);
	Player DropBot6=Player(-115,60,-110,55, 1,8,0,true,true,false);
	Player DropBot7=Player(-115,70,-110,65, 1,8,0,true,true,false);
	Player DropBot8=Player(-115,80,-110,75, 1,8,0,true,true,false); //Drop 
//second mission
Player botFloor=Player(-100,-.1,120,-5,1,5);



//Player Block1 = Player(-60,-10,60,-15,1,5);
//Player Block2 = Player(60,-15,120,-20,1,5);
//Player Block3 = Player(30, 25,35, 5,1,5);
//Player LeftWall = Player(-70,50,-60,-10,1,5);
Player Start = Player(-45*1.778,45,45*1.778,-45,1,4);
//Player RightWall = Player(60,50,70,-10,5);
//Player Health = Player( -50, 50, -30, 20,1,6);
//Player Move = Player( -30, 10, -10, 5,1, 5, 2,true);
//Player MoveH = Player( -40, 30, -30, 27,1, 5, 1,true);
//Player testEn3 = Player(-50,45,-45, 40, 1,8,0,true,true,false);

//std::vector<Player> Blocks(2);
int blockLength=60;
int numBullets=10000;
Player Blocks[60];//change with blockLength
Player Bullets[10000];

//Player movingBlocks[1];
float Xtemp=0;
float Ytemp=0;
float Velo;
float fall =2.6;
//variables for moving object
float Xtri = 0;		
float Ytri = 0;			//x and y coords of the user controlled object
float Vtri = 0;			//velocity of the moving object.
float heading = 0;		//heading of the moving object. 
int pauseTime=0; //so enter key doesn't get spammed
//OPENGL FUNCTION PROTOTYPES
void display();				//draws everything to the screen
void reshape(int width, int height);				//called when the window is resized
void init();				//called in winmain when the program starts.
void processKeys();			//called in winmain to process keyboard controls
void processMovement(); //moving platforms
void shoot(float x, float y, float dir);
void shootPlay(float x, float y, float dir);
void processBullets();
void reset();
void boundries();
void triggers();
void loadMission();
void setVSync(bool sync);
void setScore();
/*************    START OF OPENGL FUNCTIONS   ****************/
void display()									
{
	
	
	glClear(GL_COLOR_BUFFER_BIT);
		
	glLoadIdentity();
	
	glPushMatrix();
	glPushMatrix();
	
	glTranslatef(-Xtemp*.65,-Ytemp*.65, 0);
	Back.draw();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-Xtemp*.5,-Ytemp*.5, 0);
	BackStar.draw();

	glPopMatrix();

	Blocks[blockLength-1].draw();
	
	glTranslatef(-Xtemp,-Ytemp, 0);
	for(int i=0; i < blockLength-1;i++){
		Blocks[i].draw();
		
	}
	
	for(int i=0; i < numBullets; i++){
	Bullets[i].draw();
	}

	glPopMatrix();
	Score.draw();
	Start.draw();

	glFlush(); 
	glLoadIdentity();
	
	//update the position of the user controlled object.
	//Xtri += Vtri*cos((90+heading)*(PI/180.0f));
	//Ytri += Vtri*sin((90+heading)*(PI/180.0f));
}

void reshape(int width, int height)		// Resize the OpenGL window
{
	screenWidth=width; screenHeight = height;           // to ensure the mouse coordinates match 
														// we will use these values to set the coordinate system
	
	
  float aspect = (float)width/(float)height; //makes sure that the window is about 16:9
 if(aspect>=1.8 || aspect<=1.75){
	  for(int x =width; x >0; x--){
		  for(int y = height; y >0;y--){
			  if(((float)x /(float)y)<=1.778 && ((float)x /(float)y)>=1.7776){
				  width=x;
				  height=y;
				x=0;
		  }
		  }
	  }
 }
   aspect = (float)width/(float)height; //new aspect
   
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
	glViewport((screenWidth-width)/2,(screenHeight-height)/2,width,height);	//this is the letterboxing					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	//gluOrtho2D(-45,45,-45,45);           // set the coordinate system for the window
	gluOrtho2D(-45*aspect, 45*aspect, -45, 45); //kespes the aspect ration
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}
void init()
{
	glClearColor(0,.0,0.0,0.0);						//sets the clear colour to yellow
												//glClear(GL_COLOR_BUFFER_BIT) in the display function
														//will clear the buffer to this colour.
	//Blocks.push_back(Block1);
	Blocks[0]=BlockFloor;
	Blocks[1]=BlockFloorLeft;
	Blocks[2]=BlockFloorTop;
	Blocks[4]=BlockFloorRight;
	Blocks[3]=lowBlockV;
	Blocks[10]=BlockFloor2ndTop;
	Blocks[9]=cageBlockV;
	Blocks[8]=BlockFloorWall;
	Blocks[7]=onetrueGod;
	Blocks[6]=BlockFloorLeftCage;
	Blocks[5]=lowBlockH;
	Blocks[blockLength-1]=Player1;


	//what
		Blocks[11] = bottom;
	Blocks[20]=bottom1;
	Blocks[13]=bottom2; //vert?
	Blocks[14]= bottom3; //horizontal 
	Blocks[15]=bottom4; //tall pillar
	Blocks[16]=bottom5; //floating pillar
	Blocks[21]=bottom6; // moving up platform
	Blocks[18]=bottom7; //moving up platform left
	Blocks[19]=bottom8; // left bot
	Blocks[12]=bottom9; // left mid bot
	Blocks[17]=bottom10; //left top bot
	Blocks[22]=bottom11; //right top bot
	Blocks[23]=bottom12; //right bot bot 
	Blocks[24]=bottom13; // tall fat block 
	Blocks[25]=topThing; //ceiling
	Blocks[26]=topThing2;
	Blocks[27]=secndRoomLeft;
	Blocks[28]=secndRoomCeil;
	Blocks[29]=secndRoomRight;
	Blocks[30]=secndRoomfloor;
	Blocks[31]=DropBot;
	Blocks[32]=vertDrop;
	Blocks[33]=DropBot2;
	Blocks[34]=DropBot3;
	Blocks[35]=large;
	Blocks[36]=mainroof;
	Blocks[37]=mainwall;
	Blocks[38]=leftwall;
	Blocks[39]=vertDropLeft;
	Blocks[40]=DropBot4;
	Blocks[41]=DropBot5;
	Blocks[42]=DropBot6;
	Blocks[43]=DropBot7;
	Blocks[44]=vertDropRight;
	Player1.setUpTextures();
	Score.setHealth(0);
	for(int x =0; x < 11; x++){
		Blocks[x].setHealth(1);
	}
	for(int x =11; x < blockLength-1; x++){
		Blocks[x].setHealth(0);
	}
	//Player Bullets[100];//BULLETS FOR EVERYONE
	PlaySound("backMusic.wav", NULL, SND_LOOP | SND_ASYNC);
}
void setScore(){
	
		//Score.setColor(24);
		int counter =0;
		if(Blocks[19].getHealth()==0 && Blocks[12].getHealth()==0 &&Blocks[17].getHealth()==0){
			counter++;
		}if(Blocks[22].getHealth()==0 && Blocks[23].getHealth()==0){
			counter++;
		}if(Blocks[31].getHealth()==0 && Blocks[33].getHealth()==0 &&Blocks[34].getHealth()==0){
			counter++;
		}if(Blocks[40].getHealth()==0 && Blocks[41].getHealth()==0 &&Blocks[42].getHealth()==0 && Blocks[43].getHealth()==0){
			counter++;
		}
		if(counter==0){
		 
			Score.setColor(20);
		}else if(counter==1){
			Score.setColor(21);
		}else if(counter==2){
			Score.setColor(22);
		}else if(counter==3){
			Score.setColor(23);
		}else if(counter==4){
			 Score.setColor(24);
		}

	
}
void boundries(){
	setScore();
	if(mission==0){
		
	if(Blocks[3].getY()>=25){
		Blocks[3].setDirection(2);
	}
	if(Blocks[7].getX()>20){
		Blocks[7].setDirection(0);
	}
		if(Blocks[9].getY()>30){
		Blocks[9].setDirection(2);
		}
		
		if(Xtemp<=-50){
			Blocks[6].setHealth(0);
		}
	
	if(Blocks[7].getHealth()==0){
		mission++;
		
	}
	}else{
		if(Blocks[3].getY()>=55){
		Blocks[3].setDirection(2);
		}
		if(Blocks[21].getY()>=40){
			Blocks[21].setDirection(2);
		}
		if(Blocks[18].getY()>=42){
			Blocks[18].setDirection(2);
		}
		if(Blocks[13].getY()>=40){
			Blocks[13].setDirection(2);
		}
		if(Blocks[32].getY()>=50){
			Blocks[32].setDirection(2);
		}
		if(Blocks[blockLength-1].collision(Blocks[35],Xtemp, Ytemp+1.5)){
			Blocks[35].startMoving();
		
		}
		if(Blocks[blockLength-1].collision(Blocks[35],Xtemp, Ytemp+-1.5)){
			Blocks[35].startMoving();
		
		}if(Blocks[35].getY()>=105){
			Blocks[35].setDirection(0);
		}
		if(Blocks[35].getX()<=105){
			Blocks[35].stopMoving();

		}	if(Blocks[44].getY()>=120){
			Blocks[44].setDirection(2);
		}
		if(Blocks[39].getY()>=120){
			Blocks[39].setDirection(2);
		}
	}
}
/*
method for moving platforms
*/
void processMovement(){
	boundries();
	float temp=0;
	float hitMe=0;
	float hitMeY=0;
	for(int i=0; i <blockLength;i++){
		
		if(Blocks[i].isMoving() && Blocks[i].getHealth()!=0 && !Blocks[i].hasGun()&& !Blocks[i].isBull()){
				if(Blocks[i].getDirection()==0){

					temp=.2;

				}else if(Blocks[i].getDirection()==1){
					temp=-.2;
					
				}else if(Blocks[i].getDirection()==2){
					temp=.2;
				}else if(Blocks[i].getDirection()==3){
					temp=-.2;
				} //looks alright 
			
			for(int x=0; x <blockLength-1;x++){
				if(i==x){
					x++;
				}
				if(Blocks[x].getHealth()!=0){
				if(Blocks[i].getDirection()<=1){ //left or whatevr
				
			if(Blocks[i].collision(Blocks[x], -temp, 0)){
			temp=0;
		}
			if(Blocks[blockLength-1].collision(Blocks[i], Xtemp+temp, Ytemp)){ //player collision this works
			temp=0;	
			hitMe=-1;
		}
			}
				if(Blocks[i].getDirection()>1){
					if(Blocks[i].collision(Blocks[x], 0, -temp)){
			temp=0;
		}	if(Blocks[blockLength-1].collision(Blocks[i], Xtemp, Ytemp+temp)){ //player collision this works
			temp=0;	
			hitMeY=-1;
					}
				}

				}//x loop
			}
			if(Blocks[i].getDirection()<=1){
			Blocks[i].setX(temp);
			if(temp==0 && hitMe==0){
					if(Blocks[i].getDirection()==0){
				Blocks[i].setDirection(1);
				
			}else {
				Blocks[i].setDirection(0);
			}
			}
			
}//y stuff starts here 
			if(Blocks[i].getDirection()>1){
			Blocks[i].setY(temp);
			if(temp==0 && hitMeY==0){
					if(Blocks[i].getDirection()==2){
				Blocks[i].setDirection(3);
			}else {
				Blocks[i].setDirection(2);
			}
			}
		
			
		}
		}
	}
}
void processAI(){
	
	float temp=0;
	float hitMe=0;
	float hitMeY=0;
	for(int i=0; i <blockLength;i++){
		
		
		if(Blocks[i].isMoving() && Blocks[i].getHealth()!=0 && Blocks[i].hasGun()&& !Blocks[i].isBull()){
			temp=0;
			 hitMe=0;
				if(Blocks[i].getDirection()==0){

					temp=.25;

				}else if(Blocks[i].getDirection()==1){
					temp=-.25;
					
				}else if(Blocks[i].getDirection()==2){
					temp=.25;
				}else if(Blocks[i].getDirection()==3){
					temp=-.25;
				} //looks alright 
			
			for(int x=0; x <blockLength-1;x++){
				if(i==x){
					x++;
				}
				if(Blocks[x].getHealth()!=0){
				if(Blocks[i].getDirection()<=1){ //left or whatevr
				
			if(Blocks[i].collision(Blocks[x], -temp, 0)){ //supect when bullets are firing
			temp=0;
			
		}
			if(Blocks[blockLength-1].collision(Blocks[i], Xtemp+temp, Ytemp)){ //player collision this works althouh not used
			temp=0;	
			hitMe=-1;
			Blocks[blockLength-1].setHealth(0);
			
			}
			if(hitMe!=-1){
				
				for(int z =0; z < 1000; z++){
			if(Blocks[blockLength-1].collision(Blocks[i], Xtemp+(temp*z), Ytemp)){ //player collision this works

			hitMe=-1;
			//bullet needs to shoot here 
			if(Blocks[i].getDirection()==0){//left
			
				shoot(Blocks[i].getX()+-3, Blocks[i].getY()-abs((Blocks[i].getY()-Blocks[i].getY2())/2)+1.5, 0);
				
			}else if(Blocks[i].getDirection()==1){//right
				
				shoot(Blocks[i].getX2()+4,Blocks[i].getY()-abs((Blocks[i].getY()-Blocks[i].getY2())/2)+1.5, 1);
				
			}
			temp=0;	
			//x=99999;
		}
			}
			
			}
				}
				if(Blocks[i].getDirection()>1){
					if(Blocks[i].collision(Blocks[x], 0, -temp)){
			temp=0;
		}	if(Blocks[blockLength-1].collision(Blocks[i], Xtemp, Ytemp+temp)){ //player collision this works
			temp=0;	
			hitMeY=-1;
					}
				}

				}//x loop
			}
			if(Blocks[i].getDirection()<=1){
			Blocks[i].setX(temp);
			if(temp==0 && hitMe==0){
					if(Blocks[i].getDirection()==0){
				Blocks[i].setDirection(1);

			}else {
				Blocks[i].setDirection(0);
			}
			}
			
}//y stuff starts here 
			if(Blocks[i].getDirection()>1){
			Blocks[i].setY(temp);
			if(temp==0 && hitMeY==0){
					if(Blocks[i].getDirection()==2){
				Blocks[i].setDirection(3);
				
			}else {
				Blocks[i].setDirection(2);
			}
			}
		
			
		}
		}
	}
}
void processBullets(){
	float temp=0;
	float hitMe=0;
	float hitMeY=0;
	for(int i=0; i <numBullets;i++){
		
		if(Bullets[i].isBull() && Bullets[i].getHealth()!=0){
				if(Bullets[i].getDirection()==0){
					temp=1;
				}else if(Bullets[i].getDirection()==1){
					temp=-1;
					
				}else if(Bullets[i].getDirection()==2){
					temp=1;
				}else if(Bullets[i].getDirection()==3){
					temp=-1;
				} //looks alright 
			
			for(int x=0; x <blockLength-1;x++){
				
				if(Blocks[x].getHealth()!=0){
				if(Bullets[i].getDirection()<=1){ //left or whatevr
				
			if(Bullets[i].collision(Blocks[x], -temp, 0)){
			temp=0;
			Bullets[i].setHealth(0);
			if(Blocks[x].hasGun()){
				Blocks[x].setHealth(0);
			}
		}
			if(Bullets[i].collision(Blocks[x], -temp, 0)){
			temp=0;
			Bullets[i].setHealth(0);
			if(Blocks[x].hasGun()){
				Blocks[x].setHealth(0);
			}
		}
			if(Blocks[blockLength-1].collision(Bullets[i], Xtemp+temp, Ytemp)){ //player collision this works
			temp=0;	
			hitMe=-1;
			//bullet needs to shoot here 
			//shoot(Blocks[i].getX()+temp, Blocks[i].getY(), Blocks[i].getDirection());
			Blocks[blockLength-1].setHealth(0);
			Bullets[i].setHealth(0);
			}
	
				}
				if(Bullets[i].getDirection()>1){
					if(Bullets[i].collision(Blocks[x], 0, -temp)){
			temp=0;
		}	if(Blocks[blockLength-1].collision(Bullets[i], Xtemp, Ytemp+temp)){ //player collision this works
			temp=0;	
			hitMeY=-1;
			Blocks[blockLength-1].setHealth(0);
			Bullets[i].setHealth(0);
					}
				}

				}//x loop
			}
			if(Bullets[i].getDirection()<=1){
			Bullets[i].setX(temp);
			if(temp==0 && hitMe==0){
					if(Bullets[i].getDirection()==0){
				Bullets[i].setDirection(1);
				
			}else {
				Bullets[i].setDirection(0);
			}
			}
			
}//y stuff starts here 
			if(Bullets[i].getDirection()>1){
			Bullets[i].setY(temp);
			if(temp==0 && hitMeY==0){
					if(Bullets[i].getDirection()==2){
				Bullets[i].setDirection(3);
			}else {
				Bullets[i].setDirection(2);
			}
			}
		
			
		}
		}
	}
}
void shoot(float x, float y, float dir){
	
	for(int i = 0; i <numBullets; i++){
		if(Bullets[i].getHealth()==0 || Bullets[i].getTime()>=500){
			if(firerate>=30){
			Bullets[i].setXBull(x);
			Bullets[i].setYBull(y);
			Bullets[i].setHealth(1);
			Bullets[i].setTime(0);
			Bullets[i].setDirection(dir);
			firerate=0;
			
		}
	}
	}
}
void shootPlay(float x, float y, float dir){
	
	for(int i = 0; i <numBullets; i++){
		if(Bullets[i].getHealth()==0 || Bullets[i].getTime()>=500){
			if(firerate2>=15){
			Bullets[i].setXBull(x);
			Bullets[i].setYBull(y);
			Bullets[i].setHealth(1);
			Bullets[i].setTime(0);
			Bullets[i].setDirection(dir);
			firerate2=0;
		}
	}
	}
}
void reset(){
		glClearColor(0,.0,0.0,0.0);						//sets the clear colour to yellow
														//glClear(GL_COLOR_BUFFER_BIT) in the display function
														//will clear the buffer to this colour.
		if(mission>=1){
			Blocks[11] = bottom;
	Blocks[20]=bottom1;
	Blocks[13]=bottom2; //vert?
	Blocks[14]= bottom3; //horizontal 
	Blocks[15]=bottom4; //tall pillar
	Blocks[16]=bottom5; //floating pillar
	Blocks[21]=bottom6; // moving up platform
	Blocks[18]=bottom7; //moving up platform left
	Blocks[19]=bottom8; // left bot
	Blocks[12]=bottom9; // left mid bot
	Blocks[17]=bottom10; //left top bot
	Blocks[22]=bottom11; //right top bot
	Blocks[23]=bottom12; //right bot bot 
	Blocks[24]=bottom13; // tall fat block 
	Blocks[25]=topThing; //ceiling
	Blocks[26]=topThing2;
	Blocks[27]=secndRoomLeft;
	Blocks[28]=secndRoomCeil;
	Blocks[29]=secndRoomRight;
	Blocks[30]=secndRoomfloor;
	Blocks[31]=DropBot;
	Blocks[32]=vertDrop;
	Blocks[33]=DropBot2;
	Blocks[34]=DropBot3;
	Blocks[35]=large;
	Blocks[36]=mainroof;
	Blocks[37]=mainwall;
	Blocks[38]=leftwall;
	Blocks[39]=vertDropLeft;
	Blocks[40]=DropBot4;
	Blocks[41]=DropBot5;
	Blocks[42]=DropBot6;
	Blocks[43]=DropBot7;
	Blocks[44]=vertDropRight;

	for(int i=12; i < blockLength-1; i++){
		if(!Blocks[i].isBull()){
		Blocks[i].setHealth(1);
		}
		}
		}

		for(int i=0; i < numBullets; i++){
		Bullets[i].setHealth(0);
	
	}
	Xtemp=0;
	Ytemp=0;
	Blocks[blockLength-1].setHealth(1);
}

/*
Triggers for end of level and various things
*/
void triggers(){

if(Blocks[blockLength-1].getHealth()==0){ //death

Blocks[blockLength-1].setnoJump();
	}
if(mission==0){


}
if(mission==1){
	loadMission();
	Score.setHealth(1);
	mission++;
}

}

void loadMission(){
	for(int x =0; x < 11; x++){
		Blocks[x].setHealth(0);
	}
	for(int x =11; x < blockLength-1; x++){
		if(!Blocks[x].isBull()){
		Blocks[x].setHealth(1);
		}
	}
	
	reset();
}
void processKeys()
{
triggers();
if(Blocks[blockLength-1].getHealth()==0){
	reset();
}
	if(keys[VK_RETURN])
	{
		//Blocks[blockLength-1].setJump(false);
		//Blocks[blockLength-1].setJump(true);
		if(pauseTime==0){
		if(Start.getHealth()==1){
			Start.setHealth(0);
		
		}else{
			Start.setHealth(1);
			
		
		}
		}
		pauseTime=-20;
	
		
	}
	if(pauseTime!=0){
	pauseTime++;
	}
	if(Start.getHealth()==0){
	processMovement();
	processAI();
	processBullets();
	firerate++;
	firerate2++;
		for(int i = 0; i <numBullets; i++){
		if(Bullets[i].getHealth()!=0){
			Bullets[i].setTime(Bullets[i].getTime()+1);

		}
		}


	if(Ytemp<-1000){
		reset();}
	float temp;
	float xCheck=Xtemp;
	if(Blocks[blockLength-1].isJump()){
		int plat =0; 
			temp = Ytemp+Blocks[blockLength-1].jump();
		
		for(int i=0; i <blockLength-1;i++){
			if(Blocks[i].getHealth()!=0){
			
			if(Blocks[blockLength-1].collision(Blocks[i], Xtemp, temp)){
			  
				countStuck++;
			temp=Ytemp;
			
			}
		}
		}
		Ytemp=temp;
		if(countStuck==3){
			Blocks[blockLength-1].setnoJump();
			fall=1.521;
			countStuck=0;
		}
	}
	

	if(keys[VK_UP])
	{
			if(pauseTime==0){
		if(!Blocks[blockLength-1].isJump()){
			Blocks[blockLength-1].setJump(true);
			fall=1.6;
		}
		pauseTime=-20;
			}
			
	
	}
	
	
	if(!Blocks[blockLength-1].isJump()){
	temp=Ytemp+-fall;
	int counter=-1;
		for(int i=0; i <blockLength-1;i++){
			if(Blocks[i].getHealth()!=0){
			if(Blocks[blockLength-1].collision(Blocks[i], Xtemp, temp)){
				fall=1.521;
				if(Blocks[i].isMoving()){
					counter=i;
				}
			temp=Ytemp;
			}
			}
		}
		if(counter!=-1){ //move with the block
		
			if(Blocks[counter].getDirection()==1){
				xCheck=Xtemp+.2;
				for(int i=0; i <blockLength-1;i++){
					if(counter==i){
						i++;
					}
					if(Blocks[i].getHealth()!=0){
			if(Blocks[blockLength-1].collision(Blocks[i], xCheck, temp)){

			xCheck=Xtemp;
				}
					}
				}
			}else if(Blocks[counter].getDirection()==0){
					xCheck=Xtemp+-.2;
				for(int i=0; i <blockLength-1;i++){
					if(counter==i){
						i++;
					}
					if(Blocks[i].getHealth()!=0){
			if(Blocks[blockLength-1].collision(Blocks[i], xCheck, temp)){
			xCheck=Xtemp;
				}
					}
				}
			}else if(Blocks[counter].getDirection()==2){
				temp=Ytemp+-.2;
			}else if(Blocks[counter].getDirection()==3){
					temp=Ytemp+.2;
			}
		
		
	Xtemp=xCheck;
		
		
		}
	
	Ytemp=temp;
		if(fall<=1.521){
		fall=fall+fall*.025;//increase fall speed
		}

	}
		if(keys[VK_LEFT])
	{
	
		Blocks[blockLength-1].setDirection(0);
		temp = Xtemp+-.9;
		for(int i=0; i <blockLength-1;i++){
		if(Blocks[i].getHealth()!=0){
			if(Blocks[blockLength-1].collision(Blocks[i], temp, Ytemp)){
				if(Blocks[i].hasGun()){ //kills if run into enemy
					Blocks[blockLength-1].setHealth(0);
				}
			temp=Xtemp;
			}
		}
		}
		Xtemp=temp;
	
	}
	if(keys[VK_RIGHT])
	{
		Blocks[blockLength-1].setDirection(1);
		temp = Xtemp+.9;
			for(int i=0; i <blockLength-1;i++){
				if(Blocks[i].getHealth()!=0){
			if(Blocks[blockLength-1].collision(Blocks[i], temp, Ytemp)){
				if(Blocks[i].hasGun()){
					Blocks[blockLength-1].setHealth(0);
				}
			temp=Xtemp;
			}
				}
		}
			
		Xtemp=temp;
		//Back.setX(Xtemp);
	
	}
		if(keys[VK_DOWN])
	{
		//reset();
		//Blocks[6].setHealth(0);
		Blocks[blockLength-1].setJump(false);
		Blocks[blockLength-1].setnoJump();
		//mission=1;
		}
		if(keys[VK_CONTROL])
	{
		//reset();
		//Blocks[6].setHealth(0);
		loadMission();
			
		//mission=1;
		}
		if(keys[VK_SPACE]){
			if(Blocks[blockLength-1].getDirection()==1){
				shootPlay(Xtemp+4,Ytemp+8,1);
			}else{
				shootPlay(Xtemp+-8,Ytemp+8,0);

		}
		}
	/*temp=Ytemp+-.4;
			for(int i=0; i <blockLength;i++){
			if(Blocks[blockLength-1].collision(Blocks[i], Xtemp, temp)){
			temp=Ytemp;
			}
		}
		Ytemp=temp;*/
		
		//temp = Ytemp+-.005;
		//	if(!Blocks[blockLength-1].collision(Blocks[0], temp, Ytemp)){
		//
		//	//Ytemp=Ytemp+-.005;
		//	}
		
	}
	
}
//testing
void setVSync(bool sync)
{	
	// Function pointer for the wgl extention function we need to enable/disable
	// vsync
	typedef BOOL (APIENTRY *PFNWGLSWAPINTERVALPROC)( int );
	PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;

	const char *extensions = (char*)glGetString( GL_EXTENSIONS );
	
	if( strstr( extensions, "WGL_EXT_swap_control" ) == 0 )
	{
		return;
	}
	else
	{
		wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC)wglGetProcAddress( "wglSwapIntervalEXT" );

		if( wglSwapIntervalEXT )
			wglSwapIntervalEXT(sync);
	}
}
/**************** END OPENGL FUNCTIONS *************************/

//WIN32 functions
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
void KillGLWindow();									// releases and destroys the window
bool CreateGLWindow(char* title, int width, int height); //creates the window
int WINAPI WinMain(	HINSTANCE, HINSTANCE, LPSTR, int);  // Win32 main function

//win32 global variabless
HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

/******************* WIN32 FUNCTIONS ***************************/
int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	bool	done=false;								// Bool Variable To Exit Loop

	// Create Our OpenGL Window
	if (!CreateGLWindow("spectre",screenWidth,screenHeight))
	{
		return 0;									// Quit If Window Was Not Created
	}
	setVSync(true);		
	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=true;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			if(keys[VK_ESCAPE])
				done = true;
			
			processKeys();
				setVSync(true);	
			display();					// Draw The Scene
			SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (int)(msg.wParam);						// Exit The Program
}

//WIN32 Processes function - useful for responding to user inputs or other events.
LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}
		break;

		case WM_SIZE:								// Resize The OpenGL Window
		{
			reshape(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
		break;

		case WM_LBUTTONDOWN:
			{
	            mouse_x = LOWORD(lParam);          
				mouse_y = screenHeight - HIWORD(lParam);
				LeftPressed = true;
			}
		break;

		case WM_LBUTTONUP:
			{
	            LeftPressed = false;
			}
		break;

		case WM_MOUSEMOVE:
			{
	            mouse_x = LOWORD(lParam);          
				mouse_y = screenHeight  - HIWORD(lParam);
			}
		break;
		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = true;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}
		break;
		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = false;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}
		break;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void KillGLWindow()								// Properly Kill The Window
{
	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*/
 
bool CreateGLWindow(char* title, int width, int height)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;											// Return FALSE
	}
	
	dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
	dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		24,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		24,											// 24Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	reshape(width, height);					// Set Up Our Perspective GL Screen

	init();
	
	return true;									// Success
}



