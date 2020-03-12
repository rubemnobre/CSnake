#include<GL/freeglut.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<time.h>
#define w 640
#define h 640
#define dif 75
const float s = .1;
const float of = 0.005;
long lstloop = 0;
int spd = 200;
int dir = 2;
int lvl = 1;
int dead = 0;
int desync = 0;
char nome[4];
int win;
typedef struct{
    int x;
    int y;
}pos;
pos snk[1600];
pos food;

void logicLoop();
void loop();

void sn_init(){
    int i;
    for(i = 0;i < 32*24;i++){
        snk[i].x = i;
        snk[i].y = i;
    }
}
void sqr(GLfloat x,GLfloat y,int r,int g){
    glBegin(GL_QUADS);
    glColor3f(r,g,0);
    x *= s;
    y *= s;
    x -= 1;
    y += 1-s;
    glVertex2f(x,y+of);
    glVertex2f(x+s-of,y+of);
    glVertex2f(x+s-of,y+s);
    glVertex2f(x,y+s);
    glEnd();
    glFlush();
}
int cnt = 0;
void input(int key,int a,int b){
	switch(key){
		case 100:if(dir != 2) dir = 0;
			logicLoop();
			desync = 1;
			lstloop = clock();
			break;
		case 101:if(dir != 3) dir = 1;
			logicLoop();
			desync = 1;
			lstloop = clock();
			break;
		case 102:if(dir != 0) dir = 2;
			logicLoop();
			desync = 1;
			lstloop = clock();
			break;
		case 103:if(dir != 1) dir = 3;
			logicLoop();
			desync = 1;
			lstloop = clock();
			break;
	}
}
int rep(pos *a,pos b){
	int j;
	for(j = 0;j < lvl;j++){
		if(a[j].x == b.x && a[j].y == b.y){
			return 1;
		}
	}
	return 0;
}
void mov(){
	int i;
	for(i = 20*20-1;i > 0;i--){
		snk[i] = snk[i-1];
	}
	switch(dir){
		case 0:snk[0].x--;break;
		case 1:snk[0].y++;break;
		case 2:snk[0].x++;break;
		case 3:snk[0].y--;break;
	}
}
void cfood(int a){
	int x,y;
	x = food.x;
	y = food.y;
	if(a == 0) sqr(food.x,food.y,0,0);
	while(rep(snk+1,food) || (food.x == x&&food.y == y)){
		food.x =   rand() % 20 ;
		food.y = -(rand() % 20);
	}
	sqr(food.x,food.y,0,1);
}
int k = 0;

char arg;



void logicLoop(){
	if(k > dif){
		cfood(0);
		k = 0;
	}
	k++;
	mov();
	if(rep(snk+1,snk[0]) == 1){
		printf("\nScore: %d\nPress ENTER to quit",lvl-1);
        glutHideWindow();
		dead = 1;
	}
	if(snk[0].x < 0 || snk[0].y > 0|| snk[0].x > 19 || snk[0].y < -19){
		printf("\nScore: %d\nPress ENTER to quit",lvl-1);
        glutHideWindow();
		dead = 1;
	}
	sqr(snk[lvl].x,snk[lvl].y,0,0);
	sqr(snk[ 0 ].x,snk[ 0 ].y,1,0);
	if(snk[0].x == food.x && snk[0].y == food.y){
		lvl++;
		if(spd > 50){
            spd -= 5;
            printf("%d\n", spd);
        }
		cfood(1);
		k = 0;
	}
	if(k >= dif){
		cfood(0);
		k = 0;
	}
}

void loop(){
    if(dead){
        glutDestroyWindow(win);
        getchar();
        return;
    }
	if(desync == 0){
		logicLoop();
		lstloop = clock();
	}
	desync = 0;
	int dt = clock()-lstloop;
    int delay = spd - (dt*1000)/CLOCKS_PER_SEC;
    if(delay < 1) delay = 1;
	glutTimerFunc(delay,loop,0);
}

void displayFunc(){}


int main(int a,char **b){
	
	srand(clock()*time(NULL));
	sn_init();
	glutInit(&a,b);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(w,h);
	win = glutCreateWindow("SNAKES-rn");
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	sqr(snk[0].x,snk[0].y,1,0);
	glutSpecialFunc(input);
	glutDisplayFunc(displayFunc);
	cfood(1);
	lstloop = clock();
	loop();
	//glutPopWindow();
	//printf("entering mainloop\n");
	glutMainLoop();
	return 105;
}

