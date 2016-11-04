#ifndef __DRAWER_HPP__
#define __DRAWER_HPP__

#include "Input.hpp"
#include <SFML/Graphics.hpp>

#define FRAMESIZEX 200
#define FRAMESIZEY FRAMESIZEX * 1.618
#define BRUSHSIZE FRAMESIZEX / (20 * 2)

class Drawer : public sf::Drawable, public sf::Transformable {
public:
  Drawer(sf::Color color) : _color(color) {
    _frame.setSize({FRAMESIZEX, FRAMESIZEY});
    _frame.setFillColor(sf::Color::Transparent);
    _frame.setOutlineColor(_color);
    _frame.setOutlineThickness(10);

    _brush.setRadius(BRUSHSIZE);
    _brush.setFillColor(_color);

    // Quad stuff
    _vertices = sf::VertexArray(sf::Quads, 4);

    _vertices[0].position = {0,0};
    _vertices[1].position = {FRAMESIZEX,0};
    _vertices[2].position = {FRAMESIZEX,FRAMESIZEY};
    _vertices[3].position = {0,FRAMESIZEY};

    _vertices[0].texCoords = {0,0};
    _vertices[1].texCoords = {FRAMESIZEX,0};
    _vertices[2].texCoords = {FRAMESIZEX,FRAMESIZEY};
    _vertices[3].texCoords = {0,FRAMESIZEY};

    // Texture shiet
    _renderTexture.create(FRAMESIZEX, FRAMESIZEY);


  }

  void update(float) {
    if (Input::isClicked) {
      sf::Vector2i localPosition = Input::pos - sf::Vector2i(getPosition());
      if (sf::IntRect(0,0,FRAMESIZEX, FRAMESIZEY).contains(localPosition)) {
        _brush.setPosition(localPosition.x, localPosition.y);

        sf::Sprite last(_texture);
        _renderTexture.clear(sf::Color::White);


        _renderTexture.draw(last);
        _renderTexture.draw(_brush);

        _renderTexture.display();
        _texture = _renderTexture.getTexture();
      }
    }
  }



private:
  sf::Color _color;

  sf::RectangleShape _frame;
  sf::CircleShape _brush;

  sf::VertexArray _vertices;
  sf::RenderTexture _renderTexture;
  sf::Texture _texture;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform.translate(getPosition());

    target.draw(_frame, states);

    states.texture = &_texture;
    target.draw(_vertices, states);
  }

};

#endif
