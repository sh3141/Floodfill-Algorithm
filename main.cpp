//flood fill on c++ lets see how you do bruh L ratio
#include <iostream>
#include <cstring>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>

using namespace std;

int ori=0;
const int dim=8;
int goal_x=3;
int goal_y=7;

struct cell{
    int x,y,v;
    bool r_wall;
    bool u_wall;
    bool visited;
    bool reset;
};
void inialise(cell maze[dim][dim],int goal_x,int goal_y);
///////////////////
void move_forward(cell &cur_pos,int dir);
void turn_right(){ori=(ori+1)%4;}
void turn_left() {ori=(ori+3)%4;}
void move_back(cell &cur_pos);
//////////////////
void move_to_target(cell &cur_pos, cell target);
//////////////////
void test_print(vector<cell> v){
 for(int i=0;i<v.size();i++) cout<<"("<<v[i].y<<","<<v[i].x<<")"<<endl;
 cout<<"----------------------------"<<endl;
}
void read_input(string input_maze[2*dim+3]){
	string s;
	for(int i=2*dim;i>=0;i--){
		getline(cin,s);
		input_maze[i]=s;
	}
}
bool check_w(string input_maze[2*dim+3],cell cur_pos,int dir);
bool is_wall_f(string input_maze[2*dim+3],cell cur_pos);
bool is_wall_r(string input_maze[2*dim+3],cell cur_pos);
bool is_wall_l(string input_maze[2*dim+3],cell cur_pos);

void print(cell maze[dim][dim]){
    for(int i=dim-1;i>=0;i--){
    	for(int j=0;j<dim;j++){
    		if(!j)cout<<" ";
                if(maze[i][j].u_wall) cout<<"- ";

                else cout<<"  ";
                       }
//if(j==4&&i==0) cout<<"("<<i<<","<<j<<"): "<<maze[i][j].u_wall<<" "<<maze[i][j].r_wall;
                       cout<<endl;

 for(int j=0;j<dim;j++){
    if(!j) cout<<"|";
        cout<<maze[i][j].v;
           if(maze[i][j].r_wall) cout<<"|";
          	else cout<<" ";
           }
           cout<<endl;
    }

for(int q=0;q<dim;q++)cout<<" -";
}

void set_walls(cell maze[][dim], cell return_maze[][dim],cell cur_pos,int dir);
void update_walls(cell maze[][dim],cell return_maze[][dim] ,cell cur_pos,string input_maze[2*dim+3]);
cell min(vector<cell> a){
    cell m=a[0];
	for(int i=1;i<a.size();i++) if(a[i].v<m.v) m=a[i];
	return m;
}

void insert(vector<cell> v, queue <cell> &q){
	for(int i=0;i<v.size();i++) q.push(v[i]);
}

void insert_unedited(vector<cell> v, queue <cell> &q){
	for(int i=0;i<v.size();i++) if(!v[i].reset) q.push(v[i]);
}

vector<cell> get_avaiable_cells(cell maze[][dim],cell c){
       vector<cell> ava;
        if(!c.u_wall) if(c.y+1<dim) ava.push_back(maze[c.y+1][c.x]);
        if(!c.r_wall) if(c.x+1<dim) ava.push_back(maze[c.y][c.x+1]);
        if(c.x>0 )
        if(!(maze[c.y][c.x-1].r_wall))
            ava.push_back(maze[c.y][c.x-1]);
        if(c.y>0)
        if(!(maze[c.y-1][c.x].u_wall)) ava.push_back(maze[c.y-1][c.x]);
       return ava;
}
bool check_neighbourhood(cell maze[][dim],cell c,cell &target);
void flood_fill(cell maze[][dim],cell cur_pos,queue <cell> &q);

void test_floodfill(cell cur_pos,cell maze[][dim],cell &target,queue<cell>&q){

    test_print(get_avaiable_cells(maze,maze[cur_pos.y][cur_pos.x]));
	if(!check_neighbourhood(maze,maze[cur_pos.y][cur_pos.x],target)){
	    flood_fill(maze,cur_pos,q);
cout << maze[cur_pos.y][cur_pos.x].v<<endl;
for(auto c : get_avaiable_cells(maze,maze[cur_pos.y][cur_pos.x]))
    cout<<"("<<c.y<<","<<c.x<<") -> "<<maze[c.y][c.x].v<<endl;
}
}

void creat_return_maze(cell maze[][dim],cell return_maze[][dim]){
for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++){
			return_maze[i][j].x=maze[i][j].x;
			return_maze[i][j].y=maze[i][j].y;
			return_maze[i][j].v=maze[i][j].v;
			return_maze[i][j].r_wall=maze[i][j].r_wall;
			return_maze[i][j].u_wall=maze[i][j].u_wall;
			return_maze[i][j].visited=0;
			return_maze[i][j].reset=0;
		}
	}
}
void search_for_goal(cell maze[][dim],cell return_maze[][dim],string input_maze[2*dim+1],cell &cur_pos){
int j=0;
cell target;
queue <cell>q;
//test_print(get_avaiable_cells(maze,maze[0][3]));
      update_walls(maze,return_maze,maze[cur_pos.y][cur_pos.x],input_maze);

     cout<<"("<<cur_pos.y<<","<<cur_pos.x<<")";
      while(maze[cur_pos.y][cur_pos.x].v>0){
j++;
	 while(check_neighbourhood(maze,maze[cur_pos.y][cur_pos.x],target)){
	     move_to_target(cur_pos,target);
	     update_walls(maze,return_maze,maze[cur_pos.y][cur_pos.x],input_maze);
	      cout<<endl<<"upper wall state: "<<cur_pos.u_wall<<endl;
	     cout<<" -> ("<<cur_pos.y<<","<<cur_pos.x<<")";
     }

if(maze[cur_pos.y][cur_pos.x].v>0)flood_fill(maze,maze[cur_pos.y][cur_pos.x],q);

if(j==2) break;
	 }
	 cout<<endl;

print(maze);
cout<<endl;


}
void return_floodfill(cell return_maze[][dim],cell st_pos,queue <cell> &q);
//////////////////////////////
int main(){
	string input_maze[2*dim+1];
	queue <cell> q;
	read_input(input_maze);
	 cell maze[dim][dim];
	 cell return_maze[dim][dim];
	 cell target;
	 int st_x=4;
	 int st_y=0;
	 cell cur_pos;
	 cur_pos.x=st_x;
	 cur_pos.y=st_y;
	 inialise(maze,goal_x,goal_y);
	 cur_pos=maze[st_y][st_x];
	 cout<<endl;
print(maze);
cout<<endl;

update_walls(maze,return_maze,maze[cur_pos.y][cur_pos.x],input_maze);
for(int j=0;j<5;j++){
        cur_pos=maze[st_y][st_x];
ori=0;
    for(int i=0;i<50;i++){
      //  cout<<"-------------"<<i<<"----------------"<<endl;
        if(!maze[cur_pos.y][cur_pos.x].v) break;
            update_walls(maze,return_maze,maze[cur_pos.y][cur_pos.x],input_maze);
    if(check_neighbourhood(maze,maze[cur_pos.y][cur_pos.x],target)) {
        //cout<<"yay"<<endl;
      //  cout<<" -> ("<<target.y<<","<<target.x<<")";
         move_to_target(cur_pos,target);
   //  cout<<" -> ("<<target.y<<","<<target.x<<")";
	    update_walls(maze,return_maze,maze[cur_pos.y][cur_pos.x],input_maze);

	     cout<<" -> ("<<cur_pos.y<<","<<cur_pos.x<<")";
    }
    else {
        if(maze[cur_pos.y][cur_pos.x].v>0)flood_fill(maze,maze[cur_pos.y][cur_pos.x],q);
    }
    }
}
    print(maze);
	// creat_return_maze(maze,return_maze);
	// return_floodfill(return_maze,return_maze[st_y][st_x],q);
	// cout<<endl<<"return maze"<<endl;
	// print(return_maze);
	 //cout<<endl;
	// search_for_goal(return_maze,maze,input_maze,cur_pos);
	 //search_for_goal(maze,return_maze,input_maze,cur_pos);

}
void inialise(cell maze[dim][dim],int goal_x,int goal_y){
	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++){
			maze[i][j].x=j;
			maze[i][j].y=i;
			maze[i][j].v=abs(j-goal_x)+abs(i-goal_y);
			maze[i][j].r_wall=0;
			maze[i][j].u_wall=0;
			maze[i][j].visited=0;
			maze[i][j].reset=0;

		}
	}
}

void update_walls(cell maze[][dim],cell return_maze[][dim], cell cur_pos,string input_maze[2*dim+3]){
	int dir;
	if(is_wall_f(input_maze,cur_pos)){
		dir=ori;
		set_walls(maze,return_maze, cur_pos,dir);
	}

	if(is_wall_r(input_maze,cur_pos)){
		dir=(ori+1)%4;
		set_walls(maze,return_maze, cur_pos,dir);
	}
	if(is_wall_l(input_maze,cur_pos)){
		dir=(ori+3)%4;
		set_walls(maze,return_maze, cur_pos,dir);
	}

}
void set_walls(cell maze[][dim], cell return_maze[][dim],cell cur_pos,int dir){
	switch(dir){
		case 0:
			maze[cur_pos.y][cur_pos.x].u_wall =1;
			return_maze[cur_pos.y][cur_pos.x].u_wall =1;
			break;
		case 1:
			maze[cur_pos.y][cur_pos.x].r_wall =1;
			return_maze[cur_pos.y][cur_pos.x].r_wall =1;
			break;
		case 2:
			if(cur_pos.y>0)
			{maze[cur_pos.y-1][cur_pos.x].u_wall =1;
			return_maze[cur_pos.y-1][cur_pos.x].u_wall =1;
			}
			break;
		case 3:
			if(cur_pos.x>0)
			{maze[cur_pos.y][cur_pos.x-1].r_wall =1;
			return_maze[cur_pos.y][cur_pos.x-1].r_wall =1;
			}
			break;
		}
}

bool check_w(string input_maze[2*dim+3],cell cur_pos,int dir){
switch(dir){
    case 0:
        //cout<<input_maze[2*(cur_pos.y) +2][2*(cur_pos.x) +1]<<endl;
    	if(input_maze[2*(cur_pos.y) +2][2*(cur_pos.x) +1]=='-')
            return 1;
    	else return 0;
    case 1:
        //cout<<input_maze[2*(cur_pos.y)+1][2*(cur_pos.x)+2]<<endl;
    	if(input_maze[2*(cur_pos.y)+1][2*(cur_pos.x)+2]=='|') return 1;
    	else return 0;
     case 2:
        //cout<<input_maze[2*(cur_pos.y)][2*(cur_pos.x)+1]<<endl;
    	if(input_maze[2*(cur_pos.y)][2*(cur_pos.x)+1]=='-') return 1;
    	else return 0;
    case 3:
        //cout<<input_maze[2*(cur_pos.y)+1][2*(cur_pos.x)]<<endl;
    	if(input_maze[2*(cur_pos.y)+1][2*(cur_pos.x)]=='|') return 1;
    	else return 0;

    }
    return 0;
}
bool is_wall_f(string input_maze[2*dim+3],cell cur_pos){
    int dir=ori;
    return check_w(input_maze,cur_pos,dir);
}
bool is_wall_r(string input_maze[2*dim+1],cell cur_pos){
    int dir=(ori+1)%4;
    return check_w(input_maze,cur_pos,dir);
}

bool is_wall_l(string input_maze[2*dim+1],cell cur_pos){
    int dir=(ori+3)%4;
    return check_w(input_maze,cur_pos,dir);
}
bool check_neighbourhood(cell maze[][dim],cell c,cell &target){
       vector<cell> ava=get_avaiable_cells(maze,c);
       cell m=min(ava);
       if(c.v<=m.v) return 0;
       else{
       	target=m;
       	return 1;
       }

}

void move_forward(cell &cur_pos,int dir){
    int n=dir;
    switch(n){
case 0:
    if(cur_pos.y!=dim-1) cur_pos.y++ ;
   // cout<<"hel"<<endl;
    break;
case 1:
   // cout<<"die"<<endl;
    if(cur_pos.x!=dim-1) cur_pos.x++;
    break;
case 2:
   // cout<<"bye"<<endl;
    if(cur_pos.y>0) cur_pos.y--;
    break;
case 3:
   // cout<<"dog"<<endl;
     if(cur_pos.x>0) cur_pos.x--;
    break;
    }

}
void move_back(cell &cur_pos){
 move_forward(cur_pos,(ori+2)%4);
}

void move_to_target(cell &cur_pos, cell target){
	int dir;
    if(target.y-cur_pos.y==1) dir=(4-ori)%4;
    if(target.x-cur_pos.x==1) {
    dir=(1+4-ori)%4;}
    if(target.y-cur_pos.y==-1) {

            dir=(2+4-ori)%4;}
    if(target.x-cur_pos.x==-1) dir=(3+4-ori)%4;

    switch(dir){
    case 0:
    	move_forward(cur_pos,ori);
    	break;
    case 1:
    	turn_right();
        move_forward(cur_pos,ori);
    	break;
    case 2:
    	move_back(cur_pos);
    	break;
    case 3:
    	turn_left();
        move_forward(cur_pos,ori);
    	break;
    }
}
void flood_fill(cell maze[][dim],cell cur_pos,queue <cell> &q){
	q.push(cur_pos);
	while(!q.empty()){
		vector<cell> ava= get_avaiable_cells(maze,maze[q.front().y][q.front().x]);
		cell m=min(ava);
		if(q.front().v>0){
            if(q.front().v<=m.v ){

        maze[q.front().y][q.front().x].v=(m.v)+1;
     // cout<<endl<<"("<<q.front().y<<","<<q.front().x<<") :-> "<<maze[q.front().y][q.front().x].v<<endl;
        insert(ava,q);
      // test_print(ava);
    }
		}

     //   cout<<endl<<"     maze, after updating ("<<q.front().y<<","<<q.front().x<<")       "<<endl;
	 //print(maze);
	 //cout<<endl;
	   q.pop();
	}
}
void return_floodfill(cell return_maze[][dim],cell st_pos,queue <cell> &q){
    return_maze[st_pos.y][st_pos.x].v=0;
     return_maze[st_pos.y][st_pos.x].reset=1;
q.push(return_maze[st_pos.y][st_pos.x]);
	while(!q.empty()){
		vector<cell> ava= get_avaiable_cells(return_maze,return_maze[q.front().y][q.front().x]);

		for(cell c:ava){
            if(!return_maze[c.y][c.x].reset)
            { cout<<endl<<"     maze, after updating ("<<c.y<<","<<c.x<<")   ->    ";
                return_maze[c.y][c.x].v=return_maze[q.front().y][q.front().x].v+1;
            return_maze[c.y][c.x].reset=1;
            cout<<  return_maze[c.y][c.x].v<<endl;
		}
		}
insert_unedited(ava,q);
	   q.pop();
	}
}


