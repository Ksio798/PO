#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <vector>
#include <chrono>
#include <conio.h>

char territory[20][20];
int PlayerX = 1, PlayerY = 1, PlayerDmg = 1, kills = 0, targetKills = 10, TargetTime = 60, bIndex = 0, enIndex = 0;
float PlayerSpeed = 0.1f, prevMove = 0.0f;
std::pair<int, int> PlayerRotation;
std::string preset = "";
float mapCD = 0.09f;
float currentMCD = 0;
class Bullet;
class Enemy;
class Spawner;
std::vector<Bullet> Bullets;
std::vector<Enemy> Enemies;
std::vector<Spawner> Spawners;

class MovingObject {
public:
	float speed;
	int x = 1, y = 1;
	bool destroyed = true;
	float prevtimeMove = 0;
	std::pair<int, int> vector2;
};

class Enemy : public MovingObject {
public:
	int HP = 1;

	std::pair<int, int> getWay() {
		int a = (std::rand() % 3) - 1;
		int b = (std::rand() % 3) - 1;
		return std::make_pair(a, b);
	}

	void move(float t) {
		if (destroyed)
			return;
		if (t - prevtimeMove >= speed) {
			prevtimeMove = t;
			vector2 = getWay();
			if (territory[x + vector2.first][y + vector2.second] == '-') {
				territory[x][y] = '-';
				x += vector2.first;
				y += vector2.second;
				territory[x][y] = 'E';
			}
		}
	}

	void die() {
		territory[x][y] = '-';
		destroyed = true;
		kills++;
	}

	void takeDmg(int dmg) {
		HP -= dmg;
		if (HP <= 0)
			die();
	}
};

class Bullet : public MovingObject{
public:
	int dmg = 1;
	
	void destroy() {
		territory[x][y] = '-';
		destroyed = true;
	}

	void move(float t) {
		if (destroyed)
			return;
		if (t - prevtimeMove >= speed) {
			prevtimeMove = t;
			if (territory[x + vector2.first][y + vector2.second] == '-') {
				territory[x][y] = '-';
				x += vector2.first;
				y += vector2.second;
				territory[x][y] = '*';
				return;
			}
			else if (territory[x + vector2.first][y + vector2.second] == 'E') {
				for (int i = 0; i < Enemies.size(); i++)
				{
					if (Enemies[i].x == x + vector2.first && Enemies[i].y == y + vector2.second) {
						Enemies[i].takeDmg(dmg);
						break;
					}
				}
				
			}
			destroy();
		}
	}
};


class Spawner {
public:
	int x = 1, y = 1;
	int maxEnemy = 5;
	int currentEnCount = 0;
	int cd = 5;
	int prevtime = 0;

	void addEnemy() {
		if (territory[x][y + 1] == '-') {
			Enemies.at(enIndex).x = x; 	Enemies.at(enIndex).y = y + 1;
		}
		else if (territory[x + 1][y] == '-') {
			Enemies.at(enIndex).x = x + 1; 	Enemies.at(enIndex).y = y;
		}
		else if (territory[x - 1][y] == '-') {
			Enemies.at(enIndex).x = x - 1; 	Enemies.at(enIndex).y = y;
		}
		else {
			Enemies.at(enIndex).x = x; 	Enemies.at(enIndex).y = y - 1;
		}
		territory[Enemies.at(enIndex).x][Enemies.at(enIndex).y] = 'E';
		Enemies.at(enIndex).destroyed = false;

		enIndex++;
		if (enIndex >= 20)
			enIndex = 0;
	}

	void Spawn(int t) {
		if (currentEnCount < maxEnemy && t - prevtime >= cd) {
			currentEnCount++;
			prevtime = t;
			addEnemy();
		}
	}
};

class Timer {
	std::chrono::system_clock::time_point tp1 = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point tp2 = std::chrono::system_clock::now();
public:
	float time = 0;

	void update() {
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> duration = tp2 - tp1;
		time = duration.count();
	}
};

void addSpawner(int x, int y) {
	Spawner s;
	s.x = x;
	s.y = y;
	Spawners.push_back(s);
}

void setP() {
	preset += "####################";
	preset += "#@-----------------#";
	preset += "#------------------#";
	preset += "#-------------#----#";
	preset += "#------------------#";
	preset += "#----$-------------#";
	preset += "#------------##----#";
	preset += "#------------------#";
	preset += "#------------------#";
	preset += "#--------##--------#";
	preset += "#------------------#";
	preset += "#------------------#";
	preset += "#----#-------------#";
	preset += "#------------$-----#";
	preset += "#------------------#";
	preset += "#####----###########";
	preset += "#------------------#";
	preset += "#--------------$---#";
	preset += "#------------------#";
	preset += "####################";
}

void setMap() {
	setP();

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			territory[i][j] = preset[i * 20 + j];
			if (territory[i][j] == '$')
				addSpawner(i, j);
		}
	}
}

void printMap(int t) {
	system("cls");
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			std::cout << territory[i][j];
		}
		std::cout << "\n";
	}
	std::cout << "Kills: " << kills << " Time: " << t << '\n';
	std::cout << "@ - you; E - enemy; * - bullet; $ - spawner; # - border";
}


void moving(int x, int y, float t) {
	if (t - prevMove < PlayerSpeed)
		return;

	prevMove = t;
	if (territory[PlayerX + x][PlayerY + y] == '-') {
		territory[PlayerX][PlayerY] = '-';
		PlayerX += x;
		PlayerY += y;
		territory[PlayerX][PlayerY] = '@';
	}

	PlayerRotation = std::make_pair(x, y);
}

void attack() {
	if (!(territory[PlayerX + PlayerRotation.first][PlayerY + PlayerRotation.second] == '-' 
		|| territory[PlayerX + PlayerRotation.first][PlayerY + PlayerRotation.second] == 'E'))
		return;
	Bullets.at(bIndex).dmg = PlayerDmg;
	Bullets.at(bIndex).vector2 = PlayerRotation;
	Bullets.at(bIndex).x = PlayerX + PlayerRotation.first;
	Bullets.at(bIndex).y = PlayerY + PlayerRotation.second;
	Bullets.at(bIndex).destroyed = false;
	bIndex++;
	if (bIndex >= 20)
		bIndex = 0;
}

void SetBullets() {
	for (int i = 0; i < 20; i++)
	{
		Bullet b;
		b.speed = 0.1f;
		b.destroyed = true;
		Bullets.push_back(b);
	}
}

void SetEnemies() {
	for (int i = 0; i < 20; i++)
	{
		Enemy e;
		e.speed = 1.1f;
		e.destroyed = true;
		Enemies.push_back(e);
	}
}

int main()
{
	std::cout << "Make " << targetKills << " kills in " << TargetTime << " seconds\n";
	std::cout << "Press eny key to start";
	_getch();

	SetBullets();
	SetEnemies();
	std::srand(time(0));
	Timer timer;

	setMap();
	while (true)
	{
		timer.update();

		for (int i = 0; i < Spawners.size(); i++)
			Spawners[i].Spawn(timer.time);


		for (int i = 0; i < Enemies.size(); i++)
			Enemies[i].move(timer.time);

		for (int i = 0; i < Bullets.size(); i++)
			Bullets[i].move(timer.time);

		if (timer.time - currentMCD >= mapCD) {
			printMap(timer.time);
			currentMCD = timer.time;
		}

		if (_kbhit()) {
			char move1 = _getch();
			std::cout << move1;
			switch (move1) {
			case 'w': moving(-1, 0, timer.time); break;
			case 'a':moving(0, -1, timer.time); break;
			case 's': moving(1, 0, timer.time); break;
			case 'd': moving(0, 1, timer.time); break;
			case 'e': attack(); break;
			}

		}

		if (kills >= targetKills || timer.time >= TargetTime)
			break;
	}

	system("cls");
	if (kills >= targetKills)
		std::cout << "You Win!";
	else
		std::cout << "You lose, Kills: " << kills;
}