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

int calculateH(node ass){
	return abs(endX - ass.pX) + abs(endY - ass.pY);
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

void aStar(){
	
	cou = 0;
	open[startX][startY] = 1;
	
	

	obstacles[2][2] = 1;
	
	obstacles[4][0] = 1;

	obstacles[4][2] = 1;
	
	obstacles[4][3] = 1;
	
	obstacles[4][4] = 1;
	
	obstacles[4][5] = 1;
	
	obstacles[5][2] = 1;
	
	obstacles[6][2] = 1;

	
	int i, j;
//initialize nodes
	for (i = 0; i < XSIZE; i++){
		for (j = 0; j < YSIZE; j++){
			//open[i][j] = 0;
			nodes[i][j].pX = i;
			nodes[i][j].pY = j;
			//nodes[i][j].h = abs(i - endX) + abs(j - endY);
			nodes[i][j].g = 0;
			nodes[i][j].f = 255;

			camefrom[i][j].pX = 255;
			camefrom[i][j].pY = 255;
			//camefrom[i][j].h = 255;
			camefrom[i][j].g = 0;
			camefrom[i][j].f = 255;
		}
	}

	
	int tempF = 255;
	int tempX = 255;
	int tempY = 255;
	nodes[startX][startY].f = nodes[startX][startY].g + getH(startX,startY,endX,endY);
	//nodes[startX][startY].f = nodes[startX][startY].g + calculateH(nodes[startX][startY]);
	tempX = startX;
	tempY = startY;
	//cou++;
	while (checkEmptyMatrix(open) == 0){
		/*
		for(i=0;i<XSIZE;i++){
			for(j=0;j<YSIZE;j++){
				printf("%d ", open[i][j]);
			}
			printf("\n");
		}
*/
		for (i = 0; i < XSIZE; i++){
			for (j = 0; j < YSIZE; j++){
				if (open[i][j] == 1 && nodes[i][j].f < tempF){
 
					tempF = nodes[i][j].f;
					tempX = i;
					tempY = j;
/*
					if (nodes[i][j].pX = endX && nodes[i][j].pY == endY){
						reconstructPath(&nodes[i][j]);
						printf("finised reconstruct\n");
					}*/
				}
			}
		}
		//if (nodes[i][j].pX == endX && nodes[i][j].pY == endY){
		if(tempX == endX && tempY == endY){
			printf("started reconstruct\n");
			reconstructPath(&nodes[i][j]);
			printf("finished reconstruct\n");
		}
		open[tempX][tempY] = 0; //remove from open
		closed[tempX][tempY] = 1; //add to closed


		node neighbor;
		//neighbors
		for (i = 0; i < 4; i++){
			switch(i){
				case 0: 
					neighbor.pX = tempX+1;
					neighbor.pY = tempY;
					if (neighbor.pX >= XSIZE){
						neighbor.pX = tempX;
					}
					break;

				case 1: 
					neighbor.pX = tempX-1;
					neighbor.pY = tempY;
					if (neighbor.pX < 0){
						neighbor.pX = tempX;
					}
					break;

				case 2: 
					neighbor.pX = tempX;
					neighbor.pY = tempY+1;
					if (neighbor.pY >= YSIZE){
						neighbor.pY = tempY;
					}
					break;

				case 3: 
					neighbor.pX = tempX;
					neighbor.pY = tempY-1;
					if (neighbor.pY < 0){
						neighbor.pY = tempY;
					}
					break;
			}

			if (closed[neighbor.pX][neighbor.pY] == 1){}
			else if (obstacles[neighbor.pX][neighbor.pY] == 1){}
			else{
				int tempG = nodes[tempX][tempY].g + 1; //distance b/w current and neighbor

				if (open[neighbor.pX][neighbor.pY] == 0 || tempG < nodes[tempX][tempY].g){
					camefrom[neighbor.pX][neighbor.pY].pX = nodes[tempX][tempY].pX;
					camefrom[neighbor.pX][neighbor.pY].pY = nodes[tempX][tempY].pY;
					camefrom[neighbor.pX][neighbor.pY].g = nodes[tempX][tempY].g;
					camefrom[neighbor.pX][neighbor.pY].f = nodes[tempX][tempY].f;

					nodes[neighbor.pX][neighbor.pY].g = tempG;
					nodes[neighbor.pX][neighbor.pY].f = nodes[neighbor.pX][neighbor.pY].g + getH(neighbor.pX,neighbor.pY,endX,endY);
					//nodes[neighbor.pX][neighbor.pY].f = nodes[neighbor.pX][neighbor.pY].g + calculateH(nodes[neighbor.pX][neighbor.pY]);

					if (open[neighbor.pX][neighbor.pY] == 0){
						open[neighbor.pX][neighbor.pY] = 1;
					}
				}//if open
			} // else
		}//for
		
	}//while
	
	//return;
}

int main(){
	aStar();
	printf("%d\n", cou);
	printf("ugh\n");
}
