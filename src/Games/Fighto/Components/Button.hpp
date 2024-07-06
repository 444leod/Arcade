/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Button
*/

#pragma once

#include "ILibrary.hpp"
#include "Vector.hpp"
#include <map>
#include <variant>
#include <functional>

class SceneManager;

namespace components {
    class Button {
        public:
            enum class Align {
                LEFT,
                CENTER,
                RIGHT
            };

            enum class State {
                NORMAL,
                HOVER,
                CLICKED,
                END
            };

            struct TextInformations {
                std::string text = "";
                arc::Color color = arc::Color{0, 0, 0, 255};
                std::shared_ptr<arc::IFont> font = nullptr;
                uint32_t fontSize = 12;
                Align align = Align::CENTER;
            };

            struct BorderInformations {
                arc::Color borderColor = arc::Color{0, 0, 0, 255};
                uint32_t borderSize = 1;
            };

            struct BackgroundInformations {
                std::variant<arc::Color, std::shared_ptr<arc::ITexture>> background;
                std::optional<BorderInformations> border = std::nullopt;
            };

            struct StateInformation {
                TextInformations text;
                BackgroundInformations background;
                std::function<void()> callback;
            };

            class ButtonStateInformations {
                private:
                    TextInformations _text;
                    BackgroundInformations _background;
                    std::function<void()> _callback;

                public:
                    ButtonStateInformations() = default;
                    ButtonStateInformations(TextInformations text, BackgroundInformations background, std::function<void()> callback);
                    ~ButtonStateInformations();

                    void draw(arc::ILibrary &lib, dVector pos, dVector size);

                    void setTextInformations(TextInformations text);
                    void setText(std::string text);
                    void setTextColor(arc::Color color);
                    void setFont(std::shared_ptr<arc::IFont> font);
                    void setFontSize(uint32_t fontSize);
                    void setAlign(Align align);

                    void setBackgroundInformations(BackgroundInformations background);
                    void setBackgroundColor(arc::Color color);
                    void setBackgroundTexture(std::shared_ptr<arc::ITexture> texture);
                    void setBorderInformations(BorderInformations border);
                    void setBorderColor(arc::Color color);
                    void setBorderSize(uint32_t borderSize);

                    void setCallback(std::function<void()> callback);

                    const TextInformations& textInformations() const;
                    const BackgroundInformations& backgroundInformations() const;
                    const std::function<void()>& callback() const;
            };

        private:
            dVector _pos;
            dVector _size;
            std::map<State, ButtonStateInformations> _states;
            State _state = State::NORMAL;

        public:
            Button(dVector pos, dVector size);
            Button(TextInformations text, BackgroundInformations background, dVector pos, dVector size);
            Button(std::map<State, ButtonStateInformations> states, dVector pos, dVector size);
            ~Button();

            void draw(arc::ILibrary &lib);
            void setState(State state);

            void setPos(dVector pos);
            void setSize(dVector size);
            void setAlign(Align align);
            void setText(TextInformations text);
            void setText(std::string text);
            void setTextColor(arc::Color color);
            void setFont(std::shared_ptr<arc::IFont> font);
            void setFontSize(uint32_t fontSize);
            void setBackground(BackgroundInformations background);
            void setBackgroundColor(arc::Color color);
            void setBackgroundTexture(std::shared_ptr<arc::ITexture> texture);
            void setBorderInformations(BorderInformations border);
            void setBorderColor(arc::Color color);
            void setBorderSize(uint32_t borderSize);
            void setCallback(std::function<void()> callback);

            const ButtonStateInformations& state(State state);

            const dVector& pos() const;
            const dVector& size() const;
            const arc::Rect<int> bounds() const;
            const State& state() const;

    };
}
