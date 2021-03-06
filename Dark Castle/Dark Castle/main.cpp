#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"

using namespace sf;
class Player { // ����� ������
public:
	float x, y, w, h, dx, dy, speed = 0; 
	int dir = 0; 
	String File; 
	Image image;
	Texture texture;
	Sprite sprite;
	
	Player(String F, float X, float Y, float W, float H) { //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(84, 109, 142));//������� �������� ����
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	void update(float time) //������� "���������" ������� ������. 
	{
		switch (dir)//��������� ��������� � ����������� �� �����������.
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}

		x += dx*time;
		y += dy*time;

		speed = 0;//�������� ��������, ����� �������� �����������.
		sprite.setPosition(x, y);
		interactionWithMap();
	}
	void interactionWithMap()//�-��� �������������� � ������
	{

		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j<(x + w) / 32; j++)
			{
				if (TileMap[i][j] == '0')
				{
					if (dy>0)
					{
						y = i * 32 - h;//�� �������� ���������� ����� ���������. 
					}
					if (dy<0)
					{
						y = i * 32 + 32;//���������� � ������� �����. dy<0, ������ �� ���� �����
					}
					if (dx>0)
					{
						x = j * 32 - w;//���� ���� ������, �� ���������� � ����� ����� ����� ������ ���������
					}
					if (dx < 0)
					{
						x = j * 32 + 32;//���������� ���� �����
					}
				}

				if (TileMap[i][j] == 's') { //���� ������ ����� 's' (������)
					x = 300; y = 300;
					TileMap[i][j] = ' ';//������� ������, ���� ����� �����. ����� � �� �������, ������.
				}
			}
	}
};
int main()
{
	RenderWindow window(sf::VideoMode(800, 600), "Dark Castle");
	Player p("hero.png", 24, 32, 24, 32);
	
	//�����
	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Clock clock;
	float CurrentFrame = 0;//������ ������� ����
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 600;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//����������
		if (Keyboard::isKeyPressed(Keyboard::W)) { 
			p.dir = 3; p.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(24 * int(CurrentFrame), 0, 24, 32));
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			p.dir = 2; p.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(24 * int(CurrentFrame), 64, 24, 32));
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) { 
			p.dir = 1 ; p.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(24 * int(CurrentFrame), 96, 24, 32));
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			p.dir = 0; p.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(24 * int(CurrentFrame), 32, 24, 32)); 
		}
		p.update(time);

		window.clear();
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); 
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));


				s_map.setPosition(j * 32, i * 32);//�� ���� ����������� ����������.

				window.draw(s_map);//������ ���������� �� �����
			}
		window.draw(p.sprite);
		window.display();
	}

	return 0;
}