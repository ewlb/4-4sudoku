#include<bits/stdc++.h>
using namespace std;

int spaces = 0;
vector<vector<int> > sudoku;
bool blank[4][4]{};
const string red("\033[;31m");
const string yellow("\033[0;33m");
const string white("\033[0m");
const string green("\033[;32m");

void ERRORofspaces(int n){
	cout << red <<"only "<< n <<", please try again\n" << white;
	cout <<"==========================\n";
}

void ErrorOfFillinOutOfRange(){
	cout << red << "x and y must in the range of [1, 5), please try again\n" << white;
	cout << "==========================\n";
}
void ErrorOfFillinAlreadyExit(){
	cout << red << "you can't fill the position x y, please try again\n" << white;
	cout << "==========================\n";
}

void Spaces(int n){
	int x=0;
	int y=0;
	for(int i=0;i<n;i++){
		while(true){
			x = rand()%4;
			y = rand()%4;
			if(sudoku[x][y]!=0){
				sudoku[x][y]=0;
				blank[x][y] = 1;
				break;
			}
		}
	}	
}

void fillin(int x,int y){
	int answer=0;
	cout <<"filling the answer, your answer is: ";
	cin >> answer;
	sudoku[x][y]=answer;
}

void create(){
    vector<int> vec={1, 2, 3, 4};
    sudoku.resize(4);
    for(int i=0;i<4;i++)
        sudoku[i].resize(4, 0);
    srand(time(NULL));
    random_shuffle(vec.begin(), vec.end());
    sudoku[0]=vec;
    for(int x=1;x<4;x++){
        random_shuffle(vec.begin(), vec.end());
        sudoku[x]=vec;
        for(int y=0;y<4;y++){
			if(sudoku[x][y]==sudoku[x-1][y]){
				random_shuffle(vec.begin(), vec.end());
				sudoku[x]=vec;
				y=-1;
				continue;
			}

            if(sudoku[x][y]==sudoku[(x+1)%4][y] || sudoku[x][y]==sudoku[(x+2)%4][y] || sudoku[x][y]==sudoku[(x+3)%4][y]){
                y=-1;
                random_shuffle(vec.begin(), vec.end());
                sudoku[x]=vec;
            }
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cout<<sudoku[i][j]<<" ";
        }
        cout<<endl;
    }
}

void printQuestion(){
	for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
			if(blank[i][j]){
				cout << yellow << " " << sudoku[i][j] << white ;
			}
			else
				cout << " " << sudoku[i][j];
			if(j<3)
				cout << " | ";
			else
				cout << endl;
        }
		if(i<3)
			cout <<"----------------\n";
    }
}

void makeQ(){
	create();
	cout <<"sets the number of spaces\n";
	cout <<"the maxmum of spaces: 16\n";
	while(cin >> spaces){
		if(spaces>16){
			ERRORofspaces(16);
		}else{
			break;
		}
	}	
	Spaces(spaces);
	printQuestion();
}

int check(){
	int sum[2][4]={0};
	for(int x=0;x<4;x++){
		sum[0][x]=0;
		sum[1][x]=0;
		for(int y=0;y<4;y++){
			sum[0][x]+=sudoku[x][y];
			sum[1][x]+=sudoku[y][x];
		}	
		if(sum[0][x]!=10 || sum[1][x]!=10){
			cout << "not done yet\nchoose spaces (x and y) \n";
			return 0;
		}
	}	
	
	cout << green << "you are done\n";
	cout << "Congratulation!\n" << white;
	return 1;
}

int main(){
	// START:
	int complete = 0;
	int x = 0;
	int y = 0;

	makeQ();
	cout << "choose spaces (x(row) and y(column))\n";
	cout << "the maximum of x and y is 5\n";
	do{
		cin >> x >> y;
		if(x<=0 || x>=5 || y<=0 || y>=5){
			ErrorOfFillinOutOfRange();
			continue;
		}
		if(sudoku[x-1][y-1]!=0){
			ErrorOfFillinAlreadyExit();
			continue;
		}
		fillin(x - 1, y - 1);
		printQuestion();
		complete=check();
	}while(complete!=1);
		
	// goto START;
		
	return 0;
} 
