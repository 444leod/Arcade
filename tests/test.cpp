/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** test
*/

#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>

class SoundPlayer {
public:
    SoundPlayer() {
        if (!buffer.loadFromFile("./test.ogg")) {
            throw std::runtime_error("Failed to load sound");
        }
        sound.setBuffer(buffer);
    }

    void play() {
        std::thread([this]() {
            sound.play();
            while (sound.getStatus() == sf::Sound::Playing) {
                // Wait for the sound to finish playing
                sf::sleep(sf::milliseconds(100));
            }
        }).detach();
    }

private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
};

int main() {
    try {
        SoundPlayer player;
        player.play();
        sf::sleep(sf::seconds(2)); // Wait for a while to let the sound play
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
