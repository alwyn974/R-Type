/*
** EPITECH PROJECT, 2023
** Random.hpp
** File description:
** Random.hpp
*/

#ifndef R_TYPE_RANDOM_HPP
#define R_TYPE_RANDOM_HPP

#include <random>

class Random {
public:
    /**
     * @brief Construct a new Random object, default constructor
     */
    Random() = default;

    /**
     * @brief Generate a random short using the std::default_random_engine & uniform_int_distribution
     * @param min the minimum value
     * @param max the maximum value
     * @return a random short number
     */
    short generate(short min, short max)
    {
        std::default_random_engine gen(this->_random_device());
        std::uniform_int_distribution<short> uniform_dist(min, max);
        return uniform_dist(gen);
    }

    /**
     * @brief Generate a random int using the std::default_random_engine & uniform_int_distribution
     * @param min the minimum value
     * @param max the maximum value
     * @return a random int number
     */
    int generate(int min, int max)
    {
        std::default_random_engine gen(this->_random_device());
        std::uniform_int_distribution<int> uniform_dist(min, max);
        return uniform_dist(gen);
    }

    /**
     * @brief Generate a random long using the std::default_random_engine & uniform_int_distribution
     * @param min the minimum value
     * @param max the maximum value
     * @return a random long number
     */
    long generate(long min, long max)
    {
        std::default_random_engine gen(this->_random_device());
        std::uniform_int_distribution<long> uniform_dist(min, max);
        return uniform_dist(gen);
    }

    /**
     * @brief Generate a random std::size_t using the std::default_random_engine & uniform_int_distribution
     * @param min the minimum value
     * @param max the maximum value
     * @return a random std::size_t number
     */
    std::size_t generateSizeT(std::size_t min, std::size_t max)
    {
        std::default_random_engine gen(this->_random_device());
        std::uniform_int_distribution<std::size_t> uniform_dist(min, max);
        return uniform_dist(gen);
    }

    /**
     * @brief Generate a random double using the std::default_random_engine & uniform_real_distribution
     * @param min the minimum value
     * @param max the maximum value
     * @return a random double number
     */
    double generate(double min, double max)
    {
        std::default_random_engine gen(this->_random_device());
        std::uniform_real_distribution<double> uniform_dist(min, max);
        return uniform_dist(gen);
    }

    /**
     * @brief Generate a random float using the std::default_random_engine & uniform_real_distribution
     * @param min the minimum value
     * @param max the maximum value
     * @return a random float number
     */
    float generate(float min, float max)
    {
        std::default_random_engine gen(this->_random_device());
        std::uniform_real_distribution<float> uniform_dist(min, max);
        return uniform_dist(gen);
    }

private:
    std::random_device _random_device;
};

#endif //R_TYPE_RANDOM_HPP
