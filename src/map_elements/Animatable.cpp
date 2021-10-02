#include "boulder-dash2/map_elements/Animatable.hpp"

bd2::Animatable::Animatable(Type _type, MapCoordinates _position)
    : MapElement(_type, _position), is_animating_(false) {}

void bd2::Animatable::simulateAnimation(sf::Time elapsed_time) {

    if (is_animating_) {

        animation_time_ += elapsed_time;

        if (animation_time_ >= animation_duration_) {

            is_animating_ = false;
            return;
        }

        auto texture_size = getTexture()->getSize();
        int frames_num = texture_size.x / texture_size.y;

        int current_frame = static_cast<int>(static_cast<float>(frames_num) *
                                             (animation_time_ / animation_duration_));

        sf::IntRect frame_rectangle(current_frame * texture_size.y, 0, texture_size.y,
                                    texture_size.y);

        setTextureRect(frame_rectangle);

        float scale =
            static_cast<float>(tile_size_) / static_cast<float>(texture_size.y);

        setScale(sf::Vector2f(scale, scale));
    }
}


void bd2::Animatable::startAnimation(
    std::shared_ptr<const sf::Texture> animation_texture, sf::Time duration,
    sf::Time initial_time) {

    is_animating_ = true;
    animation_time_ = initial_time;
    animation_duration_ = duration;
    setTexture(*animation_texture, false);
}

bool bd2::Animatable::isAnimating() const { return is_animating_; }