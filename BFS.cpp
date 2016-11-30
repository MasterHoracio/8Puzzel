#include <cstdio>
#include <vector>
#include <queue>
#include <map>

#define rep(i, n) for (int i = 0; i < n; i++)
#define LIMIT 3

using namespace std;

typedef vector<vector<int> > board;
typedef pair<int, int> pii;

map<board, bool> visitado;
map<board, board > padre;
board estadoFinal(3, vector<int> (3));

//izquierda, derecha, abajo, arriba
int movimientosX[]={-1, +1, 0, 0};
int movimientosY[]={0, 0, -1, +1};

void computeFinalBoard(){
    estadoFinal[0][0] = 1; estadoFinal[0][1] = 2; estadoFinal[0][2] = 3;
    estadoFinal[1][0] = 4; estadoFinal[1][1] = 5; estadoFinal[1][2] = 6;
    estadoFinal[2][0] = 7; estadoFinal[2][1] = 8; estadoFinal[2][2] = 0;
}

bool isGoal(board estadoActual){

    rep(i,3){
        rep(j,3){
            if(estadoActual[i][j] != estadoFinal[i][j])
                return false;
        }
    }
    return true;
}

isVisited(board estado){
    if(visitado[estado] == true)
        return true;
    return false;
}

bool inRange(int x,int y)
{
	if(x >= 0 && x <= 2 && y >= 0 && y <= 2)
        return true;
	return false;
}

pii findSpace(board estado){
    pii position;
    rep(i,3){
        rep(j,3){
            if(estado[i][j] == 0){
                position.first = i;
                position.second = j;
            }
        }
    }
    return position;
}

vector<vector<vector<int> > > computeMoves(board current){
    pii position = findSpace(current);
    vector<vector<vector<int> > > moves;
    int x, y;

    rep(i,4){
        x = position.second + movimientosX[i];
        y = position.first + movimientosY[i];
        vector<vector<int> > temp = current;
        if(inRange(x, y)){
            swap(temp[y][x],temp[position.first][position.second]);
            moves.push_back(temp);
        }
    }
    return moves;
}

void printBoard(board current){
    rep(i,3){
        rep(j,3){
            printf("%d ",current[i][j]);
        }printf("\n");
    }
}

void printCamino(board current){
    if(padre.count(current))
        printCamino(padre[current]);

   printBoard(current);
   printf("\n");
 return;
}

void DFS(board start){
    queue <board> cola;
    board current;
    cola.push(start);

    while(!cola.empty()){
        current = cola.front();
        cola.pop();

        visitado[current] = true;

        if(isGoal(current)){
            printCamino(current);
            break;
        }

        vector<vector<vector<int> > > moves = computeMoves(current);
		vector<vector<vector<int> > >::iterator it;

        for(it = moves.begin(); it != moves.end(); it++){
            vector<vector<int> > aux = *it;
            if(!visitado[aux]){
                cola.push(aux);
                padre.insert(pair<vector<vector<int> > , vector<vector<int> > >(aux,current));
            }
        }
    }
}

int main()
{
    board estadoInicial(3, vector <int> (3));
    computeFinalBoard();

    printf("\n\n#######################Ingrese los elementos del tablero#######################\n\n");

    rep(i,LIMIT)
        rep(j,LIMIT)
            scanf("%d",&estadoInicial[i][j]);

    DFS(estadoInicial);

    return 0;
}
