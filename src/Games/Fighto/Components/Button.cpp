/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Button
*/

#include "Button.hpp"
#include <iostream>

using components::Button;

Button::Button(dVector pos, dVector size) : _pos(pos), _size(size)
{
    auto textInfo = TextInformations{};
    auto backgroundInfo = BackgroundInformations();
    auto state = ButtonStateInformations(textInfo, backgroundInfo, [](){});
    for (uint8_t i = 0; i < static_cast<uint8_t>(State::END); i++) {
        _states[static_cast<State>(i)] = state;
    }
}

Button::Button(TextInformations text, BackgroundInformations background, dVector pos, dVector size) : _pos(pos), _size(size)
{
    auto state = ButtonStateInformations(text, background, [](){});
    for (uint8_t i = 0; i < static_cast<uint8_t>(State::END); i++) {
        _states[static_cast<State>(i)] = state;
    }
}

Button::Button(std::map<State, ButtonStateInformations> states, dVector pos, dVector size) : _pos(pos), _size(size)
{
    _states = states;
}

Button::~Button()
{
}

void Button::draw(arc::ILibrary& lib)
{
    _states[_state].draw(lib, _pos, _size);
}

void Button::setState(State state)
{
    _state = state;
    _states[_state].callback()();
}

void Button::setPos(dVector pos)
{
    _pos = pos;
}

void Button::setSize(dVector size)
{
    _size = size;
}

void Button::setAlign(Align align)
{
    for (auto &state : _states) {
        state.second.setAlign(align);
    }
}

void Button::setCallback(std::function<void()> callback)
{
    for (auto &state : _states) {
        state.second.setCallback(callback);
    }
}

void Button::setText(TextInformations text)
{
    for (auto &state : _states) {
        state.second.setTextInformations(text);
    }
}

void Button::setText(std::string text)
{
    for (auto &state : _states) {
        state.second.setText(text);
    }
}

void Button::setTextColor(arc::Color color)
{
    for (auto &state : _states) {
        state.second.setTextColor(color);
    }
}

void Button::setFont(std::shared_ptr<arc::IFont> font)
{
    for (auto &state : _states) {
        state.second.setFont(font);
    }
}

void Button::setFontSize(uint32_t fontSize)
{
    for (auto &state : _states) {
        state.second.setFontSize(fontSize);
    }
}

void Button::setBackground(BackgroundInformations background)
{
    for (auto &state : _states) {
        state.second.setBackgroundInformations(background);
    }
}

void Button::setBackgroundColor(arc::Color color)
{
    for (auto &state : _states) {
        state.second.setBackgroundColor(color);
    }
}

void Button::setBackgroundTexture(std::shared_ptr<arc::ITexture> texture)
{
    for (auto &state : _states) {
        state.second.setBackgroundTexture(texture);
    }
}

void Button::setBorderInformations(BorderInformations border)
{
    for (auto &state : _states) {
        state.second.setBorderInformations(border);
    }
}

void Button::setBorderColor(arc::Color color)
{
    for (auto &state : _states) {
        state.second.setBorderColor(color);
    }
}

void Button::setBorderSize(uint32_t borderSize)
{
    for (auto &state : _states) {
        state.second.setBorderSize(borderSize);
    }
}

const Button::ButtonStateInformations& Button::state(State state)
{
    return _states[state];
}

const dVector& Button::pos() const
{
    return _pos;
}

const dVector& Button::size() const
{
    return _size;
}

const arc::Rect<int> Button::bounds() const
{
    return arc::Rect<int>(_pos.x, _pos.y, _size.x, _size.y);
}

const Button::State& Button::state() const
{
    return _state;
}

Button::ButtonStateInformations::ButtonStateInformations(TextInformations text, BackgroundInformations background, std::function<void()> callback) : _text(text), _background(background), _callback(callback)
{
}

Button::ButtonStateInformations::~ButtonStateInformations()
{
}

void Button::ButtonStateInformations::setAlign(Align align)
{
    _text.align = align;
}

void Button::ButtonStateInformations::setTextInformations(TextInformations text)
{
    _text = text;
}

void Button::ButtonStateInformations::setText(std::string text)
{
    _text.text = text;
}

void Button::ButtonStateInformations::setTextColor(arc::Color color)
{
    _text.color = color;
}

void Button::ButtonStateInformations::setFont(std::shared_ptr<arc::IFont> font)
{
    _text.font = font;
}

void Button::ButtonStateInformations::setFontSize(uint32_t fontSize)
{
    _text.fontSize = fontSize;
}

void Button::ButtonStateInformations::setBackgroundInformations(BackgroundInformations background)
{
    _background = background;
}

void Button::ButtonStateInformations::setBackgroundColor(arc::Color color)
{
    _background.background = color;
}

void Button::ButtonStateInformations::setBackgroundTexture(std::shared_ptr<arc::ITexture> texture)
{
    _background.background = texture;
}

void Button::ButtonStateInformations::setBorderInformations(BorderInformations border)
{
    _background.border = border;
}

void Button::ButtonStateInformations::setBorderColor(arc::Color color)
{
    if (_background.border.has_value())
        _background.border.value().borderColor = color;
    else
        _background.border = BorderInformations(color, 1);
}

void Button::ButtonStateInformations::setBorderSize(uint32_t borderSize)
{
    if (_background.border.has_value())
        _background.border.value().borderSize = borderSize;
    else
        _background.border = BorderInformations(arc::Color{0, 0, 0, 255}, borderSize);
}

void Button::ButtonStateInformations::setCallback(std::function<void()> callback)
{
    _callback = callback;
}

const Button::TextInformations& Button::ButtonStateInformations::textInformations() const
{
    return _text;
}

const Button::BackgroundInformations& Button::ButtonStateInformations::backgroundInformations() const
{
    return _background;
}

const std::function<void()>& Button::ButtonStateInformations::callback() const
{
    return _callback;
}

void Button::ButtonStateInformations::draw([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] dVector pos, [[maybe_unused]] dVector size)
{
    std::cout << "ButtonStateInformations::draw not implemented." << std::endl;
    // if (_background.background.index() == 0) {
    //     auto color = std::get<arc::Color>(_background.background);
    //     lib.drawRect(pos.x, pos.y, size.x, size.y, color);
    // } else {
    //     auto texture = std::get<std::shared_ptr<arc::ITexture>>(_background.background);
    //     lib.drawTexture(texture, pos.x, pos.y, size.x, size.y);
    // }
    // if (_background.border.has_value()) {
    //     auto border = _background.border.value();
    //     lib.drawRect(pos.x, pos.y, size.x, size.y, border.borderColor, border.borderSize);
    // }
    // auto text = _text;
    // text.pos = pos;
    // text.size = size;
    // lib.drawText(text);
}

