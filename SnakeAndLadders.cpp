#include<bits/stdc++.h>
using namespace std;

class Player {
private:
	string name;
	int pos;
public:
	Player(string name) {
		this->name=name;
		pos=0;
	}
	void move(int x) {
		if (pos+x>100) return;
		pos+=x;
	}
	void setPos(int pos) {
		this->pos=pos;
	}
	string getName() {
		return this->name;
	}
	int getPos() {
		return this->pos;
	}
};

class SnakeAndLadders {
private:
	int board[101];
	unordered_map<int,int> snakes;
	unordered_map<int,int> ladders;
	vector<Player> players;
	void print(Player &p,int num,int oldPos,int newPos) {
		cout<<p.getName()<<" rolled a "<<num;
		cout<<" and moved from "<<oldPos<<" to "<<newPos;
		cout<<endl;
	}
	void victory(Player &p) {
		cout<<p.getName()<<" wins the game";
	}
	void upLadder(Player &p,int oldPos,int newPos) {
		cout<<p.getName()<<" finds a ladder";
		cout<<" and moved from "<<oldPos<<" to "<<newPos;
		cout<<endl;
	}
	void downSnake(Player &p,int oldPos,int newPos) {
		cout<<p.getName()<<" finds a snake";
		cout<<" and moved from "<<oldPos<<" to "<<newPos;
		cout<<endl;
	}
	bool isLadder(Player &p,int pos) {
		if (ladders.find(pos)==ladders.end()) {
			return false;
		}
		p.setPos(ladders[pos]);
		return true;
	}
	bool isSnake(Player &p,int pos) {
		if (snakes.find(pos)==snakes.end()) {
			return false;
		}
		p.setPos(snakes[pos]);
		return true;
	}
public:
	void addSnake(int start,int end) {
		snakes[start]=end;
	}
	void addLadder(int start,int end) {
		ladders[start]=end;
	}
	void addPlayer(string name) {
		players.push_back(Player(name));
	}
	void start() {
		srand(time(0));
		while (true) {
			for (int i=0;i<players.size();i++) {
				int num=1+rand()%6;
				int oldPos=players[i].getPos();
				players[i].move(num);
				int newPos=players[i].getPos();
				print(players[i],num,oldPos,newPos);
				if (isLadder(players[i],newPos)) {
					upLadder(players[i],newPos,players[i].getPos());
				}
				if (isSnake(players[i],newPos)) {
					downSnake(players[i],newPos,players[i].getPos());
				}
				newPos=players[i].getPos();
				if (newPos==100) {
					victory(players[i]);
					return;
				}
			}
		}
	}
};

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	SnakeAndLadders game;
	int n,x,y;
	string name;
	cin>>n;
	for (int i=0;i<n;i++) {
		cin>>name;
		game.addPlayer(name);
	}
	cin>>n;
	for (int i=0;i<n;i++) {
		cin>>x>>y;
		game.addSnake(x,y);
	}
	cin>>n;
	for (int i=0;i<n;i++) {
		cin>>x>>y;
		game.addLadder(x,y);
	}
	game.start();
	return 0;
}
