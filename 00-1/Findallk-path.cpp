#include<iostream>
#include<stack>

using namespace std;

char** maze;
int row, col, k; // k-path means th length of the path is k

//direction
int dx[] = { -1, 1, 0, 0, -2, -2, 2, 2, 1, -1, 1, -1 };
int dy[] = { 0, 0, -1, 1, -1, 1, -1, 1, -2, 2, 2, -2 };
int CountPaths();

int main(void) {
    cin >> row >> col >> k; //y,x,k step

    maze = new char* [row];
    for (int i = 0; i < row; i++) {
        maze[i] = new char[col];
    }


    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> maze[i][j];
        }
    }

    //output
    //#the number of possible k - paths
    cout << CountPaths() << endl;

    for (int i = 0; i < row; i++) {
        delete[] maze[i];
    }
    delete[] maze;

    return 0;

}



int CountPaths() {
    stack < pair<pair<int, int>, int> > st;  //current position and K steps ((y,x),K)


    int count = 0; //count k path

    //search start point
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (maze[i][j] == 'S') //S is start point
                st.push(make_pair(make_pair(i, j), 0));  // 0 means 0 step
        }
    }

    //dfs search

    while (!st.empty()) {
        int y = st.top().first.first;
        int x = st.top().first.second;
        int length = st.top().second;
        st.pop();

        //dfs end condition
        if (length > k) continue;
       
        if ( length == k) {
            if(maze[y][x]=='E')
                count++;
            continue;
        }


        for (int i = 0; i < 12; i++) {

            int nextX = x + dx[i];
            int nextY = y + dy[i];
            //if (nextX, nextY)is  possible , push and the steps
            if (nextX >= 0 && nextY >= 0 && nextY < row && nextX < col  )
                if (maze[nextY][nextX] != '1') {
                    if (maze[nextY][nextX] == 'E') {
                        if (length == k-1)
                            st.push(make_pair(make_pair(nextY, nextX), length + 1));
                    }
                    else {
                        st.push(make_pair(make_pair(nextY, nextX), length + 1));
                    }
                }

                    

        }


    }//while end
    return count;

}

