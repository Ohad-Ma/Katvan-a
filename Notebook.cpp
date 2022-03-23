#include "Notebook.hpp"

/**
 * @brief Source file of Notebook object. Basic first (just for tests)
 * 
 */
namespace ariel{
    void Notebook::write(int PAGE, int ROW, int COL, Direction dir, const std::string &st){}

    std::string Notebook::read(int PAGE, int ROW, int COL, Direction dir, int len){ return "";}

    void Notebook::erase(int PAGE, int ROW, int COL, Direction dir, int len){}

    void Notebook::show(int page){}

    Notebook::~Notebook(){}
}