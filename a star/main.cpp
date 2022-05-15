// #include <bits/stdc++.h>
#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

map<vector<vector<int>> , bool> visited; //declaring a map named "visited" that takes vector(which stores vectors that takes integer values) as its key, and a boolean as its value
map<vector<vector<int>> , vector<vector<int>>> parent;	//child parent
vector<vector<int> > goal = {{0,1,2}, {3,4,5}, {6,7,8}}; 

bool visit(vector<vector<int> > a)  //boolean to see if node is visited
{
	if(visited[a]==true)
		return true;
	
	return false;
}


//Manhattan or A*(A-star) search to find the distance
//below function is used to find the dis of the nodes of the curr matrix with the goal matrix
int manhattan (vector<vector<int> > a , int moves)
{
	int dist = moves;
	for (int i=0; i<3; i++) //for loop to go through each row and column (like matrices). [00,01,02,10,11,12,20,21,22] We'll be using this i,j loop more.
	{
		for (int j=0; j<3; j++)
		{
			if(a[i][j] != 0)
			{
				for (int k=0; k<3; k++)
				{
					for (int l=0; l<3; l++)
					{
						if(a[i][j]==goal[k][l])
							dist+=abs(i-k)+abs(j-l); //absolute value since it may be negative
					}
				}
			}
		}
	}
	return dist;	
}
//below code is used to check the boundary cases.
bool safe(int i,int j)
{
	if(i>=0 && i<=2 && j>=0 && j<=2)
		return true;
	
	return false;
}


int dx[]={-1,1,0,0}; //array named "dx", with 4 length
int dy[]={0,0,1,-1};

//the below function will basically return all the possible states which can be generated by the given matrix.
vector<vector<vector<int> > > neighbours(vector<vector<int> > a) 
{
	pair<int,int> pos; //vector of pairs named "pos" (pairs an integer to another integer)
	for (int i=0; i<3; i++)
	{
		for (int j=0; j<3; j++){
			if(a[i][j] == 0) 
			{
				pos.first=i;
				pos.second=j;
				break;
			 } 												
		}		
		
	}
	
	vector<vector<vector<int> > > ans; //"answer" vector to add the correct values by pushing back
	for (int k=0; k<4; k++) // 4, not 3, since our dx and dy arrays have 4 length
	{
		int cx = pos.first; //to keep track of the "i" values
		int cy = pos.second; //to keep track of the "j" values
		vector<vector<int> > n = a;
		if(safe(cx+dx[k], cy+dy[k]))
		{
			swap(n[cx+dx[k]][cy+dy[k]], n[cx][cy]); //swap tiles(or we can say swap arrays)
			ans.push_back(n);			
		}
	}
		
	return ans; //result vector
		
}

typedef pair<vector<vector<int> > , int> state; // new type defined named "state" that's a vector of pairs (which is a vector to integer pair)
	
//below struct is used for comparing ordering our priority queue.
struct cmp 
{
	bool operator() (state &a, state &b) // overloading the unary operator "()"
	{
		int am = manhattan(a.first,a.second);
		int bm = manhattan(b.first,b.second);
		return am<bm;		
	}	
};

//the below function is used to print the matrix
void print_path(vector<vector<int> > s)
{
	if(parent.count(s)) //to see if our vector s is present in our map named "parent" which takes vectors in it for both key and value, and if it is present
	print_path(parent[s]); //then print the path
	
    for(int i=0;i<3;i++)
    {
 	  for(int j=0;j<3;j++)
	  {
		 printf("%d ",s[i][j]);
	  }
	 cout<<endl;
    }
   cout<<endl;
   
 return;
}




void solve(vector<vector<int> > a, int moves)
{
	priority_queue<state, vector<state>, cmp> Q; //Priority queue named "Q". 
	Q.push(state(a,moves));
	while(!Q.empty())
	{
		vector<vector<int> > s = Q.top().first;
		Q.pop();
		visited[s]=true;
		if(s==goal) //print(s)
		{
			print_path(s);
			break;
		}
		vector<vector<vector<int> > > ns = neighbours(s); //in ns variable we are storing all the neighbouring states of the current matrix.

		vector<vector<vector<int> > >::iterator it;
		for(it=ns.begin();it!=ns.end();it++) //now we are iterating our ns array.
		{
			vector<vector<int> > temp = *it;
			if(!visit(temp)) //if the neigh is not visited then we will push it into the priority queue.
			{
				parent.insert(pair<vector<vector<int> > , vector<vector<int> > >(temp,s)); //storing the child ,parent.
				Q.push(state(temp,moves+1));
			}
		}
	}
	return;
}

int main()
{

	cout<<"Please enter your 8 Puzzle! (Format is shown below) \n";
	cout<<"\nFor example => 0 1 2 3 4 5 6 7 8\n";
	vector<vector<int> > a(3,vector<int> (3));	
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cin>>a[i][j];	
		}
	}
    //initializing our goal matrix
	
	cout << "Matrix Given by the User: " << endl;
	for (int i = 0; i < 3;i++)
	{
		for (int j = 0; j < 3;j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Goal Matrix is: " << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3;j++)
		{
			cout << goal[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "\n Puzzle is solving...\n";

	solve(a,0);
}