
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{

  in_menu = true;
  play_selected = true;

  menu_text.setString("Welcome to Whack-a-mole. Please select an option");
  menu_text.setFont(font);
  menu_text.setCharacterSize(20);
  menu_text.setFillColor(sf::Color(255,0,0,128));
  menu_text.setPosition(
    window.getSize().x / 3.5 - menu_text.getGlobalBounds().width / 3.5,
    window.getSize().y / 6 - menu_text.getGlobalBounds().height / 6);

  play_option.setString("  Play  ");
  play_option.setFont(font);
  play_option.setCharacterSize(15);
  play_option.setFillColor(sf::Color(255,255,255,128));
  play_option.setPosition(
    window.getSize().x / 2 - play_option.getGlobalBounds().width / 2,
    window.getSize().y / 4 - play_option.getGlobalBounds().height / 4);

  quit_option.setString("  Quit  ");
  quit_option.setFont(font);
  quit_option.setCharacterSize(15);
  quit_option.setFillColor(sf::Color(255,255,255,128));
  quit_option.setPosition(
    window.getSize().x / 2 - quit_option.getGlobalBounds().width / 2,
    window.getSize().y / 3 - quit_option.getGlobalBounds().height / 3);

  // Load Background Textures
  if(!background_texture.loadFromFile("Data/Images/background.png"))
  {
    std::cout << "background texture did not load \n";
  }
  background.setTexture(background_texture);
  // Load Gorilla Icon
  if (!gorilla_texture.loadFromFile("Data/Images/gorilla.png"))
  {
    std::cout << "gorilla texture did not load \n";
  }
  gorilla.setTexture(gorilla_texture);
  gorilla.setPosition(100,100);
  // Load Text
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Font did not load \n";
  }

  title_text.setString("Whack-a-mole");
  title_text.setFont(font);
  title_text.setCharacterSize(100);
  title_text.setFillColor(sf::Color(255,255,255,128));
  title_text.setPosition(
    window.getSize().x / 2 - title_text.getGlobalBounds().width / 2,
    window.getSize().y / 2 - title_text.getGlobalBounds().height / 2);

  score_text.setString("Score: ");
  score_text.setFont(font);
  score_text.setCharacterSize(25);
  score_text.setFillColor(sf::Color(255,0,0,128));
  score_text.setPosition(
    window.getSize().x / 8 - score_text.getGlobalBounds().width / 2,
    window.getSize().y / 8 - score_text.getGlobalBounds().width / 2);

  return true;
}

void Game::update(float dt)
{

  if (!reverse)
  {
    gorilla.move(1.0f*speed* dt, 0);
    if ((gorilla.getPosition().x > (window.getSize().x - gorilla.getGlobalBounds().width)) ||
        (gorilla.getPosition().x < 0))
    {
      reverse = !reverse;
    }
  }
  else
  {
    gorilla.move(-1.0f * speed * dt, 0);
    if ((gorilla.getPosition().x > (window.getSize().x - gorilla.getGlobalBounds().width)) ||
        (gorilla.getPosition().x < 0))
    {
      reverse = !reverse;
    }
  }
}

void Game::render()
{
  if(in_menu)
  {
    window.draw(menu_text);
    window.draw(play_option);
    window.draw(quit_option);
  }
  else
  {
    window.draw(background);
    window.draw(gorilla);
    window.draw(title_text);
    window.draw(score_text);
  }

}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);

  // check if in bounds of gorilla Sprite
  if (collisionCheck(click, gorilla))
  {
    score_text.setString("Score: " + std::to_string(score));
    spawn();
  }
}

void Game::keyPressed(sf::Event event)
{
    if (
      (event.key.code == sf::Keyboard::Up) ||
      (event.key.code == sf::Keyboard::Down)
      )
    {
      play_selected =! play_selected;
      if (play_selected)
      {
        play_option.setString ("> Play  ");
        quit_option.setString ("  Quit  ");
      }
      else
      {
        play_option.setString ("  Play  ");
        quit_option.setString ("> Quit  ");
      }
    }
    else if (event.key.code == sf::Keyboard::Enter)
    {
      if (play_selected)
      {
        in_menu = false;
      }
      else
      {
        window.close();
      }
    }
}

bool Game::collisionCheck(sf::Vector2i click, sf::Sprite sprite)
{
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    sf::Vector2f click = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    sf::FloatRect bounds = sprite.getGlobalBounds();

    if (bounds.contains(click))
    {
      score += 1;
      std::cout << "\nScore: " << score;
      return true;
    }
    else
    {
      return false;
    }
  }
  return false;
}

void Game::spawn()
{
  gorilla.setPosition(rand()%100,rand()%500);
}
