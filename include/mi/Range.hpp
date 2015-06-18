/**
 * @file Range.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 *
 */
#ifndef MI_RANGE_HPP
#define MI_RANGE_HPP 1
#include "math.hpp"
#include <iterator>
namespace mi
{
        class Range
        {
        public:
                class iterator// :  public std::iterator<std::input_iterator_tag, Point3i>
                {
                public:
			iterator ( void );
                        iterator ( const iterator& that );
                        iterator& operator = ( const iterator& that );
                        virtual ~iterator ( void );
			iterator&  init ( Range* range, const bool isBeginning = true );
                        iterator& operator ++ ( void );
                        iterator  operator ++ ( int  );
                        bool      operator == ( const iterator& rhs );
                        bool      operator != ( const iterator& rhs );
                        iterator  operator +  ( const int n );
                        iterator& operator += ( const int n );
                        Point3i&  operator *  ( void );
                private:
			class Impl;
			Impl *_impl;
                };//iterator
        public:
                explicit Range ( const Point3i& bmin, const Point3i& bmax );
                explicit Range ( const Range& that );
                ~Range ( void );
                Range& operator = ( const Range& that );
                bool isValid ( const Point3i& p ) const;
                Point3i getMin( void ) const;
		Point3i getMax( void ) const;

		Range::iterator begin( void );
		Range::iterator end( void );
        private:
		class Impl;
		Impl* _impl;
        };
}
#endif //MI_RANGE_HPP
