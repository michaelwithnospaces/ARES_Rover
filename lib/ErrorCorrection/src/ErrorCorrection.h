#ifndef errorcorrection_h
#define errorcorrection_h

class ErrorCorrection
{
    public:
        using chunk = unsigned long long;

        static chunk* encodeString(char* s, int len);
        static char* decodeData(chunk* data, int len);
        
    private:
        static chunk* fromString(char* s, int len);
        static char* toString(chunk* data, int originalLength);
        static chunk encode(chunk data);
        static chunk decode(chunk &encoded);

};

#endif