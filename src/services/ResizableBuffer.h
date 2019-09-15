#ifndef RESIZABLE_BUFFER_H_INCLUDED
#define RESIZABLE_BUFFER_H_INCLUDED

#include <iostream>
#include <cstdlib>
using namespace std;

class ResizableBuffer{
private:
    char* _pBuffer;
    unsigned int _bufferSize;
    unsigned int _bufferSizeUsed;

public:
    ResizableBuffer(){
        _pBuffer = nullptr;
        _bufferSize = _bufferSizeUsed = 0;
    }

    ResizableBuffer(unsigned int initBufferSize){
        _pBuffer =  (char*)malloc(initBufferSize);
        _bufferSize = initBufferSize;
        _bufferSizeUsed = 0;
    }

    virtual ~ResizableBuffer(){
        if(_pBuffer)
            free(_pBuffer);
        _pBuffer = nullptr;
        _bufferSize = _bufferSizeUsed = 0;
    }

    const char* GetBuffer() const{ return _pBuffer; }

    unsigned int GetBufferUsedSize() const{ return _bufferSizeUsed; }

    void Add(const char* pString, unsigned int size){
        if((_bufferSize - _bufferSizeUsed) < size){
            auto bufferSize = (_bufferSize <= 0 ? 1024 : 2*_bufferSize);
            _pBuffer = (char*)realloc(_pBuffer, bufferSize);
            _bufferSize = bufferSize;
        }

        memcpy(&_pBuffer[_bufferSizeUsed], pString, size);
        _bufferSizeUsed += size;
    }

    bool PeekBuffer(int offset){
        if(((int)_bufferSizeUsed) + offset < 0){
            return false;
        }
        _bufferSizeUsed += offset;
        return true;
    }
};

#endif // RESIZABLE_BUFFER_H_INCLUDED