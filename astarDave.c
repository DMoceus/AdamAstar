#include <stdio.h>
#include <stdlib.h>

#define XSIZE 7
#define YSIZE 7

typedef struct nodeStruct
{
	int pX; //x position
	int pY; //y position
	int g; //cost to get to x from A (the start)
	//int h; //cost to get from x to B (the goal)
	int f;
} node;

int cou;

int open[XSIZE][YSIZE] = {0}; //1 = in open set, 0 = not in open set
int closed[XSIZE][YSIZE] = {0}; // empty
int obstacles[XSIZE][YSIZE] = {0}; //0 = no obstacle, 1 = obstacle

node nodes[XSIZE][YSIZE]; //describe open set

node camefrom [XSIZE][YSIZE];

int startX = 2; // start point
int startY = 0;

int endX = 5; // end point
int endY = 4;

int numObstacles = 8;



node lowestF(int** matrix){
	int minVal = 256;
	int minX = -1;
	int minY = -1;
	int i,j;
	for(i=0;i<XSIZE;i++){
		for(j=0;j<YSIZE;j++){
			if(1 == matrix[i][j]){
				if(minVal > nodes[i][j].f){
					minVal = nodes[i][j].f;
					minX = i;
					minY = j;
				}
			}
		}
	}
	node temp;
	temp.pX = minX;
	temp.pY = minY;
	return temp;
}

void printMatrix(int** matrix){
	int i,j;

	for(i=0;i<XSIZE;i++){
		for(j=0;j<YSIZE;j++){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

//returns 1 if empty
int checkEmptyMatrix(int matrix[XSIZE][YSIZE]){
	int i, j;

	for (i = 0; i < XSIZE; i++){
		for (j = 0; j < YSIZE; j++){
			if (matrix[i][j] == 1){
				return 0;
			}
		}
	}

	return 1;
}

int getH(int sX, int sY, int eX, int eY){
	int temp1 = eX - sX;
	if(temp1<0){
		temp1 = -temp1;
	}
	int temp2 = eY - sY;
	if(temp2<0){
		temp2 = -temp2;
	}
	return temp1+temp2;
}

int calculateH(node ass){
	return abs(endX - ass.pX) + abs(endY - ass.pY);
}

int finalpath[YSIZE*XSIZE][2] = {255};

void reconstructPath(node * current){
	node temp;
	temp.pX = current->pX;
	temp.pY = current->pY;

	finalpath[0][0] = temp.pX;
	finalpath[0][1] = temp.pY;

	while(camefrom[temp.pX][temp.pY].pX != 255){
		int temporaryX, temporaryY;
		temporaryX = temp.pX;
		temporaryY = temp.pY;

		temp.pX = camefrom[temporaryX][temporaryY].pX;
		temp.pY = camefrom[temporaryX][temporaryY].pY;

		int k = 0;
		for (k = 0; finalpath[k][0] == 255; k++){
			
		}
		finalpath[k][0] = temp.pX;
		finalpath[k][1] = temp.pY;
	}

}

int aStar(){
	open[startX][startY] = 1;
	int i,j;
	//Initialize camefrom[][]
	for(i=0;i<XSIZE;i++){
		for(j=0;j<YSIZE;j++){
			node temp;
			temp.pX = -1;
			temp.pY = -1;
			temp.g = 0;
			temp.f = 255;
			camefrom[i][j] = temp;
		}
	}
	//Initialize nodes[][]
	for(i=0;i<XSIZE;i++){
		for(j=0;j<YSIZE;j++){
			node temp;
			temp.pX = i;
			temp.pY = j;
			temp.g = 0;
			temp.f = 255;
			nodes[i][j] = temp;
		}
	}
	nodes[startX][startY].f = nodes[startX][startY].g + getH(startX,startY,endX,endY);
	node current;
	node neighbor;
	int tempGScore;
	while(0 == checkEmptyMatrix(open)){
		current = lowestF(open);
		if(current.pX == endX && current.pY == endY){
			//reconstructPath(current);
			return 1;
		}
		open[current.pX][current.pY] = 0;
		closed[current.pX][current.pY] = 1;
		
		for(i=0;i<4;i++){
			switch(i){
				case 0:
					neighbor.pX = current.pX+1;
					neighbor.pY = current.pY;
					if(neighbor.pX>=XSIZE){neighbor.pX = current.pX;}
					break;
				case 1:
					neighbor.pX = current.pX-1;
					neighbor.pY = current.pY;
					if(neighbor.pX<0){neighbor.pX=current.pX;}
					break;
				case 2:
					neighbor.pX = current.pX;
					neighbor.pY = current.pY+1;
					if(neighbor.pY>=YSIZE){neighbor.pY=current.pY;}
					break;
				case 3:
					neighbor.pX = current.pX;
					neighbor.pY = current.pY-1;
					if(neighbor.pY<0){neighbor.pY=current.pY;}
					break;
			}
			
			if(1==closed[neighbor.pX][neighbor.pY]){}
			else if(1==obstacles[neighbor.pX][neighbor.pY]){}
			else{
				tempGScore = nodes[current.pX][current.pY].g + 1;
				if(0==open[neighbor.pX][neighbor.pY] || tempGScore<nodes[neighbor.pX][neighbor.pY].g){
					camefrom[neighbor.pX][neighbor.pY] = current;
					nodes[neighbor.pX][neighbor.pY].g = tempGScore;
					nodes[neighbor.pX][neighbor.pY].f = nodes[neighbor.pX][neighbor.pY].g + getH(neighbor.pX,neighbor.pY,endX,endY);
					if(0==open[neighbor.pX][neighbor.pY]){
						open[neighbor.pX][neighbor.pY] = 1;
					}
				}
			}
		}
	}
	return -1;
}

int main(){
	if(-1 == aStar()){printf("Shit Don't Work\n");}
	else{printf("It Worked!\n");}
	//printf("%d\n", cou);
	//printf("ugh\n");
}
