/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** CSVParser
*/

#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
class CSVParser {
public:
    CSVParser() = default;
    CSVParser(const CSVParser &other) = delete;
    CSVParser &operator=(const CSVParser &other) = delete;
    CSVParser(std::string &filename) : _filename(filename) {}
    CSVParser(const char *filename) : _filename(std::string(filename)) {}
    ~CSVParser() = default;

    class CSVParserException : public std::exception {
    public:
        CSVParserException(const std::string &message)
        {
            std::stringstream ss;
            ss << "CSVParserException: " << message;
            _message = ss.str();
        }
        const char *what() const noexcept override {
            return _message.c_str();
        }
    private:
        std::string _message;
    };

    /**
     * @brief Parse the file and store the data
     */
    void parse()
    {
        if (_filename.empty())
            throw CSVParserException("No filename set");
        std::ifstream file(_filename);
        if (!file.is_open())
            throw CSVParserException("Could not open file");
        std::string line;
        while (std::getline(file, line)) {
            std::vector<T> vec;
            std::stringstream ss(line);
            std::string token;
            while (std::getline(ss, token, ',')) {
                std::stringstream sst(token);
                T value;
                sst >> value;
                if (sst.fail())
                    throw CSVParserException("Invalid CSV file or type");
                vec.push_back(value);
            }
            _data.push_back(vec);
        }
    }

    /**
     * @brief Get the parsed data by lines
     *
     * @return std::vector<std::vector<T>>
    */
    std::vector<std::vector<T>> getData() const
    {
        return _data;
    }

    /**
     * @brief Set the name of the file to parse
     *
     * @param filename
     */
    void setFilename(const std::string &filename)
    {
        _filename = filename;
        _data = {};
    }

private:
    std::string _filename = "";
    std::vector<std::vector<T>> _data;
};
