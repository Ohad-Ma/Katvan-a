#pragma once
#include "Direction.hpp"
#include <string>
/**
 * @brief Header file of Notebook class 
 * 
 */
namespace ariel{
    class Notebook{
        /**
         * @brief Much more to be added such as constructors and etc.. Just for first task which focus on Test cases
         * 
         */
        public:

        void write(int PAGE, int ROW, int COL, Direction dir, const std::string &st);

        static std::string read(int PAGE, int ROW, int COL, Direction dir, int len);

        void erase(int PAGE, int ROW, int COL, Direction dir, int len);

        void show(int page);

        ~Notebook();

    };
}