/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** test
*/

#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>

#include <future>

class SoundPlayer {
public:
    SoundPlayer() {
        if (!buffer.loadFromFile("./test.ogg")) {
            throw std::runtime_error("Failed to load sound");
        }
        sound.setBuffer(buffer);
    }

    void play() {
        soundFuture = std::async(std::launch::async, [this]() {
            sound.play();
            while (sound.getStatus() == sf::Sound::Playing) {
                // Wait for the sound to finish playing
                sf::sleep(sf::milliseconds(100));
            }
        });
    }

private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
    std::future<void> soundFuture;
};

int main() {
    try {
        SoundPlayer player;
        player.play();
        std::cout << "ouais" << std::endl;
        sf::sleep(sf::seconds(2)); // Wait for a while to let the sound play
        std::cout << "ouais" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
