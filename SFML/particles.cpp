///
/// A little SFML experiment: Generate particles and move them in a sort of 3D way.
///
#include <SFML/Graphics.hpp>
#define PI 3.141592
#include<ctime>


float v2f_len(const sf::Vector2f& a) {return sqrt(a.x*a.x + a.y*a.y);}


void v2f_setLen(sf::Vector2f &b, float a) {
	b.x = a;
	//b.y = a;
}

void setCubeSize(sf::RectangleShape* a, sf::Vector2f b, int size) {
	for (int i = 0; i < size; ++i)
		a[i].setSize(b);
}

void setCubeColor(sf::RectangleShape* a, int size) {
	for (int i = 0; i < size; ++i) {
		int color = rand() % 8 + 1;
		//int color = 1;
		switch (color) {
		case 1: a[i].setFillColor(sf::Color::Green	);	break;
		case 2: a[i].setFillColor(sf::Color::Yellow	);	break;
		case 3: a[i].setFillColor(sf::Color::Black	);	break;
		case 4: a[i].setFillColor(sf::Color::Blue	);	break;
		case 5: a[i].setFillColor(sf::Color::White	);	break;
		case 6: a[i].setFillColor(sf::Color::Magenta);	break;
		case 7: a[i].setFillColor(sf::Color::Red	);	break;
		case 8: a[i].setFillColor(sf::Color::Cyan	);	break;
		default: a[i].setFillColor(sf::Color::Cyan	);	break;
		}
	}
}


void setCubePos(sf::RectangleShape* a, int size) {
	for (int i = 0; i < size; ++i) {
		int offsetx = rand() % 200;
		int offsety = rand() % 200;

		int signx = pow(-1, offsetx);
		int signy = pow(-1, offsety);

		a[i].setPosition(640 + offsetx*signx, 360 + offsety*signy);
	}
}

#define CUBE_ARR_SIZE 30

int main()
{
	sf::Vector2f size;
	size.x = 20;
	size.y = 20;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	
	// Rectangles
	sf::RectangleShape cubearr[CUBE_ARR_SIZE];
	int cube_arr_size = 20;
	setCubeColor(cubearr, CUBE_ARR_SIZE);

	setCubePos(cubearr, CUBE_ARR_SIZE);
	setCubeSize(cubearr, size, CUBE_ARR_SIZE);

	for (int i = 0; i < CUBE_ARR_SIZE; ++i)
		cubearr[i].setOrigin(10, 10);
	// Movement vectors.

	sf::Vector2f movement[CUBE_ARR_SIZE]; ///here
	for (int i = 0; i < CUBE_ARR_SIZE; ++i)
		v2f_setLen(movement[i], rand()%10+5);// SPEEEEDO
	// Angle.
	srand(time(NULL));
	int rng = rand() % 20 + 15;
	float angle[CUBE_ARR_SIZE]; /// here.

	// Movement in a square.
	int squareSize[CUBE_ARR_SIZE];
	for (int i = 0; i < CUBE_ARR_SIZE; ++i)
		squareSize[i] = rand() % 80+20;
	int counter = 0;

	for (int i = 0; i < CUBE_ARR_SIZE; ++i)
		angle[i] = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		for (int i = 0; i < CUBE_ARR_SIZE; ++i){
			float tempx = movement[i].x;
			float tempy = movement[i].y;
			movement[i].x = tempx * cos(angle[i]) - tempy * sin(angle[i]);
			movement[i].y = tempx * sin(angle[i]) + tempy * cos(angle[i]);
			angle[i] = PI/45 ;
			cubearr[i].rotate(angle[i]);
			//g = rand() % 20 + 3;
			cubearr[i].move(movement[i]);
			
			// get back to centre 
		
			if (cubearr[i].getPosition().x < 0 || cubearr[i].getPosition().x>1280)
				cubearr[i].setPosition(640, 360);
			if (cubearr[i].getPosition().y < 0 || cubearr[i].getPosition().y>720)
				cubearr[i].setPosition(640, 360);

		}

		++counter;
		window.clear();

		for(int i=0;i<CUBE_ARR_SIZE;++i)
			window.draw(cubearr[i]);

		window.display();
	}

	return 0;
}