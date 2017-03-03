#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <list>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

struct Vertex {
	vector<int> neighbors;
	bool isInfected = false;
	bool visited;
};

vector<Vertex> cities;
queue<int> infected;
int noOfCities, noOfRoads, initInfected, days;
int counter = 0;

void importData(char* infileName) {
	fstream file(infileName);
	file >> noOfCities;
	cities.resize(noOfCities + 1);
	file >> noOfRoads;
	file >> initInfected;
	file >> days;
	for (int i = 1; i <= noOfRoads; i++) {
		int cityI, cityJ;
		file >> cityI;
		file >> cityJ;
		cities[cityI].neighbors.push_back(cityJ);
		cities[cityJ].neighbors.push_back(cityI);
	}
	for (int i = 1; i <= initInfected; i++) {
		int temp;
		file >> temp;
		cities[temp].isInfected = true;
		infected.push(temp);
	}

}

void uniterState(int days) {
	for (int k = 1; k <= days; k++) {
		int x = infected.size();
		for (int i = 0; i < x; i++) {
			int node = infected.front();
			for (int j = 0; j < cities[node].neighbors.size(); j++) {
				if (cities[cities[node].neighbors[j]].isInfected == false) {
					cities[cities[node].neighbors[j]].isInfected = true;
					infected.push(cities[node].neighbors[j]);
				}
			}
			infected.pop();
		}
	}
}
void separate(Vertex v) {
	queue<Vertex*> temp;
	if (v.isInfected == false) {
		v.visited = true;
		temp.push(&v);
		while (!temp.empty()) {
			Vertex* x = temp.front();
			temp.pop();
			for (int i = 0; i < x->neighbors.size(); i++) {
				if (cities[x->neighbors[i]].visited == false
						&& cities[x->neighbors[i]].isInfected == false) {
					cities[x->neighbors[i]].visited = true;
					temp.push(&cities[x->neighbors[i]]);
				}
			}
		}
		counter++;
	}
}

int main(int argc,char* argv[]) {
    if(argc!=3){
    	cout<<"Usage: ./project4 input output"<<endl;
    	return 0;
  	}
	importData(argv[1]);
	uniterState(days);
	for(int i=1; i<cities.size(); i++){
		if(cities[i].isInfected==true)
			continue;
		else if(cities[i].isInfected==false && cities[i].visited==false){
	 		separate(cities[i]);
	 	}
	}
	ofstream myfile(argv[2]);
	myfile<<counter<<endl;
}
