#include "../Include/sound.h"
#include <SFML/Audio.hpp>
#include <thread>

void playSound(const std::string& soundPath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(soundPath)) {
        // Lida com o erro ao carregar o arquivo de som
        return;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    // Aguarda um tempo suficiente para o som tocar
    sf::sleep(sf::seconds(2.5)); // Por exemplo, aguarda 5 segundos

    sound.stop();
}

void playSoundInBackground(const std::string& soundPath) {
    std::thread soundThread(playSound, soundPath);
    soundThread.detach();
}
