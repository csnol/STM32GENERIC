/*
  Copyright (c) 2014 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _RING_BUFFER_
#define _RING_BUFFER_

#ifdef __cplusplus

#include <stdint.h>

// Define constants and variables for buffering incoming serial data.  We're
// using a ring buffer (I think), in which head is the index of the location
// to which to write the next incoming character and tail is the index of the
// location from which to read.

#ifdef __arm__
#define RINGBUF_DEFAULTTYPE int
#else  /*for avr*/ 
#define RINGBUF_DEFAULTTYPE uint8_t
#endif

template<typename T = RINGBUF_DEFAULTTYPE>
class RingBuffer
{
//protected:
  public:
    RingBuffer(){}
	~RingBuffer(){
		this->deInit();
	}
    
	void init(uint8_t *buf, const unsigned int size){
      _aucBuffer = buf;
      _bufSize   = size;
      clear();
	}
	
	void init(const unsigned int size){
      _aucBuffer =(uint8_t *) malloc((size_t)size);
      _bufSize   = size;
	  _externBuf = true;
      clear();
	}
	
	void deInit(){
	  if(_externBuf) free((void*)_aucBuffer);
      _externBuf = false;	  
	}
	
    inline void clear() {
      _iHead = 0;
      _iTail = 0;
    }
	
    void push( uint8_t c ) {
      int i = nextIndex(_iHead);
      // if we should be storing the received character into the location
      // just before the tail (meaning that the head would advance to the
      // current location of the tail), we're about to overflow the buffer
      // and so we don't write the character or advance the head.
      if ( i != _iTail )
      {
        _aucBuffer[_iHead] = c ;
        _iHead = i ;
      }
    }
	inline void operator = (uint8_t c) {
       push(c);
    }

    int pop() {
      if (isEmpty()) return -1;
	  
      uint8_t value = _aucBuffer[_iTail];
      _iTail = nextIndex(_iTail);

      return value;
    }

    inline operator int () {
      return pop();
    }

    void backSpace() {   /* remove last date */
      if (isEmpty()) return;
      _iHead =(_iHead + _bufSize -1) % _bufSize;
    }

    int available() {
      int delta = _iHead - _iTail;
	  
      if (delta < 0)
        return _bufSize + delta;
      else
        return delta;
    }
	
    inline int availableForWrite(){
		return _bufSize - available();
	}
	
    inline int peek() {
      return (isEmpty()? -1:_aucBuffer[_iTail]);
    }
	
    inline int bufSize() {
      return _bufSize;
    }

    inline bool isFull() {
      return (nextIndex(_iHead) == _iTail);
    }
	
    inline bool isEmpty() {
      return (_iHead == _iTail);
    }

  private:
    volatile T 	_iHead,_iTail;
             T 	_bufSize;
             uint8_t *_aucBuffer;
	      bool 	_externBuf = false;
		  
    inline   T nextIndex(T index) {
      return (index + 1) % _bufSize;
    }
} ;

#endif // __cplusplus
#endif /* _RING_BUFFER_ */
