
#include <stdexcept>

using namespace std;

class socket_error : exception
{
public:
    socket_error(const string& strMessage)
        :_errStr("Windows Socket ´íÎó : ")
    {
        _errStr += strMessage;
    }

    virtual ~socket_error(){}

    virtual const char* what() const
    {
        return _errStr.c_str();
    }

private:
    string _errStr;
};

