
#include<iostream>
#include<fstream>
#include<climits>


using namespace std;

struct edge{
	int s, d, w;  //source, destination, weight
};


struct node {  //nested structure
	edge e;
	node *next;
};

class Heap{
	edge *A;
	int s;
	int l;
	
	void swap(int i, int j){
		
		edge temp = A[i];
		A[i] = A[j];
		A[j] = temp;
		
		return;
	
	}
	
	void adjust(){
		int i = l;
		int ip; 
		while(i > 0){
			ip = (i - 1)/2;
			if(A[i].w < A[ip].w){
				swap(i, ip);
				i = ip;
				
			}
			else
				return;
		
		
		}
		return;
	
	}
	
	void heapify(){
		int i = 0;
		int left,right;
		int min;
		while( i <= l){
			left = 2 * i + 1;
			right = 2 * i + 2;
			if(left > l)
				return;
			if(right > l){
				if(A[i].w > A[left].w){
					swap(i,left);
					i = left;
				
				
				}
				else
					return;
			
			
			}
			else{
				if(A[left].w < A[right].w)
					min = left;
				else
					min = right;
				if(A[i].w > A[min].w){
					swap(i,min);
					i = min;
				}
				else
					return;
			
			
			}
		
		
		}
		return;
	}
	
	public:
	
	Heap(int n){
		s = n * n;
		A = new edge[s * s];
		l = -1;
		
	}
	void insert(edge e){
		if(l == s-1)
			return;
		cout<<e.s<<"\t"<<e.d<<"\t"<<e.w<<"  inserted"<<endl;
		A[++l] = e;
		adjust();
		return;
	
	}
	bool isEmpty(){
		return l == -1;
	
	
	}
	void showHeap(){
		for(int i = 0; i <= l; i++)
			cout<<A[i].s<<"\t"<<A[i].d<<"\t"<<A[i].w<<endl;
	
	}
	edge remove(){
		edge e = A[0];
		//cout<<e.s<<"\t"<<e.d<<"\t"<<e.w<<endl;
		A[0] = A[l];
		l--;
		heapify();
		return e;
	
	}



};

class Graph{
	node **A;
	int v;
	
	void makeHeap(Heap &h){
	
		node *ptr;
		edge e;
		for(int i = 0; i < v; i++){
			ptr = A[i];
			while(ptr){
				e = ptr->e;
				if(e.s < e.d)
					h.insert(e);
			
			       ptr=ptr->next;
			}
		}
	}
	void unon(int set[], edge e){
		int min, max;
		if(set[e.s]< set[e.d]){
			min = set[e.s];
			max = set[e.d];
		}	
		else {
			max = set[e.s];
			min = set[e.d];
		}
			
		for(int i = 0; i < v; i++){
			if(set[i] == max)
				set[i] = min;
		}
	
	}
	public:
	Graph(string filename){
		fstream fin;
		fin.open(filename, ios::in);
		if(!fin) return;
		fin>>v;
		cout<<"no of vertices = "<<v;
		A = new node*[v];
		if(!A) return;
		//ptr shd be NULL
		node *nn;
		int k;
		for(int i = 0; i < v; i++)
			A[i] = NULL;
		for(int i = 0; i < v; i++){
			for(int j = 0; j < v; j++){
				fin>>k;
				if(k){
					nn = new node;
					if(!nn) return;
					nn->e.s = i;
					nn->e.d = j;
					nn->e.w = k;
					nn->next = A[i];
					A[i] = nn;
					
				}
			}
		}
		fin.close();
	
	}
	void Display(){
	node *p;
		for(int i = 0; i < v; i++){
			cout<<"i = "<<i<<endl;;
			p = A[i];
			while(p){
				cout<<p->e.s<<"\t"<< p->e.d<<"\t"<<p->e.w<<"\n";
				p = p->next;
			}
			cout<<endl;
				
		}
		return;
	}
	
void Kruskals(){
	Heap h(v);
	makeHeap(h);
	h.showHeap();
	edge e;
	int set[v];
	for(int i = 0; i < v; i++)
		set[i] = i;
	
	// loop for v -1 edges
	// every loop remove one edge from heap
	//check that edge is not forming a cycle
	//include it
	cout<<"\nmin Spanning Tree\n";
	int i = 0;
	while( i < v -1){
		e = h.remove();
		if(set[e.s] != set[e.d]){
			cout<<e.s<<"\t"<<e.d<<"\t"<<e.w<<endl;
			i++;
			unon(set, e);
		
		}
	
	}
	return;


}

};
int main(){
	Graph G("graph1.txt");
	
	G.Display();
	
	G.Kruskals();
	return 0;
}
