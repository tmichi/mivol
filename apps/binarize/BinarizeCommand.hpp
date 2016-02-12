#ifndef BINARIZE_COMMAND_HPP
#define BINARIZE_COMMAND_HPP 1

#include <string>
#include <mi/CommandTemplate.hpp>
#include <mi/math.hpp>
template<typename T>
class BinarizeCommand : public mi::CommandTemplate
{
private:
        int _header_size;
        mi::Point3i _size;
        int _grain_size;

        std::string _input_file;
        std::string _output_file;
        T _threshold;
public:
        BinarizeCommand ( void ) ;
        ~BinarizeCommand ( void ) ;
        bool init ( const mi::Argument& arg ) ;
        bool run  ( void );
        bool term ( void );
};
#endif //BINARIZE_COMMAND_HPP

