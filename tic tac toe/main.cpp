#include <SFML/Graphics.hpp>

int main() {
    char state[][3] = {  // Can omit first dimension
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
    };


    sf::RenderWindow window(sf::VideoMode({ 600, 600 }), "SFML works");
	int cursor_x = 2;
	int cursor_y = 1;
    sf::CircleShape circle;
    sf::RectangleShape line;
    sf::RectangleShape cursor;
    bool is_x_turn = true;

    char winner = ' ';

    auto DrawX = [&](float position_x, float position_y)
        {
            line.setSize({ 200.f, 20.f });
            line.setOrigin(line.getGeometricCenter());
            line.setFillColor(sf::Color::White);
            line.setOutlineColor(sf::Color(170, 255, 0));
            line.setPosition({ position_x , position_y });
            line.setRotation(sf::degrees(45.f));
            window.draw(line);
            line.setRotation(sf::degrees(-45.f));
            window.draw(line);
        };
    auto DrawO = [&](float position_x, float position_y)
        {
            circle.setRadius(100.f);
            circle.setOrigin(circle.getGeometricCenter());
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineColor(sf::Color(0, 170, 255));
            circle.setOutlineThickness(-20.f);
            circle.setPosition({ position_x , position_y });
            window.draw(circle);
        };
    auto DrawWinningLine = [&](float position_x, float position_y, float angle, float scale =1.f)
        {
            line.setSize({ 600.f*scale,10.f });
            line.setOrigin(line.getGeometricCenter());
            line.setFillColor(sf::Color::Red);
            line.setPosition({ position_x , position_y });
            line.setRotation(sf::degrees(angle));
            window.draw(line);
        };
    auto DrawCursor = [&](float position_x, float position_y)
        {
            cursor.setSize({ 200.f, 200.f });
            cursor.setOrigin(cursor.getGeometricCenter());
            cursor.setFillColor(sf::Color::Transparent);
			cursor.setOutlineColor(sf::Color::Green);
			cursor.setOutlineThickness(-10.f);
            cursor.setPosition({ position_x , position_y });
            window.draw(cursor);
		};
    while (window.isOpen())
    {
        while (std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
				window.close();

            else if (auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->scancode == sf::Keyboard::Scancode::Escape)
                {
                    for (int i = 0; i < 3; i++)
                    {
                        for (int j = 0; j < 3; j++)
                        {
                            state[i][j] = ' ';
                            cursor_x = 1;
                            cursor_y = 1;
                            is_x_turn = true;
                            winner = ' ';
                        }
                    }
                }
                if (winner == ' ')
                {
                 if      ((key->scancode == sf::Keyboard::Scancode::A) and (cursor_x > 0)) cursor_x--;
                 else if ((key->scancode == sf::Keyboard::Scancode::D) and (cursor_x < 2)) cursor_x++;
                 else if ((key->scancode == sf::Keyboard::Scancode::S) and (cursor_y < 2)) cursor_y++;
                 else if ((key->scancode == sf::Keyboard::Scancode::W) and (cursor_y > 0)) cursor_y--;
            
                 if (key->scancode == sf::Keyboard::Scancode::Space)
                 {
                    if (state[cursor_y][cursor_x] == ' ')
                    {
                        if (is_x_turn)
                            state[cursor_y][cursor_x] = 'x';
                        else
                            state[cursor_y][cursor_x] = 'o';
                        is_x_turn = not is_x_turn;
                    }
                 }
               
				}
                
                
            }
            
        }
        float window_w = window.getView().getSize().x;
        float window_h = window.getView().getSize().y;
        float window_min = (window_w < window_h) ? window_w : window_h;

		window.clear(sf::Color::Black);
        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < 3; i++)
            {

                if (state[j][i] == 'o')
                    DrawO(window_w / 2 + 200.f * (i - 1), window_h / 2 + 200.f * (j - 1));

                else if (state[j][i] == 'x')
                    DrawX(window_w / 2 + 200.f * (i - 1), window_h / 2 + 200.f * (j - 1));

            }
            for (int j = 0; j < 3; j++)
      
             for (int i = 0; i < 3; i++)
             {
                 if ((state[i][0] != ' ') and (state[i][0] == state[i][1]) and (state[i][1] == state[i][2]))
                 {
                     DrawWinningLine(window_w / 2, window_h / 2 + 200.f * (i - 1), 0.f);
                     winner = state[i][0];
                 }
                 if ((state[0][i] != ' ') and (state[0][i] == state[1][i]) and (state[1][i] == state[2][i]))
                 {
                     DrawWinningLine(window_w / 2 + 200.f * (i - 1), window_h / 2, 90.f);
                     winner = state[0][i];
                 }
             }
            if ((state[0][0] != ' ') and (state[0][0] == state[1][1]) and (state[1][1] == state[2][2]))
            {
                DrawWinningLine(window_w / 2, window_h / 2, 45.f, 1.4f);
                winner = state[0][0];
            }
            if ((state[0][2] != ' ') and (state[0][2] == state[1][1]) and (state[1][1] == state[2][0]))
            {
                DrawWinningLine(window_w / 2, window_h / 2, -45.f, 1.4f);
                winner = state[0][2];
            }

            
        }
		DrawCursor(window_w / 2 + 200.f * (cursor_x - 1), window_h / 2 + 200.f * (cursor_y - 1));
        window.display();
    }
}