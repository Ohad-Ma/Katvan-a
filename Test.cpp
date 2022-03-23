/**
 * AUTHORS: <Ohad Maday>
 * 
 * Date: 2022-03
 */

#include "doctest.h"
#include "Notebook.hpp"
#include <string>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
using namespace ariel;

string randomString(bool flag);
int integerGenerator(bool type);

const Direction HORI = Direction::Horizontal;
const Direction VERT = Direction::Vertical;


/**
 * @brief suppose to write:
 *    0 1 2 3 4 5 6 7 8 9 10
 * 0  c p p _ _ c u r s e _
 * 1  _ _ _ _ _ _ _ _ _ _ _
 * 2  _ o _ _ _ _ _ _ _ _ _
 * 3  _ h _ _ _ _ _ _ _ _ _
 * 4  _ a _ _ _ _ _ _ _ _ _
 * 5  _ d _ _ _ _ _ _ _ _ _
 * 6  _ _ _ _ _ _ _ _ _ _ _
 * 
 * After overwrite: (Should get error)
 *    0 1 2 3 4 5 6 7 8 9 10
 * 0  c p p _ _ c u r s e _
 * 1  _ _ _ _ _ _ _ _ _ _ _
 * 2  _ o _ _ _ _ _ _ _ _ _
 * 3  _ h _ _ _ _ _ _ _ _ _
 * 4  _ e _ _ _ _ _ _ _ _ _
 * 5  _ v _ _ _ _ _ _ _ _ _
 * 6  _ _ _ _ _ _ _ _ _ _ _
 * 
 */
TEST_CASE("Read horizontal & vertical"){
	Notebook notebook;
	notebook.write(0,0, 0, HORI, "cpp"); // Write the word "cpp" HORIZONTAL from (0,0)
	string word = notebook.read(0,0, 0, HORI, 4);
	string correct = "cpp_";
	for (size_t i = 0; i < 4; i++)
	{
		CHECK_EQ(word.at(i), correct.at(i));
	}
	notebook.write(0,0, 5, HORI, "curse_"); // Write the word "curse" HORIZONTAL from (0,5)
	word = notebook.read(0,0, 0, HORI, 10);
	correct = "cpp__curse_";
	for (size_t i = 0; i < 10; i++)
	{
		CHECK_EQ(word.at(i), correct.at(i));
	}

	notebook.write(0,2, 1, VERT, "ohad"); // Write the word "ohad" VERTICAL from (2,1)
	word = notebook.read(0,0, 1, VERT, 8);
	correct = "p_ohad_";
	for (size_t i = 0; i < 8; i++)
	{
		CHECK_EQ(word.at(i), correct.at(i));
	}

	// Check overwriting + bad char input AKA space
	CHECK_THROWS(notebook.write(0,4, 0, HORI, " e"));
	CHECK_THROWS(notebook.write(0,5, 0, HORI, " v"));
	word = notebook.read(0,2, 1, VERT, 4); // Supposed to read the word "ohev" VERTICALLY
	correct = "ohad";
	for (size_t i = 0; i < 4; i++)
	{
		CHECK_NE(word.at(i), correct.at(i));
	}
    
}

/**
 * @brief Many write() function cases
 * 
 */
TEST_CASE("write() cases"){
    srand(time(NULL));
    Notebook notebook;
    string big_random_word = randomString(true);
    int posNum = integerGenerator(true);
    int posNum2 = integerGenerator(true);
    int negNum = integerGenerator(false);
    string s = randomString(false); // generate string length of 50
    string many_underscores = ""; // Will hold many '_' chars 

    for (size_t i = 0; i < 100; i++)
    {
        many_underscores.push_back('_');
    }
    
    // Check that the string cannot contain more than 100 chars
    CHECK_THROWS(notebook.write(0,0,0,HORI,big_random_word)); // write big word at once
    CHECK_NOTHROW(notebook.write(0,0,0,HORI,s)); // Write random string length of 50
    notebook.write(0,0,50,HORI,"l"); // Add some char
    CHECK_THROWS(notebook.write(0,0,51,HORI,s)); // Write anoter random string length of 50 - line supposed to have 101 chars
    
    // Try to write on the same place twice
    notebook.write(1,0,5,HORI,s);
    CHECK_THROWS(notebook.write(1,0,5,HORI,s));
    

    while(posNum == 0 || posNum == 1){ // If posNum happen to be 0 or 1
        posNum = integerGenerator(true);
        if(posNum != 0 || posNum != 1 ){
            break;
        }
    } 

    // See what happens when I try to write 100 twice '_' chars (the default lines has '_' blocks) SHOULD NOT throw exception
    notebook.write(posNum,posNum2,posNum,HORI,many_underscores);
    CHECK_NOTHROW(notebook.write(posNum,posNum2,posNum,HORI,many_underscores));


    /**
     * @brief Check if can write bad chars such as space,\n ,\r, \0 etc...
     * 
     */
    CHECK_THROWS(notebook.write(posNum,posNum2,posNum,HORI," "));
    CHECK_THROWS(notebook.write(posNum,posNum2,posNum,HORI,"\t"));
    CHECK_THROWS(notebook.write(posNum,posNum2,posNum,HORI,"\n"));
    CHECK_THROWS(notebook.write(posNum,posNum2,posNum,HORI,"\0"));
    CHECK_THROWS(notebook.write(posNum,posNum2,posNum,HORI,"~"));
    CHECK_THROWS(notebook.write(posNum,posNum2,posNum,HORI,"\r"));

    CHECK_THROWS(notebook.write(posNum,posNum2,posNum,VERT," "));
    CHECK_THROWS(notebook.write(posNum,posNum2,posNum,VERT,"\t"));
    CHECK_THROWS(notebook.write(posNum,posNum2,posNum,VERT,"\n"));
    CHECK_THROWS(notebook.write(posNum,posNum2,posNum,VERT,"\0"));
    CHECK_THROWS(notebook.write(posNum,posNum2,posNum,VERT,"~"));
    CHECK_THROWS(notebook.write(posNum,posNum2,posNum,VERT,"\r"));

    


    CHECK_THROWS(notebook.write(negNum,posNum2,posNum,VERT,s)); // Try to write VERTICALLY at negative page
    CHECK_THROWS(notebook.write(negNum,posNum2,posNum,HORI,s)); // Try to write HORIZONTAL at negative page

    CHECK_THROWS(notebook.write(posNum,negNum,posNum2,VERT,s)); // Try to write VERTICALLY random word in negative row
    CHECK_THROWS(notebook.write(posNum,negNum,posNum,HORI,s)); // Try to write HORIZONTAL random word in negative row

    CHECK_THROWS(notebook.write(posNum,posNum2,negNum,VERT,s)); // Try to write VERTICALLY random word in negative col
    CHECK_THROWS(notebook.write(posNum,posNum2,negNum,HORI,s)); // Try to write HORIZONTAL random word in negative col

    CHECK_THROWS(notebook.write(negNum,negNum,posNum2,VERT,s)); // Try to write VERTICALLY at negative page, negative row
    
    CHECK_THROWS(notebook.write(negNum,posNum,negNum,VERT,s)); // Try to write VERTICALLY at negative page, negative col

    CHECK_THROWS(notebook.write(posNum,negNum,negNum,VERT,s)); // Try to write VERTICALLY at negative row & col

    CHECK_THROWS(notebook.write(negNum,negNum,negNum,VERT,s)); // Try to write VERTICALLY at negative page, negative row, negative col

    CHECK_THROWS(notebook.write(negNum,negNum,posNum,HORI,s)); // Try to write HORIZONTAL at negative page, negative row

    CHECK_THROWS(notebook.write(negNum,posNum,negNum,HORI,s)); // Try to write HORIZONTAL at negative page, negative col

    CHECK_THROWS(notebook.write(posNum,negNum,negNum,HORI,s)); // Try to write HORIZONTAL at negative row & col
    
    CHECK_THROWS(notebook.write(negNum,negNum,negNum,HORI,s)); // Try to write HORIZONTAL at negative page, negative 
}

/**
 * @brief Test many possibilities on erase() function
 * 
 */
TEST_CASE("erase() cases"){
    srand(time(NULL));
    Notebook notebook;
    int posNum = integerGenerator(true);
    int posNum2 = integerGenerator(true);
    int negNum = integerGenerator(false);
    string s = randomString(false); // generate random string length of 50

    notebook.write(1,0,3,HORI,s);
    CHECK_NOTHROW(notebook.erase(1,0,3,HORI,20));
    CHECK_THROWS(notebook.write(1,0,3,HORI,s)); // Should not be able to write after erasing


    notebook.erase(0,0,0,HORI,4);
    CHECK_NOTHROW(notebook.erase(0,0,0,HORI,4)); // Can erase twice HORIZONTAL

    notebook.erase(0,0,0,VERT,4);
    CHECK_NOTHROW(notebook.erase(0,0,0,VERT,4)); // Can erase twice VERTICALLY


    CHECK_THROWS(notebook.erase(posNum,posNum,posNum2,HORI,negNum)); // Erase HORIZONTAL negative length
    CHECK_THROWS(notebook.erase(posNum,posNum,posNum2,VERT,negNum)); // Erase VERTICALLY negative length

    CHECK_THROWS(notebook.erase(negNum,posNum2,posNum,HORI,posNum)); // Erase negative page
    CHECK_THROWS(notebook.erase(negNum,posNum2,posNum,VERT,posNum)); // Erase negative page

    CHECK_THROWS(notebook.erase(posNum,negNum,posNum2,HORI,posNum)); // Erase negative row
    CHECK_THROWS(notebook.erase(posNum,negNum,posNum2,VERT,posNum)); // Erase negative row

    CHECK_THROWS(notebook.erase(posNum,posNum2,negNum,HORI,posNum)); // Erase negative col
    CHECK_THROWS(notebook.erase(posNum,posNum2,negNum,VERT,posNum)); // Erase negative col

    CHECK_THROWS(notebook.erase(negNum,negNum,posNum2,HORI,posNum2)); // Erase negative page & row
    CHECK_THROWS(notebook.erase(negNum,negNum,posNum2,VERT,posNum2)); // Erase negative page & row

    CHECK_THROWS(notebook.erase(posNum,negNum,negNum,HORI,posNum)); // Erase negative col & row
    CHECK_THROWS(notebook.erase(posNum,negNum,negNum,VERT,posNum)); // Erase negative col & row

    CHECK_THROWS(notebook.erase(negNum,negNum,negNum,HORI,posNum)); // Erase negative page, row, col
    CHECK_THROWS(notebook.erase(negNum,negNum,negNum,VERT,posNum)); // Erase negative page, row, col
    
    CHECK_THROWS(notebook.erase(posNum,posNum2,negNum,HORI,negNum)); // Erase negative page, col
    CHECK_THROWS(notebook.erase(posNum,posNum2,negNum,VERT,negNum)); // Erase negative page, col
    
    CHECK_THROWS(notebook.erase(posNum,negNum,posNum,HORI,negNum)); // Erase negative page, row
    CHECK_THROWS(notebook.erase(posNum,negNum,posNum,VERT,negNum)); // Erase negative page, row

    CHECK_THROWS(notebook.erase(negNum,posNum,posNum,HORI,negNum)); // Erase negative page, length
    CHECK_THROWS(notebook.erase(negNum,posNum,posNum,VERT,negNum)); // Erase negative page, length
    
    CHECK_THROWS(notebook.erase(negNum,negNum,negNum,HORI,negNum)); // Erase negative page, row, col, length
    CHECK_THROWS(notebook.erase(negNum,negNum,negNum,VERT,negNum)); // Erase negative page, row, col, length

}

/**
 * @brief Test many read() function cases
 * 
 */
TEST_CASE("read() cases"){
    srand(time(NULL));
    Notebook notebook;
    int posNum = integerGenerator(true);
    int posNum2 = integerGenerator(true);
    int negNum = integerGenerator(false);
    string s = randomString(false); // generate string length of 50

    CHECK_THROWS(notebook.read(posNum,posNum,posNum,HORI,negNum)); // Write HORIZONTAL negative length
    CHECK_THROWS(notebook.read(posNum,posNum,posNum,VERT,negNum)); // Write VERTICALLY negative length

    CHECK_THROWS(notebook.read(negNum,posNum,posNum,HORI,posNum)); // Write negative page
    CHECK_THROWS(notebook.read(negNum,posNum,posNum,VERT,posNum)); // Write negative page

    CHECK_THROWS(notebook.read(posNum2,negNum,posNum,HORI,posNum)); // Write negative row
    CHECK_THROWS(notebook.read(posNum2,negNum,posNum,VERT,posNum)); // Write negative row

    CHECK_THROWS(notebook.read(posNum,posNum2,negNum,HORI,posNum)); // Write negative col
    CHECK_THROWS(notebook.read(posNum,posNum2,negNum,VERT,posNum)); // Write negative col

    CHECK_THROWS(notebook.read(negNum,negNum,posNum,HORI,posNum)); // Write negative page & row
    CHECK_THROWS(notebook.read(negNum,negNum,posNum,VERT,posNum)); // Write negative page & row

    CHECK_THROWS(notebook.read(posNum,negNum,negNum,HORI,posNum)); // Write negative col & row
    CHECK_THROWS(notebook.read(posNum,negNum,negNum,VERT,posNum)); // Write negative col & row

    CHECK_THROWS(notebook.read(negNum,negNum,negNum,HORI,posNum)); // Write negative page, row, col
    CHECK_THROWS(notebook.read(negNum,negNum,negNum,VERT,posNum)); // Write negative page, row, col
    
    CHECK_THROWS(notebook.read(posNum,posNum,negNum,HORI,negNum)); // Write negative page, col
    CHECK_THROWS(notebook.read(posNum,posNum,negNum,VERT,negNum)); // Write negative page, col
    
    CHECK_THROWS(notebook.read(posNum,negNum,posNum2,HORI,negNum)); // Write negative page, row
    CHECK_THROWS(notebook.read(posNum,negNum,posNum2,VERT,negNum)); // Write negative page, row

    CHECK_THROWS(notebook.read(negNum,posNum2,posNum,HORI,negNum)); // Write negative page, length
    CHECK_THROWS(notebook.read(negNum,posNum2,posNum,VERT,negNum)); // Write negative page, length
    
    CHECK_THROWS(notebook.read(negNum,negNum,negNum,HORI,negNum)); // Write negative page, row, col, length
    CHECK_THROWS(notebook.read(negNum,negNum,negNum,VERT,negNum)); // Write negative page, row, col, length
        
}

/**
 * @brief Not many cases to check here, just if the integer in argument is negative
 * 
 */
TEST_CASE("show() cases"){
    srand(time(NULL));
    Notebook notebook;
    int negNum = integerGenerator(false);
    CHECK_THROWS(notebook.show(negNum)); // Supposed to throw exception when negative page tried to be shown shown

}

/**
 * @brief generates a random sized string length of 100 or 50
 * @param flag :
 *               true  - generate string length of 100
 *              ,false - generates a string length of 50
 * @return string 
 */
string randomString(bool flag)
{
    int len = 50;
    string s = "";
    if (flag){ // Specific for str length bigger than 100
        len = 101;
    }
    for (size_t i = 0; i < len; i++)
    {
        s += (char)(65+ ( rand() % 57) );

    }
    return s;

}

/**
 * @brief generates random number between 0 and 25 so it won't take the test a long running time and pass the TIMEOUT in 'grade' file
 * @param type :
 *               true - positive integer
 *              ,false - negative integer
 * @return int
 */
int integerGenerator(bool type){
    int num = (int) rand()%(25+1-0)+0;
    return type ? num : -num;
}
