// Easy way to include libraries!
#pragma comment(lib, "opengl32.lib")

/*	nvImage.h contains all of the function prototypes needed for image loading.
	This MUST be included before gl.h and glu.h because of dependencies therein - WAYNE! */
#include "Image_Loading/nvImage.h"

// This stores a handle to the texture
GLuint textures[14];
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "Player.h"
#include <stdio.h>
#include <math.h>     /* abs */
Player::Player(){
x=3;
	x2=0;
	y=-3;
	y2=-6;
	color=7;
	jumpHeight=-40;
	boJump=false;
	direction=0;
	moving=true;
	health=0;
	gun=false;
	bullet=true;
	time =0;
	invi=false;
}

Player::Player(float x1temp, float y1temp, float x2temp,float y2temp,int h, int newcolor, bool invis){
	x=x1temp;
	x2=x2temp;
	y=y1temp;
	y2=y2temp;
	color=newcolor;
	jumpHeight=-40;
	boJump=false;
	direction=1;
	moving=false;
	health=h;
	invi=invis;
}
Player::Player(float x1temp, float y1temp, float x2temp,float y2temp,int h, int newcolor){
	x=x1temp;
	x2=x2temp;
	y=y1temp;
	y2=y2temp;
	color=newcolor;
	jumpHeight=-40;
	boJump=false;
	direction=1;
	moving=false;
	health=h;
		invi=false;
		// Texture loading object
}
Player::Player(float x1temp, float y1temp, float x2temp,float y2temp, int h, int newcolor,int move, bool dir){
		x=x1temp;
	x2=x2temp;
	y=y1temp;
	y2=y2temp;
	color=newcolor;
	jumpHeight=-40;
	boJump=false;
	direction=move;
	moving=dir;
	health=h;
		invi=false;
}
Player::Player(float x1temp, float y1temp, float x2temp,float y2temp,int h, int newcolor,int move, bool dir, bool enemy, bool bulls){
	x=x1temp;
	x2=x2temp;
	y=y1temp;
	y2=y2temp;
	color=newcolor;
	jumpHeight=-40;
	boJump=false;
	direction=move;
	moving=dir;
	health=h;
	gun=enemy;
	bullet=bulls;
	time =0;
		invi=false;
}
/**
	Return health of player
*/
int Player::getHealth(void)
{
	return health;
}
void Player::setColor(int co){
	color=co;
}
/**
	Return X location
*/
float Player::getX(void)
{
	return x;
}

/**
	Return y location
*/
float Player::getY(void)
{
	return y;
}
/**
	Return X2 location
*/
float Player::getX2(void)
{
	return x2;
}
bool Player::hasGun(){
	return gun;
}
bool Player::isBull(){
	return bullet;
}
/**
	Return y location
*/
float Player::getY2(void)
{
	return y2;
}
	

/**
	Start tank moving forward
*/
void Player::startMoving(void)
{
	moving = true;
}

/**
	Stop tank moving forward
*/
void Player::stopMoving(void)
{
	moving = false;
}

/**
	Player's update function
*/
int Player::getDirection(){
	return direction;
};
bool Player::isMoving(){
	return moving;
}
void Player::update()
{

}
void Player::setXBull(float tempX){
	x=tempX;
	x2=tempX-3;
}
void Player::setYBull(float tempY){
	y=tempY;
	y2=tempY-3;

}
void Player::setTime(int times){
	time = times;
}
int Player::getTime(){
	return time;
}
/*
	Player X update
*/
void Player::setX(float tempX){
	x=x+-tempX;
	x2=x2+-tempX;
}
/*
	Player Y update
*/
void Player::setY(float tempY){
	y=y+-tempY;
	y2=y2+-tempY;
}
/*
Jump counter
*/
float Player::jump(){
	jumpHeight++;
	if(jumpHeight==40){
		jumpHeight=-40;
		
		setJump(false);
		return (jumpHeight*jumpHeight * -.001);
	}
	if(jumpHeight<0){
	return (jumpHeight*jumpHeight * .001);
	}
	return (jumpHeight*jumpHeight * -.001);
}
void Player::setnoJump(){
	setJump(false);
	jumpHeight=-40;
}
bool Player::isInvi(){
	return invi;
}
bool Player::isJump(){
	return boJump;
}
void Player::setJump(bool jump){
	boJump=jump;
}
void Player::setDirection(int i ){
	direction=i;
}
/**
	<Insert obvious comment here>
*/
void Player::draw()
{//&& invi==false
		if(health>0 ){
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	if(color==5||color==10){
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	}else if(color==0){
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	}else if(color==1){
		glBindTexture(GL_TEXTURE_2D, textures[1]);
	}else if(color==6){
		glBindTexture(GL_TEXTURE_2D, textures[3]);
	}else if(color==3){
		glBindTexture(GL_TEXTURE_2D, textures[4]);
	}else if(color==4){
		glBindTexture(GL_TEXTURE_2D, textures[5]);
	}else if(color==7){
		glBindTexture(GL_TEXTURE_2D, textures[6]);
	}else if(color==8){
		glBindTexture(GL_TEXTURE_2D, textures[7]);
	}else if(color==20){
		glBindTexture(GL_TEXTURE_2D,textures[8]);
	}else if(color==21){
		glBindTexture(GL_TEXTURE_2D,textures[9]);
	}else if(color==22){
		glBindTexture(GL_TEXTURE_2D,textures[10]);
	}else if(color==23){
		glBindTexture(GL_TEXTURE_2D,textures[11]);
	}else if(color==24){
		glBindTexture(GL_TEXTURE_2D,textures[12]);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if(color==5){ //textures that get tiled 
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0); glVertex2f(x,y);
		glTexCoord2f(abs(x-x2)/4, 1.0); glVertex2f(x2,y);
		glTexCoord2f(abs(x-x2)/4, 0.0); glVertex2f(x2,y2);
		glTexCoord2f(0.0, 0.0); glVertex2f(x,y2);
	glEnd();
	}else if(color==1||color==3){ //background
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0); glVertex2f(x,y);
		glTexCoord2f(5.0, 1.0); glVertex2f(x2,y);
		glTexCoord2f(5.0, 0.0); glVertex2f(x2,y2);
		glTexCoord2f(0.0, 0.0); glVertex2f(x,y2);
	glEnd();
	}else if(color==10){ //background
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, abs(y-y2)/4.0); glVertex2f(x,y);
		glTexCoord2f(1.0, abs(y-y2)/4.0); glVertex2f(x2,y);
		glTexCoord2f(1.0, 0.0); glVertex2f(x2,y2);
		glTexCoord2f(0.0, 0.0); glVertex2f(x,y2);
	glEnd();
	}else{ //textures that are not repeated 
		if(direction==1){
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0); glVertex2f(x,y);
		glTexCoord2f(1.0, 1.0); glVertex2f(x2,y);
		glTexCoord2f(1.0, 0.0); glVertex2f(x2,y2);
		glTexCoord2f(0.0, 0.0); glVertex2f(x,y2);
		}else if(direction==0){
			glBegin(GL_QUADS);
		glTexCoord2f(1.0, 1.0); glVertex2f(x,y);
		glTexCoord2f(0.0, 1.0); glVertex2f(x2,y);
		glTexCoord2f(0.0, 0.0); glVertex2f(x2,y2);
		glTexCoord2f(1.0, 0.0); glVertex2f(x,y2);
		}
	glEnd();
	}

	glDisable(GL_TEXTURE_2D);

	glDisable(GL_BLEND);


	glPopMatrix();
		}
}
void Player::setHealth(int h){
	health=h;
}
bool Player::collision(Player p1, float Xtemp, float Ytemp){
	//top side 
	if(x2<=p1.getX2()-Xtemp && x>=p1.getX()-Xtemp && y2<=p1.getY()-Ytemp && y>=p1.getY2()-Ytemp  //top
		||x2<=p1.getX2()-Xtemp && x2>=p1.getX()-Xtemp && y2<=p1.getY()-Ytemp && y>=p1.getY2()-Ytemp
		||x<=p1.getX2()-Xtemp && x>=p1.getX()-Xtemp && y2<=p1.getY()-Ytemp && y>=p1.getY2()-Ytemp //problem?
		//||x2>=p1.getX2()-Xtemp && x<=p1.getX()-Xtemp && y2<=p1.getY()-Ytemp && y>=p1.getY2()-Ytemp
		||x2>=p1.getX2()-Xtemp && x<=p1.getX()-Xtemp && y2<=p1.getY()-Ytemp && y>=p1.getY2()-Ytemp
		||x<=p1.getX()-Xtemp && x2>=p1.getX2()-Xtemp && y<=p1.getY()-Ytemp && y2>=p1.getY2()-Ytemp
		||x>=p1.getX()-Xtemp && x2<=p1.getX2()-Xtemp && y>=p1.getY()-Ytemp && y2<=p1.getY2()-Ytemp
		){
		
		return true;
	}
	/*if(x2<=p1.getX()-Xtemp||y2<=p1.getY()-Ytemp){
		return true;
	}*/
	/*return (abs(x - (p1.getX()-Xtemp)) * 2 < ((x2-x) + (p1.getX2()-Xtemp)-(p1.getX()-Xtemp))) &&
		(abs(y - (p1.getY()-Ytemp)) * 2 < ((y-y2) +(p1.getY()-Ytemp)-(p1.getY2()-Ytemp)));
*/
	return false;

}
void Player::setUpTextures()
{	
      nv::Image img;

	// Return true on success
	
		  	if(img.loadImageFromFile("backnew2.png"))
	{
		glGenTextures(1, &textures[1]);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}
	setUpTexturesPlatforms();
	setUpTexturesPlayer();
	setUpTexturesHealth();
	//setUpTextureBackGround();
	//setUpTexturesEnemy();
	setUpTexturesStars();
	setUpTexturesStartScreen();
	setUpTexturesBullet();
	setUpTexturesTurret();
	setUpTexturesScore1();
	setUpTexturesScore2();
	setUpTexturesScore3();
	setUpTexturesScore4();
	setUpTexturesScore5();
}

void Player::setUpTexturesPlayer(){
	
      nv::Image img;
	if(img.loadImageFromFile("ninja.png"))
	{
		glGenTextures(1, &textures[0]);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}else{
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);
}

	/**********************************************************************************************/
}
void Player::setUpTexturesPlatforms(){
	
      nv::Image img;
	if(img.loadImageFromFile("tile.png"))
	{
		glGenTextures(1, &textures[2]);
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	else
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);

	/**********************************************************************************************/
}
void Player::setUpTexturesHealth(){ //not used
	      nv::Image img;
	if(img.loadImageFromFile("livewhite.png"))
	{
		glGenTextures(1, &textures[3]);
		glBindTexture(GL_TEXTURE_2D, textures[3]);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	//else
		//MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);

}
void Player::setUpTexturesStars(){
	      nv::Image img;
	if(img.loadImageFromFile("stars.png"))
	{
		glGenTextures(1, &textures[4]);
		glBindTexture(GL_TEXTURE_2D, textures[4]);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	else
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);

}
void Player::setUpTexturesStartScreen(){
		nv::Image img;
		if(img.loadImageFromFile("startNew.png"))
	{
		glGenTextures(1, &textures[5]);
		glBindTexture(GL_TEXTURE_2D, textures[5]);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}
}
void Player::setUpTexturesBullet(){
	
		nv::Image img;
		if(img.loadImageFromFile("bullet.png"))
	{
		glGenTextures(1, &textures[6]);
		glBindTexture(GL_TEXTURE_2D, textures[6]);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}
}
void Player::setUpTexturesTurret(){
	nv::Image img;
		if(img.loadImageFromFile("turret.png"))
	{
		glGenTextures(1, &textures[7]);
		glBindTexture(GL_TEXTURE_2D, textures[7]);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}
}
void Player::setUpTexturesScore1(){
	nv::Image img;
		if(img.loadImageFromFile("Section1.png"))
	{
		glGenTextures(1, &textures[8]);
		glBindTexture(GL_TEXTURE_2D, textures[8]);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}
}
void Player::setUpTexturesScore2(){
	nv::Image img;
		if(img.loadImageFromFile("Section2.png"))
	{
		glGenTextures(1, &textures[9]);
		glBindTexture(GL_TEXTURE_2D, textures[9]);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}
}
void Player::setUpTexturesScore3(){
	nv::Image img;
		if(img.loadImageFromFile("Section3.png"))
	{
		glGenTextures(1, &textures[10]);
		glBindTexture(GL_TEXTURE_2D, textures[10]);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}
}
void Player::setUpTexturesScore4(){
	nv::Image img;
		if(img.loadImageFromFile("Section4.png"))
	{
		glGenTextures(1, &textures[11]);
		glBindTexture(GL_TEXTURE_2D, textures[11]);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}
}
void Player::setUpTexturesScore5(){
	nv::Image img;
		if(img.loadImageFromFile("Section5.png"))
	{
		glGenTextures(1, &textures[12]);
		glBindTexture(GL_TEXTURE_2D, textures[12]);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}
}
